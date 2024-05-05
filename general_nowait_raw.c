/**
 * tcp, udp, icmp 패킷을 수신하는 스니퍼 프로그램 작성
 * 인터페이스를 프로미스큐어스로 설정
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "print_header.h"

#define MAX_LEN 65535

int main(){
    // TCP, UDP, ICMP 소켓 번호
    int sock_tcp, sock_udp, sock_icmp;
    // 수신한 tcp, udp, icmp 메시지의 길이, 버퍼의 길이, 구조체의 길이, 메시지 번호
    int ret_tcp, ret_udp, ret_icmp, buf_len, len, msg_number;
    // 수신한 메시지를 저장할 버퍼
    char buffer_icmp[MAX_LEN], buffer_udp[MAX_LEN], buffer_tcp[MAX_LEN];
    // 소켓 주소 구조체
    struct sockaddr_in from_icmp, from_tcp, from_udp;
    // 인터페이스 구조체
    struct ifreq ifreq;
    // 인터페이스의 이름
    char *interface = "eth0";

//    if(argc > 2){
//        printf("사용법 오류! 사용법 ./general_nowait_raw [인터페이스 이름]");
//    } else if(argc == 2){
//        // 입력된 인터페이스를 선택
//        interface = argv[1];
//    }

    //소켓 번호 생성
    sock_icmp = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);
    sock_tcp = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);
    sock_udp = socket(PF_INET, SOCK_RAW, IPPROTO_UDP);

    if(sock_icmp < 0 || sock_tcp < 0 || sock_udp < 0) {
        perror("소켓 생성 실패");
        exit(1);
    }

    //인터페이스를 프로미스큐어스 모드로 전환
    strncpy(ifreq.ifr_name, interface, strlen(interface));

    if(ioctl(sock_tcp, SIOCGIFFLAGS, &ifreq) < 0){
        perror("ifnet의 플래그를 가져오는 걸 실패!");
        exit(1);
    }
    ifreq.ifr_flags |= IFF_PROMISC;
    if(ioctl(sock_tcp, SIOCSIFFLAGS, &ifreq) < 0){
        perror("ifnet의 플래그 설정에 실패!");
        exit(1);
    }

    /*
    ifr.ifr_ifindex = addr.can_ifindex;
    ioctl(s, SIOCGIFNAME, &ifr);
    printf("Received a CAN frame from interface %s", ifr.ifr_name);
    */

    len = sizeof(from_icmp);
    buf_len = MAX_LEN;
    msg_number = 0;


    while(1){
        ret_icmp = recvfrom(sock_icmp, buffer_icmp, buf_len, MSG_DONTWAIT, (struct sockaddr *) &from_icmp, (socklen_t *)&len);
        ret_tcp = recvfrom(sock_tcp, buffer_tcp, buf_len, MSG_DONTWAIT, (struct sockaddr *) &from_tcp, (socklen_t *) &len);
        ret_udp = recvfrom(sock_udp, buffer_udp, buf_len, MSG_DONTWAIT, (struct sockaddr *) &from_udp, (socklen_t *) &len);

        if(ret_icmp > 0){
            printf("\n메시지 번호 : %d / ICMP 소켓으로부터 수신한 데이터의 길이는 %d입니다.\n", msg_number, ret_icmp);
            struct ip_header_t *ip = (struct ip_header_t *)&buffer_icmp;
            struct icmp_header_t *icmp = (struct icmp_header_t *) (buffer_icmp + (4 * ip -> hlen));
            if(ip -> protocol == PROTO_ICMP) {
                ip_header_print(ip);
                icmp_header_print(icmp);
                msg_number++;
            }
        }
        if(ret_tcp > 0){
            printf("\n메시지 번호 : %d / TCP 소켓으로부터 수신한 데이터의 길이는 %d입니다.\n", msg_number, ret_tcp);
            struct ip_header_t *ip = (struct ip_header_t *)&buffer_tcp;
            struct tcp_header_t *tcp = (struct tcp_header_t *) (buffer_tcp + (4 * ip -> hlen));
            if(ip -> protocol == PROTO_TCP) {
                ip_header_print(ip);
                tcp_header_print(tcp);
                msg_number++;
            }
        }
        if(ret_udp > 0){
            printf("\n메시지 번호 : %d / UDP 소켓으로부터 수신한 데이터의 길이는 %d입니다.\n", msg_number, ret_udp);
            struct ip_header_t *ip = (struct ip_header_t *)&buffer_udp;
            struct udp_header_t *udp = (struct udp_header_t *) (buffer_udp + (4 * ip -> hlen));
            if(ip -> protocol == PROTO_UDP) {
                ip_header_print(ip);
                udp_header_print(udp);
                msg_number++;
            }
        }
        if((ret_icmp < 0) && (ret_udp < 0) && (ret_tcp < 0)){
            printf("........................waiting........................ \n");
        }
        sleep(2);
    }
    return 0;
}
