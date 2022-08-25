#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#ifdef LOG
#include "logger.h"
#endif

#include "utils.h"

int main() {
    int stop = 0;
    FILE* file = NULL;
    char* filename = NULL;

#ifdef LOG
    char* logfile = get_string();
    FILE* logger = log_init(logfile);
    logcat(logger, "logger init", info);
#endif

    while (!stop) {
        int option;
        if (read_option(&option) == 0) {
#ifdef LOG
            logcat(logger, "option is valid", trace);
#endif
            if (option == 1) {
                if (option_1(&filename, &file) != 0) {
                    handle_error();
                }
            } else if (option == 2) {
                if (option_2(&filename, &file) != 0) {
                    handle_error();
                }
            } else if (option == 3) {
                if (option_3() != 0) {
                    handle_error();
                }
            } else if (option == 4) {
                if (option_4() != 0) {
                    handle_error();
                }
            } else {  // option == -1
#ifdef LOG
                logcat(logger, "input stopped", debug);
#endif
                stop = 1;
            }
        } else {
#ifdef LOG
            logcat(logger, "invalid option", error);
#endif
            handle_error();
        }
    }

    clear_string(&filename);
    close_file(&file);

#ifdef LOG
    logcat(logger, "file closed, string freed", warning);
    logcat(logger, "logger finished", info);
    log_close(logger);
#endif

    return 0;
}

int option_1(char** filename, FILE** file) {
    int return_value = 0;

    clear_string(filename);
    *filename = get_string();
    if (*filename != NULL) {
        if (print_file(file, *filename) != 0) {
            return_value = ERR;
        }
    } else {
        return_value = ERR;
    }

    return return_value;
}

int option_2(char** filename, FILE** file) {
    int return_value = 0;

    char* text = get_string();
    if (*file != NULL && *filename != NULL) {
        close_file(file);
        *file = fopen(*filename, "a");
        if (*file != NULL && text != NULL) {
            fprintf(*file, "%s", text);
            if (print_file(file, *filename) != 0) {
                return_value = ERR;
            }
        } else {
            return_value = ERR;
        }
    } else {
        return_value = ERR;
    }
    clear_string(&text);

    return return_value;
}

int option_3() {
    int return_value = 0;

    char* directory = get_string();
    if (directory != NULL) {
        if (modify_directory(&directory) != 0) {
            return_value = ERR;
        } else {
            DIR *dir;
            dir = opendir(directory);
            if (dir != NULL) {
                int shift;
                if (read_int(&shift) == 0) {
                    struct dirent *dirent;
                    while ((dirent = readdir(dir)) != NULL) {
                        size_t len = strlen(dirent->d_name);
                        if (dirent->d_name[len - 1] == 'c' && dirent->d_name[len - 2] == '.') {
                            encode(&directory, dirent->d_name, shift % 26);
                        }
                        if (dirent->d_name[len - 1] == 'h' && dirent->d_name[len - 2] == '.') {
                            char* path = full_path(directory, dirent->d_name);
                            FILE* header = fopen(path, "w");
                            fclose(header);
                            free(path);
                        }
                    }
                    closedir(dir);
                } else {
                    return_value = ERR;
                }
            } else {
                return_value = ERR;
            }
        }
        clear_string(&directory);
    }

    return return_value;
}

int option_4() {
    int return_value = 0;

    char* directory = get_string();
    if (directory != NULL) {
        if (modify_directory(&directory) != 0) {
            return_value = ERR;
        } else {
            DIR *dir;
            dir = opendir(directory);
            if (dir != NULL) {
                struct dirent *dirent;
                while ((dirent = readdir(dir)) != NULL) {
                    size_t len = strlen(dirent->d_name);
                    if (dirent->d_name[len - 1] == 'c' && dirent->d_name[len - 2] == '.') {
                        des(directory, dirent->d_name);
                    }
                    if (dirent->d_name[len - 1] == 'h' && dirent->d_name[len - 2] == '.') {
                        char* path = full_path(directory, dirent->d_name);
                        FILE* header = fopen(path, "w");
                        fclose(header);
                        free(path);
                    }
                }
                closedir(dir);
            } else {
                return_value = ERR;
            }
        }
        clear_string(&directory);
    }

    return return_value;
}

