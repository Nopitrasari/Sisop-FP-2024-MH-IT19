# Sisop-FP-2024-MH-IT19

Anggota Kelompok IT19 :

1. Riskiyatul Nur Oktarani (5027231013)
2. Aswalia Novitriasari (5027231012)
3. Benjamin Khawarizmi Habibi (5027231078)

# DISCORT IT

1. REGISTER

berikut adalah kode untuk register dalam discortit.c
```
void register_user(int sock, const char *username, const char *password) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "REGISTER %s -p %s", username, password);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("%s\n", buffer);
}
```

dibawah ini adalah kode register dalam server.c
```
void register_user(int sock, const char *username, const char *password) {
    // This function should save the username and password to a database or file.
    // For simplicity, we assume the registration is always successful.
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "User %s registered successfully.", username);
    send(sock, buffer, strlen(buffer), 0);
}
```

dan ini untuk dokumentasi ketika kita bisa register

![WhatsApp Image 2024-06-28 at 20 16 01_4db0f2d4](https://github.com/Nopitrasari/Sisop-FP-2024-MH-IT19/assets/151911480/6c98ee17-f98c-46a3-bf9f-49e437de48ee)


2. LOGIN

dibawah ini adalah kode untuk login dalam file discortit.c
```
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
```

sedangkan ini adalah kode untuk login dalam file server.c
```
void login_user(int sock, const char *username, const char *password) {
    // This function should validate the username and password against a database or file.
    // For simplicity, we assume the login is always successful.
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "User %s logged in successfully.", username);
    send(sock, buffer, strlen(buffer), 0);
}
```
dibawah ini adalah jika kita sudah berhasil login

![WhatsApp Image 2024-06-28 at 20 16 49_13b3d06c](https://github.com/Nopitrasari/Sisop-FP-2024-MH-IT19/assets/151911480/47f376ad-e09d-43e8-b582-c2db25521f7d)

3. LIST CHANNEL

untuk kode list channel dalam discordit.c
```
void list_channel(int sock) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST CHANNEL");
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("%s\n", buffer);
}
```

dibawah ini adalah kode untuk list channel dalam server.c
```
void list_channels(int sock, const char *username) {
    // This function should return a list of available channels.
    // For simplicity, we use a static list of channels.
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "Available channels: care, bancar, qurb");
    send(sock, buffer, strlen(buffer), 0);
}

```

dan ini untuk kode list channel dalam monitor.c
```
void list_channels(int sock) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST CHANNEL");
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("Channels:\n%s\n", buffer);
}
```

ini untuk dokumentasi list channel

![WhatsApp Image 2024-06-28 at 20 17 03_adf01b01](https://github.com/Nopitrasari/Sisop-FP-2024-MH-IT19/assets/151911480/b44e73da-aa19-4b0a-9e13-72b6127cba1d)

4. LIST USER

Untuk membuat list user dari program discorit.c 
```
void list_user(int sock, const char *channel) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST USER %s", channel);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("Users list:\n%s\n", channel, buffer);
}
```
untuk program dari server.c
```
void list_users(int sock, const char *username, const char *channel) {
    // This function should return a list of users within a channel.
    // For simplicity, we use a static list of users.
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "Users in channel %s: root, admin, qurbancare", channel);
    send(sock, buffer, strlen(buffer), 0);
}
```
untuk program dari monitor.c
```
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
```



5. LIST ROOM
6. JOIN
