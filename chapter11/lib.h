#ifndef LIB_H_
#define LIB_H_

#include <stdio.h>
inline void err_exit(int err, const char* prefix) {
  printf("%s err %d\n", prefix, err);
}

#endif
