# This tests the functionality of the 'ffc' esh plugin
# Written for CS 3214 Spring 2015
#
# To run the test on your own shell, add the test to your plugins.tst and simply run:
#
# $ cp /web/courses/cs3214/spring2015/projects/student-plugins/alisiraj_neily1/ffc/ffc_test.py <path/to/your/plugins>
# $ cd <path/to/your/esh>
# $ ~cs3214/bin/stdriver.py -p plugins/ plugins.tst
#
# from the directory that your "esh" and "eshoutput.py" are in. 
#
# @author Siraj Ali, Neil Yavorski
#
import sys, imp, atexit
sys.path.append("/home/courses/cs3214/software/pexpect-dpty/");
import pexpect, shellio, signal, time, os, re, proc_check

# Determine the path this file is in
thisdir = os.path.dirname(os.path.realpath(__file__))

#Ensure the shell process is terminated
def force_shell_termination(shell_process):
    c.close(force=True)

#pulling in the regular expression and other definitions
definitions_scriptname = sys.argv[1]
plugin_dir = sys.argv[2]
def_module = imp.load_source('', definitions_scriptname)
logfile = None
if hasattr(def_module, 'logfile'):
    logfile = def_module.logfile

#spawn an instance of the shell
c = pexpect.spawn(def_module.shell + plugin_dir, drainpty=True, logfile=logfile)

atexit.register(force_shell_termination, shell_process=c)

# set the timeout
c.timeout = 2

#############################################################################
# Now the real test starts!
#

# ensure that shell prints expected prompt
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)" 

#check to see if the output of the 'ffc' command is correct
c.sendline("ffc -u 10 10")
assert c.expect("usage: -d, -a,s,m,d <int1> <int2>") == 0, "ffc usage didn't print correctly"

c.sendline("ffc -a 10 10")
assert c.expect("Sum: 20") == 0, "ffc didn't add correctly"

c.sendline("ffc -s 10 10")
assert c.expect("Difference: 0") == 0, "ffc didn't sub correctly"

c.sendline("ffc -m 10 10")
assert c.expect("Product: 100") == 0, "ffc didn't mult correctly"

c.sendline("ffc -d 10 10")
assert c.expect("Quotient: 1.00") == 0, "ffc didn't div print correctly"

c.sendline("ffc -d 10 0")
assert c.expect("Divide by zero error!") == 0, "ffc didn't handle div by 0"

# Exit the test
shellio.success()
