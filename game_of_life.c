#include <stdio.h>
#include <ncurses.h>

// game options
#define ROWS 25
#define COLS 80
#define UPDATE_RATE 100  // milliseconds
#define MIN_SPEED 5000
#define MAX_SPEED 10

// graphics
#define LIFE 'o'
#define EMPTY ' '
#define WALL '|'
#define CB '-'  // CB - Ceiling bottom
#define CROSS '+'

#define AVG_MSG_WIDTH 38  // average final message length for calculation

void new_generation(char field[ROWS][COLS], char result_arr[ROWS][COLS]);  // writes new gen in arr
int is_over(char current[ROWS][COLS], char previous[ROWS][COLS]);  // checks if it's end of game
void read_from_input(char result[ROWS][COLS]);  // reading from stdin
void swap_arrays(char first[ROWS][COLS], char second[ROWS][COLS]);  // swap two static arrays
void draw_field(char field[ROWS][COLS]);  // draws main field
void init_empty(char field[ROWS][COLS]);  // inits arr with EMPTY
void await_input(int* over, int* update_rate);  // handles keyboard input
void gameover_message(int count, int y, int x);  // final message print
void handle_error();

int main() {
    char current_gen[ROWS][COLS];  // array for current generation
    char next_gen[ROWS][COLS];  // array for next generation
    int update_rate = UPDATE_RATE;  // start update rate is equal the one in #define

    init_empty(current_gen);  // inits with EMPTY symbol
    init_empty(next_gen);  // inits with EMPTY symbol
    read_from_input(current_gen);  // inits from manual input or redirection

    if (!freopen("/dev/tty", "r", stdin)) {  // resets standart input to keyboard in terminal
        handle_error();  // prints error message
    } else {
        initscr();  // inits new ncurses screen
        noecho();  // typed symbols aren't shown
        curs_set(FALSE);  // cursor isn't shown

        int gen_count = 0;  // number of generations
        int over = 0;  // boolean variable that shows if game is over
        while (!over) {  // main drawing loop
            draw_field(current_gen);  // draws field
            refresh();  // applies drawing for ncurses screen
            new_generation(current_gen, next_gen);  // fills new generation array
            swap_arrays(current_gen, next_gen);  // swap arrays because we draw only current generation
            over = is_over(next_gen, current_gen);  // check for game ending
            await_input(&over, &update_rate);  // handles keyboard input
            ++gen_count;  // increases generation count
            clear();  // clears the old frame
        }

        int width = getmaxx(stdscr);  // get width of screen
        int height = getmaxy(stdscr);  // get height of screen
        endwin();  // disable ncurses mode
        gameover_message(gen_count, height, width);  // print end message
    }

    return 0;
}

void handle_error() {
    printf("Failed redirecting stdin to terminal keyboard input");
}

void await_input(int* over, int* update_rate) {
    timeout(*update_rate);  // time in ms to wait for getch()
    char sym = getch();
    if (sym == 'q') {  // exit
        *over = 1;
    } else if (sym == 'f' && *update_rate > MAX_SPEED) {  // speed up
        *update_rate /= 2;
    } else if (sym == 's' && *update_rate < MIN_SPEED) {  // slow down
        *update_rate *= 2;
    }
}

void swap_arrays(char first[ROWS][COLS], char second[ROWS][COLS]) {
    char temp[ROWS][COLS];  // empty temp array

    for (int i = 0; i < ROWS; ++i) {  // filling empty array with first array
        for (int j = 0; j < COLS; ++j) {
            temp[i][j] = first[i][j];
        }
    }

    for (int i = 0; i < ROWS; ++i) {  // filling first array with second array values
        for (int j = 0; j < COLS; ++j) {
            first[i][j] = second[i][j];
        }
    }

    for (int i = 0; i < ROWS; ++i) {  // filling second array with temp array values
        for (int j = 0; j < COLS; ++j) {
            second[i][j] = temp[i][j];
        }
    }
}

