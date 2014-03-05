#include "xmlrpc_transfer.h"

int main(int argc, char ** argv) {

    node_t * result;

    if (argc-1 > 0) {
        fprintf(stderr, "This program has no arguments\n");
        exit(1);
    }

    result = xmlrpc_client_callmethod("http://localhost:8080/RPC2", "std.getblock", 100);

    unsigned int i;
    for(i = 0; i < 3; i++){
      printf("Server says data ID is %d\n", result[i].ID);
      printf("Server says data IP is %s\n", result[i].IP);
      printf("Server says data PORT is %d\n", result[i].PORT);
      printf("Server says data DATA is %d\n", result[i].DATA);
    }
    return 0;
}
