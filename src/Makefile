# Nombre del compilador
CXX = g++
# Flags de compilación
CXXFLAGS = -O2 -Wall
# Nombre del ejecutable
TARGET = main
# Archivos fuente
SRC = main.cpp

RED    := \033[0;31m
GREEN  := \033[0;32m
YELLOW := \033[1;33m
BLUE   := \033[0;34m
CYAN   := \033[0;36m
RESET  := \033[0m

all: $(TARGET)
	@echo "$(GREEN)✨ Proyecto compilado completamente!$(RESET)"

$(TARGET): $(SRC)
	@echo "$(BLUE)🚀 Compiling $(SRC)...$(RESET)"
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)
	@echo "$(GREEN)✅ Compilation finished successfully!$(RESET)"

run: $(TARGET)
	@echo "$(YELLOW)🧪 Running program...$(RESET)"
	./$(TARGET) 
	@echo "$(CYAN)✅ Running completed!$(RESET)"

clean:
	@echo "$(RED)🧹 Cleaning up...$(RESET)"
	rm -f $(TARGET)
	@echo "$(RED)🗑️ Cleanup complete.$(RESET)"

