#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


// typedef struct in_addr in_addr;
// typedef struct in6_addr in6_addr;
// typedef struct sockaddr_in sockaddr_in;

// struct sockaddr {
//     //len specifies length of address
//     uint8_t sa_len;
//     // family specifies type of address
//     sa_family_t sa_family;
//     char sa_data[22];
// };

// struct in_addr {
//     in_addr_t s_addr;
// };

// struct sockaddr_in {
//     u_int8_t     sin_len;
//     sa_family_t sin_family;
//     in_port_t   sin_port;
//     in_addr     sin_addr;
//     char        sin_pad[16];
// };


// struct in6_addr{
//     uint8_t     s6_addr[16];
// };

// struct sockaddr_in6 {
//     uint8_t     sin6_len;
//     sa_family_t sin6_family;
//     in_port_t   sin6_port;
//     uint32_t    sin6_flowinfo;
//     in6_addr    sin6_addr;
// };


// struct addrinfo {
//  int ai_flags; // input flags
//  int ai_family; // AF_INET, AF_INET6, ...
//  int ai_socktype; // IPPROTO_TCP, IPPROTO_UDP
//  int ai_protocol; // SOCK_STREAM, SOCK_DRAM, ...
//  socklen_t ai_addrlen; // length of socket-address
//  struct sockaddr *ai_addr; // socket-address for socket
//  char *ai_canonname; // canonical name of host
//  struct addrinfo *ai_next; // pointer to next in list
// };


int main(){
    int backlog = 10;
    int fd = socket(AF_INET,SOCK_STREAM,0);


    struct sockaddr_in addr;
    //INADDR_ANY means the server will listen on the default address
    addr.sin_addr.s_addr    = INADDR_ANY;
    addr.sin_family         = AF_INET;
    //convert to port number with htons
    addr.sin_port           = htons(1024);

    if(fd == -1){
        fprintf(stderr,"Error: socket creation failed\n");
        return -1;

    }
    if (bind(fd,(struct sockaddr *)(&addr), sizeof(addr)) == -1){
        fprintf(stderr,"%d\n ",errno);
        fprintf(stderr,"Error: Unable to bind\n");
        close(fd);
        return -1;
    }

    if (listen(fd,backlog) == -1){
        fprintf(stderr,"Error: Cannot listen");
        return -1;
    }


    while(1){

        struct sockaddr_in cliaddr;
        socklen_t cliaddr_len = sizeof(cliaddr);
        int connfd = accept(fd,(struct sockaddr *)(&cliaddr),&cliaddr_len);
        if (connfd ==-1){
            fprintf(stderr,"Error while listening");
            return -1;
        }



    }
    fprintf(stdout,"Listening\n");


    #define BUFLEN 1500

    ssize_t rcount;
    char buf[BUFLEN];
    int flags =0;

    rcount = recv(fd,buf,BUFLEN,flags);
    if (rcount ==-1){
        fprintf(stderr,"error loading data");
    }




    return 0;
};

