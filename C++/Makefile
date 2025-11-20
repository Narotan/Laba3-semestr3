# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lgtest -lgtest_main -pthread

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
TEST_OBJ_DIR = $(BUILD_DIR)/test_obj

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Test files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp,$(TEST_OBJ_DIR)/%.o,$(TEST_SOURCES))

# Targets
MAIN = main
TEST_EXEC = $(BUILD_DIR)/run_tests

# Colors for output
GREEN = \033[0;32m
NC = \033[0m # No Color

.PHONY: all clean test coverage run directories

all: directories $(MAIN)

directories:
	@mkdir -p $(OBJ_DIR) $(TEST_OBJ_DIR)

$(MAIN): $(OBJECTS) main.cpp
	@echo "$(GREEN)Building main executable...$(NC)"
	$(CXX) $(CXXFLAGS) main.cpp $(OBJECTS) -o $(MAIN)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "$(GREEN)Compiling $<...$(NC)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test compilation
$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	@echo "$(GREEN)Compiling test $<...$(NC)"
	$(CXX) $(CXXFLAGS) --coverage -c $< -o $@

# Build object files for coverage
$(OBJ_DIR)/%.cov.o: $(SRC_DIR)/%.cpp
	@echo "$(GREEN)Compiling with coverage $<...$(NC)"
	$(CXX) $(CXXFLAGS) --coverage -c $< -o $@

test: directories $(TEST_EXEC)
	@echo "$(GREEN)Running tests...$(NC)"
	./$(TEST_EXEC)

$(TEST_EXEC): $(patsubst $(OBJ_DIR)/%.o,$(OBJ_DIR)/%.cov.o,$(OBJECTS)) $(TEST_OBJECTS)
	@echo "$(GREEN)Building test executable...$(NC)"
	$(CXX) $(CXXFLAGS) --coverage $^ -o $@ $(LDFLAGS)

coverage: test
	@echo "$(GREEN)Generating coverage report...$(NC)"
	@mkdir -p coverage
	@{ \
	if command -v lcov >/dev/null 2>&1; then \
	  echo "Using lcov"; \
	  lcov --capture --directory . --output-file coverage/coverage.info --ignore-errors inconsistent,unsupported,format || true; \
	  lcov --remove coverage/coverage.info '/usr/*' '/Library/*' '/Library/Developer/*' '/opt/*' '/opt/homebrew/*' '*/tests/*' --output-file coverage/coverage.cleaned.info || true; \
	  if [ -s coverage/coverage.cleaned.info ]; then genhtml coverage/coverage.cleaned.info --output-directory coverage/html || true; fi; \
	else \
	  echo "lcov not found"; \
	fi; \
	if [ ! -d coverage/html ] || [ ! -s coverage/coverage.cleaned.info ]; then \
	  if command -v gcovr >/dev/null 2>&1; then \
	    echo "Falling back to gcovr"; \
	    gcovr -r . --html --html-details -o coverage/html/index.html; \
	  else \
	    echo "Neither lcov/genhtml nor gcovr produced a report. Install lcov or gcovr."; exit 1; \
	  fi; \
	fi; \
	echo "$(GREEN)Coverage report generated in coverage/html/index.html$(NC)"; \
	}

run: $(MAIN)
	@echo "$(GREEN)Running main program...$(NC)"
	./$(MAIN)

clean:
	@echo "$(GREEN)Cleaning...$(NC)"
	rm -rf $(BUILD_DIR) $(MAIN) coverage *.gcda *.gcno *.gcov *.bin
	find . -name "*.o" -delete
	find . -name "*.gcda" -delete
	find . -name "*.gcno" -delete

help:
	@echo "Available targets:"
	@echo "  make all      - Build main executable"
	@echo "  make run      - Build and run main executable"
	@echo "  make test     - Build and run tests"
	@echo "  make coverage - Generate coverage report (requires lcov)"
	@echo "  make clean    - Remove all build artifacts"
