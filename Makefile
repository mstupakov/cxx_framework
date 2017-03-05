TARGET := app

AR := $(CROSS_COMPILE)ar
LD := $(CROSS_COMPILE)ld
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
STRIP := $(CROSS_COMPILE)strip

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
	rm -rf $(TARGET) $(BUILD_DIR)/*

$(TARGET): main.cpp $(BUILD_DIR)/base.a $(BUILD_DIR)/system.a
	$(CXX) -ggdb $< -o $(TARGET)
	
$(BASE_OBJ): $(BASE_SRC)
	$(CXX) -ggdb -c $< -o $@ 

$(BUILD_DIR)/base.a: $(BASE_OBJ)
	$(AR) crs $@ $^

$(SYSTEM_OBJ): $(SYSTEM_SRC)
	$(CXX) -ggdb -c $< -o $@ 

$(BUILD_DIR)/system.a: $(SYSTEM_OBJ)
	$(AR) crs $@ $^

.PHONY: all clean
