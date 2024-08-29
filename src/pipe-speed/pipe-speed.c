#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>

int main() {
    int fd[2];
    char buffer[4096];
    
    pipe(fd);
    if (fork() == 0) {
        // 子プロセス
        struct timeval start, end;
        long elapsed;
        close(fd[1]); // 書き込み用ディスクリプタを閉じる
        gettimeofday(&start, NULL); // 開始時間を取得
        while(1){
            if(read(fd[0], buffer, sizeof(buffer)) < 1){
               break; 
            }
        }
        gettimeofday(&end, NULL); // 終了時間を取得
        close(fd[0]); // 読み取り用ディスクリプタを閉じる
        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
        printf("データ送受信にかかった時間: %ld マイクロ秒\n", elapsed);
    } else {
        // 親プロセス
        close(fd[0]); // 読み取り用ディスクリプタを閉じる
        for(int i=0; i < 1024*1024 ; i++){
            write(fd[1], "Hello, child process!", 21);
        }
        close(fd[1]); // 書き込み用ディスクリプタを閉じる
    }
    wait(NULL); //子プロセスの終了を待つ
    return 0;
}