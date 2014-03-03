#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#include <xmlrpc-c/base.h>
#include <xmlrpc-c/client.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/server_abyss.h>

#include "xmlrpc_config.h"

#define NAME "Xmlrpc-c Test Client"
#define VERSION "1.0"
#define WIN32_LEAN_AND_MEAN  /* required by xmlrpc-c/server_abyss.h */


#define MAXLENGTH 1024
typedef struct node{
  int ID;
  char IP[MAXLENGTH];
  int PORT;
  int DATA;
} node_t;

/* used to terminate the server */
static xmlrpc_server_abyss_t * serverToTerminateP;
static void sigtermHandler(int const signalClass);
static void setupSigtermHandler(xmlrpc_server_abyss_t * const serverP);
static void restoreSigtermHandler(void);

/* subfunctions */
static void dieIfFailed(const char * const description, xmlrpc_env * env);
void getDataBlock(xmlrpc_env *    envP,
			 xmlrpc_value *  DataStructP,
			 xmlrpc_value ** OutDataStructPP);
xmlrpc_value * std_getblock(xmlrpc_env *  envP,
				   xmlrpc_value * paramArrayP,
				   void *         serverInfo,
				   void *         channelInfo);

/* client side top-level */
node_t * xmlrpc_client_callmethod(const char * serverUrl, const char * methodName, unsigned int argVersion);

/* server side top-level */
void init_rpc_server(struct xmlrpc_method_info3 const * methodInfo, int portnum );
