#include "helper.h"

/* Returns number of jobs input to the command line */
int
get_num_jobs(struct esh_command_line * cline)
{
	return list_size(&cline->pipes);
}

/* Returns the number of commands in a job */
int get_num_cmd(struct esh_pipeline * job)
{
	return list_size(&job->commands);
}

/* Checks if the command is a built in command */
bool is_built_in_cmd(struct esh_pipeline * job)
{
	struct esh_command * cmd = get_first_cmd(job);
	char *cmd_name = cmd->argv[0];

	if(strcmp(cmd_name, "jobs") == 0) {
		return true;
	} else if (strcmp(cmd_name, "fg") == 0) {
		return true;
	} else if (strcmp(cmd_name, "bg") == 0) {
		return true;
	} else if (strcmp(cmd_name, "kill") == 0) {
		return true;
	} else if (strcmp(cmd_name, "stop") == 0) {
		return true;
	} else if (strcmp(cmd_name, "exit") == 0) {
		return true;
	} else {
		return false;
	}
}

/* Checks if the job is meant to run in the foreground */
bool is_fg_cmd(struct esh_pipeline * job)
{
	if(job->bg_job == false) {
		return true;
	} else {
		return false;
	}
}

/* Checks if the job is meant to run in the background */
bool is_bg_cmd(struct esh_pipeline * job)
{
	if(job->bg_job == true) {
		return true;
	} else {
		return false;
	}
}

/* Returns the foreground job in the jobs list if it exists */
struct esh_pipeline * get_fg_job(void)
{
	struct list_elem * e = list_begin(p_jobs_list);
	int i = 0;
	int num_jobs = list_size(p_jobs_list);

	while(i < num_jobs) {
		struct esh_pipeline * job = list_entry(e, struct esh_pipeline, elem);

		if(job->status == FOREGROUND) {
			return job;
		}

		i++;
		e = list_next(e);
	}

	return NULL;	
}


/* Returns a job that has the specified pid as a child process */
struct esh_pipeline * get_job(pid_t child)
{

	struct list_elem * e = list_begin(p_jobs_list);
	int i = 0;
	int num_jobs = list_size(p_jobs_list);
	
	while(i < num_jobs) {
		struct esh_pipeline * job = list_entry(e, struct esh_pipeline, elem);

		struct list_elem * c = list_begin(&(job->commands));

		int j = 0;
		int num_cmd = list_size(&(job->commands));
		while(j < num_cmd) {

			struct esh_command * cmd = list_entry(c, struct esh_command, elem);
			if(child == cmd->pid) {
				return job;
			}
			j++;
			c = list_next(c);
		}

		e = list_next(e);
		i++;
	}
	return NULL;	
}

/* Returns the job with the corresponding jid */
struct esh_pipeline *get_job_jid(int jid)
{

	struct list_elem * e = list_begin(p_jobs_list);
	int i = 0;
	int num_jobs = list_size(p_jobs_list);
	
	while(i < num_jobs) {
		
		struct esh_pipeline * job = list_entry(e, struct esh_pipeline, elem);
		if(job->jid == jid) {
			return job;
		}

		e = list_next(e);
		i++;
	}
	return NULL;	
}

/* Returns the command with the corresponding pid */
struct esh_command * get_cmd(struct esh_pipeline * job, pid_t child)
{
		struct list_elem * e = list_begin(&(job->commands));

		int i = 0;
		int num_cmd = list_size(&(job->commands));
		while(i < num_cmd) {
			struct esh_command * cmd = list_entry(e, struct esh_command, elem);
			if(child == cmd->pid) {
				return cmd;
			}
			i++;
			e = list_next(e);
		}	
	return NULL;
}

/* Returns the first command in the command list */
struct esh_command * get_first_cmd(struct esh_pipeline * job)
{
	struct list_elem * e = list_begin (&job->commands); 
	struct esh_command *first_cmd = list_entry(e, struct esh_command, elem);
	return first_cmd;
}


/* Gets the next job in the pipeline */
struct esh_pipeline * get_next_job(struct esh_command_line * cline)
{
	struct list_elem * e = list_pop_front(&cline->pipes);
	struct esh_pipeline * job;
	job = list_entry(e, struct esh_pipeline, elem);
	return job;	
}

