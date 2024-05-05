//
//

#include "general_packet.h"
#ifndef NET_PLAYGROUND_PRINT_HEADER_H
#define NET_PLAYGROUND_PRINT_HEADER_H

#endif //NET_PLAYGROUND_PRINT_HEADER_H


void ip_header_print(struct ip_header_t *ipHeader);
void tcp_header_print(struct tcp_header_t *tcpHeader);
void icmp_header_print(struct icmp_header_t *icmpHeader);
void udp_header_print(struct udp_header_t *udpHeader);
