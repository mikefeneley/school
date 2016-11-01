#!/usr/bin/python
#
# Tests for the flip (Coin Flipper) esh plug-in
#
# To run this test on your own shell, simply run:
#
# ~cs3214/public_html/spring2015/projects/student-plugins/shb279/rps/rps_test.py eshoutput.py
#
# from the directory in which your "esh" and your "eshoutput.py" is located.
#

#======
# Setup 
#======
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

#========
# Testing 
#========

# Run the rps plug-in
c.sendline("flip")

# Throw a 'rock' command
c.sendline("flip")
assert c.expect('HEADS!|TAILS!') == 0, \
    "expected flip %s" % ("HEADS!|TAILS!")


# Test the secret "shotgun" throw
c.sendline("flip 10")
assert c.expect_exact('Flipping 10 times...') == 0, \
    "expected flip %s" % ('Flipping 10 times...')

# Test the 'stats' command
c.sendline("flip stats")
assert c.expect('HEADS: .*') == 0, \
    "expected flip %s" % ('HEADS: #')

# Test the 'quit' command
c.sendline("q")
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)"

# Exit the test
shellio.success()
