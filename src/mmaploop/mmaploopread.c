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
    for(i=0; i < st.st_size; i++) {
      printf("[%c]",p[i]);
    }
    printf("\n");
    sleep(1);
  }
  close(fd);
}
