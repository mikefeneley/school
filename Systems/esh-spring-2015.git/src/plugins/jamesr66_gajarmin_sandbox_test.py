#! /usr/bin/python

import sys, imp, atexit, os
sys.path.append("/home/courses/cs3214/software/pexpect-dpty");
import pexpect, shellio, signal, time, os, re, proc_check

thisdir = os.path.dirname(os.path.realpath(__file__))

def force_shell_termination(shell_process):
  c.close(force=True)

definitions_scriptname = sys.argv[1]
def_module = imp.load_source('', definitions_scriptname)

logfile = None
if hasattr(def_module, 'logfile'):
  logfile = def_module.logfile

c = pexpect.spawn(def_module.shell, drainpty=True, logfile=logfile, args=['-p', thisdir])

atexit.register(force_shell_termination, shell_process=c)

c.timeout = 2

assert c.expect(def_module.prompt) == 0, "Shell did not print expected prompt (1)"

###################################################################
# Step 1. Run a sandboxed command: 'echo 'The quick brown fox''
# Should not kill the command

c.sendline("echo 'The quick brown fox'")

assert c.expect_exact("The quick brown fox") == 0, \
  "Shell did not execute echo 'The quick brown fox' correctly"

###################################################################
# Step 2. Run the same command but block syscall write
# Should kill the command

c.sendline("sandbox -C write echo 'The quick brown fox'")

assert c.expect_exact("Blacklisted syscall: write caught.\r\n") == 0, "Plugin did not report that blacklisted syscall write was caught."
assert c.expect_exact("Killing\r\n") == 0, "Plugin did not report that it was killing the command"

###################################################################
# Step 3. Run the sme command but block syscall clone
# Should not kill the command

c.sendline("sandbox -C clone echo 'The quick brown fox'")

assert c.expect_exact("The quick brown fox") == 0, "The shell did not print 'The quick brown fox'"

shellio.success()
