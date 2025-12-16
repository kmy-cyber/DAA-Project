# Nombre del compilador
CXX = g++
CXXFLAGS = -O2 -Wall
# Nombre del ejecutable
TARGET = main
GEN    = gen
JUDGE  = judge

SRC_MAIN = main.cpp
SRC_GEN   = test_generator.cpp
SRC_JUDGE = judge.cpp

RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[1;33m
BLUE   := \033[0;34m
CYAN   := \033[0;36m
RESET  := \033[0m

all: $(TARGET) $(GEN) $(JUDGE)
	@echo "$(GREEN)✨ Proyecto compilado completamente!$(RESET)"

$(TARGET): $(SRC_MAIN)
	@echo "$(BLUE)🚀 Compiling $(SRC)...$(RESET)"
	$(CXX) $(CXXFLAGS) $(SRC_MAIN) -o $(TARGET)
	@echo "$(GREEN)✅ Compilation finished successfully!$(RESET)"

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

# run: $(TARGET)
# 	@echo "$(YELLOW)🧪 Running program...$(RESET)"
# 	./$(TARGET) 
# 	@echo "$(CYAN)✅ Running completed!$(RESET)"

full: all
	@echo "$(YELLOW)🧪 Generating tests...$(RESET)"
	./$(GEN)
	@echo "$(YELLOW)🧪 Running judge...$(RESET)"
	./$(JUDGE)
	@echo "$(CYAN)📄 Results in results.txt$(RESET)"
	@cat results.txt

clean:
	@echo "$(RED)🧹 Cleaning up...$(RESET)"
	rm -f $(TARGET) $(GEN) $(JUDGE) tests.txt input.tmp output.tmp results.txt
	@echo "$(RED)🗑️ Cleanup complete.$(RESET)"
