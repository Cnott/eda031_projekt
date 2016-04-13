#
# Makefile to make the file libclientserver.a, containing
# connection.o and server.o
#
# Define the compiler. g++ can be
# changed to clang++.
CXX = g++
CC	= g++

# Define output folder
OUTPUT_DIR=../../bin

# Define preprocessor, compiler, and linker flags. Uncomment the # lines
# if you use clang++ and wish to use libc++ instead of libstdc++.
CPPFLAGS =	-std=c++11
CXXFLAGS =	-O2 -Wall -Wextra -pedantic-errors -Wold-style-cast
CXXFLAGS += -std=c++11
CXXFLAGS += -g
#CXXFLAGS =	-stdlib=libc++
#CPPFLAGS =	-stdlib=libc++
#CXXFLAGS += -stdlib=libc++

# Targets for server files
PROGS = testMain

all: $(PROGS)
testMain: testMain.o article.o newsgroup.o

# Targets rely on implicit rules for compiling and linking
#tag_main: tag_main.o tagremover.o


# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f *.o libclientserver.a

# Generate dependencies in *.d files
%.d: %.cc
	@set -e; rm -f $@; \
				 $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
				 sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
				 rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)

# Output to bin directory
$(OUTPUT_DIR)/%.o: %.c
		$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
