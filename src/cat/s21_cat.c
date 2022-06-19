#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

// structure for short options
struct cat {
    int b;
    int e;
    int v;
    int n;
    int s;
    int t;
    int E;
    int T;
};

// structure for long options
static struct option long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
    {NULL, 0, NULL, 0}};

// function to set value to structure variables
void set_flags(struct cat *t, int arguments);
// function to print file
void print_file(struct cat, char *argv[]);

int main(int argc, char *argv[]) {
    if (argc > 1) {
        int option = 0;
        struct cat flags = {0, 0, 0, 0, 0, 0, 0, 0};
        struct cat *flagss = &flags;
        while ((option = getopt_long(argc, argv, ":bevnstET", long_options, NULL)) != -1) {
            set_flags(flagss, option);
        }
        print_file(flags, argv);
    }

    return 0;
}

// function to parse options and set flags into structure
void set_flags(struct cat *t, int arguments) {
    switch (arguments) {
        case 'b':
            t->b = 1;
            break;
        case 'e':
            t->e = 1;
            t->v = 1;
            break;
        case 'n':
            t->n = 1;
            break;
        case 's':
            t->s = 1;
            break;
        case 't':
            t->t = 1;
            t->v = 1;
            break;
        case 'E':
            t->E = 1;
            t->e = 1;
            break;
        case 'T':
            t->T = 1;
            t->t = 1;
            break;
        case 'v':
            t->v = 1;
            break;
    }
}

void print_file(struct cat example, char *argv[]) {
    int line_number = 1;
    int flag_char_number = 0;
    int previous_line = 0;
    int current_line = 1;
    char ch;
    FILE *file;
    file = fopen(argv[optind], "r");
    if (file != NULL) {
        while ((ch = fgetc(file)) != EOF) {
            if (example.s == 1 && ch == '\n') {
                if (current_line == 1 && previous_line == 1) {
                    continue;
                } else if (current_line == 1) {
                    previous_line = 1;
                } else {
                    previous_line = 0;
                    current_line = 1;
                }
            } else {
                current_line = 0;
            }
            if (example.b == 1 && ch != '\n' && flag_char_number == 0) {
                printf("%6d\t", line_number++);
            }
            if (example.n == 1 && example.b == 0 && flag_char_number == 0) {
                printf("%6d\t", line_number++);
            }
            if (example.e == 1 && ch == '\n') {
                printf("$");
            }
            flag_char_number++;
            if (ch == '\n') {
                flag_char_number = 0;
            }
            if (example.v == 1 && ch < 32 && ch >= 0 && ch != 9 && ch != 10 && ch != 127) {
                printf("^");
                ch += 64;
            } else if (example.v == 1 && ch == 127) {
                printf("^?");
            }
            if (example.t == 1 && ch == '\t') {
                printf("^I");
            }
            printf("%c", ch);
        }
    }
}