/* Returns the last job in the jobs list */
struct esh_pipeline * get_last_job(void)
{
	if(list_empty(p_jobs_list)) {
		return NULL;
	}

	struct list_elem * e = list_back(p_jobs_list);
	struct esh_pipeline * job = list_entry(e, struct esh_pipeline, elem);

	return job;

}	

/* Returns the last stopped job in the jobs list */
struct esh_pipeline * get_last_stopped_job(void)
{
	if(list_empty(p_jobs_list)) {
		return NULL;
	}

	struct list_elem * e = list_back(p_jobs_list);
		
	int num_jobs = list_size(p_jobs_list);
	int i = 0;

	while(i < num_jobs) {

		struct esh_pipeline * job = list_entry(e, struct esh_pipeline, elem);
		if(job->status == STOPPED) {
			return job;
		}
		i++;
		e = list_next(e);
	}
		


	return NULL;
}

/* Adds a job to the jobs list */
bool add_job(struct list * jobs_list, struct esh_pipeline * job)
{
	esh_signal_block(SIGCHLD);
	list_push_back(jobs_list, &job->elem);
	esh_signal_unblock(SIGCHLD);
	return true;
}

/* Removes a job from the jobs list */
bool remove_job(struct esh_pipeline * job)
{
	list_remove(&(job->elem));
	return true;
}

/* Prints information about all the jobs in the jobs list */
bool print_jobs(struct list * jobs_list)
{

	struct list_elem * e = list_begin(jobs_list);

	int i = 0;
	int num_jobs = list_size(jobs_list);
	
	while(i < num_jobs) {

		struct esh_pipeline * job = list_entry(e, struct esh_pipeline, elem);
		printf("[%d]+ %s\t\t", job->jid, get_status(job->status));
		print_commands(&(job->commands));
		e = list_next(e);
		i++;
	}

	return true;
}

/* Prints information about a single job */
bool print_job(struct esh_pipeline *job)
{
	printf("\n[%d]+ %s\t", job->jid, get_status(job->status));
	print_commands(&(job->commands));
	return true;
}

/* Sends the specified signal to all the children of a job */
bool send_to_all(struct list * command_list, int sig)
{
	struct list_elem * e = list_begin(command_list);
	int i = 0;
	int num_cmd = list_size(command_list);
	while(i < num_cmd) {
		struct esh_command * cmd = list_entry(e, struct esh_command, elem);
		pid_t pid = cmd->pid;
		if(kill(pid, sig) < 0) {
			perror("Kill signal failed");
		}		
		e = list_next(e);
		i++;	 
	}
	return true;
}

/* Prints information about all the commands of in the command list */
bool print_commands(struct list * command_list)
{
	struct list_elem * e = list_begin(command_list);
	printf("(");
	int i = 0;
	int num_cmd = list_size(command_list);
	while(i < num_cmd) {
		struct esh_command * cmd = list_entry(e, struct esh_command, elem);
		char **p = cmd->argv;
	
		if(e != list_begin(command_list)) {
			printf(" | ");
		}

		while (*p) {
       			printf("%s", *p++);
			if(*p){
				printf(" ");
			}
		}	
		
		e = list_next(e);
		i++;	 
	}
	printf(")\n");		
	
	return true;
}

/* Prints a message when a job is added to the foreground */
bool print_fg_message(struct list * command_list)
{
	struct list_elem * e = list_begin(command_list);
	int i = 0;
	int num_cmd = list_size(command_list);
	while(i < num_cmd) {
		struct esh_command * cmd = list_entry(e, struct esh_command, elem);
		char **p = cmd->argv;
	
		if(e != list_begin(command_list)) {
			printf("|");
		}

		while (*p) {
       			printf("%s", *p++);
			if(*p){
				printf(" ");
			}
		}	
		
		e = list_next(e);
		i++;	 
	}
	printf("\n");	
	return true;
}

/* Prints a message when a job is added to the background */
bool print_bg_message(struct esh_pipeline * job)
{
	printf("[%d] %d\r\n", job->jid, job->pgrp);
	return true;
}

/* Converts job status to required output */
char * get_status(int status)
{
	switch(status) {
		case 0:
		return "Running";
		case 1:
		return "Running";
		case 2:
		return "Stopped";
		case 3:
		return "Stopped";
		default:
		return NULL;		
	}
}

