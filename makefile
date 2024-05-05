# Makefile variables
CC := gcc
CXX := g++
OBJ := ./object_files
IMP := ./implement_files
IMPS := $(wildcard $(IMP)/*.cpp)
OBJS := $(patsubst $(IMP)/%.cpp,$(OBJ)/%.o,$(IMPS))
MKDIR := mkdir
RMDIR := rm -rf $(OBJ)
EXE := ./gamma

.PHONY: all run clean

# Used to compile all files
all: $(EXE)

# Compile main.cpp
$(EXE): $(OBJS)
	$(CXX) main.cpp -o gamma $(OBJS)

# Compiles any missing files from the 'object_files' folder
$(OBJ)/%.o: $(IMP)/%.cpp | $(OBJ)
	$(CC) -c $^ -o $@

# Makes the 'object_files' folder if it does not exist
$(OBJ):
	$(MKDIR) $@

# Runs the program (no args)
run: $(EXE)
	./$^

# Removes ALL complied files and 'object_files' directory
clean:
	$(RMDIR) \
	rm gamma