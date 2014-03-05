#include "xmlrpc_transfer.h"

void *rpc_server(void* args){
    int portnum = ((int*)args)[0];
    struct xmlrpc_method_info3 const methodInfo = {
         .methodName     =  "std.getblock",
         .methodFunction =  &std_getblock,
	 .serverInfo     =  NULL
    };
    
    init_rpc_server(&methodInfo, portnum);
}

int main(int argc, char ** argv) {
    sigset_t sig_pipe; 
    pthread_t tid;
    int loopindicate = 1;
    int * args;
    char buf[MAXLENGTH];

    if (argc-1 != 1) {
        fprintf(stderr, "You must specify 1 argument:  The TCP port "
                "number on which the server will accept connections "
                "for RPCs (8080 is a common choice).  "
                "You specified %d arguments.\n",  argc-1);
        exit(1);
    }

    args = malloc(sizeof(int));
    args[0] = atoi(argv[1]);

    pthread_create(&tid, NULL, rpc_server, (void*) args);
    pthread_detach(tid);

    while(loopindicate){
      printf("WAIT FOR COMMAND:\n ");
      printf("1. lookup; 2. delete; 3. exit.\n");

      memset(buf, '\0', MAXLENGTH);
      int numbytes = read(0, buf, MAXLENGTH);
      buf[strlen(buf)-1] = '\0';

      if(!strcmp(buf, "exit")){
	loopindicate = 0;
	pthread_kill(tid,SIGTERM);
	pthread_join(tid,NULL);
	printf("program exits!\n");
      }else if(!strcmp(buf, "lookup")){
	printf("lookup cmd\n");
      }else if(!strcmp(buf, "locallookup")){
	node_t * result = xmlrpc_client_callmethod("http://localhost:8080/RPC2", "std.getblock", 100);

	unsigned int i;
	for(i = 0; i < 3; i++){
	  printf("Server says data ID is %d\n", result[i].ID);
	  printf("Server says data IP is %s\n", result[i].IP);
	  printf("Server says data PORT is %d\n", result[i].PORT);
	  printf("Server says data DATA is %d\n", result[i].DATA);
	}

      }else if(!strcmp(buf, "delete")){
	printf("delete cmd\n");
      }else{
	printf("cmd is not recognized\n");
      }
      printf("\n");
    }

    return 0;
}
