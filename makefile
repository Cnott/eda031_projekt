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
MEMSRV = src/server/newsserver_memory/
DSKSRV = src/server/newsserver_disk/
CONNEC = src/connection/
CLIENT = src/client/
EXCEPT = $(CONNEC)exceptions/

# Targets
PROGS = $(MEMSRV)newsserver_memory $(CLIENT)clientMain \
				$(DSKSRV)newsserver_disk

install: $(PROGS)
	rm -f -r $(OUTPUT)
	mkdir $(OUTPUT)
	mv $(MEMSRV)newsserver_memory $(OUTPUT)
	mv $(DSKSRV)newsserver_disk $(OUTPUT)
	mv $(CLIENT)clientMain $(OUTPUT)client

all: $(MEMSRV)newsserver_memory $(DSKSRV)newsserver_disk $(CLIENT)clientMain

# Targets rely on implicit rules for compiling and linking
$(MEMSRV)newsserver_memory: $(MEMSRV)newsserver_memory.o $(SERVER)newsserver.o \
														$(SERVER)server.o $(SERVER)article.o \
														$(SERVER)newsgroup.o $(MEMSRV)memdatabase.o \
														$(CONNEC)connection.o $(CONNEC)messagehandler.o \
														$(SERVER)servercommandhandler.o
$(DSKSRV)newsserver_disk: 	$(DSKSRV)newsserver_disk.o $(SERVER)newsserver.o \
														$(SERVER)server.o $(SERVER)article.o \
														$(SERVER)newsgroup.o $(DSKSRV)diskdatabase.o \
														$(CONNEC)connection.o $(CONNEC)messagehandler.o \
														$(SERVER)servercommandhandler.o
$(CLIENT)clientMain: 				$(CLIENT)clientMain.o $(CONNEC)connection.o \
														$(CONNEC)messagehandler.o \
														$(CLIENT)clientcommandhandler.o \
														$(CLIENT)inputhandler.o \
														$(EXCEPT)inputexception.h \
														$(EXCEPT)noarticleexception.h \
														$(EXCEPT)ngexistsexception.h \
														$(EXCEPT)ngdoesnotexistexception.h \
														$(EXCEPT)invalidpathexception.h

# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f $(SERVER)*.o $(SERVER)*.d
	rm -f $(MEMSRV)*.o $(MEMSRV)*.d
	rm -f $(DSKSRV)*.o $(DSKSRV)*.d
	rm -f $(CONNEC)*.o $(CONNEC)*.d
	rm -f $(CLIENT)*.o $(CLIENT)*.d
	rm -f -r $(OUTPUT)
	#rm -f -r database
	#rm -f -r database/.dbinfo

# Generate dependencies in *.d files
%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)
