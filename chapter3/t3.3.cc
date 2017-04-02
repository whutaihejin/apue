#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "gtest/gtest.h"

class OpenTest : public testing::Test {

protected:
  OpenTest(): fd_(-1), path_("/tmp/apue.log") {}

  virtual void SetUp() {
    fd_ = open(path_, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    printf("-- %d--> create %s\n", fd_, path_);
    int r = close(fd_);
    printf("-- %d--> close %s\n", r, path_);
  }

  virtual void TearDown() {
    printf("-- --> tear down ...\n");
  }
  
  int fd_;
  const char* path_;
};

TEST_F(OpenTest, TestReadOnly) {
  int fd = open(path_, O_RDONLY);
  printf("-- fd = %d read only\n", fd); 
  EXPECT_EQ(3, fd);
  close(fd); 
}

TEST_F(OpenTest, TestWriteOnly) {
  int fd = open(path_, O_WRONLY);
  printf("-- fd = %d write only\n", fd); 
  EXPECT_EQ(3, fd);
  close(fd); 
}

TEST_F(OpenTest, TestRDWR) {
  int fd = open(path_, O_RDWR);
  printf("-- fd = %d read write\n", fd); 
  EXPECT_EQ(3, fd);
  close(fd); 
}

// opensuse not surpport the O_EXEC option.
//TEST_F(OpenTest, TestEXEC) {
//  int fd = open(path_, O_EXEC);
//  printf("-- fd = %d, exec\n", fd); 
//  close(fd); 
//}

// opensuse no surport the O_SEARCH option.
//TEST_F(OpenTest, TestSearch) {
//  int fd = open(path_, O_SEARCH);
//  printf("-- fd = %d, search\n", fd); 
//  close(fd); 
//}

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
