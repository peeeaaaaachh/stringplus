CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
CHECK_FLAGS = $(shell pkg-config --libs check)
GCOV_FLAGS = -fprofile-arcs -ftest-coverage

LIB_SRCS := $(wildcard *.c)
TEST_SRCS := $(wildcard tests/*.c)

LIB_OBJS = $(LIB_SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

NAME = test
REPORT_NAME = report

all: s21_string.a test

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

s21_string.a: $(LIB_OBJS)
	ar rcs s21_string.a $(LIB_OBJS)

test: s21_string.a $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) s21_string.a $(CHECK_FLAGS) -o $(NAME)
	./$(NAME)

gcov_report:
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(LIB_SRCS) $(TEST_SRCS) $(CHECK_FLAGS) -o $(NAME)
	-./$(NAME) || true
	lcov -t "$(NAME)" -o $(NAME).info --no-external -c -d .
	mkdir -p $(REPORT_NAME)
	genhtml -o $(REPORT_NAME) $(NAME).info
	rm -f $(NAME)

clean:
	rm -f $(LIB_OBJS) $(TEST_OBJS) *.a *.gcda *.gcno *.info $(NAME)
	rm -rf $(REPORT_NAME)

format:
	cp ../materials/linters/.clang-format .
	clang-format -i *.c *.h
	clang-format -i tests/*.c tests/*.h
	clang-format -n *.c *.h
	clang-format -n tests/*.c tests/*.h
	
remove_format: 
	rm -f .clang-format

.PHONY: all test gcov_report clean format remove_format