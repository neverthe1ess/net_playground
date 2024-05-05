/*
 * IP, TCP, UDP, ICMP의 헤더 정보를 출력하는 코드
 * */


#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "print_header.h"

struct in_addr src, dst;

void ip_header_print(struct ip_header_t *ipHeader){
    printf("---------------IP HEADER ---------------\n");
    src.s_addr = ipHeader -> src_ip;
    dst.s_addr = ipHeader -> dsg_ip;
    printf("Src ip = %s\n", inet_ntoa(src));
    printf("Dst ip = %s\n", inet_ntoa(dst));
    printf("총 길이 = %d\n", ntohs(ipHeader -> length));
    printf("식별자 = %d\n", ntohs(ipHeader -> id));
    printf("TTL = %d\n", ntohs(ipHeader -> ttl));
    printf("헤더 검사합 = 0x%X\n", ntohs(ipHeader -> checksum));
}
void tcp_header_print(struct tcp_header_t *tcpHeader){
    printf("---------------TCP HEADER ---------------\n");
    printf("Src port = %d\n", ntohs(tcpHeader -> src_port));
    printf("Dst port = %d\n", ntohs(tcpHeader -> dst_port));
    printf("순서번호 = 0x%X\n", ntohl(tcpHeader -> seqnum));
    printf("Ack 번호 = 0x%X\n", ntohl(tcpHeader -> acknum));
    printf("체크섬 = 0x%X\n", ntohs(tcpHeader -> checksum));
}

void icmp_header_print(struct icmp_header_t *icmpHeader){
    printf("---------------ICMP HEADER ---------------\n");
    printf("타입 = %d\n", ntohs(icmpHeader -> type));
    printf("코드 = %d\n", ntohs(icmpHeader -> code));
    printf("체크섬 = 0x%X\n", ntohs(icmpHeader -> cksum));
    printf("식별자 = %d\n", ntohs(icmpHeader -> id));
    printf("순서번호 = %d\n", ntohs(icmpHeader -> seq_num));
}
void udp_header_print(struct udp_header_t *udpHeader){
    printf("---------------UDP HEADER ---------------\n");
    printf("Src_port = %d\n", ntohs(udpHeader -> src_port));
    printf("Dst_port = %d\n", ntohs(udpHeader -> dst_port));
    printf("총 길이 = %d\n", ntohs(udpHeader -> tot_len));
    printf("체크섬 = %d\n", ntohs(udpHeader -> checksum));
}
