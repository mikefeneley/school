#!/usr/bin/python
#
# Tests the functionality of temp_converter esh plugin
#
# Written for CS 3214 Spring 2015.
#
# To run this test on your own shell, simply run:
#
# ./esh -p /web/courses/cs3214/spring2015/projects/student-plugins/joevt/temp_converter 
#
# from the directory in which your "esh" and your "eshoutput.py" is located.
#
# @author Joe Fletcher, Shawn Amjad 
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

c.sendline("temp -c 212")
assert c.expect("Celcius: 100.0C") == 0, \
	"expect temp %s" % ('Celcius: 100.0C')

c.sendline("temp -f 90")
assert c.expect("Fahrenheit: 194.0F") == 0, \
	"expect temp %s" % ('Fahrenheit: 194.0F')

c.sendline("temp -c 100")
assert c.expect("Celcius: 37.8C") == 0, \
	"expect temp %s" % ('Celcius: 37.8C')

c.sendline("temp -f 0")
assert c.expect("Fahrenheit: 32.0F") == 0, \
	"expect temp %s" % ('Fahrenheit: 32.0F')	

# Exit the test
shellio.success()

