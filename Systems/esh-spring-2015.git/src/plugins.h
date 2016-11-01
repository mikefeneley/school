#ifndef __PLUGINS_H
#define __PLUGINS_H
 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <fcntl.h>
#include <sys/wait.h>
#include "esh.h"

int process_plugin(struct esh_command *cmd);

int setupAndRun(void);

bool is_plugin(struct esh_command *cmd);
#endif
