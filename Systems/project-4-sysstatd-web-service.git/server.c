#include "csapp.h"
#include "ip_help.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "app_help.h"
#include <stdbool.h>
#include <sys/mman.h>

#define BLOCKSIZE 268435456

void *handle_connection(void *file_descriptor);
void do_get(int fd, rio_t *rp, char *method, char *uri, char * version);
void do_loadavg(int fd, char *uri, char *version);
void do_meminfo(int fd, char *uri, char *version);
void do_runloop(int fd, char *version);
void do_freeanon(int fd,  char* version);
void do_allocanon(int fd, char* version);
void do_servefile(int fd, char* filelocation, char *version);
int read_requesthdrs(rio_t *rp);
void get_filetype(char *filename, char *filetype);
static void* serverloop_IPv4();
static void* serverloop_IPv6();

/* Variables to store server argumetns */
char *port;
char *rootDir;

/* Holds virtual memory block lost */
struct vm_block *vm_list;


/*
 * Main server program accepts connections from clients and provides services.
 */
int main(int ac, char *av[])
{


    /* Default server values */
    port = "9011";
    rootDir = ".";
    int c;
        while ((c = getopt(ac, av, "p: R:")) != EOF) {
            switch (c) {
            case 'p':
                port = optarg;
                printf("%s\n", optarg);
                break;
            case 'R':
                rootDir = optarg;
                printf("%s\n", optarg);
                break;
            default:
                printf("Error\n");
            }            
        }


    int i;
    pthread_t ipv4_thread;
    pthread_t ipv6_thread;
    pthread_create(&ipv4_thread, NULL, serverloop_IPv4, &i);
    pthread_create(&ipv6_thread, NULL, serverloop_IPv6, &i);


    /* Stop the main thread from terminating */
    pthread_join(ipv4_thread, NULL);
    pthread_join(ipv6_thread, NULL);

    return 0;   
}

/* 
 * The thread executing this server loops continuously, accepts connections,
 * from IPv4 machines, and processes all server requests 
 */
static void* serverloop_IPv4(int i;)
{


    int listen_fd = Open_listenfd_IPv4(atoi(port));
    socklen_t client_size;
    struct sockaddr_in clientaddr;

    /* Wait for connections. Then process requests and clock connection */
    while(1) {

        int *connfd = malloc(sizeof(connfd));
        client_size = sizeof(clientaddr);

        *connfd = Accept(listen_fd, (SA *)&clientaddr, &client_size);

        /* Handle new client connection */
        pthread_t new_connect;
        pthread_create(&new_connect, NULL, handle_connection,  connfd);
        pthread_detach(new_connect);
    }
    return NULL;
}

/* 
 * The thread executing this server loops continuously, accepts connections,
 * from IPv6 machines, and processes all server requests.
 */ 
static void* serverloop_IPv6(int i;)
{

    int listen_fd = Open_listenfd_IPv6(port);
    socklen_t client_size;
    struct sockaddr_in clientaddr;

    /* Wait for connections. Then process requests and clock connection */
    while(1) {
        
        int *connfd = malloc(sizeof(connfd));
        client_size = sizeof(clientaddr);
        *connfd = Accept(listen_fd, (SA *)&clientaddr, &client_size);

        /* Handle new client connection */
        pthread_t new_connect;
        pthread_create(&new_connect, NULL, handle_connection,  connfd);
        pthread_detach(new_connect);    
    }

    return NULL;

}

