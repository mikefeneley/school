#include "plugins.h"

int process_plugin(struct esh_command *cmd){

	struct list_elem * e = list_begin(&esh_plugin_list);
	for (; e != list_end(&esh_plugin_list); e = list_next(e)) {

		struct esh_plugin *plugin = list_entry(e, struct esh_plugin, elem);
		//printf("%s\n", plugin->plugin_Name);
		if (plugin->process_builtin == NULL)
        	    continue;

		/* This should work because the list should be listed in priority order*/
		bool pStatus = plugin->process_builtin(cmd);
		if (pStatus)
			return 0;

	}
	return -1;
}

bool is_plugin(struct esh_command *cmd) {
	char *pluginName = cmd->argv[0];
        struct list_elem * e = list_begin(&esh_plugin_list);

	for (; e != list_end(&esh_plugin_list); e = list_next(e))
	{
		struct esh_plugin *plugin = list_entry(e, struct esh_plugin, elem);

		if (strcmp(pluginName, plugin->plugin_Name) == 0)
		{
			return true; 
		}
	}

	return false; 
}


int setupAndRun(void){
	struct list_elem * e = list_begin(&esh_plugin_list);

	for (; e != list_end(&esh_plugin_list); e = list_next(e))
	{
		struct esh_plugin *plugin = list_entry(e, struct esh_plugin, elem);

		printf("Plugin: %s\t", plugin->plugin_Name);
		if (plugin->process_raw_cmdline != NULL)
		{
			printf("Has process_raw_cmdline\t");
		}

                if (plugin->process_pipeline != NULL)
                {
                        printf("Has process_pipeline\t");
                }

                if (plugin->process_builtin != NULL)
                {
                        printf("Has process_builtin\t");
                }

                if (plugin->make_prompt != NULL)
                {
                        printf("Has make_prompt\t");
                }

                if (plugin->pipeline_forked != NULL)
                {
                        printf("Has pipeline_forked\t");
                }

                if (plugin->command_status_change != NULL)
                {
                        printf("Has command_status_changed\t");
                }
		printf("\n");
	}
	return -1;
}
