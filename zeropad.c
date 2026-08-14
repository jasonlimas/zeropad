#include <stddef.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./zeropad <filename>\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("%s\n", "Error reading file");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }

    fclose(fp);

    struct termios orig_termios;
    tcgetattr(STDIN_FILENO, &orig_termios);

    struct termios raw = orig_termios;
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    // Terminal size detection
    printf("terminal size: %d, %d\n", (int)ws.ws_row, (int)ws.ws_col);

    char c;
    while (1) {
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        if (bytesRead == 0) continue;

        // Clear the screen and move cursor to top left before printing something else
        write(STDOUT_FILENO, "\x1b[2J", 4);
        write(STDOUT_FILENO, "\x1b[H", 3);

        if (c == '\x1b') {
            read(STDIN_FILENO, &c, 1);

            if (c == '[') {
                read(STDIN_FILENO, &c, 1);
                switch (c) {
                    case 'A':
                        printf("ARROW UP\r\n");
                        break;
                    case 'B':
                        printf("ARROW DOWN\r\n");
                        break;
                    case 'C':
                        printf("ARROW RIGHT\r\n");
                        break;
                    case 'D':
                        printf("ARROW LEFT\r\n");
                        break;
                }
            }
            else {
                printf("ESCAPE\r\n");
            }
        }
        else {
            // Quit
            if (c == 'q') break;

            printf("key: %c (%d)\r\n", c, (int)bytesRead);
        }
    }
    
    // Cleanly reset the terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); 

    return 0;
}
