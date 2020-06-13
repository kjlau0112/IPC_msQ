#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>

#define MAX_MSG_SIZE        256
#define MSG_BUFFER_SIZE     (MAX_MSG_SIZE + 10)


int main(int argc, char **argv)
{

   // char buffer[MSG_BUFFER_SIZE];
    int recvr_msgq_fd = 0;
    int attempt = 0;
    char *buffer = "Linux Engineer\n";

    if(argc <= 1)
    {
        printf("provide a reciepient msgQ name : format </msgq-name>\n");
        return 0;
    }

    // memset(buffer, 0, MSG_BUFFER_SIZE);
    // printf("Enter msg to be sent to reciever %s\n", argv[1]);
    // scanf("%s", buffer);

    if ((recvr_msgq_fd  = mq_open (argv[1], O_WRONLY | O_CREAT, 0, 0)) == -1) 
    {
        printf ("Client: mq_open failed, errno = %d", errno);
        exit (1);
    }

    // for (attempt=0; attempt<10;attempt++)
    // {
    if (mq_send (recvr_msgq_fd, "importantl\n", strlen (buffer) + 1, 5) == -1) 
    {
        perror ("Client: Not able to send message to server");
        exit (1);
    }

    if (mq_send (recvr_msgq_fd, "CRITICAL\n", strlen (buffer) + 1, 10) == -1) 
    {
        perror ("Client: Not able to send message to server");
        exit (1);
    }
       // sleep(1);
    // }


    mq_close(recvr_msgq_fd);
    return 0;
}

