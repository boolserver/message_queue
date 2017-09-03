#include "server_for_frontend_backend.h"

int init_socket(){
    int listenfd = socket(AF_INET, SOCK_STREAM, 0); 

    struct sockaddr_in serv_addr;
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
                                    
    if(listen(listenfd, 10) == -1){printf("\nERROR: Failed to listen\n"); return -1;}

    return listenfd;
}

char* get_uuid_as_server(int connfd){
    //int listenfd = init_socket();
    //printf("Initialized socket for client\n");
    //int connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    char* uuid_buf = malloc(UUID_SIZE_FOR_STR);  // UUID str will be stored in temp_buf
    memset(uuid_buf, '0', sizeof(uuid_buf));
    //printf("Waiting for client now\n");
    int bytes_received = read(connfd, uuid_buf, UUID_SIZE_FOR_STR);
    printf("Bytes recived -> %i\n", bytes_received);
    if(bytes_received < UUID_SIZE_FOR_STR){printf("\nERROR: bytes read less then UUID size\n");}

    return uuid_buf;
}

int main(){
    char* r_uuid;
    printf("Starting the Client\n"); 
    int listenfd = init_socket();
    char frontend_or_msgqueue;
    
    while(1){
        int connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        int br = read(connfd, &frontend_or_msgqueue, 1);
        if(br != 1){printf("\nInitiation not defined\n\n");}

        if(frontend_or_msgqueue == 'f'){
            r_uuid = get_uuid_as_server(connfd);
            printf("Pushing data to msg queue");
            send_m_buffer_to_queue(r_uuid);
            printf("Recived this UUID-> %s\n", r_uuid);
        }
        else if(frontend_or_msgqueue == 'm'){
            char* r_uuid_str = receive_m_buffer_from_queue();
            if(strlen(r_uuid_str) != 32){
                char *empty = EMPTY_STR;
                write(connfd, empty, UUID_SIZE_FOR_STR);
            } 
            write(connfd, r_uuid_str, UUID_SIZE_FOR_STR);
        }
        close(connfd);
    }
}
