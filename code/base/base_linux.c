#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

static u64 file_size_from_fd(i32 fd) {
  struct stat stat;
  fstat(fd, &stat);
  return stat.st_size;
}

u8* read_file(Arena* arena, const char* file_path, u64* buf_len, b8 null_terminated) {
  i32 fd = open(file_path, O_RDONLY);
  Assert((fd > 0) && "file not found");

  u64 file_size = file_size_from_fd(fd);

  u8* buf;
  u64 size = 0;

  if (null_terminated) {
    buf            = arena_push_array(arena, u8, file_size + 1);
    size           = file_size + 1;
    buf[file_size] = '\0';
  }
  else {
    buf  = arena_push_array(arena, u8, file_size);
    size = file_size;
  }

  u64 read_size = read(fd, buf, file_size);
  Assert(read_size == file_size);

  if (buf_len != NULL) {
    *buf_len = size;
  }

  return buf;
}
