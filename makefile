
COMPILER=g++

SRC_DIR=src
BUILD_DIR=build

FILE=main.cpp
OUT=out
OUT_BUF=$(FILE)

FLAGS=-std=c++20 -o

$(BUILD_DIR)/$(OUT): $(SRC_DIR)/$(FILE)
	$(COMPILER) $(SRC_DIR)/$(FILE) $(FLAGS) $(BUILD_DIR)/$(OUT)

