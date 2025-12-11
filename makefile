# -------------------------
# Configuration
# -------------------------
BUILD_DIR = Build
OBJ_DIR = $(BUILD_DIR)/objects
MSYS_PATH_BIN = /c/msys64/mingw64/bin
TARGET = Main.exe
SRC_DIR = Src
COPY_DLL = None

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -O2
CXXFLAGS += -I $(SRC_DIR)/imgui
CXXFLAGS += -I $(SRC_DIR)/imgui/backends
LDFLAGS = -ld3d11 -ld3dcompiler -lgdi32 -ldwmapi -luser32 -lkernel32 -lole32 -loleaut32

# -------------------------
# Source and object files
# -------------------------

# Find all .cpp files recursively
SRC = $(shell find $(SRC_DIR) -type f -name '*.cpp')

# Flatten object files: put them all in OBJ_DIR
OBJ = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.cpp=.o)))

# Path to required DLLs
DLL = $(MSYS_PATH_BIN)/libstdc++-6.dll
DLL += $(MSYS_PATH_BIN)/libwinpthread-1.dll
DLL += $(MSYS_PATH_BIN)/libgcc_s_seh-1.dll

# -------------------------
# Targets
# -------------------------

# Default target
all: $(BUILD_DIR)/$(TARGET) $(COPY_DLL)
	@echo "Build complete."

# Create build and object directories
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile each source file into an object file in OBJ_DIR
define make-compile-rule
$(OBJ_DIR)/$(notdir $(1:.cpp=.o)): $(1) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $$< -o $$@
endef
$(foreach src,$(SRC),$(eval $(call make-compile-rule,$(src))))

# Link all object files
$(BUILD_DIR)/$(TARGET): $(OBJ) | $(BUILD_DIR)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)


.PHONY: $(COPY_DLL)
$(COPY_DLL):
	@for dll in $(DLL); do \
		cp $$dll $(BUILD_DIR); \
	done

# Clean only object files
.PHONY: cleanobj
cleanobj:
	rm -f $(OBJ_DIR)/*.o

# Clean everything
.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/*.o $(BUILD_DIR)/$(TARGET)
