#!/usr/bin/python
#
# test for tipcal
# made by Ching Chau(ching93) & Fernando Mendoza (armendo)
#
#
import sys, imp, atexit
sys.path.append("/home/courses/cs3214/software/pexpect-dpty/");
import pexpect, shellio, signal, time, os, re, proc_check

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

#---------------------------------------------------------------------------------
# test start

# ensure that shell prints expected prompt
assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)" 

# check the output is the desired output

c.sendline("tipcal")
assert c.expect("Must enter only 2 arguments") == 0, "error when # of argv = 0"

c.sendline("tipcal 100")
assert c.expect("Must enter only 2 arguments") == 0, "error when # of argv = 1"

c.sendline("tipcal 100 100 100")
assert c.expect("Must enter only 2 arguments") == 0, "error when # of argv > 2"

c.sendline("tipcal abc 10")
assert c.expect("Amount is 0 or it is not a valid number") == 0, "error when amount is not number"

c.sendline("tipcal 0 10")
assert c.expect("Amount is 0 or it is not a valid number") == 0, "error when amount is 0"

c.sendline("tipcal 10 abc")
assert c.expect("Tip rate is 0 or it is not a valid number") == 0, "error when tiprate is not number"

c.sendline("tipcal 10 0")
assert c.expect("Tip rate is 0 or it is not a valid number") == 0, "error when tiprate is 0"

c.sendline("tipcal 9.99 15")
assert c.expect("The tip for this meal is : 1.50.") == 0, "print the wrong tip"

shellio.success()