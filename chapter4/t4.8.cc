#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("usage: t4.8 <pathname>\n");
    return -1;
  }
  if (access(argv[1], R_OK) < 0) {
    printf("access error for %s\n", argv[1]);
  } else {
    printf("read access ok\n");
  }
  if (open(argv[1], O_RDONLY) < 0) {
    printf("open error for %s\n", argv[1]);
    return -1;
  } else {
    printf("open for reading ok\n");
  }
  return 0;
}
