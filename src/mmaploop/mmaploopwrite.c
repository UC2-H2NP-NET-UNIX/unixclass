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
  fd=open("mmap.dat",O_RDWR);
  fstat(fd, &st);
  p=mmap(0,st.st_size,(PROT_READ|PROT_WRITE),MAP_SHARED,fd,0);
  while(1) {
    char c=p[0];
    for(i=0; i < st.st_size-1; i++) {
      p[i]=p[(i+1)];
    }
    p[st.st_size-1]=c;
    msync(p,st.st_size,MS_SYNC);
    sleep(1);
  }
  close(fd);
}
