#include <dak_script/file_descriptor.h>

#ifdef __unix__
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#elif defined(WIN32) || defined(_WIN32)
#include <Windows.h>
#endif

namespace dak_script {
#ifdef __unix__

file_descriptor file_open(std::string path, file_mode mode) {
  return file_open(path.c_str(), mode);
}

file_descriptor file_open(const char *path, file_mode mode) {
  return ::open(path, O_RDONLY);
}

int file_close(file_descriptor fd) { return ::close(fd); }

size_t len(file_descriptor fd) {
  if (fd == -1)
    return 0;
  struct stat sb;
  if (fstat(fd, &sb) == -1)
    return 0;

  return sb.st_size;
}

#elif defined(WIN32) || defined(_WIN32)

file_descriptor file_open(std::string path, file_mode mode = READ_ONLY) {
  return file_open(path.c_str());
}

file_descriptor file_open(std::string path, file_mode mode = READ_ONLY) {
  return ::open(path.c_str(), O_RDONLY);
}

void handle_close(file_descriptor handle);

size_t len(file_descriptor handle);

#endif

} // namespace dak_script
