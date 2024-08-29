#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
int main(void)
{
  int fd;
  struct stat st;
  char *p;
  int i;
  fd=open("mmap.dat",O_RDWR); // mmapで使うファイルをオープン
  fstat(fd, &st); // ファイルサイズを取得
  // メモリマップ
  p=mmap(0,st.st_size,(PROT_READ|PROT_WRITE),MAP_SHARED,fd,0);
  while(1) {
    char c=p[0];
    for(i=0; i < st.st_size-1; i++) {
      p[i]=p[(i+1)]; // メモリマップされた領域を表示
    }
    p[st.st_size-1]=c; // 文字をずらす
    msync(p,st.st_size,MS_SYNC); // ファイルに書き込み
    sleep(1);
  }
  close(fd);
}
