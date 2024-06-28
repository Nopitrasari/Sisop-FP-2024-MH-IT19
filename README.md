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

note tambahan untuk tulisan "Users in channel aji123" pada outputnya pada seharusnya hanya tulisan "Users" saja dan hanya menampilkan USER yang sudah ada, dikarenakan kurangnya ketelitian kami dalam tulisannya maka jadi seperti begitu.  

5. LIST ROOM
Fungsi ini mengirimkan pesan "LIST ROOM" ke server menggunakan socket sock, kemudian menerima respons dari server dan mencetak daftar ruangan dalam format yang sesuai ke layar.
Untuk program membuat list room dari program discorit.c ialah 
```
void list_room(int sock, const char *channel) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST ROOM %s", channel);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("%s\n", buffer);
}
```

untuk program dari server.c ialah 

```
void list_rooms(int sock, const char *channel) {
    // This function should return a list of rooms within a channel.
    // For simplicity, we use a static list of rooms.
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "Available rooms in channel %s: urban, banru, runab", channel);
    send(sock, buffer, strlen(buffer), 0);
}
```
Untuk program dari monitor.c ialah 
```
void list_rooms(int sock, const char *channel) {
    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "LIST ROOM %s", channel);
    send(sock, buffer, strlen(buffer), 0);
    
    memset(buffer, 0, sizeof(buffer));
    recv(sock, buffer, sizeof(buffer), 0);
    
    printf("Rooms in channel %s:\n%s\n", channel, buffer);
}
```

Output yang dihasilkan : 

![WhatsApp Image 2024-06-28 at 23 59 28_7a9efaf6](https://github.com/Nopitrasari/Sisop-FP-2024-MH-IT19/assets/149749135/7b7ccf04-d1ef-4e16-a309-74e6a825799c)


6. JOIN

Untuk kasus Join channel ataupunn join room dari kelompok kami masih belum bisa mengatasi kendala yang  ada dikarenakan kurangnya kemampuan kami. jadi, untuk programnya seperti ini : 

Dari program server.c : 
```
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
```

Untuk program discorit.c :
```
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
```

Untuk progarm monitor.c :
```
else if (strncmp(input, "JOIN", 4) == 0) {
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
}
```
Outputnya :

<img width="499" alt="image" src="https://github.com/Nopitrasari/Sisop-FP-2024-MH-IT19/assets/149749135/0fd430f4-caf3-4fc2-b31c-3c28cc2cd999">
Dengan mematikan port 8080

maka dari program kita sendiri baru bisa ko join channel, setelah mengalami stuck untuk join :

<img width="618" alt="image" src="https://github.com/Nopitrasari/Sisop-FP-2024-MH-IT19/assets/149749135/7a1f3e67-cbe5-4dbd-98fa-ebe2dc6dd719">

Dengan begitu program kami pun kembali keluar dari awal


dalam monitor.c ini perintah join akan otomatis terkirim langsung ke server melalui send(sock, input, strlen(input), kemudian client atau pengguna tinggal memasukkan key(bila memang perlu) dan mengirim ke server. Setelah mengirim ke server, cleint atau pengguna akan menerima respon yang akan ditampilkan "printf("%s\n", buffer);" 

# KENDALA 
1. Dikarenakan kurangnya pengetahuan terkait socket programming dari kelompok kami agak cukup bingung dalam pengimplementasiannya serta bagaimana membauat chat history atau rekaman chat di dalam room yang ada. 
2. Terkait dengan fungsi Join dari kelompok kami belum ada hasil yang bagus, dan ada terkait maslaah socket

# Tambahan 
Untuk Final Project sisop ini tugas yang diberikan mirip seperti membuat konsep SNS Server-Client dengan metode socket programming melalui bahasa C, sehingga perlu pengetahun sedikit terkait socket programming. Selain itu, dengan membuat Kosep Server-Client dengan tambahan Create, Update, Read(list), dan Delete pada pada channel maupun room yang ada sedikit rumit disertai penambahan jejak percakapan yang ada, yang mana mesti kami monitor. Terakhir, kita juga diminta untuk membuat hak Root, chennal, room bisa berbeda-beda dan diminta juga agar bisa keluar dari discorit tersebut. 

Sekian, Terima kasih untuk Para Asisten Sistem Operasi pada semester 2 kali ini :) 
Semoga lancar perkuliahannya hingga lulus 
