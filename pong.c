#include <stdio.h>

// coords
#define BALL_X_POS      39
#define BALL_Y_POS      12
#define BALL_X_DIR      1
#define BALL_Y_DIR      0
#define CEILING         0
#define BOTTOM          24
#define LEFT_WALL       0
#define RIGHT_WALL      79
#define CENTER_X        39
#define CENTER_Y        12
#define SCORE1_POS_X    30
#define SCORE2_POS_X    48
#define SCORE_POS_Y     5
#define ROCK_L_POS_X    4
#define ROCK_R_POS_X    75
#define ROCK_R_POS_Y    12
#define ROCK_L_POS_Y    ROCK_R_POS_Y

// game options
#define START_SCORE_1   0
#define START_SCORE_2   0
#define WIN_SCORE       21

// directions
#define NEGATIVE -1
#define POSITIVE 1

// symbols
#define BALL "*"
#define PIPE "|"
#define CB   "-"


int graph(int rock_l_pos, int rock_r_pos, int ball_x_pos, int ball_y_pos, int score1, int score2);
int game(int rock_l_pos, int rock_r_pos, int ball_x_pos, int ball_y_pos,
         int ball_x_dir, int ball_y_dir, int score1, int score2);
void clearScreen(void);
void next_frame(int rock_l_pos, int rock_r_pos, int ball_x_pos, int ball_y_pos, int score1, int score2);
int print_score(int score, int x, int y, int num);


int main() {
    clearScreen();
    int score1 = START_SCORE_1, score2 = START_SCORE_2;
    graph(ROCK_L_POS_Y, ROCK_R_POS_Y, BALL_X_POS, BALL_Y_POS, score1, score2);
    game(ROCK_L_POS_Y, ROCK_R_POS_Y, BALL_X_POS, BALL_Y_POS, BALL_X_DIR, BALL_Y_DIR, score1, score2);
    return 0;
}

int print_score(int score, int x, int y, int num) {
    if (x == (num == 1 ? SCORE1_POS_X : SCORE2_POS_X) && y == SCORE_POS_Y) {
        if (score < 10) {
            printf("%d", score);
        } else {
            printf("%d", score / 10);
        }
        return 1;
    }

    if (score >= 10 && x == (num == 1 ? SCORE1_POS_X : SCORE2_POS_X) + 1 && y == SCORE_POS_Y) {
        printf("%d", score % 10);
        return 1;
    }
    return 0;
}

