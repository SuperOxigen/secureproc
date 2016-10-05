
# Source Code Directories
# Public Headers
INC=include
# Library Source
SRC=src
# Tool Source
TOOL=tools
# Test Source
TEST=tests

# Build Directories
# Tools and Test Build
BIN=bin
# Library Binaries
LIB=lib

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

.PHONY: clean secureproc tools test all safestring

# Library Builds

COMMON=$(INC)/secureproc/common.h $(INC)/secureproc/_preproc_.h

$(SRC)/safestring.c: $(INC)/secureproc/safestring.h $(COMMON)
	touch $@

$(LIB)/safestring.o: $(SRC)/safestring.c $(COMMON)
	$(CC) $(CFLAGS) $(BFLAGS) -o $@ -c $<

safestring: $(LIB)/safestring.o



COMPONENTS= safestring

secureproc:
	$(eval export BFLAGS = $(RELEASEFLAGS))
	$(MAKE) $(COMPONENTS)

# Tool Builds
tools:
	echo "Tools"

# Test Builds
test:
	echo "Tests"

all: secureproc tools

clean:
	rm $(BIN)/* $(LIB)/*
