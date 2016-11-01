#ifndef __HELP_H
#define __HELP_H

#include "esh.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <assert.h>
#include "esh-sys-utils.h"

/* Declaration of headers used by shell */
struct list * p_jobs_list;
struct list jobs_list;
struct termios * p_state_manager;


/* Global variabes used by shell */
pid_t shell_pgid;
int job_id;
bool plugins_loaded;

/* Helper methods to access jobs and commands */
struct esh_pipeline * get_next_job(struct esh_command_line * cline);
struct esh_command * get_first_cmd(struct esh_pipeline * job);
struct esh_pipeline * get_job(pid_t);
struct esh_command * get_cmd(struct esh_pipeline * job, pid_t child);
struct esh_pipeline * get_fg_job(void);
struct esh_pipeline * get_last_job(void);
struct esh_pipeline *get_job_jid(int jid);
struct esh_pipeline * get_last_stopped_job(void);


/* Status check methods */
bool is_built_in_cmd(struct esh_pipeline * job);
bool is_fg_cmd(struct esh_pipeline * job);
bool is_bg_cmd(struct esh_pipeline * job);
bool is_child(int pid);
bool is_parent(int pid);
int max_jid(struct list * p_jobs_list);


/* Job status update methods */
bool print_jobs(struct list * jobs_list);
bool print_job(struct esh_pipeline *job);
bool print_fg_message(struct list * command_list);
bool print_commands(struct list * command_list);
bool print_bg_message(struct esh_pipeline * job);
char * get_status(int status);

/* System update methods */
bool set_pgrp(pid_t pgrp);
bool update_pgrp(struct esh_pipeline * job, pid_t pid);
bool update_pid(struct esh_command * cmd, pid_t pid);
bool redirect_input(struct esh_command * cmd);
bool redirect_output(struct esh_command * cmd);
bool update_fd(int read_fd, int write_fd);
void give_terminal_to(pid_t pgrp, struct termios *pg_tty_state);
void wait_for_job(struct esh_pipeline *pipeline);
bool child_status_change(pid_t child, int status);
bool send_to_all(struct list * command_list, int sig);
bool unblock_signals(void);
void sigchld_handler(int sig, siginfo_t *info, void *_ctxt);

/* List manipulation methods */
bool add_job(struct list * jobs_list, struct esh_pipeline * job);
bool remove_job(struct esh_pipeline * job);
bool add_to_fg(struct esh_pipeline * job, struct termios *pg_tty_state);
bool add_to_bg(struct esh_pipeline * job);
bool stop_job(struct esh_pipeline * job);
int get_num_jobs(struct esh_command_line * cline);
int get_num_cmd(struct esh_pipeline * job);

/* Error check methods */
bool check_dup2_error(int syscall);
bool check_exit_error(int syscall);
bool check_close_error(int syscall);
bool check_fork_error(int syscall);
bool check_setpgid_error(int syscall);
bool check_kill_error(int syscall);
bool check_open_error(int syscall);
bool check_pipe_error(int syscall);


#endif
