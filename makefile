# -------------------------
# Configuration
# -------------------------
BUILD_DIR = Build
TARGET = Main.exe
SRC_DIR = Src

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -O2
LDFLAGS = 

# Automatically find all .cpp files in SRC_DIR
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC))

# -------------------------
# Targets
# -------------------------

# Only build with 'make all'
all: $(BUILD_DIR)/$(TARGET)

# Create build dir if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile each .cpp into .o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link all object files into the final executable
$(BUILD_DIR)/$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Clean
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*.o $(BUILD_DIR)/$(TARGET)
