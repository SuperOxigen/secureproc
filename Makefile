
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
CFLAGS= -std=c11 -Wall -I$(INC) -D_XOPEN_SOURCE=700

# Warning Flags
# GNU C and Compiler Warnings
GNUCWARN= -Wsuggest-attribute=[pure|const|noreturn|format]
BUILDWARN= -Wmissing-include-dirs
# Programatic Warnings
MATHWARN= -Wfloat-equal
LOGICWARN=
STRWARN= -Wformat=2
# Groupings
ALLPROGWARN= $(MATHWARN) $(LOGICWARN) $(STRWARN)
EXWARNFLAGS= -Wextra $(ALLPROGWARN) $(GNUCFLAGS) $(BUILDWARN)
# Build Mode Flags
DEBUGFLAGS= $(EXWARNFLAGS) -D_DEBUG_ -D_VERBOSE_
RELEASEFLAGS= -Werror

.PHONY: clean secureproc tools test all safestring

# Library Builds

COMMON=$(INC)/secureproc/common.h $(INC)/secureproc/_preproc_.h

$(SRC)/safestring.c: $(INC)/secureproc/safestring.h $(COMMON)
	touch $@

$(LIB)/safestring.o: $(SRC)/safestring.c $(COMMON)
	$(CC) $(CFLAGS) $(BFLAGS) -o $@ -c $<

safestring: $(LIB)/safestring.o

$(SRC)/logger.c: $(INC)/secureproc/logger.h $(COMMON)
	touch $@

$(LIB)/logger.o: $(SRC)/logger.c $(COMMON)
	$(CC) $(CFLAGS) $(BFLAGS) -o $@ -c $<

logger: $(LIB)/logger.o

COMPONENTS= safestring logger

secureproc:
	$(eval export BFLAGS = $(RELEASEFLAGS))
	$(MAKE) $(COMPONENTS)

debug:
	$(eval export BFLAGS = $(DEBUGFLAGS))
	$(MAKE) $(COMPONENTS)

# Tool Builds
tools:
	echo "Tools"

# Test Builds


$(BIN)/logger.test: $(TEST)/logger.test.c $(LIB)/logger.o
	$(CC) $(CFLAGS) $(BFLAGS) -o $@ $(TEST)/logger.test.c $(LIB)/logger.o

$(BIN)/safestring.test: $(TEST)/safestring.test.c $(LIB)/safestring.o
	$(CC) $(CFLAGS) $(BFLAGS) -o $@ $(TEST)/safestring.test.c $(LIB)/logger.o $(LIB)/safestring.o

TESTSUITES= $(BIN)/logger.test $(BIN)/safestring.test

test:
	$(eval export BFLAGS = $(DEBUGFLAGS))
	$(MAKE) $(TESTSUITES)
	$(BIN)/logger.test
	$(BIN)/safestring.test

all: secureproc tools

clean:
	rm $(BIN)/* $(LIB)/*