/* Handle multiple HTTP request/response transactions */
void *handle_connection(void *file_descriptor)
{
    /* Set up connection handeling variables */
    int fd = *(int *)file_descriptor;
    free(file_descriptor);
    rio_t rio;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    int eof = 0;


    /* Read request Line */
    Rio_readinitb(&rio, fd);

    /* Loop until the connection is terminated */
    while(1) {

        eof = Rio_readlineb(&rio, buf, MAXLINE);
        eof = read_requesthdrs(&rio);
        
        /* Check if there is any input in the buffer to parse */
        if(buf[0] != '\0')
        {
            sscanf(buf, "%s %s %s", method, uri, version);
            int protocol = check_protocol(fd, version);

            if(protocol == HTTP_0) {
                if(strcasecmp(method, "GET") == 0) {
                    do_get(fd, &rio, method, uri, version);
                } else {
                    clienterror(fd, method, "501", "Not Implemented", "Not a valid HTTP method");
                }
                break;
             } else if(protocol == HTTP_1) {
                if(strcasecmp(method, "GET") == 0) {
                    do_get(fd, &rio, method, uri, version);
                }  else {
                    clienterror(fd, method, "501", "Not Implemented", "Not a valid HTTP method");
                }
            }
        }

        /* Terminate on EOF */
        if(eof < 1) {
            break;
        }

        buf[0] = '\0';
    }

    Close(fd);
    return NULL;
}

/*
 * Handle a clients get request.
 */
void do_get(int fd, rio_t *rp, char *method, char *uri, char *version)
{
    if(strncasecmp(uri, "/loadavg", strlen("/loadavg")) == 0) {
        do_loadavg(fd, uri, version);
    } else if(strncasecmp(uri, "/meminfo", strlen("/meminfo")) == 0) {
        do_meminfo(fd, uri, version);
   } else if(strncasecmp(uri, "/runloop", strlen("/runloop")) == 0) {
        do_runloop(fd, version);
   } else if(strncasecmp(uri, "/allocanon", strlen("/allocanon")) == 0) {
        do_allocanon(fd, version);
   } else if(strncasecmp(uri, "/freeanon", strlen("/freeanon")) == 0) {
        do_freeanon(fd, version);
   } else if(strncasecmp(uri, "/files", strlen("/files")) == 0) {
        char filelocation[256];
        sprintf(filelocation, "%s%s", rootDir, uri );
        do_servefile(fd, filelocation ,version);
   } else {
        clienterror(fd, uri, "404", "Not Found", "Incorrect URI");
   }
    return;
}

/*
 * Returns system load information to the client. 
 */
void do_loadavg(int fd, char* uri, char* version)
{

    /* Handle the callback case. */
    if(strlen(uri) > strlen("/loadavg"))
    {
        if(uri[strlen("/loadavg")] != '?')
        {
           clienterror(fd, uri, "404", "Not Found", "Incorrect URI");
           return;
        }
    }

    FILE *load_info = fopen("/proc/loadavg", "r");
    if (load_info == NULL)
    {
        clienterror(fd, "/proc/loadavg", "404", "Not found", "File not found on server");
        return;
    }

    char *callback;

    char output[MAXBUF];
    char header[MAXBUF];
    char message[MAXBUF];
    
    float cpu1, cpu2, cpu3;
    int running_threads, total_threads;
    fscanf(load_info, "%f %f %f %d/%d", &cpu1, &cpu2, &cpu3, &running_threads, &total_threads);

    /* Get the first part of a callback function */
    if((callback = strstr(uri, "?callback=")) != NULL) {
        callback = strstr(callback, "=");
        callback = strtok(callback, "= &");
        sprintf(message, "%s(", callback);
        sprintf(message, "%s{\"total_threads\": \"%d\",", message, total_threads);
    } else if((callback = strstr(uri, "&callback=")) != NULL) {
        callback = strstr(callback, "=");
        callback = strtok(callback, "= &");
        sprintf(message, "%s(", callback);
        sprintf(message, "%s{\"total_threads\": \"%d\",", message, total_threads);
    } else {
        sprintf(message, "{\"total_threads\": \"%d\",",  total_threads);
    }

    sprintf(message, "%s \"loadavg\": [\"%.2f\", \"%.2f\", \"%.2f\"],", message, cpu1, cpu2, cpu3);
    sprintf(message, "%s \"running_threads\": \"%d\"}", message, running_threads);

   if(callback != NULL) {
        sprintf(message, "%s)", message);
        int size = strlen(message);
        make_header(header, version, size, JAVASCRIPT);
    } else {
        sprintf(message, "%s\r\n", message);
        int size = strlen(message);
        make_header(header, version, size, JSON);
    }

    /* Write output back to client */
    sprintf(output, "%s%s", header, message);
    Rio_writen(fd, output, strlen(output));
    fclose(load_info);

    return;
}

/*
 * Returns system memory information to the client. 
 */
void do_meminfo(int fd, char* uri, char* version)
{

    /* Check the callback connection */
    if(strlen(uri) > strlen("/meminfo"))
    {
        if(uri[strlen("/loadavg")] != '?')
        {
           clienterror(fd, uri, "404", "Not Found", "Incorrect URI");
           return;
        }
    }


    FILE *meminfo = fopen("/proc/meminfo", "r");
    if (meminfo == NULL)
    {
        clienterror(-1, "/proc/meminfo", "404", "Not found", "File not found on server");
        return;
    }

    char *callback;

    char output[MAXBUF];
    char header[MAXBUF];
    char message[MAXBUF];
    memset(message, 0, MAXBUF);
    
    /* Get the first part of a callback function */
    if((callback = strstr(uri, "?callback=")) != NULL) {
        callback = strstr(callback, "=");
        callback = strtok(callback, "= &");
        sprintf(message, "%s(", callback);
    } else if((callback = strstr(uri, "&callback=")) != NULL) {
        callback = strstr(callback, "=");
        callback = strtok(callback, "= &");
        sprintf(message, "%s(", callback);
    }

    char line[256];
    int writebacktmp;
    int swaptotal;
    int active_anon;
    int swapfree;
    int directmap4k;
    int kernelstack;
    int memfree;
    int hugepages_rsvd;
    int committed_as;
    int active_file;
    int nfs_unstable;
    int vmallocchunk;
    int writeback;
    int inactive_file;
    int memtotal;
    int vmallocused;
    int hugepages_free;
    int anonhugepages;
    int anonpages;
    int active;
    int inactive_anon;
    int commitlimit;
    int hugepagesize;
    int cached;
    int swapcached;
    int vmalloctotal;
    int shmem;
    int mapped;
    int sunreclaim;
    int unevictable;
    int sreclaimable;
    int mlocked;
    int directmap2m;
    int hugepages_surp;
    int bounce;
    int inactive;
    int pagetables;
    int hardwarecorrupted;
    int hugepages_total;
    int slab;
    int buffers;
    int dirty;
    int directmap;

    while(fgets(line, sizeof(line), meminfo))
    {
        sscanf(line, "MemTotal: %d kB", &memtotal);
        sscanf(line, "MemFree: %d kB", &memfree);
        sscanf(line, "Buffers: %d kB", &buffers);
        sscanf(line, "Cached: %d kB", &cached);
        sscanf(line, "SwapCached: %d kB", &swapcached);
        sscanf(line, "Active: %d kB", &active);
        sscanf(line, "Inactive: %d kB", &inactive);
        sscanf(line, "Active(anon): %d kB", &active_anon);
        sscanf(line, "Inactive(anon): %d kB", &inactive_anon);
        sscanf(line, "Active(file): %d kB", &active_file);
        sscanf(line, "Inactive(file): %d kB", &inactive_file);
        sscanf(line, "Unevictable: %d kB", &unevictable);
        sscanf(line, "Mlocked: %d kB", &mlocked);
        sscanf(line, "SwapTotal: %d kB", &swaptotal);
        sscanf(line, "SwapFree: %d kB", &swapfree);
        sscanf(line, "Dirty: %d kB", &dirty);
        sscanf(line, "Writeback: %d kB", &writeback);
        sscanf(line, "AnonPages: %d kB", &anonpages);
        sscanf(line, "Mapped: %d kB", &mapped);
        sscanf(line, "Shmem: %d kB", &shmem);
        sscanf(line, "Slab: %d kB", &slab);
        sscanf(line, "SReclaimable: %d kB", &sreclaimable);
        sscanf(line, "SUnreclaim: %d kB", &sunreclaim);
        sscanf(line, "KernelStack: %d kB", &kernelstack);
        sscanf(line, "PageTables: %d kB", &pagetables);
        sscanf(line, "NFS_Unstable: %d kB", &nfs_unstable);   
        sscanf(line, "Bounce: %d kB", &bounce);       
        sscanf(line, "WritebackTmp: %d kB", &writebacktmp);
        sscanf(line, "CommitLimit: %d kB", &commitlimit);
        sscanf(line, "Committed_AS: %d kB", &committed_as);
        sscanf(line, "VmallocTotal: %d kB", &vmalloctotal);
        sscanf(line, "VmallocUsed: %d kB", &vmallocused);
        sscanf(line, "VmallocChunk: %d kB", &vmallocchunk);
        sscanf(line, "HardwareCorrupted: %d kB", &hardwarecorrupted);
        sscanf(line, "AnonHugePages: %d kB", &anonhugepages);     
        sscanf(line, "HugePages_Total: %d kB", &hugepages_total);
        sscanf(line, "HugePages_Free: %d kB", &hugepages_free);
        sscanf(line, "HugePages_Rsvd: %d kB", &hugepages_rsvd);
        sscanf(line, "HugePages_Surp: %d kB", &hugepages_surp);
        sscanf(line, "Hugepagesize: %d kB", &hugepagesize);
        sscanf(line, "DirectMap4k: %d kB", &directmap4k);
        sscanf(line, "DirectMap2M: %d kB", &directmap2m);
        sscanf(line, "DirectMap1G: %d kB", &directmap);
    }

    sprintf(message, "%s{\"WritebackTmp\": \"%d\",", message, writebacktmp);
    sprintf(message, "%s \"SwapTotal\": \"%d\",", message, swaptotal);
    sprintf(message, "%s \"Active(anon)\": \"%d\",", message, active_anon);
    sprintf(message, "%s \"SwapFree\": \"%d\",", message, swapfree);
    sprintf(message, "%s \"DirectMap4k\": \"%d\",", message, directmap4k);
    sprintf(message, "%s \"KernelStack\": \"%d\",", message, kernelstack);
    sprintf(message, "%s \"MemFree\": \"%d\",", message, memfree);
    sprintf(message, "%s \"HugePages_Rsvd\": \"%d\",", message, hugepages_rsvd);
    sprintf(message, "%s \"Committed_AS\": \"%d\",", message, committed_as);
    sprintf(message, "%s \"Active(file)\": \"%d\",", message, active_file);
    sprintf(message, "%s \"NFS_Unstable\": \"%d\",", message, nfs_unstable);
    sprintf(message, "%s \"VmallocChunk\": \"%d\",", message, vmallocchunk);
    sprintf(message, "%s \"Writeback\": \"%d\",", message, writeback);
    sprintf(message, "%s \"Inactive(file)\": \"%d\",", message, inactive_file);
    sprintf(message, "%s \"MemTotal\": \"%d\",", message, memtotal);
    sprintf(message, "%s \"VmallocUsed\": \"%d\",", message, vmallocused);
    sprintf(message, "%s \"HugePages_Free\": \"%d\",", message, hugepages_free);
    sprintf(message, "%s \"AnonHugePages\": \"%d\",", message, anonhugepages);
    sprintf(message, "%s \"AnonPages\": \"%d\",", message, anonpages);
    sprintf(message, "%s \"Active\": \"%d\",", message, active);
    sprintf(message, "%s \"Inactive(anon)\": \"%d\",", message, inactive_anon);
    sprintf(message, "%s \"CommitLimit\": \"%d\",", message, commitlimit);
    sprintf(message, "%s \"Hugepagesize\": \"%d\",", message, hugepagesize);
    sprintf(message, "%s \"Cached\": \"%d\",", message, cached);
    sprintf(message, "%s \"SwapCached\": \"%d\",", message, swapcached);
    sprintf(message, "%s \"VmallocTotal\": \"%d\",", message, vmalloctotal);
    sprintf(message, "%s \"Shmem\": \"%d\",", message, shmem);
    sprintf(message, "%s \"Mapped\": \"%d\",", message, mapped);
    sprintf(message, "%s \"SUnreclaim\": \"%d\",", message, sunreclaim);
    sprintf(message, "%s \"Unevictable\": \"%d\",", message, unevictable);
    sprintf(message, "%s \"SReclaimable\": \"%d\",", message, sreclaimable);
    sprintf(message, "%s \"Mlocked\": \"%d\",", message, mlocked);
    sprintf(message, "%s \"DirectMap2M\": \"%d\",", message, directmap2m);
    sprintf(message, "%s \"HugePages_Surp\": \"%d\",", message, hugepages_surp);
    sprintf(message, "%s \"Bounce\": \"%d\",", message, bounce);
    sprintf(message, "%s \"Inactive\": \"%d\",", message, inactive);
    sprintf(message, "%s \"PageTables\": \"%d\",", message, pagetables);
    sprintf(message, "%s \"HardwareCorrupted\": \"%d\",", message, hardwarecorrupted);
    sprintf(message, "%s \"HugePages_Total\": \"%d\",", message, hugepages_total);
    sprintf(message, "%s \"Slab\": \"%d\",", message, slab);
    sprintf(message, "%s \"Buffers\": \"%d\",", message, buffers);
    sprintf(message, "%s \"Dirty\": \"%d\",", message, dirty);
    sprintf(message, "%s \"DirectMap1G\": \"%d\"}\r\n", message, directmap);

    
   if(callback != NULL) {
        sprintf(message, "%s)", message);
        int size = strlen(message);
        make_header(header, version, size, JAVASCRIPT);
    } else {
        sprintf(message, "%s\r\n", message);
        int size = strlen(message);
        make_header(header, version, size, JSON);
    }

    /* Write output back to client */
    sprintf(output, "%s%s", header, message);
    Rio_writen(fd, output, strlen(output));
    fclose(meminfo);

    return;
}

