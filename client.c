#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>

int main()
{
    int sock;
    char buf[] = "HI IPv6!\n";
    struct sockaddr_in6 addr;
    sock = socket(AF_INET6, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("sock");
        exit(-1);
    }

    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(3333);
    addr.sin6_flowinfo = 0;
    addr.sin6_addr = in6addr_loopback;
    addr.sin6_scope_id = if_nametoindex("eth0");

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect");
        exit(-1);
    }
    send(sock, buf, sizeof(buf), 0);
    close(sock);
    exit(0);
}
