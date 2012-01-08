#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char ** argv) {
    struct sockaddr_in * sa_1sss;
    int s;
    char buffer[6];
    sa_1sss = malloc(sizeof(struct sockaddr_in));
    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("socket");
        exit(1);
    }
    memset((char *) sa_1sss, 0, sizeof(sa_1sss));
    sa_1sss->sin_family = AF_INET;
    sa_1sss->sin_port = htons(63949);
    sa_1sss->sin_addr.s_addr = inet_addr("127.0.0.1");
    if (inet_aton("127.0.0.1", &sa_1sss->sin_addr) == 0) {
        perror("inet_aton");
        exit(1);
    }
    if (argc == 1) {
        strcpy(buffer, "print");
        if (sendto(s, buffer, 5, 0, (struct sockaddr *) sa_1sss, sizeof(struct sockaddr)) == -1) {
            perror("sendto");
            exit(1);
        }
    }
    else {
        if (strcmp(argv[1], "shift") == 0) {
            strcpy(buffer, "shift");
            if (sendto(s, buffer, 5, 0, (struct sockaddr *) sa_1sss, sizeof(struct sockaddr)) == -1) {
                perror("sendto");
                exit(1);
            }
        }
        else if (strcmp(argv[1], "ctrl") == 0) {
            strcpy(buffer, "ctrl");
            /*printf("%p %s %p %d\n", s, buffer, sa_1sss, sizeof(sa_1sss));*/
            if (sendto(s, buffer, 4, 0, (struct sockaddr *) sa_1sss, sizeof(struct sockaddr)) == -1) {
                perror("sendto");
                exit(1);
            }
        }
        else {
            printf("Usage: %s [ctrl|shift]\n", argv[0]);
            exit(0);
        }
    }
    exit(0);
}