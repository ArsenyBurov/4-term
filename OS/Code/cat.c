#include <unistd.h>    // read, write, close, STDOUT_FILENO
#include <fcntl.h>     // open, O_RDONLY
#include <stdio.h>     // perror
#include <stdlib.h>    // exit

int main(int argc, char *argv[]) {
    // 1. Проверка аргументов
    if (argc != 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        exit(1);
    }

    // 2. Открытие файла
    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // 3. Цикл чтения-записи
    char buf[4096];
    ssize_t n;
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        write(STDOUT_FILENO, buf, n); // Пишем ровно прочитанное
    }

    // 4. Проверка ошибки чтения
    if (n < 0) {
        perror("read");
        close(fd);
        exit(1);
    }

    // 5. Завершение
    close(fd);
    return 0;
}
