#!/usr/bin/python
#
# Tests the functionality of the 'vt' esh plugin
# Written for CS 3214 Spring 2015
#
# To run the test on your own shell, add the test to your plugins.tst and simply run:
#
# $ cp /web/courses/cs3214/spring2015/projects/student-plugins/alisiraj_neily1/vt_test.py <path/to/your/plugins>
# $ cd <path/to/your/esh>
# $ ~cs3214/bin/stdriver.py -p plugins/ plugins.tst
#
# from the directory that your "esh" and "eshoutput.py" are in. 
#
# @author Siraj Ali, Neil Yavorski
#
import sys, imp, atexit
sys.path.append("/home/courses/cs3214/software/pexpect-dpty/");
import pexpect, shellio, signal, time, os, re, proc_check

# Determine the path this file is in
thisdir = os.path.dirname(os.path.realpath(__file__))

#Ensure the shell process is terminated
def force_shell_termination(shell_process):
	c.close(force=True)

#pulling in the regular expression and other definitions
definitions_scriptname = sys.argv[1]
plugin_dir = sys.argv[2]
def_module = imp.load_source('', definitions_scriptname)
logfile = None
if hasattr(def_module, 'logfile'):
    logfile = def_module.logfile

#spawn an instance of the shell
c = pexpect.spawn(def_module.shell + plugin_dir, drainpty=True, logfile=logfile)

atexit.register(force_shell_termination, shell_process=c)

# set the timeout
c.timeout = 2

#############################################################################
# Now the real test starts!
#

# ensure that shell prints expected prompt
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)" 

#check to see if the output of the 'vt' command is correct
c.sendline("vt")
assert c.expect("===      ================") == 0, "VT didn't print correctly"

# Exit the test
shellio.success()
