#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void local_fd_close(int *fd)
{
    if (*fd != -1) {
        close(*fd);
        *fd = -1;
    }
}

static void local_free_ptr(void **ptr)
{
    free(*ptr);
    *ptr = 0;
}

char *native_file_read_all(const char *file_path, size_t *size)
{
    struct stat stats = {0};
    int fd __attribute__ ((cleanup (local_fd_close))) = -1;
    void *tmp __attribute__ ((cleanup (local_free_ptr))) = 0;
    char *result;

    if (!file_path || stat(file_path, &stats) == -1)
        return 0;
    tmp = malloc(stats.st_size);
    if (!tmp)
        return 0;
    fd = open(file_path, O_RDONLY);
    if (fd == -1 || read(fd, tmp, stats.st_size) != stats.st_size)
        return 0;
    result = tmp;
    tmp = 0;
    if (size)
        *size = stats.st_size;
    return result;
}

char *file_read_all(const char *file_path, size_t *size)
__attribute__ ((weak, alias ("native_file_read_all")));