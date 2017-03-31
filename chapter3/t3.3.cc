#include <stdio.h>
#include <fcntl.h>

#include "gtest/gtest.h"

class OpenTest : public testing::Test {

public:
  OpenTest(): fd_(-1), path_("/tmp/apue.log") {}

  virtual void SetUp() {
    fd_ = open(path_, O_RDONLY | O_CREAT);
    printf("-- %d--> create %s\n", fd_, path_);
  }

  virtual void TearDown() {
    int r = close(fd_);
    printf("-- %d--> close %s\n", r, path_);
  }
  
  int fd_;
  const char* path_;
};

TEST_F(OpenTest, TestReadOnly) {
  int fd = open(path_, O_RDONLY);
  printf("-- fd = %d\n", fd); 
  fd = open(path_, O_RDONLY);
  printf("-- fd = %d\n", fd); 
}

TEST_F(OpenTest, TestWriteOnly) {
  int fd = open(path_, O_RDONLY);
  printf("-- fd = %d\n", fd); 
  fd = open(path_, O_RDONLY);
  printf("-- fd = %d\n", fd); 
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
