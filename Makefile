include config.mk

default: all

BLDDIR = `pwd`
CFLAGS = -lpthread

# If this were a real application, working from an installed copy of
# Xmlrpc-c, XMLRPC_C_CONFIG would just be 'xmlrpc-c-config'.  It would be
# found in the user's PATH.
XMLRPC_C_CONFIG = $(BLDDIR)/xmlrpc-c-config.test

# Build up PROGS:
PROGS = xmlrpc_transfer_server xmlrpc_transfer_client

OBJECTS = xmlrpc_transfer.o xmlrpc_transfer_server.o xmlrpc_transfer_client.o

INCLUDES = -I. $(shell $(XMLRPC_C_CONFIG) client abyss-server --cflags)

LIBS_LINKING = -L. $(shell $(XMLRPC_C_CONFIG) client abyss-server --libs)

all: $(PROGS)

# When building in separate tree, directory won't exist yet
xmlrpc_transfer_client: xmlrpc_transfer_client.o xmlrpc_transfer.o
	$(CCLD) -o $@ $^ $(LIBS_LINKING) -g $(CFLAGS)

xmlrpc_transfer_server: xmlrpc_transfer_server.o xmlrpc_transfer.o
	$(CCLD) -o $@ $^ $(LIBS_LINKING) -g $(CFLAGS)

$(OBJECTS):*.c *.h
	$(CC) -g -c $^ $(INCLUDES)

.PHONY: clean
clean:
	rm -f $(PROGS) *.o *.gch