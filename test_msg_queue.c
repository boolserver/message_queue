#include "msg_queue.h"

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
    status = mq_unlink(QUEUE_MOUNT);
    free(temp_msg);
    free(r_msg);

    return 0;
}
