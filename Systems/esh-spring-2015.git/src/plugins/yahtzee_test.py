#
# Tests the functionality of the customPrompt plugin

# To run this test on your own shell, simply run:
#
# /web/courses/cs3214/spring2015/projects/student-plugins/codyc/yahtzee_test.py eshoutput.py
#
# from the directory in which your "esh" and your "eshoutput.py" is located.
# It should also be possible to make a copy of that file anywhere, as long as the
# 'customPrompt.so' file is located within the same directory.
#
# @author Cody Cahoon (codyc)
# @author Richard Donaldson (richjd9)
#

#
# Setup Section
#
import sys, imp, atexit, os
sys.path.append("/home/courses/cs3214/software/pexpect-dpty/");
import pexpect, shellio, signal, time, os, re, proc_check

# Determine the path this file is in
thisdir = os.path.dirname(os.path.realpath(__file__))

#Ensure the shell process is terminated
def force_shell_termination(shell_process):
	c.close(force=True)

# pulling in the regular expression and other definitions
# this should be the eshoutput.py file of the hosting shell, see usage above
definitions_scriptname = sys.argv[1]
def_module = imp.load_source('', definitions_scriptname)

# you can define logfile=open("log.txt", "w") in your eshoutput.py if you want logging!
logfile = None
if hasattr(def_module, 'logfile'):
    logfile = def_module.logfile

#spawn an instance of the shell, note the -p flags
c = pexpect.spawn(def_module.shell,  drainpty=True, logfile=logfile, args=['-p', thisdir])

atexit.register(force_shell_termination, shell_process=c)

# set timeout for all following 'expect*' calls to 2 seconds
c.timeout = 2 

#
# Testing Section
#

# ensure that shell prints expected prompt
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)" 


c.sendline('yahtzee -k 1 2 3 4 5')
assert c.expect('\t|  o  |') == 0, \
    "expected %s" % ('\t|  o  |')

c.sendline('yahtzee')
assert c.expect('\t|     |') == 0, \
    "expected %s" % ('\t|     |')


shellio.success()

