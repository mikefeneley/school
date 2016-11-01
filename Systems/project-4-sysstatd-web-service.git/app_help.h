#include <time.h>
#include <stdbool.h>

/*
 * our files declartions
*/
#define JSON 0
#define JAVASCRIPT 1
#define HTML 2
#define CSS 3
#define JPEG 4
#define GIF 5

#define UNSUPPORTED -1
#define HTTP_0 0
#define HTTP_1 1

/*
 * our struct for vm_blocks
*/
struct vm_block {
    struct vm_block *prev;
    struct vm_block *next;
    void *virtualmem_block;
};

/*
 * Checks to see if the  file exists
*/
bool is_file();

/* 
 *	Checks what type of conenction 1.1 or 1.0
*/
int check_protocol(int fd, char* version);

/*
 * 	a wrapper for the client error pretty nice stuff here. 
 */
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg);

/*
 * a wrapper to create the header files.
*/
void make_header(char *header, char *version, int size, int filetype);

/*
 * Part of the synthetic load runLoop rns for 15 seconds
*/
void* time_loop();