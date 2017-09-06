#include "msg_queue.h"

unsigned char *buffer_genration(const char *filename){
    FILE *fp = fopen(filename, "rb");
    unsigned char *buff = malloc(sizeof(char)*BUF_SIZE);
    
    fread(buff, 1, BUF_SIZE, fp);
    fclose(fp);

    return buff;
}

mqd_t init_message_queue(){
    struct mq_attr m_attribute;
    m_attribute.mq_flags = 0;
    m_attribute.mq_maxmsg = 1000;
    m_attribute.mq_msgsize = UUID_SIZE_FOR_STR;
    m_attribute.mq_curmsgs = 0;
    
    mqd_t m_queue = mq_open(QUEUE_MOUNT, O_RDWR | O_CREAT | O_NONBLOCK, 0666, &m_attribute);

    if(m_queue == -1){printf("ERROR in initializing\n");exit(100);}

    printf("Initiated Message Queue\n");
    
    return m_queue;
}

void uuid_to_str(uuid_t uuid, char* str_ptr){
    sprintf(
        str_ptr, "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x", 
        uuid[0], uuid[1], uuid[2], uuid[3], uuid[4], uuid[5], uuid[6], uuid[7],
        uuid[8], uuid[9], uuid[10], uuid[11], uuid[12], uuid[13], uuid[14], uuid[15]
    );
}

void send_m_buffer_to_queue(char *m_buffer){
    mqd_t m_queue_2 = mq_open(QUEUE_MOUNT, O_WRONLY | O_NONBLOCK);
    printf("\tTemp buf -> %s and size -> %d and strlen is -> %d\n", m_buffer, sizeof(m_buffer), strlen(m_buffer));
    
    int status = mq_send(m_queue_2, m_buffer, strlen(m_buffer), 1);
    
    if(status == -1){printf("Failed to send data to m queue\n");exit(100);}
}

char* receive_m_buffer_from_queue(){
    mqd_t m_queue_3 = mq_open(QUEUE_MOUNT, O_RDONLY | O_NONBLOCK);
    char* r_buffer = malloc(UUID_SIZE_FOR_STR + 1);
    int status = mq_receive(m_queue_3, r_buffer, UUID_SIZE_FOR_STR+1, NULL);
    
    if(status == -1){printf("Failed to RECEIVE data from m queue\n");}
    printf("Recived -> %s\n", r_buffer);
    
    return r_buffer;
}
/*
int main(int argc, char **argv){
    printf("Starting code\n");
    int status = 0;
    printf("Removing previous copy of the message queue\n");
    status = mq_unlink(QUEUE_MOUNT);
    //ASSERT(status != 0);
    printf("Status Unlink -> %d\n", status);

    printf("Starting intialization of message queue\n");
    mqd_t m_queue = init_message_queue();
    
    struct mq_attr m_attribute;

    mq_getattr(m_queue, &m_attribute);

    printf("Flags -> %d, mq_maxmsg -> %d, mq_maxsize -> %d, mq_curmsgs -> %d\n", m_attribute.mq_flags, m_attribute.mq_maxmsg, m_attribute.mq_msgsize, m_attribute.mq_curmsgs);
    
    //struct msgForQueue temp_msg;
    //struct msgForQueue* msg_ptr;

    //struct msgForQueue r_msg;
    //struct msgForQueue* r_ptr;

    //r_ptr = &r_msg;

    //msg_ptr = &temp_msg;

    uuid_t uuid;
    uuid_generate_random(uuid);
    
    char* temp_msg = malloc(UUID_SIZE_FOR_STR);
    //char* r_msg = malloc(UUID_SIZE_FOR_STR);

    uuid_to_str(uuid, temp_msg);

    printf("UUID in temp_msg -> %s\nSending Msg\n", temp_msg);

    send_m_buffer_to_queue(temp_msg);
    printf("Msg sent\nReciving msg\n");

    uuid_generate_random(uuid);
    //free(temp_msg);
    uuid_to_str(uuid, temp_msg);
    printf("UUID in temp_msg 2 -> %s\nSending Msg\n", temp_msg);

    send_m_buffer_to_queue(temp_msg);
    printf("Second msg sent\n");

    mq_getattr(m_queue, &m_attribute);

    printf("Flags -> %d, mq_maxmsg -> %d, mq_maxsize -> %d, mq_curmsgs -> %d\n", m_attribute.mq_flags, m_attribute.mq_maxmsg, m_attribute.mq_msgsize, m_attribute.mq_curmsgs);
    printf("\n\nSTARTING THE RECIVE\n\n");
    char* r_msg = receive_m_buffer_from_queue();
    printf("Size of r_msg -> %d\n", sizeof(r_msg)); 
    printf("UUID recived buffer -> %s\n", r_msg);

    free(temp_msg);
    free(r_msg);

    return 0;
}*/
