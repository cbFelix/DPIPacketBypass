TARGET = bin/DPIPacketBypass
SRC_DIR = src
INCLUDE_DIR = include
LIB_DIR = lib 

CXX = g++
CC = gcc

CXXFLAGS = -I$(INCLUDE_DIR) -Wall -std=c++17
CFLAGS = -I$(INCLUDE_DIR) -Wall

ifdef DEBUG
    CXXFLAGS += -g -DDEBUG=true
    CFLAGS += -g -DDEBUG=true
else
    CXXFLAGS += -O2 -DDEBUG=false
    CFLAGS += -O2 -DDEBUG=false
endif

CPP_SRCS = $(wildcard $(SRC_DIR)/**/*.cpp) $(wildcard $(SRC_DIR)/*.cpp) 
C_SRCS = $(wildcard $(SRC_DIR)/**/*.c) $(wildcard $(SRC_DIR)/*.c)
CPP_OBJS = $(CPP_SRCS:.cpp=.o)
C_OBJS = $(C_SRCS:.c=.o)

OBJS = $(CPP_OBJS) $(C_OBJS)

LIBS = -lcurl -lssl -lcrypto  
LDFLAGS = -L$(LIB_DIR) $(LIBS)

$(TARGET): $(OBJS)
	@mkdir -p $(dir $(TARGET))
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
