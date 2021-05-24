SOURCES= Main.cpp Sensor.cpp
OBJECTS=$(SOURCES:.cpp=.o)
DEPS=$(SOURCES:.cpp=.d)
EXE=prog
CXXFLAGS=-I .

# Makingforhost
# > makeARCH=host
ifeq (${ARCH},host)
CXX=g++
BUILD_DIR=build/host
BIN_DIR=bin/host
endif

# Makingfortarget15  
# > makeARCH=target
ifeq (${ARCH},target)
CXX=arm-rpizw-g++
BUILD_DIR=build/target
BIN_DIR=bin/target
endif

$(BIN_DIR)/$(EXE): $(DEPS) $(addprefix $(BUILD_DIR)/,$(OBJECTS)) # <<  Checkthe$(DEPS) newdependency
	$(CXX) $(CXXFLAGS) -o $@ $(addprefix $(BUILD_DIR)/,$(OBJECTS))
	@echo exe file made

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	@echo obj build in dir

%.d: %.cpp
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >>$@
	
copy:
	scp bin/target/prog root@10.9.8.2:

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif
