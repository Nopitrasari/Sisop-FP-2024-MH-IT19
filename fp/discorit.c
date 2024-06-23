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
        close(sock);
        exit(EXIT_FAILURE);
    }

    if (strcmp(argv[1], "REGISTER") == 0 && argc == 5 && strcmp(argv[3], "-p") == 0) {
        register_user(sock, argv[2], argv[4]);
    } else if (strcmp(argv[1], "LOGIN") == 0 && argc == 5 && strcmp(argv[3], "-p") == 0) {
        login(sock, argv[2], argv[4]);
    } else {
        fprintf(stderr, "Invalid command\n");
        close(sock);
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
        snprintf(buffer, sizeof(buffer), "%s JOIN %s", username, channel);
    } else {
        snprintf(buffer, sizeof(buffer), "%s JOIN %s\nKey: %s", username, channel, key);
    }
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("%s\n", buffer);
}

void join_room(int sock, const char *username, const char *channel, const char *room) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "%s JOIN %s/%s", username, channel, room);
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
    char current_channel[1024] = {0};
    char current_room[1024] = {0};

    while (1) {
        if (strlen(current_channel) > 0) {
            if (strlen(current_room) > 0) {
                printf("[%s/%s/%s] ", username, current_channel, current_room);
            } else {
                printf("[%s/%s] ", username, current_channel);
            }
        } else {
            printf("[%s] ", username);
        }

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
                char *key = NULL;
                printf("Enter key (or press Enter to skip): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0'; // Remove newline character from input
                if (strlen(input) > 0) {
                    key = input;
                }
                join_channel(sock, username, channel, key);
                strcpy(current_channel, channel);
                memset(current_room, 0, sizeof(current_room));
            } else {
                join_room(sock, username, channel, room);
                strcpy(current_channel, channel);
                strcpy(current_room, room);
            }
        } else {
            fprintf(stderr, "Invalid command\n");
        }
    }
}
