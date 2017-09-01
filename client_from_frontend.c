#include "client_from_frontend.h"

int init_sockfd(){ 
    int sockfd = 0;
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ 
        printf("\nERROR: Could not create socket\n");
        exit(1);
    }
    
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_IP_ADDR);

    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        printf("\nERROR : Connect Failed\n");
        exit(1);
    }

    return sockfd;
}

char* get_uuid_as_client(){
    int sockfd = init_sockfd();

    char* uuid_buf = malloc(UUID_SIZE_FOR_STR);  // UUID str will be stored in temp_buf
    memset(uuid_buf, '0', sizeof(uuid_buf));
    int bytes_received = read(sockfd, uuid_buf, UUID_SIZE_FOR_SIZE);

    if(bytes_received < UUID_SIZE_FOR_STR){printf("\nERROR: bytes read less then UUID size\n");}

    return uuid_buf
}

