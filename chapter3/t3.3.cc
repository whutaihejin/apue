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

TEST_F(OpenTest, TestAppend) {
  int fd = open(path_, O_APPEND);
  printf(" -- fd = %d, append\n", fd);
  close(fd);
}

TEST_F(OpenTest, TestCLOEXEC) {
  int fd = open(path_, O_CLOEXEC);
  printf("-- fd = %d, cloexec\n", fd);
  close(fd);
}

TEST_F(OpenTest, TestCreate) {
  int fd = open(path_, O_CREAT);
  printf("-- fd = %d, create\n", fd);
  close(fd);
}

TEST_F(OpenTest, TestDirectory) {
  int fd = open(path_, O_DIRECTORY);
  EXPECT_EQ(-1, fd);
  printf("-- fd = %d, directory\n", fd);
  close(fd);
   
  fd = open("/tmp/", O_DIRECTORY);
  printf("-- fd = %d, directory\n", fd);
  EXPECT_NE(-1, fd);
}

TEST_F(OpenTest, TestExclusive) {
  int fd = open(path_, O_CREAT | O_EXCL);
  printf("-- fd = %d, exclusive\n", fd);
  EXPECT_EQ(-1, fd); 
  close(fd);
  fd = open("/tmp/noexist.log", O_CREAT | O_EXCL);
  EXPECT_NE(-1, fd);
  printf("-- fd = %d, exclusive\n", fd);
  close(fd);
}

TEST_F(OpenTest, TestNofollow) {
  int fd = open(path_, O_NOFOLLOW);
  printf("-- fd = %d, no follow\n", fd);
  EXPECT_NE(-1, fd);
  close(fd);
  fd = open("/lib/librt.so.1", O_NOFOLLOW);
  printf("-- fd = %d, no follow\n", fd);
  EXPECT_EQ(-1, fd);
  close(fd);
}

TEST_F(OpenTest, TestSync) {
  int fd = open(path_, O_SYNC);
  printf("-- fd = %d, sync\n", fd);
  EXPECT_NE(-1, fd);
  close(fd);
}

TEST_F(OpenTest, TestTruncate) {
  int fd = open(path_, O_TRUNC);
  printf("-- fd = %d, truncate\n", fd);
  EXPECT_NE(-1, fd);
  close(fd);
}

TEST_F(OpenTest, TestOpenatAbsolute) {
  int fd = open(path_, O_RDONLY);
  printf("-- fd = %d, openat absolute\n", fd);
  EXPECT_NE(-1, fd);
  close(fd);
  fd = openat(fd, "/tmp/openat.log", O_CREAT | O_RDONLY);
  printf("-- fd = %d, openat obsolute\n", fd);
  EXPECT_NE(-1, fd);
  close(fd); 
}

TEST_F(OpenTest, TestOpenatRelative) {
  int fd = open("/tmp/", O_DIRECTORY);
  printf("-- fd = %d, openat relative 1\n", fd);
  EXPECT_NE(-1, fd);
  //close(fd);
  int at_fd = openat(fd, "openat_relative.log", O_RDONLY|O_CREAT);
  printf("-- fd = %d, openat relative 2\n", at_fd);
  EXPECT_NE(-1, at_fd);
  close(fd); 
}

TEST_F(OpenTest, TestOpenatcwd) {
  int fd = open("/tmp/", O_DIRECTORY);
  printf("-- fd = %d, openat relative 1\n", fd);
  EXPECT_NE(-1, fd);
  int at_fd = openat(AT_FDCWD, "openat_relative.log", O_RDONLY|O_CREAT);
  printf("-- fd = %d, openat relative 2\n", at_fd);
  EXPECT_NE(-1, at_fd);
  close(fd); 
}
int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