/* 
 * Runs a 15 second loop to stress the server.
 */
void do_runloop(int fd, char* version)
{

    int i;
    pthread_t loop_thread;
    pthread_create(&loop_thread, NULL, time_loop, &i);

    /* Create loop output message */
    char output[MAXBUF];
    char header[MAXBUF];
    char message[MAXBUF];
    int filetype = HTML;
    sprintf(message, "<html> <head></head><body><p>Started 15 second spin.</p></body></html>\r\n");
    int size = strlen(message);
    make_header(header, version, size, filetype);
    sprintf(output, "%s%s", header, message);
    Rio_writen(fd, output, strlen(output));
    return;
}


/*
 * Allocates a block of virtual memory using the mmap method 
 */
void do_allocanon(int fd, char* version)
{    


    struct vm_block *new_block = malloc(sizeof(struct vm_block));

    if(new_block == NULL)
    {
        printf("Malloc Failed\n");
        clienterror(fd, "allocanon", "500", "Internal Server Error", "Error while creating block of Memory");
        return;
    }

    new_block->virtualmem_block = mmap(NULL, BLOCKSIZE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);

    if(new_block->virtualmem_block == MAP_FAILED)
    {
        perror("mmap fail");
        clienterror(fd, "allocanon", "500", "Internal Server Error", "Error while creating block of Memory");
        return;
    }

    /* Set poitners for new virtual memory list */
    if(vm_list == NULL)
    {
        new_block->prev = new_block;
        new_block->next = new_block;
        vm_list = new_block;
    } else {
        new_block->prev = vm_list->prev;
        new_block->next = vm_list;
        vm_list->prev->next = new_block;
        vm_list->prev = new_block;
    }
    memset(new_block->virtualmem_block,0,  BLOCKSIZE);



    /* Generate the output message for the user */
    char output[MAXBUF];
    char header[MAXBUF];
    char message[MAXBUF];
    int filetype = HTML;
    sprintf(message, "<html> <head></head><body><p>Mapped and touched 256 MB annonoymous memory.</p></body></html>\r\n");
    int size = strlen(message);
    make_header(header, version, size, filetype);
    sprintf(output, "%s%s", header, message);
    Rio_writen(fd, output, strlen(output));

    return;
}

