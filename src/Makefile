CC = gcc
FLAG = -Wall -Wextra -Werror
OS=$(shell uname)
ifeq ($(OS), Linux)
  LIBS=-lcheck -lpthread -lrt -lm -lsubunit
else
  LIBS=-lcheck
endif

all: s21_cat s21_grep

test: s21_test_cat s21_test_grep
	$(CC) $(FLAG) s21_tests.c $(LIBS) -o s21_tests.out
	./s21_tests.out

s21_cat: 
	$(CC) $(FLAG) -c cat/s21_cat.c -o cat/s21_cat.o
	$(CC) $(FLAG) cat/s21_cat.o -o cat/s21_cat

s21_grep: 
	$(CC) $(FLAG) -c grep/s21_grep.c -o grep/s21_grep.o
	$(CC) $(FLAG) grep/s21_grep.o -o grep/s21_grep

s21_test_cat:
	cat/s21_cat -b -n cat/test.txt >> cat/s21_cat.txt
	cat/s21_cat -e cat/test.txt >> cat/s21_cat.txt
	cat/s21_cat -n cat/test.txt >> cat/s21_cat.txt
	cat/s21_cat -s cat/test.txt >> cat/s21_cat.txt
	cat/s21_cat -se cat/test.txt >> cat/s21_cat.txt
	cat/s21_cat -e cat/unreadeble.txt >> cat/s21_cat_unreadeble.txt
	cat -b -n cat/test.txt >> cat/cat_original_test.txt
	cat -e cat/test.txt >> cat/cat_original_test.txt
	cat -n cat/test.txt >> cat/cat_original_test.txt
	cat -s cat/test.txt >> cat/cat_original_test.txt	
	cat -se cat/test.txt >> cat/cat_original_test.txt
	cat -e cat/unreadeble.txt >> cat/cat_unreadeble_test.txt	

s21_test_grep:
	
	grep/s21_grep -e Hello grep/test.txt >> grep/s21_grep.txt
	grep/s21_grep -i Hello grep/test.txt >> grep/s21_grep.txt
	grep/s21_grep -v Hello grep/test.txt >> grep/s21_grep.txt
	grep/s21_grep -c Hello grep/test.txt >> grep/s21_grep.txt
	grep/s21_grep -l Hello grep/test.txt >> grep/s21_grep.txt
	grep/s21_grep -n Hello grep/test.txt >> grep/s21_grep.txt
	grep/s21_grep -h Hello grep/test.txt >> grep/s21_grep.txt
	grep -e Hello grep/test.txt >> grep/grep_original.txt
	grep -i hello grep/test.txt >> grep/grep_original.txt
	grep -v Hello grep/test.txt >> grep/grep_original.txt 
	grep -c Hello grep/test.txt >> grep/grep_original.txt
	grep -l Hello grep/test.txt >> grep/grep_original.txt
	grep -n Hello grep/test.txt >> grep/grep_original.txt
	grep -h Hello grep/test.txt >> grep/grep_original.txt

check_cat:
	cppcheck cat/s21_cat.c
	CK_FORK=no leaks --atExit -- cat/s21_cat

check_grep:
	cppcheck grep/s21_grep.c
	CK_FORK=no leaks --atExit -- grep/s21_grep

clean_test:
	rm -rf cat/*test.txt
	rm -rf grep/*test.txt
	rm -rf s21_test.out

clean:
	rm -rf cat/s21_cat.o grep/s21_grep.o
	rm -rf cat/s21_cat grep/s21_grep
	rm -rf s21_test.out
	rm -rf *.o
	rm cat/s21_cat.txt
	rm cat/cat_original_test.txt
	rm cat/s21_cat_unreadeble.txt
	rm cat/cat_unreadeble_test.txt
	rm grep/grep_original.txt
	rm grep/s21_grep.txt
leaks:
	make all
	CK_FORK=no leaks --atExit -- ./s21_tests.out
	CK_FORK=no leaks --atExit -- cat/./s21_cat
	
linters: 
	python3 ../materials/linters/cpplint.py --extensions=c *.c cat/*.c grep/*.c

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c cat/s21_cat.c grep/s21_grep.c

rebuild: clean all
