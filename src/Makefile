CXX := g++
CXX_FLAGS := -Wall -w -Wextra -std=c++17 -g
GCOVFLAGS := -L. --coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
	TEST_FLAGS := $(shell pkg-config --libs gtest)
else
	TEST_FLAGS := -lgtest
endif

LIB_TMP_BASE := $(wildcard lib/*/*.tpp)
LIB_HDR_BASE := $(wildcard lib/*.h) $(wildcard lib/*/*.h)
LIB_OBJ_BASE := s21_containers.o
LIB_BIN_BASE := s21_containers.a

LIB_TMP_PLUS := $(wildcard libplus/*/*.tpp)
LIB_HDR_PLUS := $(wildcard libplus/*.h) $(wildcard libplus/*/*.h)
LIB_OBJ_PLUS := s21_containersplus.o
LIB_BIN_PLUS := s21_containersplus.a

TESTS_SRC := $(wildcard tests/*.cpp) $(wildcard tests/*/*.cpp)
TESTS_HDR := $(wildcard tests/*.h) $(wildcard tests/*/*.h)
TESTS_BIN := tests.out
TESTS_BIN_SAN := tests_sanitize.out

ifeq ($(OS), Linux)
	MEM_CHECK := valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$(TESTS_BIN)
else
	MEM_CHECK := CK_FORK=no leaks --atExit -- ./$(TESTS_BIN_SAN)
endif

all: clean test

clean:
	rm -rf *.a *.o .clang-format $(TEST_BIN) $(TEST_BIN_SAN) *.out gcov_report* *.info report *.gcno

test: test_build
	./$(TESTS_BIN)

test_build:
	$(CXX) $(CXX_FLAGS) $(TESTS_SRC) -o $(TESTS_BIN) $(TEST_FLAGS)

test_build_sanitize:
	$(CXX) $(CXX_FLAGS) $(TESTS_SRC) -o $(TESTS_BIN_SAN) $(TEST_FLAGS) -fsanitize=address

codestyle:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n $(LIB_TMP_BASE) $(LIB_TMP_PLUS) $(LIB_HDR_BASE) $(LIB_HDR_PLUS) $(TESTS_SRC) $(TESTS_HDR)

mem_check: test_build test_build_sanitize
	$(MEM_CHECK)

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem --std=c++11 --language=c++ $(LIB_TMP_BASE) $(LIB_TMP_PLUS) $(LIB_HDR_BASE) \
			$(LIB_HDR_PLUS) $(TESTS_SRC) $(TESTS_HDR)

gcov_report:
	$(CXX) $(CXX_FLAGS) $(LIB_TMP_BASE) $(LIB_TMP_PLUS) $(TESTS_SRC) $(TEST_FLAGS) $(GCOVFLAGS) -o $@ 
	- ./$@
	lcov -t $@ -o rep.info -c -d . --ignore-errors mismatch
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno *.info
