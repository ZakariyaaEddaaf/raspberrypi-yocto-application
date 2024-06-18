# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11
DEBUGFLAGS = -g -Og
RELEASEFLAGS = -O3 -DNDEBUG

# Linker flags
LDFLAGS = -pthread

# Directories
UTILSDIR = utils
GNSSDIR = global-positioning-system
TCPDIR = transmission-control-protocol

# Source files
SRCS_UTILS = $(UTILSDIR)/serial.cpp
SRCS_GPS = $(GNSSDIR)/gnss.cpp
SRCS_TCP = $(TCPDIR)/server.cpp
SRCS_MAIN = main.cpp

# Object files
OBJS_UTILS = $(SRCS_UTILS:.cpp=.o)
OBJS_GPS = $(SRCS_GPS:.cpp=.o)
OBJS_TCP = $(SRCS_TCP:.cpp=.o)
OBJ_MAIN = $(SRCS_MAIN:.cpp=.o)

# Executable
TARGET = gnss_server

# Default target
all: release

# Debug build
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(TARGET)

# Release build
release: CXXFLAGS += $(RELEASEFLAGS)
release: $(TARGET)

# Linking
$(TARGET): $(OBJS_UTILS) $(OBJS_GPS) $(OBJS_TCP) $(OBJ_MAIN)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS_UTILS) $(OBJS_GPS) $(OBJS_TCP) $(OBJ_MAIN) $(LDFLAGS)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -f $(OBJS_UTILS) $(OBJS_GPS) $(OBJ_MAIN) $(OBJS_TCP) $(TARGET)

.PHONY: all debug release clean
