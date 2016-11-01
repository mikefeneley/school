#ifndef __JOB_H
#define __JOB_H

#include "helper.h"
#include "plugins.h"

/* Job control functions */
bool launch_job(struct esh_pipeline *job);
bool launch_single_job(struct esh_pipeline * job);
bool launch_pipe_job(struct esh_pipeline * job);
bool launch_first_cmd(int read_fd, int write_fd, struct esh_pipeline * cmd);
bool launch_interior_cmd(int read_fd, int write_fd, pid_t pgrp, struct esh_command * cmd);
bool launch_last_cmd(int read_fd, int write_fd, pid_t pgrp, struct esh_command * cmd);

/* Built in commands */
bool launch_built_in_cmd(struct esh_pipeline * jobb);
bool fg(struct esh_pipeline * job);
bool bg(struct esh_pipeline * job);
bool stop(struct esh_pipeline * job);
bool kill_job(struct esh_pipeline * job);
#endif
