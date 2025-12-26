# Nombre del compilador
CXX = g++
CXXFLAGS = -O2 -Wall
CASES_TESTS = 20
# Nombre del ejecutable
BIN = bin
BRUTE = $(BIN)/brute
TEST    = $(BIN)/test
JUDGE  = $(BIN)/judge
DCMST = $(BIN)/dcmst
CHECKER = $(BIN)/checker

SRC_BRUTE = brute_solver/main.cpp
SRC_DCMST = dcmst_sol/dcmst.cpp
SRC_TEST   = judging/test_generator.cpp
SRC_JUDGE = judging/judge.cpp
SRC_CHECKER = judging/checker.cpp

RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[1;33m
BLUE   := \033[0;34m
CYAN   := \033[0;36m
RESET  := \033[0m

$(BIN):
	mkdir -p $(BIN)

all: $(BRUTE) $(DCMST) $(TEST) $(CHECKER) $(JUDGE) 
	@echo "$(GREEN)✨ Compilation finished successfully!$(RESET)"

$(BRUTE): $(SRC_BRUTE) | $(BIN)
	@echo "$(BLUE)🚀 Compiling $(SRC_BRUTE)...$(RESET)"
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "$(GREEN)✅ Brute Force compiled!$(RESET)"

$(DCMST): $(SRC_DCMST) | $(BIN)
	@echo "$(BLUE)🚀 Compiling $(SRC_DCMST)...$(RESET)"
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "$(GREEN)✅ DCMST compiled!$(RESET)"

$(TEST): $(SRC_TEST) | $(BIN)
	@echo "$(BLUE)🚀 Compiling $(SRC_TEST)...$(RESET)"
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "$(GREEN)✅ Test generator compiled!$(RESET)"

$(CHECKER): $(SRC_CHECKER) | $(BIN)
	@echo "$(BLUE)🚀 Compiling $(SRC_CHECKER)...$(RESET)"
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "$(GREEN)✅ Checker compiled!$(RESET)"

$(JUDGE): $(SRC_JUDGE) | $(BIN)
	@echo "$(BLUE)🚀 Compiling $(SRC_JUDGE)...$(RESET)"
	$(CXX) $(CXXFLAGS) $< -o $@
	@echo "$(GREEN)✅ Judge compiled!$(RESET)"

gen-tests: test_generator
	@chmod +x generate_tests.sh
	@echo "$(YELLOW)🧪 Generating $(CASES_TESTS) tests...$(RESET)"
	./generate_tests.sh $(CASES_TESTS)

full: all gen-tests
	@echo "$(YELLOW)🧪 Running judge...$(RESET)"
	./$(JUDGE)
	@echo "$(CYAN)📄 Results in logs$(RESET)"

one: all
	@echo "$(YELLOW)🧪 Running judge...$(RESET)"
	./$(JUDGE)
	@echo "$(CYAN)📄 Results in logs$(RESET)"

clean:
	@echo "$(RED)🧹 Cleaning up...$(RESET)"
	rm -rf bin outputs logs 
	@echo "$(RED)🗑️ Cleanup complete.$(RESET)"
