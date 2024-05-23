#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_LEN 128

void *tcpRxThread(void * server_addr);
void *udpRxThread(void * server_addr);

//입력값은 포트번호 받기
int main(int argc, char *argv[]){
    //서버 주소 구조체
    struct sockaddr_in server_addr;
    //쓰레드 식별자
    pthread_t udp_s_thread, tcp_s_thread;

    if(argc != 2){
        printf("잘못된 사용법 !\n");
        exit(0);
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(argv[1]));

    if(pthread_create(&tcp_s_thread, NULL, tcpRxThread, (void *)&server_addr) != 0){
        perror("TCP 쓰레드 생성 실패 \n");
        exit(0);
    }

    if(pthread_create(&udp_s_thread, NULL, udpRxThread, (void *)&server_addr) != 0){
        perror("UDP 쓰레드 생성 실패 \n");
        exit(0);
    }

}

void *tcpRxThread(void * server1_addr) {
    int tcp_server_fd, client_fd, len, msg_size;
    struct sockaddr_in client_addr, server_addr;
    char buf[BUF_LEN];
    server_addr = *((struct sockaddr_in *) server1_addr);

    // TCP 소켓 개설
    if((tcp_server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("서버 소켓 개설이 실패하였음!\n");
        exit(0);
    }

    // 소켓 주소 바인딩
    if(bind(tcp_server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("서버: 바인딩 실패!\n");
        exit(0);
    }
    // 연결 대기 큐 설정
    listen(tcp_server_fd, 5);
    len = sizeof(client_addr);

    while(1) {
        printf("서버는 연결 요청을 대기하고 있습니다. listening......");

        client_fd = accept(tcp_server_fd, (struct sockaddr *)&client_addr, &len);
        if(client_fd < 0) {
            printf("서버 : 연결 수락 실패! \n");
            continue;
        }
        msg_size = recv(client_fd, buf, BUF_LEN, 0);
        if(msg_size < 0){
            printf("메시지 수신 실패! \n");
            exit(0);
        }
        send(client_fd, buf, msg_size, 0);
    }
}


void *udpRxThread(void * server1_addr){
    int udp_server_fd, len, msg_size;
    struct sockaddr_in client_addr, server_addr;
    char buf[BUF_LEN];
    server_addr = *((struct sockaddr_in *) server1_addr);

    // UDP 소켓 개설
    if((udp_server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        printf("서버 소켓 개설이 실패하였음!\n");
        exit(0);
    }

    // 소켓 주소 바인딩
    if(bind(udp_server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        printf("서버: 바인딩 실패!\n");
        exit(0);
    }

    len = sizeof(client_addr);

    if((msg_size = recvfrom(udp_server_fd, buf, BUF_LEN, 0, (struct sockaddr *) &client_addr, &len) < 0)){
        printf("수신 오류\n");
        exit(1);
    }

    if(sendto(udp_server_fd, buf, msg_size, 0, (struct sockaddr *)&client_addr, len) < 0){
        printf("송신 오류\n");
        exit(1);
    }

    close(udp_server_fd);

}








