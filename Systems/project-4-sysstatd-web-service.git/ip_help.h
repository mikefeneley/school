
/*
 * Sets up the socket for IPv4 connections.
 */
int open_listenfd_IPv4(int port);

/* 
 * Creates an IPv6 Listening File Descriptor that can only
 * make connectiosn with IPv6 machines.
 */
int open_listenfd_IPv6(int port);


/******************************************
 * Wrappers for the client/server helper routines 
 ******************************************/
int Open_listenfd_IPv4(int port);
int Open_listenfd_IPv6(char *port);

