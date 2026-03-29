SRC_DIR := src
BIN_DIR := bin
FLAGS 	:= -w -Wall -Wextra

SRCS := $(shell find $(SRC_DIR) -name *.cpp)

# maps sources to objects
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

getsrcs: 
	@echo $(SRCS)

server : $(OBJS)
	g++ $(OBJS) -o $(BIN_DIR)/server.exe

$(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	g++ $(FLAGS) -Iinclude -c $< -o $@

clean: 
	rm -rf $(BIN_DIR)