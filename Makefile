CC = g++ -Wall -Werror -Wextra -g 
COVFLAGS = -fprofile-arcs -std=c++17 -ftest-coverage

# Открываем результат
OPENOS = vi
ifeq ($(shell uname -s), Linux)
	OPENOS = xdg-open
endif
ifeq ($(shell uname -s), Darwin)
	OPENOS = open
endif

all: clean style s21_matrix_oop.a gcov_report

gcov: gcov_report
	@$(OPENOS) ./gcov_reportd/gcov_report.html

gcov_report: s21_matrix_oop.a test gcov_reportd/gcov_report.html

gcov_reportd/gcov_report.html : s21_matrix_oop.a test
	@mkdir -p gcov_reportd
	gcovr -r . --gcov-executable gcov --html --html-details -o gcov_reportd/gcov_report.html

test: s21_matrix_oop.a
		$(CC) -c test_s21_matrix.cpp 
		$(CC) --coverage -o test.out test_s21_matrix.o -lgtest -lgtest_main -L. s21_matrix_oop.a
		./test.out
		make clean

vg: s21_matrix_oop.a
		$(CC) -c test_s21_matrix.cpp 
		$(CC) --coverage -o test.out test_s21_matrix.o -lgtest -lgtest_main -L. s21_matrix_oop.a
		valgrind --tool=memcheck --leak-check=yes  ./test.out
		make clean

s21_matrix_oop.a: s21_matrix_oop.o
		ar rc s21_matrix_oop.a s21_matrix_oop.o
		ranlib s21_matrix_oop.a

s21_matrix_oop.o:
		$(CC) -c $(COVFLAGS) s21_matrix_oop.cpp

leaks: clean test
		leaks -atExit -- ./test.out
		make clean

cppcheck:
		cppcheck --enable=all --suppress=missingIncludeSystem *.cpp

style:
		@cp ../materials/linters/.clang-format .
		clang-format -n *.cpp *.h
		@rm -rf .clang-format

clean:
		@rm -rf *.out *.o *.a *.gcov *.gcda *.gcno *.info report gcov_reportd