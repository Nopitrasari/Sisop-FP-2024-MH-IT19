#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

typedef struct {
    int sock;
    struct sockaddr_in address;
    int addr_len;
    char username[50];
} client_t;

client_t *clients[MAX_CLIENTS];
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

// Function declarations
void *handle_client(void *arg);
void register_user(int sock, const char *username, const char *password);
void login_user(int sock, const char *username, const char *password);
void join_channel(int sock, const char *username, const char *channel, const char *key);
void join_room(int sock, const char *username, const char *channel, const char *room);
void list_channels(int sock, const char *username);
void list_rooms(int sock, const char *username, const char *channel);
void list_users(int sock, const char *username, const char *channel);

int main() {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    pthread_t tid;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    if (listen(server_sock, 10) < 0) {
        perror("listen");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    printf("Server started on port %d\n", PORT);

    while (1) {
        socklen_t client_len = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);

        if (client_sock < 0) {
            perror("accept");
            continue;
        }

        client_t *client = (client_t *)malloc(sizeof(client_t));
        client->sock = client_sock;
        client->address = client_addr;
        client->addr_len = client_len;

        pthread_create(&tid, NULL, handle_client, (void *)client);
    }

    return 0;
}

void *handle_client(void *arg) {
    client_t *client = (client_t *)arg;
    char buffer[BUFFER_SIZE];
    int len;

    while ((len = recv(client->sock, buffer, sizeof(buffer), 0)) > 0) {
        buffer[len] = '\0';

        if (strncmp(buffer, "REGISTER", 8) == 0) {
            char username[50], password[50];
            sscanf(buffer, "REGISTER %s -p %s", username, password);
            register_user(client->sock, username, password);
        } else if (strncmp(buffer, "LOGIN", 5) == 0) {
            char username[50], password[50];
            sscanf(buffer, "LOGIN %s -p %s", username, password);
            strncpy(client->username, username, sizeof(client->username));
            login_user(client->sock, username, password);
        } else if (strncmp(buffer, "JOIN", 4) == 0) {
            char channel[50], key[50];
            if (sscanf(buffer, "JOIN %s Key: %s", channel, key) == 2) {
                join_channel(client->sock, client->username, channel, key);
            } else if (sscanf(buffer, "JOIN %s", channel) == 1) {
                join_channel(client->sock, client->username, channel, NULL);
            } else if (sscanf(buffer, "JOIN %s/%s", channel, key) == 2) {
                join_room(client->sock, client->username, channel, key);
            }
        } else if (strncmp(buffer, "LIST CHANNEL", 12) == 0) {
            list_channels(client->sock, client->username);
        } else if (strncmp(buffer, "LIST ROOM", 9) == 0) {
            char channel[50];
            sscanf(buffer, "LIST ROOM %s", channel);
            list_rooms(client->sock, client->username, channel);
        } else if (strncmp(buffer, "LIST USER", 9) == 0) {
            char channel[50];
            sscanf(buffer, "LIST USER %s", channel);
            list_users(client->sock, client->username, channel);
        }
    }

    close(client->sock);
    free(client);
    return NULL;
}

void register_user(int sock, const char *username, const char *password) {
    // This function should save the username and password to a database or file.
    // For simplicity, we assume the registration is always successful.
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "User %s registered successfully.", username);
    send(sock, buffer, strlen(buffer), 0);
}

void login_user(int sock, const char *username, const char *password) {
    // This function should validate the username and password against a database or file.
    // For simplicity, we assume the login is always successful.
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "User %s logged in successfully.", username);
    send(sock, buffer, strlen(buffer), 0);
}

void join_channel(int sock, const char *username, const char *channel, const char *key) {
    // This function should handle joining a channel. If a key is required, it should validate the key.
    // For simplicity, we assume the join is always successful.
    char buffer[BUFFER_SIZE];
    if (key == NULL) {
        snprintf(buffer, sizeof(buffer), "[%s] JOIN %s\n[%s/%s]", username, channel, username, channel);
    } else {
        snprintf(buffer, sizeof(buffer), "[%s] JOIN %s\nKey: %s\n[%s/%s]", username, channel, key, username, channel);
    }
    send(sock, buffer, strlen(buffer), 0);
}

void join_room(int sock, const char *username, const char *channel, const char *room) {
    // This function should handle joining a room within a channel.
    // For simplicity, we assume the join is always successful.
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "[%s/%s] JOIN %s\n[%s/%s/%s]", username, channel, room, username, channel, room);
    send(sock, buffer, strlen(buffer), 0);
}

void list_channels(int sock, const char *username) {
    // This function should return a list of available channels.
    // For simplicity, we use a static list of channels.
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "Available channels: care, bancar, qurb");
    send(sock, buffer, strlen(buffer), 0);
}

void list_rooms(int sock, const char *username, const char *channel) {
    // This function should return a list of rooms within a channel.
    // For simplicity, we use a static list of rooms.
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "Available rooms in channel %s: urban, banru, runab", channel);
    send(sock, buffer, strlen(buffer), 0);
}

void list_users(int sock, const char *username, const char *channel) {
    // This function should return a list of users within a channel.
    // For simplicity, we use a static list of users.
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "Users in channel %s: root, admin, qurbancare", channel);
    send(sock, buffer, strlen(buffer), 0);
}
