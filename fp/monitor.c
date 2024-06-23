
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

void list_channels(int sock);
void list_rooms(int sock, const char *channel);
void list_users(int sock, const char *channel);

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock);
        exit(EXIT_FAILURE);
    }

    char input[1024];
    while (1) {
        printf("[monitor] ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character from input

        if (strcmp(input, "LIST CHANNEL") == 0) {
            list_channels(sock);
        } else if (strncmp(input, "LIST ROOM", 9) == 0) {
            char *channel = input + 10; // Skip "LIST ROOM "
            list_rooms(sock, channel);
        } else if (strncmp(input, "LIST USER", 9) == 0) {
            char *channel = input + 10; // Skip "LIST USER "
            list_users(sock, channel);
        } else if (strncmp(input, "JOIN", 4) == 0) {
            send(sock, input, strlen(input), 0);
            
            char key[50];
            printf("Key: ");
            fgets(key, sizeof(key), stdin);
            key[strcspn(key, "\n")] = '\0'; // Remove newline character

            if (strlen(key) > 0) {
                send(sock, key, strlen(key), 0);
            }
            
            char buffer[1024];
            memset(buffer, 0, sizeof(buffer));
            recv(sock, buffer, sizeof(buffer), 0);
            
            printf("%s\n", buffer); // Display server response to the user
        } else {
            fprintf(stderr, "Invalid command\n");
        }
    }

    close(sock);
    return 0;
}

void list_channels(int sock) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST CHANNEL");
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("Channels:\n%s\n", buffer);
}

void list_rooms(int sock, const char *channel) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST ROOM %s", channel);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("Rooms in channel %s:\n%s\n", channel, buffer);
}

void list_users(int sock, const char *channel) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST USER %s", channel);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("Users in channel %s:\n%s\n", channel, buffer);
}