// if fields are similar game is over
int is_over(char current[ROWS][COLS], char previous[ROWS][COLS]) {
    int over = 1;
    int cycle_end = 0;
    for (int i = 0; i < ROWS && !cycle_end; ++i) {
        for (int j = 0; j < COLS && !cycle_end; ++j) {
            if (current[i][j] != previous[i][j]) {  // if fields are not similar
                over = 0;                           // the cycle can be stopped
                cycle_end = 1;
            }
        }
    }
    return over;
}

// reads coords from stdin and ignores lines with bad format
void read_from_input(char result[ROWS][COLS]) {
    int end = 0;  // flag for input end
    int x, y;
    char sym1 = 0, sym2 = 0;
    while (!end) {
        int count = scanf("%d%c%d%c", &x, &sym1, &y, &sym2);
        if ((sym1 == ' ') &&  // input format check
            ((count == 4 && sym2 == '\n') ||
            (count == 3 && sym2 == 0))) {
            if ((x >= 0 && x < COLS) || (y >= 0 && y < ROWS)) {  // input values check
                if (result[y][x] == EMPTY) {  // makes life if no life
                    result[y][x] = LIFE;
                } else {  // deletes life is life exists
                    result[y][x] = EMPTY;
                }
            } else {
                end = 1;
            }
        } else {
            // flushes line buffer to continue input
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
    }
}

void draw_field(char field[ROWS][COLS]) {
    for (int i = -1; i < ROWS + 1; ++i) {
        for (int j = -1; j < COLS + 1; ++j) {
            if (i == -1 || i == ROWS) {
                if (j == -1 || j == COLS) {
                    printw("%c", CROSS);  // draws CROSS in corners
                } else {
                    printw("%c", CB);  // draws CB on ceiling and bottom
                }
            } else if (j == -1 || j == COLS) {
                printw("%c", WALL);  // draws WALL on walls
            } else {
                if (field[i][j] == EMPTY) {
                    printw("%c", EMPTY);  // draws EMPTY if there is no life
                } else {
                    printw("%c", LIFE);  // draws LIFE if there is no life
                }
            }
        }
        printw("\n");  // line break after every line
    }
    printw("\nPress 'f' to speed up, 's' to slow down, 'q' to exit");  // helper drawing
}

// fills array with EMPTY chars
void init_empty(char field[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            field[i][j] = EMPTY;
        }
    }
}

// calculates new generation for field array and writes it to the result_arr
void new_generation(char field[ROWS][COLS], char result_arr[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int neighbours = 0;  // neighbours counter for every cell
            for (int k = -1; k < 2; ++k) {  // neighbours y coord cycle
                int y = i + k;
                if (y < 0) {
                    y += ROWS;
                }
                if (y >= ROWS) {
                    y -= ROWS;
                }
                for (int l = -1; l < 2; ++l) {  // neighbours x coord cycle
                    int x = j + l;
                    if (x < 0) {
                        x += COLS;
                    }
                    if (x >= COLS) {
                        x -= COLS;
                    }
                    if (k != 0 || l != 0) {  // the original cell doesn't count
                        if (field[y][x] != EMPTY) {
                            ++neighbours;
                        }
                    }
                }
            }
            // standard condition for "game of life"
            if (neighbours == 3 || (neighbours == 2 && field[i][j] == LIFE)) {
                result_arr[i][j] = LIFE;
            } else {
                result_arr[i][j] = EMPTY;
            }
        }
    }
}

void gameover_message(int count, int y, int x) {
    for (int i = 0; i < y / 2; ++i) {  // skips until center line
        printf("\n");
    }
    for (int i = 0; i < (x - AVG_MSG_WIDTH) / 2; ++i) {  // skips until central place
        printf(" ");
    }
    printf("The game is over after %d generations", count);  // prints message
    for (int i = 0; i < y / 2; ++i) {  // skips lines after message
        printf("\n");
    }
}
