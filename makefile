CPPC = g++
CC = gcc
LIB_FLAGS = -Llib -lPCANBasic
INC_DIR = inc
SRC_DIR = src
OUT_DIR = out
FLAGS = -g -I$(INC_DIR) $(LIB_FLAGS)
OUTPUT = -o $@

_OBJS = main.o
OBJS = $(addprefix $(OUT_DIR)/, $(_OBJS))

PCAN_Cap.exe: $(_OBJS)
	$(CPPC) $(FLAGS) $(OBJS) -o $(OUT_DIR)/$@

%.o: $(SRC_DIR)/%.cpp
	$(CPPC) $(FLAGS) -c $^ -o $(OUT_DIR)/$@

%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -c $^ -o $(OUT_DIR)/$@

.PHONY: clean

clean:
	rm -rf $(OUT_DIR)/*.o
	rm -rf $(OUT_DIR)/*.exe