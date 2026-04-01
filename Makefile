# C++ variables
SRC_DIR 	:= src
BIN_DIR 	:= bin
CXXFLAGS 	:= -g -Wall #-Wextra

# typescript variables
NODE_PATH 	:= /c/Program Files/nodejs/
UI_SRC		:= ui/src
UI_BIN		:= ui/bin
HTML_BIN  	:= $(BIN_DIR)/html

# find all the sources
SRCS 		:= $(shell find $(SRC_DIR) -name "*.cpp")
TS_SRCS 	:= $(shell find ui/src -name "*.ts")

# map cpp sources to objects
OBJS 		:= $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o) 

# add nodeJS to path cause mingw doens't have it
export PATH := $(NODE_PATH):$(PATH)

# TARGETS
.PHONY : all clean copy-ui

all : server copy-ui

# build the server binary
server : $(OBJS)
	g++ $(OBJS) -o $(BIN_DIR)/server.exe -lws2_32

# build the object files
$(BIN_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	g++ $(CXXFLAGS) -Iinclude -c $< -o $@

# build the frontend
$(UI_BIN)/index.js : $(TS_SRCS)
	@mkdir -p $(UI_BIN)
	(cd $(UI_BIN) && npx tsc)

# copy the frontend
copy-ui: $(UI_BIN)/index.js
	@mkdir -p $(HTML_BIN)
	cp $(UI_BIN)/index.js $(UI_SRC)/index.html $(UI_SRC)/main.css $(HTML_BIN)

clean: 
	rm -rf $(BIN_DIR)
	rm -rf $(UI_BIN)