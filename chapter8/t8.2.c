#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  pid_t pid = getpid();
  pid_t ppid = getppid();
  uid_t uid = getuid();
  uid_t euid = geteuid();
  gid_t gid = getgid();
  gid_t egid = getegid();
  printf("pid = %ul, ppid = %ul, uid = %ul, euid = %ul, gid = %ul, egid = %ul\n",
        pid, ppid, uid, euid, gid, egid);
  return 0;
}
