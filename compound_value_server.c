#include "compound_value.h"

int main(int argc, char ** argv) {

    struct xmlrpc_method_info3 methodInfo = {
        /* .methodName     = */ "std.getblock",
        /* .methodFunction = */ &std_getblock,
    };

    if (argc-1 != 1) {
        fprintf(stderr, "You must specify 1 argument:  The TCP port "
                "number on which the server will accept connections "
                "for RPCs (8080 is a common choice).  "
                "You specified %d arguments.\n",  argc-1);
        exit(1);
    }

    init_rpc_server(&methodInfo, argv[1]);
    
    return 0;
}
