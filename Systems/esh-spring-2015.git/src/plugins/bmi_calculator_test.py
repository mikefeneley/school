#!/usr/bin/python
#
# This python script tests the bmi_calculator plugin
#
# Written for CS 3214 Spring 2015.
#
# To run this test on your own shell, simply run:
#
# /web/courses/cs3214/spring2015/projects/student-plugins/eyobest_ning/bmi_calculator_test.py eshoutput.py 
#
# @author Ning Li, Eyosedike Zewdier
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
#plugin_dir = sys.argv[2]
def_module = imp.load_source('', definitions_scriptname)

# you can define logfile=open("log.txt", "w") in your eshoutput.py if you want logging!
logfile = None
if hasattr(def_module, 'logfile'):
    logfile = def_module.logfile

#spawn an instance of the shell
#c = pexpect.spawn(def_module.shell + plugin_dir, drainpty=True, logfile=logfile)
c = pexpect.spawn(def_module.shell,  drainpty=True, logfile=logfile, args=['-p', thisdir])

atexit.register(force_shell_termination, shell_process=c)

#assert 1 == 0, "Unimplemented functionality"

# set timeout for all following 'expect*' calls to 2 seconds
c.timeout = 2 

#############################################################################
#
# Actual Test
# ensure that shell prints expected prompt

c.sendline("bmi 1.65 55")
assert c.expect("Your BMI result is = 20.20") == 0, "Shell didn't print properly"
c.sendline("bmi 1.7 70")
assert c.expect("Your BMI result is = 24.22") ==0, "Shell didn't print properly"
# Exit the test
shellio.success()
