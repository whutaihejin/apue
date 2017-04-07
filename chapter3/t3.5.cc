#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "gtest/gtest.h"

TEST(CloseTest, TestOpen) {
  int fd = open("/tmp/close.log", O_RDONLY|O_CREAT);
  printf("-- fd = %d open\n", fd);
  EXPECT_NE(-1, fd);
  int rst = close(fd);
  printf("-- rst = %d close\n", rst);
  EXPECT_NE(-1, rst);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
