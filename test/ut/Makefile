CXX := g++
CXXFLAGS := --std=c++11

ALG_SRC_DIR := $(CURDIR)/../../src
SORT_SRC_DIR := $(ALG_SRC_DIR)/sort
GTEST_DIR := $(CURDIR)/../googletest/googletest
GMOCK_DIR := $(CURDIR)/../googletest/googlemock


INCLUDES :=                \
	-I$(GTEST_DIR)/include \
	-I$(GMOCK_DIR)/include \
	-I$(SORT_SRC_DIR)

LIBS := \
	-lpthread

MAIN_CC := \
	main.cc

SORT_CC := \
	test_sort.cc \
	$(wildcard $(SORT_SRC_DIR)/*.cc)

MAIN_OBJ :=           \
	$(MAIN_CC:%.cc=%.o) \
	gtest.o           \
	gmock.o

SORT_OBJ := $(SORT_CC:%.cc=%.o)


BIN := gtestSort.app

build: $(BIN)

gtestSort.app: $(MAIN_OBJ) $(SORT_OBJ)
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