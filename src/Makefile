# Nombre del compilador
CXX = g++
CXXFLAGS = -O2 -Wall
# Nombre del ejecutable
BRUTE = brute
GEN    = gen
JUDGE  = judge
HEURISTIC = heuristic
KERNEL = kernel

SRC_BRUTE = main.cpp
SRC_HEURISTIC= heuristic.cpp
SRC_GEN   = test_generator.cpp
SRC_JUDGE = judge.cpp
SRC_KERNEL = kernel.cpp

RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[1;33m
BLUE   := \033[0;34m
CYAN   := \033[0;36m
RESET  := \033[0m

all: $(BRUTE) $(HEURISTIC) $(KERNEL) $(GEN) $(JUDGE) 
	@echo "$(GREEN)✨ Compilation finished successfully!$(RESET)"

$(BRUTE): $(SRC_BRUTE)
	@echo "$(BLUE)🚀 Compiling $(SRC_BRUTE)...$(RESET)"
	$(CXX) $(CXXFLAGS) $(SRC_BRUTE) -o $(BRUTE)
	@echo "$(GREEN)✅ Brute Force compiled!$(RESET)"

$(KERNEL): $(SRC_KERNEL)
	@echo "$(BLUE)🚀 Compiling $(SRC_KERNEL)...$(RESET)"
	$(CXX) $(CXXFLAGS) $(SRC_KERNEL) -o $(KERNEL)
	@echo "$(GREEN)✅ Kernel compiled!$(RESET)"

# Compilar generador de tests
$(GEN): $(SRC_GEN)
	@echo "$(BLUE)🚀 Compiling $(SRC_GEN)...$(RESET)"
	$(CXX) $(CXXFLAGS) $(SRC_GEN) -o $(GEN)
	@echo "$(GREEN)✅ Test generator compiled!$(RESET)"

# Compilar juez
$(JUDGE): $(SRC_JUDGE)
	@echo "$(BLUE)🚀 Compiling $(SRC_JUDGE)...$(RESET)"
	$(CXX) $(CXXFLAGS) $(SRC_JUDGE) -o $(JUDGE)
	@echo "$(GREEN)✅ Judge compiled!$(RESET)"

# Compilar juez
$(HEURISTIC): $(SRC_HEURISTIC)
	@echo "$(BLUE)🚀 Compiling $(SRC_HEURISTIC)...$(RESET)"
	$(CXX) $(CXXFLAGS) $(SRC_HEURISTIC) -o $(HEURISTIC)
	@echo "$(GREEN)✅ Heuristic compiled!$(RESET)"

full: all
	@echo "$(YELLOW)🧪 Generating tests...$(RESET)"
	./$(GEN)
	@echo "$(YELLOW)🧪 Running judge...$(RESET)"
	./$(JUDGE)
	@echo "$(CYAN)📄 Results in results.txt$(RESET)"
	@cat results.txt

clean:
	@echo "$(RED)🧹 Cleaning up...$(RESET)"
	rm -f $(BRUTE) $(GEN) $(JUDGE) $(HEURISTIC) $(KERNEL) tests.txt input.tmp output.tmp results.txt
	@echo "$(RED)🗑️ Cleanup complete.$(RESET)"
