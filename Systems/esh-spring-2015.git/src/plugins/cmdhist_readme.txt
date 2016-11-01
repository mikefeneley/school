The 'cmdhist' esh plugin
-------------------------

cmdhist is an implementation of Command History using the GNU history library.

cmdhist allows you to move up and down your command history with the arrow keys
similar to bash.

It saves your history in a file called .esh_history which is stored in your
home directory. If this file does not exist, it will create it.

History is saved across esh sessions, so if you exit esh and come back to it
you will still have your 25 most recent command entries in your history.

Additionally, like bash, if you run a command that is identical to the most
recent command in history, it will not be saved in the history. This prevents
duplicates from filling up your history.

--
Written by Samuel Bahr (sfbahr) and Maxwell Honosky (maxwell3) Spring 2015.
