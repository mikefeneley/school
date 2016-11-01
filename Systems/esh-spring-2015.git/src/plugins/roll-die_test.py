#!/usr/bin/python
#
# Tests the functionality of roll-die.so
#
# @author Ryan Munz (rtm8889)
# @author Dustin Pho (dpho)
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

# ensure that shell prints expected prompt
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)" 

# run a command
c.sendline("rdie")
assert c.expect("No arguments") == 0, "There should be a no argument error" 
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)"

# run a command
c.sendline("rdie foo")
assert c.expect("error") == 0, "There should be a non-number error" 
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)"

# run a command
c.sendline("rdie 3")
assert c.expect("Die 1") == 0, "There should be no errors" 
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)"

shellio.success()