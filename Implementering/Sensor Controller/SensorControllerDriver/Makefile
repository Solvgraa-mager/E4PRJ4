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

# %. cpp->  %. o needsto  be  added! Targetis  NOT just%. o...
# Rulethatdescribeshowa .d (dependency) fileis  created from a .cpp file

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	@echo obj build in dir

# Similarto  theassigmentthatyoujustcompleted%. cpp->  %. o
%.d: %.cpp
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >>$@

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif