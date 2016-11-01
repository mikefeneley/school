#!/usr/bin/python
#
# Tests the functionality of conorpp's and nluther's gcd module
#
# Written for CS 3214 Spring 2015.
#
# To run this test on your own shell, simply run:
#
# /web/courses/cs3214/spring2015/projects/student-plugins/gback/conorpp_nluther/conorpp_nluther_gcd_test.py eshoutput.py
#
# from the directory in which your "esh" and your "eshoutput.py" is located.
# It should also be possible to make a copy of that file anywhere, as long as the
# 'gcd.so' file is located within the same directory.
#
# @author conorpp
# @author nluther
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

#############################################################################
# Now the real test starts!
#

# ensure that shell prints expected prompt
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)" 

#################################################################
# Step 1. Check the gcd of two prime numbers, confirm it is 1

# Send the command to the shell
c.sendline("gcd 512927357 15485863")
assert c.expect_exact("The gcd of 512927357 and 15485863 is 1") == 0, \
            "The gcd of 512927357 and 15485863 is 1"

# ensure that shell prints expected prompt
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (2)" 

#################################################################
# Step 2. Check the gcd of two numbers, confirm it is 77523

# Send the command to the shell
c.sendline("gcd 372653061 257453883");
assert c.expect_exact('The gcd of 372653061 and 257453883 is 77523') == 0, \
            "The gcd of 372653061 and 257453883 is 77523"

assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (3)"

#exit
c.sendline("exit");
assert c.expect_exact("exit\r\n") == 0, "Shell output extraneous characters"

shellio.success()

