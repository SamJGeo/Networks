#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>




int main(){
    struct addrinfo hints, *ai, *ai0;
    int i,fd;
    memset(&hints,0,sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((i = getaddrinfo("www.google.com","80",&hints,&ai0)) !=0){
        fprintf(stderr,"Unable to lookup IP address: %s",gai_strerror(i));
        return -1;
    }

    for(ai=ai0; ai != NULL; ai = ai->ai_next){
        fd = socket(ai->ai_family,ai->ai_socktype,ai->ai_protocol);
        if (fd == -1){
            //couldn't create socket, try next
            continue;
        }
        if(connect(fd,ai->ai_addr,ai->ai_addrlen) == -1){
            //couldn't connect to address, try next
            close(fd);
            continue;
        }

        break;
    }
    if (ai == NULL){
        fprintf(stderr,"Error in making connection");
    } else {
        fprintf(stdout,"Connection made");

        char *data = "hiya";
        size_t data_len = sizeof(data);
        int flags = MSG_NOSIGNAL;

        if (send(fd,data,data_len,flags) == -1){
            fprintf(stderr,"Error in sending data, error code:%d",errno);
        }

        






    }
    return 0;
}