int graph(int rock_l_pos, int rock_r_pos, int ball_x_pos, int ball_y_pos, int score1, int score2) {
    for (int y = CEILING; y <= BOTTOM; ++y) {
        for (int x = LEFT_WALL; x <= RIGHT_WALL; ++x) {
            if (x == ball_x_pos && y == ball_y_pos) {
                printf(BALL);
                continue;
            }

            if (y == CEILING || y == BOTTOM) {
                printf(CB);
                continue;
            }

            if ((x == LEFT_WALL || x == RIGHT_WALL) ||
                (x == ROCK_L_POS_X && (y == rock_l_pos || y == rock_l_pos + 1 || y == rock_l_pos - 1)) ||
                (x == ROCK_R_POS_X && (y == rock_r_pos || y == rock_r_pos + 1 || y == rock_r_pos - 1)) ||
                (x == CENTER_X)) {
                printf(PIPE);
                continue;
            }

            if (print_score(score1, x, y, 1)) {
                continue;
            }

            if (print_score(score2, x, y, 2)) {
                continue;
            }

            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    printf("Enter command: ");
    return 0;
}

void next_frame(int rock_l_pos, int rock_r_pos, int ball_x_pos, int ball_y_pos, int score1, int score2) {
    clearScreen();
    graph(rock_l_pos, rock_r_pos, ball_x_pos, ball_y_pos, score1, score2);
}

int game(int rock_l_pos, int rock_r_pos, int ball_x_pos, int ball_y_pos,
         int ball_x_dir, int ball_y_dir, int score1, int score2) {
    int k;
    int player_1_turn = 1;
    do {
        k = getchar();
        puts("");
        if (k == 'a' || k == 'A' || k == 'z' || k == 'Z') {  // first player move
            if (!player_1_turn) {
                next_frame(rock_l_pos, rock_r_pos, ball_x_pos, ball_y_pos, score1, score2);
                continue;
            }
            if ((k == 'a' || k == 'A') && rock_l_pos != CEILING + 2) {
                rock_l_pos -= 1;
            } else if ((k == 'z' || k == 'Z') && rock_l_pos != BOTTOM - 2) {
                rock_l_pos += 1;
            }
            player_1_turn = 0;
        } else {
            if (k == 'k' || k == 'K' || k == 'm' || k == 'M') {  // second player move
                if (player_1_turn) {
                    next_frame(rock_l_pos, rock_r_pos, ball_x_pos, ball_y_pos, score1, score2);
                    continue;
                }
                if ((k == 'k' || k == 'K') && rock_r_pos != CEILING + 2) {
                    rock_r_pos -= 1;
                } else if ((k == 'm' || k == 'M') && rock_r_pos != BOTTOM - 2) {
                    rock_r_pos += 1;
                }
                player_1_turn = 1;
            } else {
                if (k == ' ') {  // irregular symbol handle
                    player_1_turn = player_1_turn == 0 ? 1 : 0;
                } else {
                    next_frame(rock_l_pos, rock_r_pos, ball_x_pos, ball_y_pos, score1, score2);
                    continue;
                }
            }
        }

        // ball reflection
        if (ball_y_pos == CEILING + 1 || ball_y_pos == BOTTOM - 1) {
            ball_y_dir = -ball_y_dir;
        }

        // first player hit
        if (ball_x_pos == ROCK_L_POS_X + 1) {
            if (ball_y_pos == rock_l_pos + 2 && ball_y_dir == -1 && ball_x_dir == -1) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = POSITIVE;
            }
            if (ball_y_pos == rock_l_pos - 2 && ball_y_dir == 1 && ball_x_dir == -1) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = NEGATIVE;
            }
            if (ball_y_pos == rock_l_pos - 1) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = NEGATIVE;
            }
            if (ball_y_pos == rock_l_pos + 1) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = POSITIVE;
            }
            if (ball_y_pos == rock_l_pos) {
                ball_x_dir = -ball_x_dir;
            }
        }
        // second player hit
        if (ball_x_pos == ROCK_R_POS_X - 1) {
            if (ball_y_pos == rock_r_pos + 2 && ball_y_dir == -1 && ball_x_dir == 1) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = POSITIVE;
            }
            if (ball_y_pos == rock_r_pos - 2 && ball_y_dir == 1 && ball_x_dir == 1) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = NEGATIVE;
            }
            if (ball_y_pos == rock_r_pos - 1) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = NEGATIVE;
            }
            if (ball_y_pos == rock_r_pos + 1) {
                ball_x_dir = -ball_x_dir;
                ball_y_dir = POSITIVE;
            }
            if (ball_y_pos == rock_r_pos) {
                ball_x_dir = -ball_x_dir;
            }
        }
        if (ball_x_pos == LEFT_WALL + 2) {
            ++score2;
            if (score2 == WIN_SCORE) {
                printf("Поздравляем игрока под номером 2 с победой!\n");
                break;
            }
            ball_x_pos = CENTER_X;
            ball_y_pos = CENTER_Y;
        }
        if (ball_x_pos == RIGHT_WALL - 1) {
            ++score1;
            if (score1 == WIN_SCORE) {
                printf("Поздравляем игрока под номером 1 с победой!\n");
                break;
            }
            ball_x_pos = CENTER_X;
            ball_y_pos = CENTER_Y;
        }
        ball_x_pos += ball_x_dir;
        ball_y_pos += ball_y_dir;
        clearScreen();
        graph(rock_l_pos, rock_r_pos, ball_x_pos, ball_y_pos, score1, score2);
    } while (k != 'q');
    return 0;
}

void clearScreen(void) {
    printf("\33[0d\33[2J");
}
