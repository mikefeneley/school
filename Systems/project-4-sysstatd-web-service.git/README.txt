Our server starts by reading in the port and root directory from the file line.
It then sets up two separate sockets for IPv4 and IPv6 connections. After
creating the sockets it waits and creates a new thread for each client that
tries to make a connection. This thread reads in http requests from the user
and returns data back to the user depending on the type of request. We support
loadavg and meminfo which read data from files in the /proc directory and formats
them in json format. We support callback on these json files.

We also support the serve file function which checks to make sure the user has access
to the requested file and if so, returns the data in that file back to the user. The serve
file URI can also return a widget which dynamically sends information back to the user.

We support synthetic load requests which can allocate and deallocate virtual memory and
run a loop for 15 seconds to temporarily increase the system load.


Team Members:
Andrew Ciambrone
Michael Feneley