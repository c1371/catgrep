#include <check.h>
#include <stdio.h>
#include <string.h>

START_TEST(s21_cat_test_) {
    FILE *s21_cat = fopen("cat/s21_cat.txt", "r");
    FILE *cat_original = fopen("cat/cat_original_test.txt", "r");
    if (s21_cat && cat_original) {
        char char1;
        char char2;
        int j = 0;
        while (char1 != EOF) {
            char1 = getc(s21_cat);
            char2 = getc(cat_original);
            j++;

            ck_assert_msg(char1 == char2, "Test fail on char №: %d", (j));
        }
    }
    fclose(s21_cat);
    fclose(cat_original);
}
END_TEST

START_TEST(s21_grep_test_) {
    FILE *s21_grep = fopen("grep/s21_grep.txt", "r");
    FILE *grep_original = fopen("grep/grep_original.txt", "r");
    int j = 0;
    if (s21_grep && grep_original) {
        char char1[1000], char2[1000];
        while (!feof(s21_grep) && !feof(grep_original)) {
            fgets(char1, 100, s21_grep);
            fgets(char2, 100, grep_original);
            j++;
            ck_assert_msg(strcmp(char1, char2) == 0, "Test fail on string №: %d", j);
        }
    }
    fclose(s21_grep);
    fclose(grep_original);
}
END_TEST

int main() {
    Suite *suite = suite_create("s21_bash");
    TCase *s21_cat_case = tcase_create("s21_cat_test_case");
    TCase *s21_grep_case = tcase_create("s21_grep_test_case");
    SRunner *sr = srunner_create(suite);
    int nf;

    suite_add_tcase(suite, s21_cat_case);
    tcase_add_test(s21_cat_case, s21_cat_test_);

    suite_add_tcase(suite, s21_grep_case);
    tcase_add_test(s21_grep_case, s21_grep_test_);

    srunner_run_all(sr, CK_VERBOSE);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
