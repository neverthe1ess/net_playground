//
//

#include "gerenal_packet.h"
#ifndef NET_PLAYGROUND_PRINT_HEADER_H
#define NET_PLAYGROUND_PRINT_HEADER_H

#endif //NET_PLAYGROUND_PRINT_HEADER_H


void ip_header_print(struct ip_header_t *structipHeader);
void tcp_header_print(struct tcp_header_t *structtcpHeader);
void icmp_header_print(struct icmp_header_t *structicmpHeader);
void udp_header_print(struct udp_header_t *structudpHeader);
