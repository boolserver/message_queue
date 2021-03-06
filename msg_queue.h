#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <mqueue.h>
#include <unistd.h>
#include <assert.h>
#include <uuid/uuid.h>

#define BUF_SIZE 256
#define UUID_SIZE_FOR_STR 32
#define QUEUE_MOUNT "/tmp_queue_test"

/*typedef struct msgForQueue{
    char uuid_str[UUID_SIZE_FOR_STR];
} MsgForQueue;*/

unsigned char *buffer_genration(const char *filename);
mqd_t init_message_queue();                                 // To be called once for a queue
void send_m_buffer_to_queue(char* m_buffer);
char* receive_m_buffer_from_queue();

void uuid_to_str(uuid_t uuid, char* str_ptr);

