#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

// Prototipe fungsi
void register_user(int sock, const char *username, const char *password);
void login(int sock, const char *username, const char *password);
void join_channel(int sock, const char *username, const char *channel, const char *key);
void join_room(int sock, const char *username, const char *channel, const char *room);
void list_channel(int sock);
void list_room(int sock, const char *channel);
void list_user(int sock, const char *channel);
void interactive_mode(int sock, const char *username);

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 6) {
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "To register: %s REGISTER username -p password\n", argv[0]);
        fprintf(stderr, "To login: %s LOGIN username -p password\n", argv[0]);
        fprintf(stderr, "To join channel: %s JOIN channel\n", argv[0]);
        fprintf(stderr, "To join channel with key: %s JOIN channel -k key\n", argv[0]);
        fprintf(stderr, "To join room: %s JOIN channel/room\n", argv[0]);
        exit(EXIT_FAILURE);
    }

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
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "REGISTER") == 0 && argc == 5 && strcmp(argv[3], "-p") == 0) {
        register_user(sock, argv[2], argv[4]);
    } else if (strcmp(argv[1], "LOGIN") == 0 && argc == 5 && strcmp(argv[3], "-p") == 0) {
        login(sock, argv[2], argv[4]);
    } else if (strcmp(argv[1], "JOIN") == 0 && argc >= 3) {
        if (argc == 3) {
            join_channel(sock, argv[2], NULL, NULL);
        } else if (argc == 5 && strcmp(argv[3], "-k") == 0) {
            join_channel(sock, argv[2], argv[4], argv[5]);
        } else if (argc == 4 && strchr(argv[3], '/') != NULL) {
            char *token = strtok(argv[3], "/");
            char *channel = token;
            token = strtok(NULL, "/");
            char *room = token;
            join_room(sock, argv[2], channel, room);
        } else {
            fprintf(stderr, "Invalid command format\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Invalid command\n");
        exit(EXIT_FAILURE);
    }

    close(sock);
    return 0;
}

void register_user(int sock, const char *username, const char *password) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "REGISTER %s -p %s", username, password);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("%s\n", buffer);
}

void login(int sock, const char *username, const char *password) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LOGIN %s -p %s", username, password);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("%s\n", buffer);
    
    // Panggil fungsi interactive_mode setelah login berhasil
    interactive_mode(sock, username);
}

void join_channel(int sock, const char *username, const char *channel, const char *key) {
    char buffer[1024];
    if (key == NULL) {
        snprintf(buffer, sizeof(buffer), "JOIN %s", channel);
    } else {
        snprintf(buffer, sizeof(buffer), "JOIN %s -k %s", channel, key);
    }
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("%s\n", buffer);
}

void join_room(int sock, const char *username, const char *channel, const char *room) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "JOIN %s/%s", channel, room);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("%s\n", buffer);
}

void list_channel(int sock) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST CHANNEL");
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("%s\n", buffer);
}

void list_room(int sock, const char *channel) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST ROOM %s", channel);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("%s\n", buffer);
}

void list_user(int sock, const char *channel) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST USER %s", channel);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("%s\n", buffer);
}

void interactive_mode(int sock, const char *username) {
    char input[1024];
    while (1) {
        printf("[%s] ", username);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character from input
        
        if (strcmp(input, "LIST CHANNEL") == 0) {
            list_channel(sock);
        } else if (strncmp(input, "LIST ROOM", 9) == 0) {
            char *channel = input + 10; // Skip "LIST ROOM "
            list_room(sock, channel);
        } else if (strncmp(input, "LIST USER", 9) == 0) {
            char *channel = input + 10; // Skip "LIST USER "
            list_user(sock, channel);
        } else if (strncmp(input, "JOIN", 4) == 0) {
            char *args = input + 5; // Skip "JOIN "
            char *channel = strtok(args, "/");
            char *room = strtok(NULL, "/");
            if (room == NULL) {
                join_channel(sock, username, channel, NULL);
            } else {
                join_room(sock, username, channel, room);
            }
        } else {
            fprintf(stderr, "Invalid command\n");
        }
    }
}
