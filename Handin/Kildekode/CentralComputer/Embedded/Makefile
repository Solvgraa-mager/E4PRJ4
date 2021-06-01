EXECUTEABLE = Exe
SRC = E4PRJ4.cpp init_ini.cpp SensorEnhed.cpp AktuatorEnhed.cpp
OBJ = $(SRC:.cpp=.o)
DEPS= $(SRC :.cpp=.d)
CXXFLAGS = -I. -Wall -pthread
SQLFLAGS = MYSQLCFLAGS= -I/usr/include/mysql -DBIG_JOINS=1 -fno-strict-aliasing -g
SQLLIBS = MYSQLLIBS= -L/usr/lib/arm-linux-gnueabihf -lmysqlclient -lpthread -lz -lm -lrt -ldl
RED=\033[0;31m
GREEN=\033[0;32m
ORANGE=\033[0;33m
BLUE=\033[0;34m
NC=\033[0m

#Making for host / target

ifeq (${ARCH},host)
CXX = g++
BUILD_DIR = build/host
BIN_DIR = bin/host
endif

ifeq (${ARCH},target)
CXX = arm-rpizw-g++
BUILD_DIR = build/target
BIN_DIR = bin/target
endif

.PHONY: all
	all: ${EXECUTEABLE}

# Her sætttes sti på filnavnet ved executable, hvor denne skal lægges.
# makefilen skal have at vide, hvor filerne til link er placeret, og derfor skkrives linje 32 om til dette.

$(BIN_DIR)/${EXECUTEABLE}:$(DEPS) $(addprefix $(BUILD_DIR)/,$(OBJ))
	@echo "${BLUE}Linking: $@ ${NC}"
	$(CXX) $(CXXFLAGS) -o $@ $(addprefix $(BUILD_DIR)/,$(OBJ))

#Tilsvarende skal compileren have at vide, hvor .o filerne skal lægges. Da .cpp ligger i src sammen med make, skal der ikke tilføjes sti til denne. 
$(BUILD_DIR)/%.o: %.cpp
	@echo "${BLUE}Compiling: $@ ${NC}"
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(SQLFLAGS) $(SQLLIBS)
	

%.d: %.cpp
	$(CXX) -MT$@ -MM $(CXXFLAGS) $< > $@  
	#Det sidste angiver input output
	$(CXX) -MT$(@:.d=.o) -MM $(CXXFLAGS) $< >> $@

#Make clean fjerne ikke .d filer, da disse ikke vil ændre sig??
ifneq ($(filter-out  clean format tidy, $(MAKECMDGOALS)),)
-include $(DEPS)
endif

#Make directories for good filestructure:
$(BUILD_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@	


format: $(SRC:.cpp=.format)
%.format: %.cpp
	@echo "Formatting file '$<'"...
	@clang-format -i $<
	@echo "" > $@

tidy: $(SRC:.cpp=.tidy)
%.tidy: %.cpp
	@echo "Tidying file '$<'"...
	@clang-tidy $< -- $(CXXFLAGS)
	@echo "" > $@


.PHONY: clean
clean:
	rm -f $(EXECUTEABLE) *.o
	rm -f $(BUILD_DIR)/$(EXECUTEABLE)%.o

.PHONY: help
help:
	@echo "Wow.. A makefile to build a 3 part file system..\nYay..."
	@echo Available target:
	@echo ${EXECUTEABLE}				


