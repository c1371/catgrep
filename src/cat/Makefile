CC = gcc
FLAG = -Wall -Werror -Wextra
all: s21_cat
s21_cat: 
	$(CC) -c s21_cat.c -o s21_cat.o
	$(CC) s21_cat.o -o s21_cat
clean:
	rm -rf s21_cat.o
	rm -rf s21_cat
rebuild: clean all