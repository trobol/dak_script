#include <dak_script/reader.h>
#include <iostream>

	
#include <stdio.h>  /* defines FILENAME_MAX */

#ifdef __unix__
    #include <sys/mman.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
#endif

//https://stackoverflow.com/questions/17925051/fast-textfile-reading-in-c
namespace dak::script {

void Reader::open(std::string name) {
    char buff[FILENAME_MAX];
    getcwd(buff, FILENAME_MAX);
    std::cout << buff << std::endl;
    m_contents = map_file(name.c_str(), m_length);
}

void Reader::close() {
    unmap_file((void*)m_contents, m_length);
}


#if defined(__unix__)

    const char* Reader::map_file(const char* fname, size_t& length) {
        int fd = ::open(fname, O_RDONLY);
        
        if (fd == -1)
            std::cout << "failed to open: " << fname << "\n";

        // obtain file size
        struct stat sb;
        if (fstat(fd, &sb) == -1)
            std::cout << "fstat failed\n";

        length = sb.st_size;

    
        const char* addr = static_cast<const char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));
        if (addr == MAP_FAILED)
            std::cout << "mmap failed \n";

        ::close(fd);

        return addr;
      
    }
    void Reader::unmap_file(void* addr, size_t length) {
        munmap(addr, length);
    }

#elif defined(WIN32) || defined(_WIN32)
 //TODO: Windows memory mapping
    const char* Reader::map_file(const char* fname, size_t& length) {

    }

    void Reader::unmap_file(const char* file, size_t length) {

    }
   
#endif





}