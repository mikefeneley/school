#!/usr/bin/python
#
# Tests the functionality of the convertnum esh plugin.
# Written for CS 3214 Spring 2015.
#
# To run this test on your own shell, simply run:
#
# python /web/courses/cs3214/spring2015/projects/student-plugins/jareds94_coreym94/convertnum/convertnum_test.py eshoutput.py
#
# from the directory in which your "esh" and your "eshoutput.py" is located.
#
# @author jareds94
# @author coreym94


##########
# Set up #
##########

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
c = pexpect.spawn(def_module.shell, drainpty=True, logfile=logfile, args=['-p', thisdir])

atexit.register(force_shell_termination, shell_process=c)

# set timeout for all following 'expect*' calls to 2 seconds
c.timeout = 2 


################
# Actual tests #
################

# ensure that shell prints expected prompt
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)"

# Tests invalid arguement  --help 
c.sendline("convertnum")
assert c.expect("convertnum: incorrect arguments, use --help") == 0, \
	"expected convertnum %s" % ('convertnum: incorrect arguments, use --help')

#Tests the command with no flags, default 
c.sendline("convertnum 32")
assert c.expect('32 Bit Binary Value: 00000000000000000000000000100000\r\nHexadecimal Value: 0x00000020') == 0, \
    "expected convertnum %s" % ('32 Bit Binary Value: 00000000000000000000000000100000\r\nHexadecimal Value: 0x00000020')

#Tests the command with -32
c.sendline("convertnum 28 -32")
assert c.expect('32 Bit Binary Value: 00000000000000000000000000011100') == 0, \
    "expected convertnum %s" % ('32 Bit Binary Value: 00000000000000000000000000011100')

#Tests the -16 option
c.sendline("convertnum 28 -16")
assert c.expect('16 Bit Binary Value: 0000000000011100') == 0, \
    "expected convertnum %s" % ('16 Bit Binary Value: 0000000000011100')

#Tests the -8 option
c.sendline("convertnum 28 -8")
assert c.expect('8 Bit Binary Value: 00011100') == 0, \
    "expected convertnum %s" % ('8 Bit Binary Value: 00011100')

#Tests the -h option
c.sendline("convertnum 28 -h")
assert c.expect('Hexadecimal Value: 0x0000001C') == 0, \
    "expected convertnum %s" % ('Hexadecimal Value: 0x0000001C')

#Error check if invalid information
c.sendline("convertnum cmac")
assert c.expect('convertnum: incorrect arguments, use --help') == 0, \
    "expected convertednum %s" % ('convertnum: incorrect arguments, use --help')

#Exit the test
shellio.success()