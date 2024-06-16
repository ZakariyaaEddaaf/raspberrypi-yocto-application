# Compiler
CXX = g++
# Compiler flags
CXXFLAGS = -Wall -std=c++11
DEBUGFLAGS = -g -Og
RELEASEFLAGS = -O3 -DNDEBUG

# Directories
UTILSDIR = utils
GNSSDIR = global-positioning-system

# Source files
SRCS_UTILS = $(UTILSDIR)/serial.cpp
SRCS_GPS = $(GNSSDIR)/gnss.cpp
SRCS_MAIN = main.cpp

# Header files
HEADERS_UTILS = $(wildcard $(UTILSDIR)/*.hpp)
HEADERS_GPS = $(wildcard $(GNSSDIR)/*.hpp)

# Object files
OBJS_UTILS = $(SRCS_UTILS:.cpp=.o)
OBJS_GPS = $(SRCS_GPS:.cpp=.o)
OBJ_MAIN = $(SRCS_MAIN:.cpp=.o)

# Executable
TARGET = gps_server

# Default target
all: release

# Debug build
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(TARGET)

# Release build
release: CXXFLAGS += $(RELEASEFLAGS)
release: $(TARGET)

# Linking
$(TARGET): $(OBJS_UTILS) $(OBJS_GPS) $(OBJ_MAIN)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS_UTILS) $(OBJS_GPS) $(OBJ_MAIN)

# Compile source files into object files
%.o: %.cpp $(HEADERS_UTILS) $(HEADERS_GPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS_UTILS) $(OBJS_GPS) $(OBJ_MAIN) $(TARGET)

.PHONY: all debug release clean
