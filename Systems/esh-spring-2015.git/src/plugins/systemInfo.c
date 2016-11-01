
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include "../esh.h"
#include "../esh-sys-utils.h"
#include <signal.h>

static bool
init_plugin(struct esh_shell *shell)
{
	printf("Plugin 'systemInfo' initialized...\n");
	return true;
}

static bool
sysInfo_builtin(struct esh_command *cmd)
{
	const double gigabyte = 1073741824;

	if (strcmp(cmd->argv[0], "systemInfo") != 0)
	{
		//printf("The call was %s not systemInfo %d\n", cmd->argv[0], strcmp(cmd->argv[0], "systemInfo"));
		return false;
	}

	struct sysinfo info;

	if (sysinfo(&info) == -1)
	{
		printf("Sysinfo returns -1");
		return false;
	}


	FILE *numProcess = popen("ps aux | wc -l", "r");
	if (numProcess == NULL) {
   	 printf("Failed to get number of processes\n" );
   	 exit(1);
  	}

	char buf[8];
	fgets(buf, sizeof(buf)-1, numProcess);

	printf("------------------------------------------------\n");
	printf("Number of processors configured: %d\n", get_nprocs_conf());
	printf("Number of processors available: %d\n", get_nprocs());
	printf("Number of processes currently running: %s", buf);
	printf("Total RAM: %lu bytes (%5.1f GB)\n", info.totalram ,info.totalram/gigabyte);
	printf("Total Free RAM: %lu bytes (%5.1f GB)\n", info.freeram, info.freeram/gigabyte);
	printf("------------------------------------------------\n");
	pclose(numProcess);


	return true;
}


struct esh_plugin esh_module = {
	.rank = 5,
	.init = init_plugin,
	.process_builtin = sysInfo_builtin
};
