#include <unistd.h>    // read, write, close, lseek, STDOUT_FILENO
#include <fcntl.h>     // open, O_RDONLY
#include <stdio.h>     // perror
#include <stdlib.h>    // exit

#define N 9            // Количество строк для вывода

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

    // 3. Находим конец файла с помощью lseek
    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == -1) {
        perror("lseek");
        close(fd);
        exit(1);
    }

    // 4. Если файл пустой — ничего не выводим
    if (file_size == 0) {
        close(fd);
        return 0;
    }

    // 5. Читаем файл с конца, ищем N строк
    char buf[4096];
    off_t pos = file_size;
    int lines_found = 0;
    ssize_t bytes_read;
    int last_char_was_newline = 0;

    // Читаем блоками с конца к началу
    while (pos > 0 && lines_found <= N) {
        // Размер текущего блока для чтения
        size_t chunk_size = sizeof(buf);
        if (pos < chunk_size) {
            chunk_size = pos;
        }
        
        // Смещаем указатель для чтения блока
        pos -= chunk_size;
        if (lseek(fd, pos, SEEK_SET) == -1) {
            perror("lseek");
            close(fd);
            exit(1);
        }
        
        // Читаем блок
        bytes_read = read(fd, buf, chunk_size);
        if (bytes_read == -1) {
            perror("read");
            close(fd);
            exit(1);
        }
        
        // Анализируем блок с конца
        for (ssize_t i = bytes_read - 1; i >= 0; i--) {
            if (buf[i] == '\n') {
                lines_found++;
                if (lines_found == N + 1) {
                    // Нашли начало нужного куска
                    pos += i + 1; // Позиция после найденного перевода строки
                    goto print_from_pos;
                }
            }
        }
    }
    
print_from_pos:
    // 6. Выводим последние N строк (или весь файл, если строк меньше N)
    if (lseek(fd, pos, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        exit(1);
    }
    
    while ((bytes_read = read(fd, buf, sizeof(buf))) > 0) {
        if (write(STDOUT_FILENO, buf, bytes_read) == -1) {
            perror("write");
            close(fd);
            exit(1);
        }
    }
    
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(1);
    }

    // 7. Завершение
    close(fd);
    return 0;
}