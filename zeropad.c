#include <stddef.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

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

    char *lines[] =
        {"Lorem ipsum dolor sit amet, consectetur adipiscing elit.",
         "Duis ac nulla vel urna auctor convallis et id urna.",
         "Donec consectetur erat et pulvinar molestie.",
         "Maecenas sit amet justo placerat, varius mauris congue, egestas",
         "lectus.",
         "Phasellus vitae lorem eget enim auctor egestas vel id nulla.",
         "Pellentesque iaculis libero at nunc ultrices, sit amet aliquet diam ",
         "faucibus.",
         "Nam vulputate felis suscipit mauris sollicitudin tristique.",
         "Quisque porttitor dolor eu augue hendrerit, et cursus urna ",
         "elementum.",
         "Pellentesque lacinia neque sed lobortis aliquam.",
         "Quisque rutrum arcu at tellus vulputate varius.",
         "Morbi at erat et nisi mollis finibus eget eu felis.",
         "Donec commodo felis a volutpat aliquam.",
         "Proin eu ante sed arcu ultricies laoreet et at massa.",
         "Duis at enim varius, ullamcorper libero eget, efficitur enim.",
         "In convallis odio quis quam imperdiet, ut fermentum orci suscipit.",
         "Quisque malesuada ipsum id placerat ultrices.",
         "Suspendisse blandit risus vel augue porttitor, id placerat ex ",
         "tincidunt.",
         "Phasellus eget dolor et tortor consequat sagittis.",
         "Fusce accumsan risus sit amet iaculis imperdiet.",
         "Etiam id arcu rhoncus, laoreet dolor vel, porttitor urna.",
         "Proin congue arcu pretium, laoreet dui eu, accumsan tortor.",
         "Nulla quis dui id metus commodo iaculis.",
         "Curabitur semper mi eu metus condimentum malesuada a ut arcu.",
         "Vestibulum euismod nibh posuere tellus tempus, ut vestibulum mauris ",
         "egestas.",
         "Fusce a massa scelerisque dui aliquam mollis.",
         "Maecenas vehicula justo a sapien iaculis, vel tristique ante ornare.",
         "Nam commodo libero ac erat sagittis, a auctor mauris malesuada.",
         "Nullam sagittis eros ut mi venenatis, sed iaculis enim maximus.",
         "Fusce at magna eget diam pulvinar mattis quis ut nibh.",
         "Integer fringilla nulla at tincidunt commodo.",
         "Nam ut nulla ornare, pellentesque est ut, tempor est.",
         "Pellentesque quis tortor ullamcorper, convallis libero nec, viverra ",
         "eros.",
         "Quisque luctus risus non lobortis iaculis.",
         "Integer eget risus nec justo finibus semper in id eros.",
         "Donec vitae massa vel ligula porttitor tincidunt ac sit amet est.",
         "Aliquam molestie turpis vitae suscipit condimentum.",
         "Nullam dapibus nibh sit amet sem tempor scelerisque.",
         "Quisque vel leo sagittis, semper metus ut, luctus nunc.",
         "Praesent sollicitudin mi tincidunt massa tempor, nec efficitur enim ",
         "pulvinar.",
         "Vestibulum pulvinar est quis tortor dapibus imperdiet.",
         "Mauris vestibulum ligula ac velit bibendum lacinia.",
         "Nullam ac libero quis mauris ullamcorper vulputate nec in enim.",
         "Duis consequat erat eget tristique ultrices.",
         "Aliquam sit amet neque ut libero semper suscipit.",
         "Quisque egestas libero vel consequat cursus.",
         "Nullam posuere purus eu nunc pretium rhoncus.",
         "Nullam sed turpis commodo, pulvinar dui sed, feugiat diam.",
         "Donec consectetur erat ac vestibulum hendrerit.",
         "Cras eu leo in lacus tincidunt luctus eu in felis.",
         "Phasellus molestie massa ac lectus maximus, sit amet aliquet nibh ",
         "tincidunt.",
         "Phasellus tristique felis eget nisl dictum ullamcorper.",
         "Proin id libero iaculis, imperdiet ex quis, fermentum tortor.",
         "Aenean elementum nibh id leo maximus accumsan.",
         "Suspendisse at tortor et lectus convallis tempor vel in neque.",
         "Nunc mollis ante ut semper dignissim.",
         "In id purus vehicula, luctus nibh eu, condimentum arcu.",
         "Suspendisse lacinia purus vitae libero malesuada malesuada.",
         "Morbi lacinia mi et odio tristique, eget rhoncus tellus molestie.",
         "Cras vitae justo quis elit interdum finibus.",
         "Nam ut lacus vitae eros auctor fringilla.",
         "Curabitur convallis justo vel turpis mollis, non efficitur ex ",
         "porttitor.",
         "Donec lacinia elit non purus fringilla sodales.",
         "Maecenas eu quam ac elit molestie interdum.",
         "Cras dignissim mi pulvinar lectus venenatis mollis.",
         "Nullam volutpat tortor eu erat posuere placerat.",
         "Integer vitae eros vel eros sagittis eleifend ut in nulla.",
         "Nulla egestas massa vitae facilisis cursus.",
         "Nam ultricies magna scelerisque eros mollis, at mattis lorem ",
         "faucibus.",
         "Vivamus in mi eget est fermentum condimentum.",
         "Aenean convallis augue id ex tristique, at accumsan metus suscipit.",
         "In id mi euismod, dictum quam quis, pretium neque.",
         "Ut suscipit dui nec consequat cursus.",
         "Nunc convallis neque quis iaculis ultricies.",
         "Integer non dolor efficitur, accumsan diam at, venenatis purus.",
         "Integer suscipit eros ut urna accumsan, quis condimentum ex ",
         "pulvinar.",
         "Quisque tempus arcu a diam maximus elementum.",
         "Nunc euismod massa nec dolor feugiat viverra.",
         "Sed vitae ipsum a erat mattis euismod ac sagittis lacus.",
         "Etiam pellentesque lectus ut diam facilisis, vel placerat felis ",
         "vehicula.",
         "Duis non erat laoreet, rhoncus tortor a, mollis sem.",
         "Nam ac mauris sollicitudin, cursus massa et, placerat lectus.",
         "Nulla pharetra nunc laoreet velit vestibulum accumsan.",
         "Suspendisse sit amet justo ornare, placerat justo sit amet, ",
         "tincidunt augue.",
         "Pellentesque ultricies mi nec quam tincidunt maximus nec sit amet ",
         "sem.",
         "Maecenas ultricies ipsum consequat sodales convallis.",
         "Aliquam consequat turpis a accumsan molestie.",
         "Mauris a orci scelerisque orci egestas tristique.",
         "Integer lobortis purus in orci ullamcorper, ut iaculis turpis ",
         "convallis.",
         "Proin laoreet lectus et nunc facilisis molestie at vehicula mauris.",
         "Aenean eget eros condimentum, interdum metus mollis, volutpat felis.",
         "In sit amet libero et justo tincidunt ullamcorper.",
         "Fusce id ligula a ante porttitor ultrices ac vitae magna.",
         "Sed molestie justo et viverra facilisis.",
         "Ut et ex eu enim commodo viverra sit amet ac felis.",
         "Phasellus sed magna id purus luctus mollis.",
         "Sed non libero eget eros porta posuere vestibulum et libero.",
         "Mauris non est fringilla, dignissim justo laoreet, lobortis urna.",
         "Nulla maximus ligula ac nulla volutpat porttitor ut aliquam orci.",
         "Nullam ullamcorper mauris vitae lacinia fermentum.",
         "Nam tincidunt nisi vitae fermentum lobortis.",
         "Duis sagittis nibh at urna iaculis porta.",
         "Donec id massa et justo interdum ultricies id a arcu.",
         "Nulla congue urna vel lacus mattis, et pretium libero sollicitudin.",
         "Mauris eget justo a arcu maximus commodo at ut nibh.",
         "Pellentesque mollis erat vitae turpis imperdiet, et aliquam ex ",
         "sagittis.",
         "Nulla quis nisi sagittis, varius nunc sit amet, ultricies massa."};

    int numLines = sizeof(lines) / sizeof(lines[0]);

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
    printf("numLines: %d\n", numLines);

    // Cursor position & row offset
    int cx = 0;
    int cy = 0;
    int lastCx = 0;
    int rowOffset = 0;

    char screenBuf[16384];
    int screenLen = 0;    

    char c;
    while (1) {
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        if (bytesRead == 0)
            continue;

        screenLen = 0;

        // Clear the screen and move cursor to top left before printing
        // something else
        memcpy(screenBuf, "\x1b[2J", 4);
        memcpy(screenBuf + 4, "\x1b[H", 3);
        screenLen = 7;

        int rowsDrawn = 0;
        for (int i = rowOffset; i < rowOffset + ws.ws_row; i++) {
            if (i > numLines - 1)
                break;

            if (rowsDrawn == ws.ws_row - 1)
                break;

            size_t lineLen = strlen(lines[i]);

            memcpy(screenBuf + screenLen, lines[i], lineLen);
            memcpy(screenBuf + screenLen + lineLen, "\r\n", 2);
            screenLen += lineLen + 2;

            rowsDrawn++;
        }

        if (c == '\x1b') {
            read(STDIN_FILENO, &c, 1);

            if (c == '[') {
                read(STDIN_FILENO, &c, 1);
                size_t currentLineLen;

                switch (c) {
                case 'A': // ARROW UP
                    if (cy > 0)
                        cy--;
                    else if (rowOffset > 0)
                        rowOffset--;

                    currentLineLen = strlen(lines[cy]);
                    if (cx > currentLineLen || lastCx > currentLineLen)
                        cx = currentLineLen;
                    else
                        cx = lastCx;
                    break;
                case 'B': // ARROW DOWN
                    if (cy < ws.ws_row - 1)
                        cy++;
                    else if (rowOffset + ws.ws_row - 1 < numLines)
                        rowOffset++;

                    currentLineLen = strlen(lines[cy]);
                    if (cx > currentLineLen || lastCx > currentLineLen)
                        cx = currentLineLen;
                    else
                        cx = lastCx;
                    break;
                case 'C': // ARROW RIGHT
                    currentLineLen = strlen(lines[cy]);
                    if (cx < ws.ws_col - 1 && cx < currentLineLen) {
                        cx++;
                        if (cx > lastCx)
                            lastCx = cx;
                    }
                    break;
                case 'D': // ARROW LEFT
                    currentLineLen = strlen(lines[cy]);
                    if (cx > 0) {
                        cx--;
                        if (cx < lastCx)
                            lastCx = cx;
                    }
                    break;
                }
            } else {
                // printf("ESCAPE\r\n");
            }
        } else {
            // Quit
            if (c == 'q')
                break;

            // printf("key: %c (%d)\r\n", c, (int)bytesRead);
        }

        // Cursor
        char cursorBuf[32];

        // Cursor debug
        // printf("%d,%d,%d (max: %d)\r\n", cx, lastCx, rowOffset, (int)strlen(lines[cy]));
        char cursorDebug[50];
        int debug = snprintf(cursorDebug, sizeof(cursorDebug), "\x1b[%d;%dH%d,%d,%d (max: %d)", cy + 1, cx + 1, cx, lastCx, rowOffset, (int)strlen(lines[cy]));

        int cursorLen = snprintf(cursorBuf, sizeof(cursorBuf), "\x1b[%d;%dH", cy + 1, cx + 1);

        // memcpy(screenBuf + screenLen, cursorBuf, cursorLen); 
        // screenLen += cursorLen;
        // TEMP:
        memcpy(screenBuf + screenLen, cursorDebug, debug);
        screenLen += debug;

        write(STDOUT_FILENO, screenBuf, screenLen);
    }

    // Cleanly reset the terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);

    return 0;
}
