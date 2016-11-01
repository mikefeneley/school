#include "job-manager.h"


/* Gets information about type of job and
 * uses that information to correctly execute
 * the job 
 */
bool 
launch_job(struct esh_pipeline *job)
{
	if(is_built_in_cmd(job)) {
		launch_built_in_cmd(job);
	} else 
	{
		int num_cmd = get_num_cmd(job);	
		if(num_cmd == 1)
		{
			launch_single_job(job);

			if(is_fg_cmd(job)) {

				job->jid = job_id++;
				add_job(p_jobs_list, job);
				add_to_fg(job, p_state_manager);
			}
			else {
				job->status = BACKGROUND;	
				job->jid = job_id++;
				add_job(p_jobs_list, job);
				print_bg_message(job);			
			}
		}
		if(num_cmd > 1)
		{
			launch_pipe_job(job);

			if(is_fg_cmd(job)) {
				job->jid = job_id++;
				add_job(p_jobs_list, job);
				add_to_fg(job, p_state_manager);
			} else {
				job->status = BACKGROUND;	
				job->jid = job_id++;
				add_job(p_jobs_list, job);
				print_bg_message(job);			
			}
		}
	}

	return true;

}

/* Updates fd and executes a single job */
bool 
launch_single_job(struct esh_pipeline * job)
{
	struct esh_command * cmd = get_first_cmd(job);

	pid_t pid = fork();

	if(is_child(pid)) {
		unblock_signals();
		update_pgrp(job, pid);
		update_pid(cmd, pid);
		redirect_input(cmd);
		redirect_output(cmd);
		if(plugins_loaded) 
		{
			int processReturn = process_plugin(cmd);
			if (processReturn == -1)
			{
				execvp(cmd->argv[0], cmd->argv);
			}
			
		} else 
		{
			execvp(cmd->argv[0], cmd->argv);
		}
		exit(0);
	}
	if(is_parent(pid))
	{
		update_pgrp(job, pid);
		update_pid(cmd, pid);
	}

	return true;
}
/* Sets up pipe for all job commands */
bool 
launch_pipe_job(struct esh_pipeline * job)
{
	esh_signal_block(SIGCHLD);
	pid_t pgrp;

	int fd[2];
	int read_fd = 0;
	int write_fd = 1;

	check_pipe_error(pipe(fd));
	write_fd = fd[1];

	launch_first_cmd(fd[0], write_fd, job);

	pgrp = job->pgrp;
	check_close_error(close(fd[1]));
	read_fd = fd[0];

	int i = 1;
	int num_cmd = get_num_cmd(job);

	struct list_elem * e = list_begin (&job->commands);
	e = list_next(e);


	while(i < num_cmd -1)
	{
		check_pipe_error(pipe(fd));

		struct esh_command *cmd = list_entry(e, struct esh_command, elem);
		launch_interior_cmd(read_fd, fd[1], pgrp, cmd);

		check_close_error(close(fd[1]));
		check_close_error(close(read_fd));
		read_fd = fd[0];
		e = list_next(e);
		i++;
	}

	struct esh_command *last_cmd = list_entry(e, struct esh_command, elem);


	launch_last_cmd(read_fd, 1, pgrp, last_cmd);
	return true;
}

/* Calls first command in the pipeling */
bool 
launch_first_cmd(int read_fd, int write_fd, struct esh_pipeline * job)
{
	struct esh_command * first_cmd = get_first_cmd(job);

	pid_t pid = fork();
	check_fork_error(pid);
	if(pid == 0) {
		check_close_error(close(read_fd));
		update_fd(STDIN_FILENO, write_fd);
		redirect_input(first_cmd);
		update_pgrp(job, pid);
		update_pid(first_cmd, pid);
		unblock_signals();
		if (plugins_loaded) {
			int processReturn = process_plugin(first_cmd);
			printf("Plugin found and returned: %d\n", processReturn);
                } else {
                        if(execvp(first_cmd->argv[0], first_cmd->argv) < 0) {
				perror("execvp error: command not found");
			}
		}
		exit(0);
	}
	
	update_pgrp(job, pid);
	update_pid(first_cmd, pid);

	return true;
}

/* Calls an interior command of the pipeline */
bool 
launch_interior_cmd(int read_fd, int write_fd, pid_t pgrp, struct esh_command * cmd)
{
	pid_t pid = fork();
	check_fork_error(pid);
	if(is_child(pid)) {
		update_fd(read_fd, write_fd);
		set_pgrp(pgrp);
		update_pid(cmd, pid);
		unblock_signals();
		if(plugins_loaded) {
			int processReturn = process_plugin(cmd);
			printf("Plugin found and returned: %d\n", processReturn);
		} else {
			if(execvp(cmd->argv[0], cmd->argv) < 0)	{
				perror("execvp error command not found");
			};
		}
		exit(0);
	}

	update_pid(cmd, pid);


	return true;
}


