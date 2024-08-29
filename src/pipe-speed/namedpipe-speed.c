#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char buffer[4096];
    if (fork() == 0) {
        // 子プロセス
        int cfd; //パイプのファイルディスクリプタ
        struct timeval start, end;
        long elapsed;   
        cfd = open("fifofile", O_RDONLY);
        gettimeofday(&start, NULL); // 開始時間を取得
        while(1){
            if(read(cfd, buffer, sizeof(buffer))< 1){
               break; 
            }
        }
        gettimeofday(&end, NULL); // 終了時間を取得
        close(cfd); // 読み取り用ディスクリプタを閉じる
        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf("データ送受信にかかった時間: %ld マイクロ秒\n", elapsed);
        exit(0);
    } else {
        // 親プロセス
        int pfd; //パイプのファイルディスクリプタ
        pfd = open("fifofile", O_WRONLY);
        for(int i=0; i < 1024*1024 ; i++){
            write(pfd, "Hello, child process!",21);
        }
        close(pfd);  //書き込み用ディスクリプタを閉じる
    }
    wait(NULL); //子プロセスの終了を待つ
    return 0;
}