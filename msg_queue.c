#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <mqueue.h>
#include <unistd.h>
#include <assert.h>

#define BUF_SIZE 256

unsigned char *buffer_genration(const char *filename){
    FILE *fp = fopen(filename, "rb");
    //unsigned char buff[BUF_SIZE] = {0};
    unsigned char *buff = malloc(sizeof(char)*BUF_SIZE);

    fread(buff, 1, BUF_SIZE, fp);
    fclose(fp);

    return buff;
}

mqd_t init_message_queue(){
    struct mq_attr m_attribute;
    m_attribute.mq_flags = 0;
    m_attribute.mq_maxmsg = 100;
    m_attribute.mq_msgsize = BUF_SIZE;
    //m_attribute.mq_curmsgs = 0;
    
    mqd_t m_queue = mq_open("/tmp_queue", O_RDWR | O_CREAT | O_NONBLOCK, 0666, &m_attribute);

    if(m_queue == -1){printf("ERROR in initializing\n");exit(100);}

    printf("Initiated Message Queue\n");

    return m_queue;
}

int main(int argc, char **argv){
    printf("Starting code\n");
    int status = 0;
    if(argc == 2){
        const char *filename = argv[1];
    } 
    else{
        printf("ERROR in filename defination\n");
    }
    printf("HERE\n");
    char* buffer = buffer_genration("test_file.json");
    size_t buf_len = strlen(buffer);
   
    printf("Removing previous copy of the message queue\n");
    status = mq_unlink("/tmp_queue");
    //ASSERT(status != 0);
    printf("Status Unlink -> %d\n", status);

    printf("Starting intialization of message queue\n");
    mqd_t m_queue = init_message_queue();

    //testing m_queue
    printf("Sending data\n"); 
    size_t temp = 6*sizeof(char);
    temp = 6;

    printf("Buffer -> %s\n", buffer);

    status = mq_send(m_queue,buffer, buf_len, 1);
    printf("Status Sending = %d\n", status);

    sleep(1);
    
    //mqd_t m_queue_2 = mq_open("/tmp_queue3", O_RDONLY | O_NONBLOCK);

    struct mq_attr m_attribute;

    mq_getattr(m_queue, &m_attribute);

    printf("Flags -> %d, mq_maxmsg -> %d, mq_maxsize -> %d, mq_curmsgs -> %d\n", m_attribute.mq_flags, m_attribute.mq_maxmsg, m_attribute.mq_msgsize, m_attribute.mq_curmsgs);

    char *buffer_2 = malloc(BUF_SIZE);
    //char buffer_2[sizeof(char) * 6];
    printf("Starting the receving functions\n");
    status = mq_receive(m_queue, buffer_2, BUF_SIZE, NULL);
    printf("Status Recive = %d\n", status);

    //printf("Buffer -> %s\n", buffer_2);

    //Testing *buffer functions
    FILE *fp = fopen("test_run_s2.json", "wb");
    fwrite(buffer_2, 1, strlen(buffer_2), fp);
    fclose(fp);

    //mq_unlink("/test_queue")
    return 0;
}
