include config.mk

default: all

BLDDIR = `pwd`

# If this were a real application, working from an installed copy of
# Xmlrpc-c, XMLRPC_C_CONFIG would just be 'xmlrpc-c-config'.  It would be
# found in the user's PATH.
XMLRPC_C_CONFIG = $(BLDDIR)/xmlrpc-c-config.test

# Build up PROGS:
PROGS = compound_value_server compound_value_client

OBJECTS = compound_value.o compound_value_server.o compound_value_client.o

INCLUDES = -I. $(shell $(XMLRPC_C_CONFIG) client abyss-server --cflags)

LIBS_LINKING = -L. $(shell $(XMLRPC_C_CONFIG) client abyss-server --libs)

all: $(PROGS)

# When building in separate tree, directory won't exist yet
compound_value_client: compound_value_client.o compound_value.o
	$(CCLD) -o $@ $^ $(LIBS_LINKING) -g

compound_value_server: compound_value_server.o compound_value.o
	$(CCLD) -o $@ $^ $(LIBS_LINKING) -g

$(OBJECTS):*.c *.h
	$(CC) -g -c $^ $(INCLUDES)

.PHONY: clean
clean:
	rm -f $(PROGS) *.o