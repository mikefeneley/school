#!/usr/bin/python
#
# Tests the functionality of timer plugin
#
# Written for CS 3214 Spring 2015.
#
# To run this test on your own shell, simply run:
# /web/courses/cs3214/spring2015/projects/student-plugins/dpho_rtm8889/timer/timer_test.py eshoutput.py
# from the directory in which your "esh", "timer.so"  and your "eshoutput.py" is located.
#
# @author Dustin Pho (dpho)
# @author Ryan Munz (rtm8889)
#
import sys, imp, atexit, os
sys.path.append("/home/courses/cs3214/software/pexpect-dpty/");
import pexpect, shellio, signal, time, os, re, proc_check, time

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

#############################################################################
# Now the real test starts!
#

# Testing input: "timer"
#c.sendline("timer");
#assert c.expect("timer: Use --help (-h) for more information and --usage (-u) to see how to invoke timer.") == 0, "Output did not match on input 'timer'"

# Testing input: "timer --help"
#c.sendline("timer --help");
#assert c.expect("Timer counts down and displays a progress bar representing the percentage of time left to wait.") == 0, "Output did not match on input 'timer --help'"

# Testing input: "timer --usage"
#c.sendline("timer --usage");
#assert c.expect("Usage: timer seconds, where seconds is an integer representing how long you want to count down from.") == 0, "Output did not match on input 'timer --usage'"


# Testing inputs: "timer invalid_arg"
c.sendline("timer d1");
assert c.expect("An integer must be passed in.") == 0, "Output did not match when passed invalid argument."
c.sendline("timer 13f");
assert c.expect("An integer must be passed in.") == 0, "Output did not match when passed invalid argument."
c.sendline("timer 1.11");
assert c.expect("An integer must be passed in.") == 0, "Output did not match when passed invalid argument."

#test timer 30
#run
#check not done
#check "#"s with regex
#sleep 30
#time.sleep(30)
#check for done with regex
#check no # with regex

shellio.success()