int modify_directory(char** directory) {
    int return_value = 0;

    size_t dir_len = strlen(*directory);
    if ((*directory)[dir_len - 1] != '/') {
        char* temp = (char*) realloc(*directory, dir_len + 2);
        if (temp != NULL) {
            *directory = temp;
            *directory = strcat(*directory, "/");
            (*directory)[dir_len + 1] = '\0';
        } else {
            free(*directory);
            return_value = ERR;
        }
    }

    return return_value;
}

char* full_path(char* dir, char* name) {
    size_t size = strlen(dir) + strlen(name) + 1;
    char* result = (char*) calloc(size, sizeof(char));
    if (result != NULL) {
        result = strcat(result, dir);
        result = strcat(result, name);
        result[size - 1] = '\0';
    }
    return result;
}

int encode(char** directory, char* original, int shift) {
    int return_value = 0;
    char* orig_full = full_path(*directory, original);
    if (orig_full == NULL) {
        return_value = ERR;
    } else {
        FILE *orig = fopen(orig_full, "r");
        if (orig != NULL) {
            char* path = full_path(*directory, "temp");
            if (path != NULL) {
                FILE *output = fopen(path, "w");
                int ch = fgetc(orig);
                while (ch != EOF) {
                    fprintf(output, "%c", encode_char(ch, shift));
                    ch = fgetc(orig);
                }
                close_file(&orig);
                close_file(&output);

                remove(orig_full);
                rename(path, orig_full);

                free(path);
                free(orig_full);
            } else {
                return_value = ERR;
            }
            close_file(&orig);
        } else {
            return_value = ERR;
        }
    }

    return return_value;
}

int encode_char(int orig, int shift) {
    if (orig >= 'a' && orig <= 'z') {
        orig += shift;
        if (orig > 'z') {
            orig -= 26;
        } else if (orig < 'a') {
            orig += 26;
        }
    } else if (orig >= 'A' && orig <= 'Z') {
        orig += shift;
        if (orig > 'Z') {
            orig -= 26;
        } else if (orig < 'A') {
            orig += 26;
        }
    }
    return orig;
}

int read_int(int* number) {
    int return_value = 0;
    char sym;
    int count = scanf("%d%c", number, &sym);
    if (count != 2 || sym != '\n') {
        return_value = ERR;
    }
    return return_value;
}

void clear_string(char** line) {
    if (*line != NULL) {
        free(*line);
        *line = NULL;
    }
}

void handle_error() {
    printf("n/a\n");
}

void flush_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

char* get_string() {
    char* filename = NULL;
    size_t size;
    getline(&filename, &size, stdin);
    filename[strlen(filename) - 1] = '\0';
    return filename;
}

void close_file(FILE** file) {
    if (*file != NULL) {
        fclose(*file);
        *file = NULL;
    }
}

int print_file(FILE** file, char* filename) {
    int return_value = 0;

    close_file(file);
    *file = fopen(filename, "r");
    if (*file == NULL) {
        return_value = ERR;
    } else {
        int ch = fgetc(*file);
        if (ch == EOF) {
            return_value = ERR;
        } else {
            while (ch != EOF) {
                printf("%c", ch);
                ch = fgetc(*file);
            }
            printf("\n");
        }
    }

    return return_value;
}

int read_option(int* option) {
    char sym;
    int return_value = 0;
    int count = scanf("%d%c", option, &sym);
    if (count != 2 || sym != '\n') {
        flush_stdin();
        return_value = ERR;
    } else if (*option != 1 && *option != 2 && *option != 3 && *option != 4 && *option != -1) {
        return_value = ERR;
    }
    return return_value;
}

