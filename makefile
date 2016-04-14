# Define the compiler and the linker. The linker must be defined since
# the implicit rule for linking uses CC as the linker. g++ can be
# changed to clang++.
CXX = g++
CC  = g++

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of libstd++.
CPPFLAGS  = -std=c++11 -I..
CXXFLAGS  = -g -O2 -Wall -W -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast
CXXFLAGS += -std=c++11
LDFLAGS   = -g -L..
#CPPFLAGS += -stdlib=libc++
#CXXFLAGS += -stdlib=libc++
#LDFLAGS +=  -stdlib=libc++

OUTPUT = bin/
SERVER = src/server/
COMMON = src/common/

# Targets
PROGS = $(SERVER)testMain $(SERVER)newsserver_memory

all: $(PROGS)
	mv $(SERVER)testMain $(OUTPUT)
	mv $(SERVER)newsserver_memory $(OUTPUT)

# Targets rely on implicit rules for compiling and linking
$(SERVER)testMain: $(SERVER)testMain.o $(SERVER)article.o $(SERVER)newsgroup.o $(SERVER)memdatabase.o
$(SERVER)newsserver_memory: $(SERVER)newsserver_memory.o $(SERVER)newsserver.o $(SERVER)server.o $(SERVER)article.o $(SERVER)newsgroup.o $(SERVER)memdatabase.o $(COMMON)connection.o $(COMMON)messagehandler.o


# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f *.o $(PROGS)
	rm -f $(SERVER)*.o
	rm -f $(SERVER)*.d
	rm -f $(COMMON)*.o
	rm -f $(COMMON)*.d
	rm -f $(OUTPUT)testMain
	rm -f $(OUTPUT)newsserver_memory

# Generate dependencies in *.d files
%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)
