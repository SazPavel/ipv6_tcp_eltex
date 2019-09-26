#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>

int main()
{
    char buf[16];
    int sock, bytes_read;
    struct sockaddr_in6 addr;
    sock = socket(AF_INET6, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(-1);
    }

    addr.sin6_family = AF_INET6;
    addr.sin6_port = htons(3333);
    addr.sin6_flowinfo = 0;
    addr.sin6_addr = in6addr_loopback;
    addr.sin6_scope_id = if_nametoindex("eth0");

    if(bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(-1);
    }
    listen(sock, 1);
    sock = accept(sock, NULL, NULL);
    if(sock < 0)
    {
        perror("sock2");
        exit(-1);
    }
    bytes_read = recv(sock, buf, 16, 0);
    printf("%s\n", buf);
    close(sock);
    exit(0);
}
