
CXX=clang++
LINKER := clang++
INCDIRS := -I. -I./lib/protobuf-2.6.1/src 
LIBDIRS := -L lib/protobuf-2.6.1/src/.libs -L lib/libdontdie 
LIBS := -lprotobuf -llibdontdie
LIBDIRS += $(LIBS)
CXXFLAGS := -std=c++11 -Wall -Wextra -pthread 
BUILD_DIR=build


PROTO := lib/protobuf-2.6.1/src/protoc
MODEL := model.proto
MODEL_DIR := model
MODEL_BIN := $(BUILD_DIR)/bin
MODEL_SRCFILES := $(wildcard $(MODEL_DIR)/*.cc) 
MODEL_OBJFILES := $(addprefix $(MODEL_BIN)/, $(patsubst %.cc,%.o,$(MODEL_SRCFILES)))
INCDIRS += -I$(MODEL_DIR)

SERVER_DIR := server
SERVER_BIN := $(BUILD_DIR)/bin
SERVER_SRCFILES := $(wildcard $(SERVER_DIR)/*.cpp) 
SERVER_OBJFILES := $(addprefix $(SERVER_BIN)/, $(patsubst %.cpp,%.o,$(SERVER_SRCFILES)))
SERVER_OBJFILES += $(MODEL_OBJFILES)

KEEP_ALIVE_ENV := DD_TCP_KEEPALIVE_TIME=4 DD_TCP_KEEPALIVE_INTVL=5 DD_TCP_KEEPALIVE_PROBES=6 

.PHONY: init_dir clean

all: init_dir keep_alive proto build_server 
	

init_dir: 
	@mkdir -p $(SERVER_BIN)/$(SERVER_DIR) $(SERVER_BIN)/$(MODEL_DIR) $(MODEL_DIR)

proto:
	$(PROTO) -I=. --cpp_out=$(MODEL_DIR) $(MODEL)

keep_alive: 
	export $(KEEP_ALIVE_ENV)

build_server: $(SERVER_OBJFILES) 
	@echo linking $^
	$(LINKER) $^ $(LIBDIRS) -o $(BUILD_DIR)/server

$(SERVER_BIN)/$(SERVER_DIR)/%.o: $(SERVER_DIR)/%.cpp
	@echo compiling $<
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

$(MODEL_BIN)/$(MODEL_DIR)/%.o: $(MODEL_DIR)/%.cc
	@echo compiling $<
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