/* Calls the last command of the pipeline */
bool 
launch_last_cmd(int read_fd, int write_fd, pid_t pgrp, struct esh_command * cmd)
{
	pid_t pid = fork();

	if(pid < 0) {
		perror("Fork error");
		exit(EXIT_FAILURE);
	}

	if(is_child(pid)) {
		update_fd(read_fd, write_fd);
		redirect_output(cmd);
		set_pgrp(pgrp);
		update_pid(cmd, pid);
		unblock_signals();
		if(plugins_loaded) {
			int processReturn = process_plugin(cmd);
                        printf("Plugin found and returned: %d\n", processReturn);
		} else {
			if(execvp(cmd->argv[0], cmd->argv) < 0) {
				perror("execvp error: command not found");
			}

		}
		exit(0);
	}
	check_close_error(close(read_fd));
	update_pid(cmd, pid);

	return true;
}

/* Executes a built in shell command */
bool 
launch_built_in_cmd(struct esh_pipeline * job)
{
	struct esh_command * cmd = get_first_cmd(job);
	char *cmd_name = cmd->argv[0];

	if(strcmp(cmd_name, "jobs") == 0) {
		print_jobs(p_jobs_list);
		return true;
	} else if (strcmp(cmd_name, "fg") == 0) {
		fg(job);
		return true;
	} else if (strcmp(cmd_name, "bg") == 0) {
		bg(job);
		return true;
	} else if (strcmp(cmd_name, "kill") == 0) {
		kill_job(job);
		return true;
	} else if (strcmp(cmd_name, "stop") == 0) {
		stop(job);
		return true;
	} else if (strcmp(cmd_name, "exit") == 0) {
		printf("exit\n");
		exit(0);
	} else {
		return false;
	}
}

/* Brings a job to the foreground */
bool 
fg(struct esh_pipeline * job)
{
	struct esh_command * cmd = get_first_cmd(job);

	if(cmd->argv[1] != NULL) {/* HAD PID */
	
		pid_t jid = strtol(cmd->argv[1], (char **)NULL, 10);
		struct esh_pipeline * old_job = get_job_jid(jid);	
		print_fg_message(&(old_job->commands));
		
		if(old_job->status == BACKGROUND) {
			add_to_fg(old_job, p_state_manager);
		} else {
			add_to_fg(old_job, &(old_job->saved_tty_state));
		}
		return true;
	} else 	{
		struct esh_pipeline * old_job = get_last_job();
		print_fg_message(&(old_job->commands));
		
		if(old_job->status == BACKGROUND) {
			add_to_fg(old_job, p_state_manager);
		} else {
			add_to_fg(old_job, &(old_job->saved_tty_state));
		}
	}
	return true;
}

/* Bring a stopped job to the background */
bool 
bg(struct esh_pipeline * job)
{
	struct esh_command * cmd = get_first_cmd(job);
	struct esh_pipeline * old_job;
	if(cmd->argv[1] != NULL) {

		pid_t jid = strtol(cmd->argv[1], (char **)NULL, 10);
		old_job = get_job_jid(jid);

		if(old_job->status == BACKGROUND) {
			esh_sys_tty_restore(p_state_manager);
		} else {
			esh_sys_tty_restore(&(old_job->saved_tty_state));
		}
	} else {


		old_job = get_last_stopped_job();

		if(old_job->status == BACKGROUND) {
			esh_sys_tty_restore(p_state_manager);
		} else {
			esh_sys_tty_restore(&(old_job->saved_tty_state));
		}

	}
	old_job->status = BACKGROUND;
	send_to_all(&(old_job->commands), SIGCONT);
	return true;
}

/* Stops the execution of a job */
bool 
stop(struct esh_pipeline * job)
{
	struct esh_command * cmd = get_first_cmd(job);
	pid_t jid = strtol(cmd->argv[1], (char **)NULL, 10);
	struct esh_pipeline * old_job = get_job_jid(jid);	
	old_job->status = STOPPED;
	send_to_all(&(old_job->commands), SIGTSTP);
	return true;
}

/* Terminate the execution of a job */
bool 
kill_job(struct esh_pipeline * job)
{
	struct esh_command * cmd = get_first_cmd(job);
	pid_t jid = strtol(cmd->argv[1], (char **)NULL, 10);
	struct esh_pipeline * old_job = get_job_jid(jid);
	send_to_all(&(old_job->commands), SIGTERM);

	return true;
}
