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
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);

    struct winsize ws;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

    // Terminal size detection
    printf("terminal size: %d, %d\n", (int)ws.ws_row, (int)ws.ws_col);

    int c;
    while (1) {
        c = getchar();

        // Clear the screen and move cursor to top left before printing something else
        write(STDOUT_FILENO, "\x1b[2J", 4);
        write(STDOUT_FILENO, "\x1b[H", 3);

        printf("key: %c (%d)\r\n", c, c);

        // Quit
        if (c == 'q') break;
    }
    
    // Cleanly reset the terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios); 

    return 0;
}
