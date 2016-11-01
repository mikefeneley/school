#!/usr/bin/python
#
# Tests the drake  esh plugin
#
# Written for CS 3214 Spring 2015.
#
# To run this test on your own shell, type:
#
# ./esh -p /web/courses/cs3214/spring2015/projects/student-plugins/blissard_jbenj93/drake 
#
# from the directory in which your "esh" and your "eshoutput.py" is located.
#
# @author Robert Blissard, Ben Jaques 
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

# Our tests are as follows

c.sendline("drake")
assert c.expect("Invoke with the arguments:") == 0, "Error: your output did not match expected output."

c.sendline("drake tc")
assert c.expect("...,............,.,,,,,,,,,,,,:") == 0, "Error: your output did not match expected output."

c.sendline("drake tml")
assert c.expect("77777777777777777777777?...............") == 0, "Error: your output did not match expected output."

c.sendline("drake nwts")
assert c.expect("\+\?\?\?\?\?") == 0, "Error: your output did not match expected output."

c.sendline("drake cs")
assert c.expect("..~~:,:~~,........,~~::==..") == 0, "Error: your output did not match expected output."

c.sendline("drake iyr")
assert c.expect("77777777777777777777777777777777777777") == 0, "Error: your output did not match expected output."

c.sendline("drake asdf")
assert c.expect("Sorry") == 0, "Error: your output did not match expected output."

shellio.success()
