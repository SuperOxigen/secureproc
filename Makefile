
# Source Code Directories
INC=include		# Public Headers
SRC=src 		# Library Source
TOOL=tools 		# Tool Source
TEST=tests 		# Test Source

# Build Directories
BIN=bin			# Tools and Test Build
LIB=lib 		# Library Binaries

# Compiler Related

CC=gcc
CFLAGS= -std=c11 -Wall -I$(INC)

# Warning Flags
# GNU C and Compiler Warnings
GNUCWARN= -Wsuggest-attribute=[pure|const|noreturn|format]
BUILDWARN= -Wmissing-include-dirs
# Programatic Warnings
MATHWARN= -Wfloat-equal
LOGICWARN= -Wduplicated-cond
STRWARN= -Wformat=2
# Groupings
ALLPROGWARN= $(MATHWARN) $(LOGICWARN) $(STRWARN)
EXWARNFLAGS= -Wextra $(ALLPROGWARN) $(GNUCFLAGS) $(BUILDWARN)
# Build Mode Flags
DEBUGFLAGS= $(EXWARNFLAGS) -D_DEBUG -D_VERBOSE
RELEASEFLAGS= -Werror

.PHONY: clean secureproc tools test all

# Library Builds
secureproc:
	echo "Library"

# Tool Builds
tools:
	echo "Tools"

# Test Builds
test:
	echo "Tests"

all: secureproc tools

clean:
	rm $(BIN)/* $(LIB)/*
