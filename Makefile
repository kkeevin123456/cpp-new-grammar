# ============================================================
#  C++ OOP Practice Project - Makefile
#  Compiler: g++ 13 | Standard: C++20
# ============================================================

CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -g
SRCDIR   := src
OBJDIR   := build
TARGET   := app

# 自動抓取所有 .cpp
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

.PHONY: all clean run help

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "✅ Built: $(TARGET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	@echo "▶ Running..."
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)
	@echo "🧹 Cleaned"

help:
	@echo "make        → build"
	@echo "make run    → build + run"
	@echo "make clean  → remove build files"