/* Frees an block of virtual memory allocated with allocanon */
void do_freeanon(int fd, char* version)
{

    /* Output message if no blocks allcoated */
    if(vm_list == NULL) {
        char output[MAXBUF];
        char header[MAXBUF];
        char message[MAXBUF];
        int filetype = HTML;
        sprintf(message, "<html> <head></head><body><p>No blocks allocated</p></body></html>\r\n");
        int size = strlen(message);
        make_header(header, version, size, filetype);
        sprintf(output, "%s%s", header, message);
        Rio_writen(fd, output, strlen(output));       
        return;
    }

    struct vm_block *freed_block = vm_list->prev;

    /* Handle single block case */
    if(freed_block == vm_list)
    {
        if(munmap(freed_block->virtualmem_block, BLOCKSIZE) < 0)
        {
            clienterror(fd, "freeanon", "500", "Internal Server Error", "Error while freeing block of Memory");
            perror("munmap failed\n");
        }

        free(freed_block);
        vm_list = NULL;
        char output[MAXBUF];
        char header[MAXBUF];
        char message[MAXBUF];
        int filetype = HTML;
        sprintf(message, "<html> <head></head><body><p>Freed 256MB Memory Block </p></body></html>\r\n");
        int size = strlen(message);
        make_header(header, version, size, filetype);
        sprintf(output, "%s%s", header, message);
        Rio_writen(fd, output, strlen(output));
        return;
    }



    freed_block->prev->next = vm_list;
    vm_list->prev = freed_block->prev;



    if(munmap(freed_block->virtualmem_block, BLOCKSIZE) < 0)
    {
        clienterror(fd, "freeanon", "500", "Internal Server Error", "Error while freeing block of Memory");
        perror("munmap failed\n");
    }


    /* Generate multi block case output message */
    char output[MAXBUF];
    char header[MAXBUF];
    char message[MAXBUF];
    int filetype = HTML;
    sprintf(message, "<html> <head></head><body><p>Freed 256MB Memory Block </p></body></html>\r\n");
    int size = strlen(message);
    make_header(header, version, size, filetype);
    sprintf(output, "%s%s", header, message);
    Rio_writen(fd, output, strlen(output));
    free(freed_block);

    return;
}

