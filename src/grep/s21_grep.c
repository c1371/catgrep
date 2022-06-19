#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct grep {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
} grep;
void set_flags_and_pattern(int argc, char **argv, grep *flags);
void print_file(grep *flags, char *string, char **argv);
void flag_e(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags);
void flag_i(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags);
void flag_v(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags);
void flag_c(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags);
void flag_l(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str);
void flag_n(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags);
void flag_h(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str);
void flag_o(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags);
void flag_f(FILE *file, regex_t *regex, char **argv, int *return_value, char *str, int indicator, int j);
int main(int argc, char **argv) {
    char string[1000] = {0};
    char *pattern_string = string;
    grep flags = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    set_flags_and_pattern(argc, argv, &flags);
    if (argc > 1) {
        if (strchr(*(argv + 1), '-') == NULL || strcmp(*(argv + 1), "-") == 0) {
            flags.e = 1;
        }
        print_file(&flags, pattern_string, argv);
    }
    return 0;
}

void print_file(grep *flags, char *pattern_string, char **argv) {
    FILE *file = NULL;
    snprintf(pattern_string, 1000, "%s", argv[optind]);
    int j = 1;
    regex_t regex;
    int return_value;
    int indicator;
    char str[2000];
    if (argv[optind + j + 1] != NULL) {
        indicator = 1;
    }
    while ((argv[optind + j]) != NULL) {
        file = fopen(argv[optind + j], "r");
        if (access(argv[optind + j], F_OK) == 0) {
            if (flags->e == 1) {
                flag_e(file, &regex, argv, &return_value, str, indicator, j, flags);
            } else if (flags->i == 1) {
                flag_i(file, &regex, argv, &return_value, str, indicator, j, flags);
            } else if (flags->v == 1) {
                flag_v(file, &regex, argv, &return_value, str, indicator, j, flags);
            } else if (flags->c == 1) {
                flag_c(file, &regex, argv, &return_value, str, indicator, j, flags);
            } else if (flags->l == 1) {
                flag_l(file, &regex, argv, &return_value, str);
            } else if (flags->n == 1) {
                flag_n(file, &regex, argv, &return_value, str, indicator, j, flags);
            } else if (flags->h == 1) {
                flag_h(file, &regex, argv, &return_value, str);
            } else if (flags->o == 1) {
                flag_o(file, &regex, argv, &return_value, str, indicator, j, flags);
            } else if (flags->f == 1) {
                flag_f(file, &regex, argv, &return_value, str, indicator, j);
            }
        } else {
            if (flags->s == 0) {
                printf("%s: can't be read or doesnt exist.\n", argv[optind + j]);
            }
        }
        j++;
        fclose(file);
    }
}

void flag_e(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags) {
    regcomp(regex, argv[optind], REG_NEWLINE | REG_NOSUB);
    while (fgets(str, 1000, file)) {
        if (str[(int)strlen(str) - 1] != '\n') {
            strncat(str, "\n", 2);
        }
        *return_value = regexec(regex, str, 0, NULL, 0);
        if ((!*return_value)) {
            if (indicator == 1 && flags->s == 0) printf("%s:", argv[optind + j]);
            printf("%s", str);
        }
    }
    regfree(regex);
}

void flag_i(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags) {
    regcomp(regex, argv[optind], REG_ICASE | REG_NEWLINE | REG_NOSUB);
    while (fgets(str, 1000, file)) {
        if (str[(int)strlen(str) - 1] != '\n') {
            strncat(str, "\n", 2);
        }
        *return_value = regexec(regex, str, 0, NULL, 0);
        if ((!*return_value)) {
            if (indicator == 1 && flags->s == 0) printf("%s:", argv[optind + j]);
            printf("%s", str);
        }
    }
    regfree(regex);
}

void flag_v(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags) {
    regcomp(regex, argv[optind], REG_NEWLINE | REG_NOSUB);
    while (fgets(str, 1000, file)) {
        if (str[(int)strlen(str) - 1] != '\n') {
            strncat(str, "\n", 2);
        }
        *return_value = regexec(regex, str, 0, NULL, 0);
        if ((*return_value)) {
            if (indicator == 1 && flags->s == 0) printf("%s:", argv[optind + j]);
            printf("%s", str);
        }
    }
    regfree(regex);
}

void flag_c(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags) {
    regcomp(regex, argv[optind], REG_NEWLINE | REG_NOSUB);
    int count = 0;
    while (fgets(str, 1000, file)) {
        if (str[(int)strlen(str) - 1] != '\n') {
            strncat(str, "\n", 2);
        }
        *return_value = regexec(regex, str, 0, NULL, 0);
        if ((!*return_value)) {
            count++;
        }
    }
    regfree(regex);
    if (indicator == 1 && flags->s == 0) printf("%s:", argv[optind + j]);
    printf("%d\n", count);
}

void flag_l(FILE *file, regex_t *regex, char **argv, int *return_value, char *str) {
    regcomp(regex, argv[optind], REG_NEWLINE | REG_NOSUB);
    int count = 0;
    while (fgets(str, 1000, file)) {
        if (str[(int)strlen(str) - 1] != '\n') {
            strncat(str, "\n", 2);
        }
        *return_value = regexec(regex, str, 0, NULL, 0);
        if (!*return_value) {
            count++;
        }
    }
    regfree(regex);
    if (count > 0) {
        printf("%s\n", argv[optind + 1]);
    }
}
void flag_n(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags) {
    regcomp(regex, argv[optind], REG_NEWLINE | REG_NOSUB);
    int count = 0;
    while (fgets(str, 1000, file)) {
        count++;
        if (str[(int)strlen(str) - 1] != '\n') {
            strncat(str, "\n", 2);
        }
        *return_value = regexec(regex, str, 0, NULL, 0);
        if (!*return_value) {
            if (indicator == 1 && flags->s == 0) printf("%s:", argv[optind + j]);
            printf("%d:%s", count, str);
        }
    }
    regfree(regex);
}
void flag_h(FILE *file, regex_t *regex, char **argv, int *return_value, char *str) {
    regcomp(regex, argv[optind], REG_NEWLINE | REG_NOSUB);
    while (fgets(str, 1000, file)) {
        if (str[(int)strlen(str) - 1] != '\n') {
            strncat(str, "\n", 2);
        }
        *return_value = regexec(regex, str, 0, NULL, 0);
        if ((!*return_value)) {
            printf("%s", str);
        }
    }
    regfree(regex);
}

void flag_o(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j, grep *flags) {
    regcomp(regex, argv[optind], REG_NEWLINE);
    regmatch_t match;
    while (fgets(str, 1000, file)) {
        if (str[(int)strlen(str) - 1] != '\n') {
            strncat(str, "\n", 2);
        }
        while (!(*return_value = regexec(regex, str, 1, &match, 0))) {
            if (indicator == 1 && flags->s == 0) printf("%s:", argv[optind + j]);
            while (match.rm_so < match.rm_eo) {
                putchar(*(str + (match.rm_so++)));
            }
            if (match.rm_so != -1) putchar('\n');
            str += match.rm_eo;
        }
    }
    regfree(regex);
}
void flag_f(FILE *file, regex_t *regex, char **argv, int *return_value,
            char *str, int indicator, int j) {
    while (fgets(str, 1000, file)) {
        int token = 0;
        char buf[1000];
        FILE *file_pattern;
        file_pattern = fopen(argv[optind], "r");
        while (fgets(buf, 1000, file_pattern) && token == 0) {
            if (str[(int)strlen(str) - 1] != '\n') {
                strncat(str, "\n", 2);
            }
            if (buf[(int)strlen(buf) - 1] == '\n') {
                buf[(int)strlen(buf) - 1] = '\0';
            }
            regcomp(regex, buf, REG_NEWLINE | REG_NOSUB);
            *return_value = regexec(regex, str, 0, NULL, 0);
            regfree(regex);
            if (!*return_value && token == 0) {
                if (indicator == 1) {
                    printf("%s:", argv[optind + j]);
                }
                printf("%s", str);
                token++;
            }
        }
        fclose(file_pattern);
    }
}
void set_flags_and_pattern(int argc, char **argv, grep *flags) {
    int arguments = 0;
    while ((arguments = getopt(argc, argv, ":eivclnhsfo")) != -1) {
        switch (arguments) {
            case 'e':
                flags->e = 1;
                break;
            case 'i':
                flags->i = 1;
                break;
            case 'v':
                flags->v = 1;
                break;
            case 'c':
                flags->c = 1;
                break;
            case 'l':
                flags->l = 1;
                break;
            case 'n':
                flags->n = 1;
                break;
            case 'h':
                flags->h = 1;
                break;
            case 's':
                flags->s = 1;
                break;
            case 'f':
                flags->f = 1;
                break;
            case 'o':
                flags->o = 1;
                break;
        }
    }
}
