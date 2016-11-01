#!/usr/bin/python
#
# Tests the functionality of the 'translate' esh plugin
# Written for CS 3214 Spring 2015
#
# To run the test on your own shell, add the test to your plugins.tst and simply run:
#
# $ cp /web/courses/cs3214/spring2015/projects/student-plugins/akatkov_treiter/vt_test.py <path/to/your/plugins>
# $ cd <path/to/your/esh>
# $ ~cs3214/bin/stdriver.py -p plugins/ plugins.tst
#
# from the directory that your "esh" and "eshoutput.py" are in. 
#
# @author Tony Reiter, Andriy Katkov
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
c.timeout = 5 

#############################################################################
# Now the real test starts!
#

# ensure that shell prints expected prompt
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)" 

#################################################################
# Step 1. Build expected output
#
#
expectedoutput = "Possible Translations:"
expectedoutput1 = "en"
expectedoutput2 = "Hallo Welt"
expectedoutput3 = "Error: invalid translation"


#################################################################
# Step 2. Testing translate
#
# run translate -l
c.sendline("translate -l");

assert c.expect_exact(expectedoutput) == 0, \
    "expected translate output %s" % (expectedoutput)

#################################################################
# Test translate -d

# ensure that shell prints expected prompt
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (3)"
c.sendline("translate -d hello");
assert c.expect_exact(expectedoutput1) == 0, \
	"expected translate output %s" % (expectedoutput1)

#################################################################
# Test translate en-de hello world
#
c.sendline("translate en-de hello world")

assert c.expect_exact(expectedoutput2) == 0, "expected translate output %s" % (expectedoutput2)

#################################################################
# Test translate with incorrect lang_code
#
c.sendline("translate en-zz hello world")

assert c.expect_exact(expectedoutput3) == 0, "expected translate output %s" % (expectedoutput3)

shellio.success()