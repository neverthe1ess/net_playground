// 리틀엔디안, 빅엔디안 계열 컴퓨터에 관계없이 호환되는 tcp, udp, ip, icmp 구조체 작성

#ifndef NET_PLAYGROUND_GERENAL_PACKET_H
#define NET_PLAYGROUND_GERENAL_PACKET_H

#endif //NET_PLAYGROUND_GERENAL_PACKET_H

/*
 *  프로토콜 유형 리스트 (IP 헤더의 Protocol(상위 계층) 필드에 해당)
 */

#define PROTO_IP 0x800
#define PROTO_ARP 0x806
#define PROTO_ICMP 0x001
#define PROTO_TCP 0x006
#define PROTO_UDP 0x011

/*
 * TCP 플래그 리스트 (TCP 헤더의 FLAG 필드 값)
 */

#define TH_FIN        0x01
#define TH_SYN        0x02
#define TH_RST        0x04
#define TH_PUSH       0x08
#define TH_ACK        0x10
#define TH_URG        0x20

/*
 * 플랫폼의 바이트 순서에 따라서 헤더 순서 조정(조건부 컴파일)
 */

struct __attribute__((packed)) ip_header_t{
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned int hlen:4;
    unsigned int version:4;
#elif __BYTE_ORDER == __BIG_ENDIAN
    unsigned int version:4;
    unsigned int hlen:4;
#else
# error "Please fix <bits/endian.h>"
#endif
    unsigned char service;
    unsigned short length;
    unsigned short id;
    unsigned short frag_off;
    unsigned char ttl;
    unsigned char protocol;
    unsigned short checksum;
    unsigned int src_ip;
    unsigned int dsg_ip;
};

struct __attribute__((packed)) tcp_header_t{
    unsigned short src_port;
    unsigned short dst_port;
    unsigned int seqnum;
    unsigned int acknum;
#if __BYTE_ORDER == __LITTLE_ENDIAN
    unsigned char res1:4;
    unsigned char hlen:4;
    unsigned char flags:6;
    unsigned char res2:2;
#elif __BYTE_ORDER == __BIG_ENDIAN
    unsigned char hlen:4;
    unsigned char res1:4;
    unsigned char res2:2;
    unsigned char flags:6;
#else
# error "Please fix <bits/endian.h>"
#endif
    unsigned short window_size;
    unsigned short checksum;
    unsigned short urgent_point;
};


/*
 * UDP와 ICMP는 헤더 순서에 바이트 순서를 연관할 필요가 없음
 */

struct __attribute__((packed)) udp_header_t{
    unsigned short src_port;
    unsigned short dst_port;
    unsigned short tot_len;
    unsigned short checksum;
};

struct __attribute ((packed)) icmp_header_t{
    unsigned char type;
    unsigned char code;
    unsigned short cksum;
    unsigned short id;
    unsigned short seq_num;
};