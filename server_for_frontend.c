#include "server_for_frontend.h"

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

char* get_uuid_as_client(){
    int listenfd = init_socket();
    printf("Initialized socket for client\n");
    int connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
    char* uuid_buf = malloc(UUID_SIZE_FOR_STR);  // UUID str will be stored in temp_buf
    memset(uuid_buf, '0', sizeof(uuid_buf));
    int bytes_received = read(connfd, uuid_buf, UUID_SIZE_FOR_STR);
    printf("Bytes recived -> %i\n", bytes_received);
    if(bytes_received < UUID_SIZE_FOR_STR){printf("\nERROR: bytes read less then UUID size\n");}

    return uuid_buf;
}

int main(){
    char* r_uuid;
    printf("Starting the Client\n");
    r_uuid = get_uuid_as_client();

    printf("Recived this UUID-> %s\n", r_uuid);
}
