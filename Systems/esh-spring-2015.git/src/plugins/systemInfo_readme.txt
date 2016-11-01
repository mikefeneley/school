
The systemInfo esh plugin
-------------------------

The 'systemInfo' plugin gives information that may or may not be correct
about the system. Such as total ram ,amount of free ram, number of processes,
and number of configured cpus.

Implemented from the process_builtin command for easy access. 

Can be called by:
esh> systemInfo

The test may fail if you change the prompt cause I do check it for the 
prompt defined in eshoutput. 


Created by:
Andrew Ciambrone (andrjc4@vt.edu) and Micheal Feneley (mfeneley@vt.edu)
