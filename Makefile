NAME = bitprob
TEST = test_bloomfilter
EXAMPLE = example_basic

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17
INCLUDES = -Iinclude

SRC = \
	src/BloomFilter.cpp \
	src/Hash.cpp

TEST_SRC = \
	tests/BloomFilterTest.cpp

EXAMPLE_SRC = \
	examples/basic.cpp

all: $(TEST) $(EXAMPLE)

$(TEST): $(SRC) $(TEST_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) $(TEST_SRC) -o $(TEST)

$(EXAMPLE): $(SRC) $(EXAMPLE_SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) $(EXAMPLE_SRC) -o $(EXAMPLE)

test: $(TEST)
	./$(TEST)

run: $(EXAMPLE)
	./$(EXAMPLE)

clean:
	rm -f $(TEST) $(EXAMPLE)

.PHONY: all test run clean