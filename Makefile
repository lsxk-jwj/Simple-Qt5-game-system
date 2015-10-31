
CXX=clang++
LINKER := clang++
INCDIRS := -I. -I./lib/protobuf-2.6.1/src 
LIBDIRS := -L lib/protobuf-2.6.1/src/.libs -L lib/libdontdie 
LIBS := -l protobuf #-l libdontdie
LIBDIRS += $(LIBS)
CXXFLAGS := -std=c++11 -pthread #-Wall -Wextra 
BUILD_DIR=build

PROTO := $(shell bash -c "pwd")/lib/protobuf-2.6.1/src/protoc
MODEL_DIR := model
MODEL_BUILD_DIR := build
MODEL_BIN := $(BUILD_DIR)/bin
MODELS := $(shell bash -c "cd $(MODEL_DIR) && ls *.proto")
INCDIRS += -I$(MODEL_DIR)/$(MODEL_BUILD_DIR)

SERVER_DIR := server
SERVER_BIN := $(BUILD_DIR)/bin
SERVER_SRCFILES := $(wildcard $(SERVER_DIR)/*.cpp) 
SERVER_OBJFILES := $(addprefix $(SERVER_BIN)/, $(patsubst %.cpp,%.o,$(SERVER_SRCFILES)))
SERVER_BUILD := $(SERVER_DIR)/server

KEEP_ALIVE_ENV := DD_TCP_KEEPALIVE_TIME=4 DD_TCP_KEEPALIVE_INTVL=5 DD_TCP_KEEPALIVE_PROBES=6 

.PHONY: init_dir clean

all: init_dir keep_alive proto $(SERVER_BUILD) 


init_dir: 
	@mkdir -p $(SERVER_BIN)/$(SERVER_DIR) $(SERVER_BIN)/$(MODEL_DIR) $(MODEL_DIR)/$(MODEL_BUILD_DIR)

proto: $(addprefix, $(MODEL_DIR)/, $(MODELS))
	@echo $^
	@cd $(MODEL_DIR) && echo compiling protocal buffer files: $(MODELS) && \
	for model in $(MODELS); do $(PROTO) -I=. --cpp_out=./$(MODEL_BUILD_DIR) $$model; done 
	
keep_alive: 
	export $(KEEP_ALIVE_ENV)

$(SERVER_BUILD): $(SERVER_OBJFILES)  $(addprefix $(MODEL_BIN)/$(MODEL_DIR)/, $(patsubst %.cc,%.o,$(shell bash -c 'cd $(MODEL_DIR)/$(MODEL_BUILD_DIR) && ls *.cc')))
	@echo linking $^
	$(LINKER) $^ $(LIBDIRS) -o $@

$(MODEL_DIR)/$(MODEL_BUILD_DIR)/%.cc: $(MODEL_DIR)/%.proto
	@echo compiling $<
	$(PROTO) -I=. --cpp_out=$(MODEL_DIR)/$(MODEL_BUILD_DIR) $< 

$(MODEL_BIN)/$(MODEL_DIR)/%.o: $(MODEL_DIR)/$(MODEL_BUILD_DIR)/%.cc
	@echo compiling $<
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

$(SERVER_BIN)/$(SERVER_DIR)/%.o: $(SERVER_DIR)/%.cpp
	@echo compiling $<
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(MODEL_DIR)/$(MODEL_BUILD_DIR)
