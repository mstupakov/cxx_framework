TARGET := app

AR := $(CROSS_COMPILE)ar
LD := $(CROSS_COMPILE)ld
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
STRIP := $(CROSS_COMPILE)strip

CFLAGS := -pg -ggdb -std=c++11 -O3 -static

BASE := $(CURDIR)
BUILD_DIR := $(BASE)/build/

BASE_DIR := $(BASE)/base/
BASE_INC := $(BASE)/base/include/

BASE_SRC := $(wildcard $(BASE_DIR)/*.cpp)
BASE_OBJ := $(subst $(BASE_DIR), $(BUILD_DIR), $(BASE_SRC:%.cpp=%.o))

SYSTEM_DIR := $(BASE)/system/
SYSTEM_INC := $(BASE)/system/include/

SYSTEM_SRC := $(wildcard $(SYSTEM_DIR)/*.cpp)
SYSTEM_OBJ := $(subst $(SYSTEM_DIR), $(BUILD_DIR), $(SYSTEM_SRC:%.cpp=%.o))

all: $(TARGET)

clean:
	rm -rf gmon.out $(TARGET)_gmon.dot $(TARGET) $(BUILD_DIR)/*

$(TARGET): main.cpp $(BUILD_DIR)/base.a $(BUILD_DIR)/system.a
	$(CXX) $(CFLAGS) -I$(BASE_INC) -I$(SYSTEM_INC) $^ -pthread -o $(TARGET)

$(BUILD_DIR)/%.o: $(BASE_DIR)/%.cpp
	$(CXX) $(CFLAGS) -I$(BASE_INC) -I$(SYSTEM_INC) -c $< -o $@

$(BUILD_DIR)/base.a: $(BASE_OBJ)
	$(AR) crs $@ $^

$(BUILD_DIR)/%.o: $(SYSTEM_DIR)/%.cpp
	$(CXX) $(CFLAGS) -I$(SYSTEM_INC) -c $< -o $@

$(BUILD_DIR)/system.a: $(SYSTEM_OBJ)
	$(AR) crs $@ $^

gmon:
	gprof $(TARGET) gmon.out | gprof2dot.py > $(TARGET)_gmon.dot
	xdot $(TARGET)_gmon.dot

.PHONY: all clean gmon
