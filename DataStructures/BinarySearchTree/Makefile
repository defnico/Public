CC = g++
#CPPFLAGS = -Wall -g -std=c++11 
CPPFLAGS = -Wall -std=c++11 
BIN = bin
MAKE_BIN = $(BIN)/.dirstamp
ifeq ($(shell uname), Darwin)
	GTEST_LL = -I $(HOME)/gtest/include/ -L $(HOME)/gtest/bin/ \
		-l gtest.o -l gtest_main.o -pthread
else
	GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread
endif

all: $(BIN)/bst_test

$(BIN)/bst_test: bst_test.cpp bst.h $(MAKE_BIN)
	$(CC) $(CPPFLAGS) bst_test.cpp $(GTEST_LL) -o $@

$(MAKE_BIN):
	-@mkdir -p bin
	-@touch $@

.PHONY: clean tests
clean:
	rm -rf bin

tests: $(BIN)/bst_test
	-@$(BIN)/bst_test
	-@echo "--- All Tested!---"
