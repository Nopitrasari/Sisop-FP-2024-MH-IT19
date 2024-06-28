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
void list_users(int sock, const char *channel) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST USER %s", channel);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("Users in channel %s:\n%s\n", channel, buffer);
}
```

Outputnya 

![WhatsApp Image 2024-06-28 at 23 55 55_52a8d417](https://github.com/Nopitrasari/Sisop-FP-2024-MH-IT19/assets/149749135/045c3294-9d9d-4c2e-ac56-6b4ae4ac09c9)


5. LIST ROOM

6. JOIN