void expansion_function(int pos, int text) {
    for (int i = 0; i < 48; i++) {
        if (E[i] == pos + 1) {
            EXPtext[i] = text;
        }
    }
}

void initialPermutation(int pos, int text) {
    int i;
    for (i = 0; i < 64; i++) {
        if (IP[i] == pos + 1) {
            break;
        }
    }
    IPtext[i] = text;
}

int F1(int i) {
    int r, c, b[6];

    for (int j = 0; j < 6; j++) {
        b[j] = X[i][j];
    }

    r = b[0] * 2 + b[5];
    c = 8 * b[1] + 4 * b[2] + 2 * b[3] + b[4];

    if (i == 0) {
        return S1[r][c];
    } else if (i == 1) {
        return S2[r][c];
    } else if (i == 2) {
        return S3[r][c];
    } else if (i == 3) {
        return S4[r][c];
    } else if (i == 4) {
        return S5[r][c];
    } else if (i == 5) {
        return S6[r][c];
    } else if (i == 6) {
        return S7[r][c];
    } else if (i == 7) {
        return S8[r][c];
    } else {
        return 0;
    }
}

int XOR(int a, int b) {
    return (a ^ b);
}

void ToBits(int value) {
    int j, m;
    static int i;

    if (i % 32 == 0) {
        i = 0;
    }

    for (j = 3; j >= 0; j--) {
        m = 1 << j;
        int k = value & m;
        if (k == 0) {
            X2[3 - j + i] = '0' - 48;
        } else {
            X2[3 - j + i] = '1' - 48;
        }
    }

    i = i + 4;
}

void SBox(const int xor[]) {
    int k = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            X[i][j] = xor[k++];
        }
    }

    for (int i = 0; i < 8; i++) {
        int value = F1(i);
        ToBits(value);
    }
}

void PBox(int pos, int text) {
    int i;
    for (i = 0; i < 32; i++) {
        if (P[i] == pos + 1) {
            break;
        }
    }
    R[i] = text;
}

void cipher(int Round, int mode) {
    for (int i = 0; i < 32; i++) {
        expansion_function(i, RIGHT[Round - 1][i]);
    }

    for (int i = 0; i < 48; i++) {
        if (mode == 0) {
            XORtext[i] = XOR(EXPtext[i], key48bit[Round][i]);
        } else {
            XORtext[i] = XOR(EXPtext[i], key48bit[17 - Round][i]);
        }
    }

    SBox(XORtext);

    for (int i = 0; i < 32; i++) {
        PBox(i, X2[i]);
    }

    for (int i = 0; i < 32; i++) {
        RIGHT[Round][i] = XOR(LEFT[Round - 1][i], R[i]);
    }
}

void finalPermutation(int pos, int text) {
    int i;
    for (i = 0; i < 64; i++) {
        if (FP[i] == pos + 1) {
            break;
        }
    }
    ENCRYPTED[i] = text;
}

void convertToBinary(int n) {
    int m;
    for (int i = 7; i >= 0; i--) {
        m = 1 << i;
        int k = n & m;

        if (k == 0) {
            fprintf(out, "0");
        } else {
            fprintf(out, "1");
        }
    }
}

void convertCharToBit(char* filepath, int n) {
    FILE* inp = fopen(filepath, "rb");
    out = fopen("bits.txt", "wb+");
    int i = n * 8;

    while (i) {
        int ch = fgetc(inp);
        if (ch == -1) {
            break;
        }
        i--;
        convertToBinary(ch);
    }
    fclose(out);
    fclose(inp);
}

