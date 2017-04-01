#include <stdio.h>
#include <fcntl.h>

#include "gtest/gtest.h"

class OpenTest : public testing::Test {

protected:
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
  printf("-- fd = %d read only\n", fd); 
  close(fd); 
}

TEST_F(OpenTest, TestWriteOnly) {
  int fd = open(path_, O_WRONLY);
  printf("-- fd = %d write only\n", fd); 
  close(fd); 
}

TEST_F(OpenTest, TestRDWR) {
  int fd = open(path_, O_RDWR);
  printf("-- fd = %d read writer\n", fd); 
  close(fd); 
}

TEST_F(OpenTest, TestEXEC) {
  int fd = open(path_, O_CREAT);
  printf("-- fd = %d, create\n", fd); 
  close(fd); 
}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
