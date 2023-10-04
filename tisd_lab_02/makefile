СС := gcc
FLAGS := -std=c99 -Wall -Werror -Wextra -pedantic -I./inc
UNIT_FLAGS := -lcheck -lm -lsubunit
UNIT_MODULES :=filter sort

FUNC_DIR := ./func_tests

SRC_DIR := ./src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

INC_DIR := ./inc
INC_FILES := $(wildcard $(INC_DIR)/*.h)

INC_C_FILES := $(filter-out $(INC_DIR)/check_%.h,$(INC_FILES))
INC_UNIT_FILES := $(filter $(INC_DIR)/check_%.h,$(INC_FILES))

UNIT_DIR := ./unit_tests
UNIT_FILES := $(wildcard $(UNIT_DIR)/*.c)

OUT_DIR := ./out
OBJ_FILES := $(SRC_FILES:$(SRC_DIR)/%.c=$(OUT_DIR)/%.o)

UNIT_OBJ := $(UNIT_FILES:$(UNIT_DIR)/%.c=$(OUT_DIR)/%.o)
UNIT_OBJ += $(addprefix ./out/,$(addsuffix .o,$(UNIT_MODULES)))

app.exe : $(OUT_DIR) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@

unit_tests.exe: $(OUT_DIR) $(UNIT_OBJ)
	$(CC) $(UNIT_OBJ) -o $@ $(UNIT_FLAGS)

$(OUT_DIR) :
	mkdir $@

$(OUT_DIR)/%.o : $(SRC_DIR)/%.c $(INC_C_FILES)
	$(CC) $(FLAGS) -c $< -o $@

$(OUT_DIR)/%.o: $(UNIT_DIR)/%.c $(INC_UNIT_FILES)
	$(CC) $(FLAGS) $(UNIT_FLAGS) -c $< -o $@

.PHONY : clean unit func all

unit: unit_tests.exe
	./$^

func :
	cd $(FUNC_DIR)/scripts && ./func_test.sh

all : app.exe unit_tests.exe

clean:
	rm -r $(OUT_DIR) *.exe