void Encryption(char* dest, long int plain[]) {
    out = fopen(dest, "ab+");
    for (int i = 0; i < 64; i++) {
        initialPermutation(i, (int)plain[i]);
    }

    for (int i = 0; i < 32; i++) {
        LEFT[0][i] = IPtext[i];
    }

    for (int i = 32; i < 64; i++) {
        RIGHT[0][i - 32] = IPtext[i];
    }

    for (int k = 1; k < 17; k++) {
        cipher(k, 0);

        for (int i = 0; i < 32; i++)
            LEFT[k][i] = RIGHT[k - 1][i];
    }

    for (int i = 0; i < 64; i++) {
        if (i < 32) {
            CIPHER[i] = RIGHT[16][i];
        } else {
            CIPHER[i] = LEFT[16][i - 32];
        }
        finalPermutation(i, CIPHER[i]);
    }

    for (int i = 0; i < 64; i++) {
        fprintf(out, "%d", ENCRYPTED[i]);
    }
    fclose(out);
}

void key56to48(int round, int pos, int text) {
    int i;
    for (i = 0; i < 47; i++) {
        if (PC2[i] == pos + 1) {
            break;
        }
    }
    key48bit[round][i] = text;
}

void key64to56(int pos, int text) {
    int i;
    for (i = 0; i < 55; i++) {
        if (PC1[i] == pos + 1) {
            break;
        }
    }
    key56bit[i] = text;
}

void key64to48(unsigned int key[]) {
    int backup[17][2];
    int CD[17][56];
    int C[17][28], D[17][28];

    for (int i = 0; i < 64; i++) {
        key64to56(i, (int)key[i]);
    }

    for (int i = 0; i < 56; i++) {
        if (i < 28) {
            C[0][i] = key56bit[i];
        } else {
            D[0][i - 28] = key56bit[i];
        }
    }

    for (int x = 1; x < 17; x++) {
        int shift = SHIFTS[x - 1];

        for (int i = 0; i < shift; i++) {
            backup[x - 1][i] = C[x - 1][i];
        }

        for (int i = 0; i < (28 - shift); i++) {
            C[x][i] = C[x - 1][i + shift];
        }

        int k = 0;
        for (int i = 28 - shift; i < 28; i++) {
            C[x][i] = backup[x - 1][k++];
        }

        for (int i = 0; i < shift; i++) {
            backup[x - 1][i] = D[x - 1][i];
        }

        for (int i = 0; i < (28 - shift); i++) {
            D[x][i] = D[x - 1][i + shift];
        }

        k = 0;
        for (int i = 28 - shift; i < 28; i++) {
            D[x][i] = backup[x - 1][k++];
        }
    }

    for (int j = 0; j < 17; j++) {
        for (int i = 0; i < 28; i++) {
            CD[j][i] = C[j][i];
        }

        for (int i = 28; i < 56; i++) {
            CD[j][i] = D[j][i - 28];
        }
    }

    for (int j = 1; j < 17; j++) {
        for (int i = 0; i < 56; i++) {
            key56to48(j, i, CD[j][i]);
        }
    }
}

void encrypt(char* dest, long int n) {
    FILE* in = fopen("bits.txt", "rb");

    long int plain[n * 64];
    int temp = -1;

    long int save = n;
    while (!feof(in)) {
        int ch = getc(in);
        plain[++temp] = ch - 48;
    }
    n = save;

    for (int i = 0; i < n; i++) {
        Encryption(dest, plain + 64 * i);
    }

    fclose(in);
}

void create16Keys() {
    for (int i = 0; i < 64; ++i) {
        key[i] -= 48;
    }

    key64to48(key);
}

long int findFileSize(char* filename) {
    FILE* inp = fopen(filename, "rb");
    long int size = 0;

    if (fseek(inp, 0L, SEEK_END)) {
        perror("fseek() failed");
    } else {
        size = ftell(inp);
    }
    fclose(inp);

    return size;
}

int des(char* directory, char* filename) {
    create16Keys();

    char* full_name = full_path(directory, filename);

    long int n = findFileSize(full_name) / 8;
    convertCharToBit(full_name, (int)n);

    char* dest = full_path(directory, "temp");

    encrypt(dest, n);

    remove(full_name);
    remove("bits.txt");
    rename(dest, full_name);

    free(full_name);
    free(dest);

    return 0;
}