/* 
 * Returns the requested file to the client 
 */
void do_servefile(int fd, char* filelocation, char* version)
{
    /* Check if the request goes outside of the files */
    if(strstr(filelocation, "//..") != NULL)
    {
        clienterror(fd, filelocation, "403", "Forbidden", "File locations with .. are Forbidden");
        return;
    }
    
    
    char header[MAXBUF];
    
   
    struct stat sbuf;
    if(stat(filelocation, &sbuf) < 0) {
        clienterror(fd, filelocation, "404", "Not Found", "File not found");
        return; 
    }


    if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
        clienterror(fd, filelocation, "403", "Forbidden", "Could not read that file");
        return;
    }

    int fp =  open(filelocation, O_RDONLY, 0);
    char* message = mmap(0, sbuf.st_size, PROT_READ, MAP_PRIVATE, fp, 0);
    close(fp);

    int filetype = -1;
    if (strstr(filelocation, ".html")) {
        filetype = HTML;
    } else {
        if (strstr(filelocation, ".css")) {
            filetype = CSS;
        } else {
            if (strstr(filelocation, ".js")) {
                filetype = JAVASCRIPT;
            } else {
                if (strstr(filelocation, ".jpeg")) {
                    filetype = JPEG;
                } else {
                    if (strstr(filelocation, ".gif")) {
                        filetype = GIF;
                    } else {
                        clienterror(fd, filelocation, "501", "Not Implemented", "Not a valid known file Extension");
                        munmap(message, sbuf.st_size);
                        return;
                    }
                }
               
            }
        }
    }

    char output[sbuf.st_size + MAXBUF];
    make_header(header, version, sbuf.st_size , filetype);

    sprintf(output, "%s%s", header, message);
    Rio_writen(fd, output, strlen(output));
    munmap(message, sbuf.st_size);
    return;
}
