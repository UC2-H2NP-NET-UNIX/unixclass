#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char buffer[4096];
  

    // 127.0.0.1 に TCP 接続

    if (fork() == 0) {  // 子プロセス
        struct timeval start, end;
        long elapsed;
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(12345);
        inet_pton(AF_INET, "0.0.0.0", &(server_addr.sin_addr));
        bind(fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
        listen(fd, 5);
        int client_fd = accept(fd, NULL, NULL);

        gettimeofday(&start, NULL); // 開始時間を取得
        while(1){
            if(read(client_fd, buffer, sizeof(buffer)) < 1){
               break; 
            }
        }
        gettimeofday(&end, NULL); // 終了時間を取得
        close(client_fd); // 読み取り用ディスクリプタを閉じる
        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf("データ送受信にかかった時間: %ld マイクロ秒\n", elapsed);
        exit(0);
    } else { // 親プロセス
        sleep(1); // 子プロセスがソケットを作成するのを待つ
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(12345);
        inet_pton(AF_INET, "127.0.0.1", &(server_addr.sin_addr));
        if ( connect(fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ) {
            perror("connect");
            return 1;
        }

        for(int i=0; i < 1024*1024 ; i++){
            write(fd, "Hello, child process!", 21);
        }
        close(fd); // 書き込み用ディスクリプタを閉じる
    }
    wait(NULL); //子プロセスの終了を待つ
    return 0;
}