/* Redirect the input of a command */
bool redirect_input(struct esh_command * cmd)
{		
	mode_t mode = S_IRUSR | S_IWUSR | S_IWGRP | S_IROTH;		
	int read_fd;
	if(cmd->iored_input != NULL ) {
			
		if((read_fd = open(cmd->iored_input, O_RDONLY, mode)) < 0) {
			perror("open error");
			exit(-1);
		}

		if(dup2(read_fd, STDIN_FILENO) < 0) {
			perror("dup2 error");
			exit(-1);
		}

		check_close_error(close(read_fd));
	}


		return true;		
}

/* Redirect the output of a command */
bool redirect_output(struct esh_command * cmd)
{		
	int write_fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IWGRP | S_IROTH;	

	if(cmd->iored_output != NULL) {

		if(cmd->append_to_output) {
			write_fd = open(cmd->iored_output, O_WRONLY | O_APPEND | O_CREAT, mode);
			check_open_error(write_fd);		
		}
		else {
			write_fd = open(cmd->iored_output, O_WRONLY | O_TRUNC | O_CREAT, mode);
			check_open_error(write_fd);		
		}

		if(dup2(write_fd, STDOUT_FILENO) < 0) {
			perror("dup2 error");
			exit(-1);
		}

		check_close_error(close(write_fd));
	}	



	return true;
}

/* Updates the process group of a job */
bool update_pgrp(struct esh_pipeline * job, pid_t pid)
{

	if(is_child(pid)) {
		pid = getpid();
	}

	job->pgrp = pid;
	check_setpgid_error(setpgid (pid, job->pgrp));
	return true;
}


/* Sets the process group of a job */
bool set_pgrp(pid_t pgrp)
{
	if(setpgid(getpid(), pgrp) < 0) {
		perror("setpgid error");
	}
	return true;
}

/* Updates the pid of a process */
bool update_pid(struct esh_command * cmd, pid_t pid)
{
	if(is_child(pid)) {
		cmd->pid = getpid();
	}
	if(is_parent(pid)) {
		cmd->pid = pid;
	}	
	return true;
}

/* Updates the file descriptors of a command for piping */
bool update_fd(int read_fd, int write_fd)
{
	if(read_fd != 0) {
		check_dup2_error(dup2(read_fd, STDIN_FILENO));
		check_close_error(close(read_fd));
	}
		
	if(write_fd != 1) {
		check_dup2_error(dup2(write_fd, STDOUT_FILENO));
		check_close_error(close(write_fd));
	}

	return true;
}



bool is_child(int pid)
{
	return (pid == 0); 
}
bool is_parent(int pid)
{
	return (pid > 0);
}

/* Adds a job to the foreground */
bool add_to_fg(struct esh_pipeline * job, struct termios *pg_tty_state)
{
	job->status = FOREGROUND;
	give_terminal_to(job->pgrp, pg_tty_state);
	check_kill_error(kill(job->pgrp, SIGCONT));
	wait_for_job(job);
	give_terminal_to(shell_pgid, p_state_manager);
	return true;
}



/**
 * Assign ownership of ther terminal to process group
 * pgrp, restoring its terminal state if provided.
 *
 * Before printing a new prompt, the shell should
 * invoke this function with its own process group
 * id (obtained on startup via getpgrp()) and a
 * sane terminal state (obtained on startup via
 * esh_sys_tty_init()).
 */
void
give_terminal_to(pid_t pgrp, struct termios *pg_tty_state)
{
    esh_signal_block(SIGTTOU);
    int rc = tcsetpgrp(esh_sys_tty_getfd(), pgrp);
    if (rc == -1)
        esh_sys_fatal_error("tcsetpgrp: ");

    if (pg_tty_state)
        esh_sys_tty_restore(pg_tty_state);
    esh_signal_unblock(SIGTTOU);
}

/*
 * SIGCHLD handler.
 * Call waitpid() to learn about any child processes that
 * have exited or changed status (been stopped, needed the
 * terminal, etc.)
 * Just record the information by updating the job list
 * data structures.  Since the call may be spurious (e.g.
 * an already pending SIGCHLD is delivered even though
 * a foreground process was already reaped), ignore when
 * waitpid returns -1.
 * Use a loop with WNOHANG since only a single SIGCHLD 
 * signal may be delivered for multiple children that have 
 * exited.
 */
