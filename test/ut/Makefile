CXX := g++
CXXFLAGS := --std=c++11

GTEST_DIR := $(CURDIR)/../googletest/googletest
GMOCK_DIR := $(CURDIR)/../googletest/googlemock


INCLUDES := \
			-I$(GTEST_DIR)/include \
			-I$(GMOCK_DIR)/include

LIBS := \
			-lpthread

MAIN_CC := \
			main.cc

MAIN_OBJ := $(MAIN_CC:.cc=.o) \
			gtest.o           \
			gmock.o

BIN := gtest.app

build: $(BIN)

$(BIN): $(MAIN_OBJ)
	$(CXX) -o $@ $^ $(LIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ -c $<

gtest.o: $(GTEST_DIR)/src/gtest-all.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -I$(GTEST_DIR) -o $@ -c $<

gmock.o: $(GMOCK_DIR)/src/gmock-all.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -I$(GMOCK_DIR) -o $@ -c $<

clean:
	find $(CURDIR) -name '*.o' -exec rm -f {} +
	find $(CURDIR) -name '*.app' -exec rm -f {} +