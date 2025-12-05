# 1. Noms des exécutables
TARGET   = main
TEST_BIN = unit_test/tests

# 2. Compilateur
CXX = g++

# 3. Options de compilation
override CXXFLAGS += -g -std=c++17 -Wall -Wextra

# 4. Bibliothèques SFML
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# 5. Sources principales (on ignore Data, .git, .ccls-cache, unit_test)
SRCS = $(shell find . \
  -type d \( -name ".ccls-cache" -o -name ".git" -o -name "Data" -o -name "unit_test" \) -prune -o \
  -type f -name '*.cpp' -print)

HEADERS = $(shell find . \
  -type d \( -name ".ccls-cache" -o -name ".git" -o -name "Data" -o -name "unit_test" \) -prune -o \
  -type f -name '*.h' -print)

OBJS = $(SRCS:.cpp=.o)

# 6. Sources de tests (dans unit_test/, nommés test_*.cpp)
TEST_SRCS = $(shell find unit_test -maxdepth 1 -type f -name 'test_*.cpp')
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

# =============== RÈGLES PRINCIPALES ===============

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o "$@" $(LIBS)

# =============== TESTS UNITAIRES ==================

test: $(TEST_BIN)
	./$(TEST_BIN)

# On linke tous les objets SAUF main.o pour ne pas embarquer ton main()
$(TEST_BIN): $(TEST_OBJS) $(filter-out ./main.o, $(OBJS))
	$(CXX) $(CXXFLAGS) $^ -o "$@" $(LIBS)

# =============== COMPILATION GÉNÉRIQUE ============

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -I. -c $< -o $@

# =============== NETTOYAGE ========================

clean:
	rm -f $(TARGET) $(TEST_BIN) $(OBJS) $(TEST_OBJS)

.PHONY: all test clean
