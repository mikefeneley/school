#include "app_help.h"
#include "csapp.h"

/*
 * Checks to see if the  file exists
*/
bool is_file()
{
	return true;
}

/* 
 *  Checks what type of conenction 1.1 or 1.0
*/
int check_protocol(int fd, char* version)
{
    if(strcasecmp(version, "HTTP/1.0") == 0) {
        return HTTP_0;
    } else  if(strcasecmp(version, "HTTP/1.1") == 0) {
        return HTTP_1;
    } else {
        clienterror(fd, version, "505", "Not Supported", "This protocol is not supported");
        return UNSUPPORTED;
    }
}

/*
 * Return an error message to client based on cause of failure 
 */
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg) 
{
    char buf[MAXLINE], body[MAXBUF];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>CS 3214 Web server Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>CS 3214 Web server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.1 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}

/*
 * Make the header portion of the output to client.
 */
void make_header(char *header, char *version, int size, int filetype)
{
    sprintf(header, "%s 200 OK\r\n", version);
    sprintf(header, "%sContent-length: %d\r\n", header, size);
    if(filetype == JSON) {
            sprintf(header, "%sContent-type: %s\r\n\r\n", header, "application/json");
    } else if (filetype == JAVASCRIPT) {
            sprintf(header, "%sContent-type: %s\r\n\r\n", header, "application/javascript");
    } else if (filetype == HTML) {
            sprintf(header, "%sContent-type: %s\r\n\r\n", header, "text/html");
    } else if (filetype == JPEG) {
            sprintf(header, "%sContent-type: %s\r\n\r\n", header, "image/jpeg");
    } else if (filetype == GIF) {
            sprintf(header, "%sContent-type: %s\r\n\r\n", header, "image/gif");
    } else if (filetype == CSS) {
            sprintf(header, "%sContent-type: %s\r\n\r\n", header, "text/css");
    }
}

/*
 * get_filetype - derive file type from file name
 */
void get_filetype(char *filename, char *filetype) 
{
    if (strstr(filename, ".html"))
    strcpy(filetype, "text/html");
    else if (strstr(filename, ".gif"))
    strcpy(filetype, "image/gif");
    else if (strstr(filename, ".jpg"))
    strcpy(filetype, "image/jpeg");
    else
    strcpy(filetype, "text/plain");
} 

/*
 * read_requesthdrs - read and parse HTTP request headers
 */
/* $begin read_requesthdrs */
int read_requesthdrs(rio_t *rp) 
{

    char buf[MAXLINE];
    int status = Rio_readlineb(rp, buf, MAXLINE);
    while(strcmp(buf, "\r\n")) {         
        status = Rio_readlineb(rp, buf, MAXLINE);
        if(status < 1)
        {
            return status;
        }
    }
    return status;
}

/*
 * Part of the synthetic load runLoop runs for 15 seconds
*/
void* time_loop()
{
    time_t t1 = time(NULL);
    time_t t2 = time(NULL);

    while(difftime(t2, t1) < 15)
    {
        t2 = time(NULL);
    }

    return NULL;
}