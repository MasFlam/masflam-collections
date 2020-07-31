
CC := g++
CC_FLAGS := -std=c++2a
CC_MAIN_FLAGS := -g
CC_TEST_FLAGS :=


MAIN_SRC_DIR := src/main
TEST_SRC_DIR := src/test
MAIN_TARGET_DIR := target/main
TEST_TARGET_DIR := target/test

MAIN_SRCS_CPP := $(wildcard $(MAIN_SRC_DIR)/*.cpp)
MAIN_SRCS_HPP := $(wildcard $(MAIN_SRC_DIR)/*.hpp)
MAIN_OBJS_O := $(patsubst $(MAIN_SRC_DIR)/%.cpp,$(MAIN_TARGET_DIR)/%.o,$(MAIN_SRCS_CPP))
MAIN_OBJC_GCH := $(patsubst $(MAIN_SRC_DIR)/%.hpp,$(MAIN_TARGET_DIR)/%.gch,$(MAIN_SRCS_HPP))
TEST_SRCS := $(wildcard $(TEST_SRC_DIR)/*.test.cpp)
TEST_OBJS := $(patsubst $(TEST_SRC_DIR)/%.test.cpp,$(TEST_TARGET_DIR)/%.test.out,$(TEST_SRCS))


.PHONY: all compile test-compile test-run clean

all: clean compile test-compile test-run


compile: $(MAIN_OBJS_O) $(MAIN_OBJS_GCH)

$(MAIN_TARGET_DIR)/%.o: $(MAIN_SRC_DIR)/%.cpp | $(MAIN_TARGET_DIR)
	$(CC) $(CC_FLAGS) $(CC_MAIN_FLAGS) -c $< -o $@

$(MAIN_TARGET_DIR)/%.gch: $(MAIN_SRC_DIR)/%.hpp | $(MAIN_TARGET_DIR)
	$(CC) $(CC_FLAGS) $(CC_MAIN_FLAGS) -c $< -o $@

$(MAIN_TARGET_DIR):
	mkdir -p $@


test-compile: $(TEST_OBJS)

$(TEST_TARGET_DIR)/%.test.out: $(TEST_SRC_DIR)/%.test.cpp | $(TEST_TARGET_DIR)
	$(CC) $(CC_FLAGS) $(CC_TEST_FLAGS) $< $(wildcard $(MAIN_TARGET_DIR)/*.gch) $(wildcard $(MAIN_TARGET_DIR)/*.o) -I$(MAIN_SRCS_DIR) -o $@

$(TEST_TARGET_DIR):
	mkdir -p $@


test-run:
	@echo "]] Running tests"
	$(foreach TEST_OBJ,$(TEST_OBJS),\
		@echo "] Running test $(notdir $(basename $(basename $(TEST_OBJ))))";\
		./$(TEST_OBJ);\
	)


clean:
	@rm -rf $(MAIN_TARGET_DIR) $(TEST_TARGET_DIR)
	@echo "]] Directories $(MAIN_TARGET_DIR) $(TEST_TARGET_DIR) have been removed"