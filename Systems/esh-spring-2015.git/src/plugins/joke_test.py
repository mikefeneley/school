
#test functionality of jokes plugin
#based off of gback_glob_test.py from CS 3214
#@author Victoria Worrall

import sys, imp, atexit, os
sys.path.append("/home/courses/cs3214/software/pexpect-dpty/");
import pexpect, shellio, signal, time, os, re, proc_check

thisdir = os.path.dirname(os.path.realpath(__file__))
#Ensure the shell process is terminated
def force_shell_termination(shell_process):
        c.close(force=True)

# pulling in the regular expression and other definitions
# this should be the eshoutput.py file of the hosting shell, see usage above
definitions_scriptname = sys.argv[1]
def_module = imp.load_source('', definitions_scriptname)
logfile = None
if hasattr(def_module, 'logfile'):
    logfile = def_module.logfile
 

#spawn an instance of the shell, note the -p flags
c = pexpect.spawn(def_module.shell,  drainpty=True, logfile=logfile, args=['-p', thisdir])

atexit.register(force_shell_termination, shell_process=c)

# set timeout for all following 'expect*' calls to 2 seconds
c.timeout = 2

c.sendline("joke")
assert c.expect('Enjoy your joke!') == 0, "this fails to tell a joke"
shellio.success()
