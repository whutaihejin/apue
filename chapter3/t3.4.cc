#include <stdio.h>
#include <fcntl.h>

#include "gtest/gtest.h"


TEST(OpenTest, TestCreate) {
  int fd = creat("/tmp/create.log", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  printf("-- fd = %d create\n", fd); 
  EXPECT_NE(-1, fd);
  close(fd); 
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
