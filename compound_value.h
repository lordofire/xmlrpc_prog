#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>

#include "xmlrpc_config.h"

#define NAME "Xmlrpc-c Test Client"
#define VERSION "1.0"
#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.h */


#define MAXLENGTH 100
typedef struct node{
  int ID;
  char IP[MAXLENGTH];
  int PORT;
  int DATA;
} node_t;

/* subfunctions */
void dieIfFaultOccurred (xmlrpc_env * const envP);
void getDataBlock(xmlrpc_env *    envP,
			 xmlrpc_value *  DataStructP,
			 xmlrpc_value ** OutDataStructPP);
xmlrpc_value * std_getblock(xmlrpc_env *  envP,
				   xmlrpc_value * paramArrayP,
				   void *         serverInfo,
				   void *         channelInfo);

/* client side top-level */
node_t * xmlrpc_client_callmethod(char * serverUrl, char * methodName, unsigned int argVersion);

/* server side top-level */
void init_rpc_server(struct xmlrpc_method_info3* methodInfo, char* portnum );
