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
CLIENT = src/client/

# Targets
PROGS = $(SERVER)testMain $(SERVER)newsserver_memory $(CLIENT)clientMain $(SERVER)newsserver_disk

all: $(PROGS)
	mv $(SERVER)testMain $(OUTPUT)
	mv $(SERVER)newsserver_memory $(OUTPUT)
	mv $(SERVER)newsserver_disk $(OUTPUT)
	mv $(CLIENT)clientMain $(OUTPUT)client

# Targets rely on implicit rules for compiling and linking
$(SERVER)testMain: $(SERVER)testMain.o $(SERVER)article.o $(SERVER)newsgroup.o $(SERVER)memdatabase.o
$(SERVER)newsserver_memory: $(SERVER)newsserver_memory.o $(SERVER)newsserver.o $(SERVER)server.o $(SERVER)article.o $(SERVER)newsgroup.o $(SERVER)memdatabase.o $(COMMON)connection.o $(COMMON)messagehandler.o $(SERVER)servercommandhandler.o
$(SERVER)newsserver_disk: $(SERVER)newsserver_disk.o $(SERVER)newsserver.o $(SERVER)server.o $(SERVER)article.o $(SERVER)newsgroup.o $(SERVER)diskdatabase.o $(COMMON)connection.o $(COMMON)messagehandler.o $(SERVER)servercommandhandler.o
$(CLIENT)clientMain: $(CLIENT)clientMain.o $(COMMON)connection.o $(COMMON)messagehandler.o $(CLIENT)clientcommandhandler.o $(CLIENT)inputhandler.o

# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f *.o $(PROGS)
	rm -f $(SERVER)*.o
	rm -f $(SERVER)*.d
	rm -f $(COMMON)*.o
	rm -f $(COMMON)*.d
	rm -f $(CLIENT)*.o
	rm -f $(CLIENT)*.d
	rm -f $(OUTPUT)*
	rm -f -r database/*
# Generate dependencies in *.d files
%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)