void
sigchld_handler(int sig, siginfo_t *info, void *_ctxt)
{
    pid_t child;
    int status;

    assert(sig == SIGCHLD);


    while ((child = waitpid(-1, &status, WUNTRACED|WNOHANG)) > 0) {
        child_status_change(child, status);
    }
}


/* Wait for all processes in this pipeline to complete, or for
 * the pipeline's process group to no longer be the foreground 
 * process group. 
 * You should call this function from a) where you wait for
 * jobs started without the &; and b) where you implement the
 * 'fg' command.
 * 
 * Implement child_status_change such that it records the 
 * information obtained from waitpid() for pid 'child.'
 * If a child has exited or terminated (but not stopped!)
 * it should be removed from the list of commands of its
 * pipeline data structure so that an empty list is obtained
 * if all processes that are part of a pipeline have 
 * terminated.  If you use a different approach to keep
 * track of commands, adjust the code accordingly.
 */ 
void
wait_for_job(struct esh_pipeline *pipeline)
{
    esh_signal_block(SIGCHLD);



    while (pipeline->status == FOREGROUND && !list_empty(&pipeline->commands)) {
        int status;
        pid_t child = (waitpid(-1, &status, WUNTRACED));
        if (child != -1)
            child_status_change(child, status);
    }

    esh_signal_unblock(SIGCHLD);

}

/* Changes the status of a child process */
bool 
child_status_change(pid_t child, int status)
{	
	struct esh_pipeline * job = get_job(child);

	if(WIFEXITED(status)) {
		struct esh_command * cmd = get_cmd(job, child);
		struct list_elem * e = &(cmd->elem);
		list_remove(e);

		if(list_empty(&job->commands)) {
			remove_job(job);
			
		
			if(list_empty(p_jobs_list)) {
				job_id = 1;
			}
			else {
				job_id = max_jid(p_jobs_list) + 1;
			}
		}
	} else if(WIFSTOPPED(status)) {

		job->status = STOPPED;

		print_job(job);
		esh_sys_tty_save(&(job->saved_tty_state));
	} else if(WIFSIGNALED(status)) {
		struct esh_command * cmd = get_cmd(job, child);
		struct list_elem * e = &(cmd->elem);
		list_remove(e);

		if(list_empty(&job->commands)) {
			remove_job(job);
			if(list_empty(p_jobs_list)) {
				job_id = 1;
			}
		}
	}

	return true;
}

/* Unblocks all the signals of a process */
bool 
unblock_signals(void)
{
	esh_signal_unblock(SIGINT);
	esh_signal_unblock(SIGCHLD);
        esh_signal_unblock(SIGTSTP);
	return true;
}

/* Returns the current highest job id */
int 
max_jid(struct list * p_jobs_list)
{
	struct list_elem * e = list_begin(p_jobs_list);
	int i = 0;
	int num_jobs = list_size(p_jobs_list);
	int max_jid = 1;
	while(i < num_jobs) {

		struct esh_pipeline * job = list_entry(e, struct esh_pipeline, elem);
		if(job->jid > max_jid) {
			max_jid = job->jid;
		}

		i++;
		e = list_next(e);
	}

	return max_jid;
}

/* Wrapper functions that report syscall failures */

bool check_open_error(int syscall)
{
	if(syscall < 0)
		perror("System error: open");

	return true;
}

bool check_dup2_error(int syscall)
{
	if(syscall < 0)
		perror("System error: dup2");

	return true;
}

bool check_exit_error(int syscall)
{
	if(syscall < 0)
		perror("System error: exit");
	
	return true;
}


bool check_close_error(int syscall)
{
	if(syscall < 0)
		perror("System error: close");
	
	return true;
}

bool check_fork_error(int syscall)
{
	if(syscall < 0)
		perror("System call error: fork");
	
	return true;
}

bool check_setpgid_error(int syscall)
{
	if(syscall < 0)
		perror("System call error: setpgid");
	
	return true;
}

bool check_kill_error(int syscall)
{
	if(syscall < 0)
		perror("System call error: kill");

	return true;
}

bool check_pipe_error(int syscall)
{
	if(syscall < 0)

		perror("System call error: pipe");
	
	return true;
}
