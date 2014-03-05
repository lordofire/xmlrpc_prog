#include "xmlrpc_transfer.h"

static void dieIfFailed(const char * const description,
            xmlrpc_env * env) {
    if (env->fault_occurred) {
      fprintf(stderr, "%s failed. %s (%d)\n", description, env->fault_string, env->fault_code);
        exit(1);
    }
}

static void sigtermHandler(int const signalClass) {
    
    xmlrpc_env env;
    
    xmlrpc_env_init(&env);

    xmlrpc_server_abyss_terminate(&env, serverToTerminateP);

    dieIfFailed("xmlrpc_server_abyss_terminate", &env);
    
    xmlrpc_env_clean(&env);
}



static void setupSigtermHandler(xmlrpc_server_abyss_t * const serverP) {

    struct sigaction mysigaction;

    serverToTerminateP = serverP;
    
    sigemptyset(&mysigaction.sa_mask);
    mysigaction.sa_flags = 0;
    mysigaction.sa_handler = sigtermHandler;
    sigaction(SIGTERM, &mysigaction, NULL);
}



static void restoreSigtermHandler(void){

    struct sigaction mysigaction;

    sigemptyset(&mysigaction.sa_mask);
    mysigaction.sa_flags = 0;
    mysigaction.sa_handler = SIG_DFL;
    sigaction(SIGTERM, &mysigaction, NULL);
}


node_t * xmlrpc_client_callmethod(const char * serverUrl, const char * methodName, unsigned int argVersion){

    xmlrpc_env env;

    xmlrpc_env_init(&env);
    xmlrpc_client_init2(&env, XMLRPC_CLIENT_NO_FLAGS, NAME, VERSION, NULL, 0);
    dieIfFailed("Client initialization", &env);

    xmlrpc_value * ID, * PORT, * DATA, * DATAP, * IP;
    
    ID = xmlrpc_int_new(&env, 23121);
    IP = xmlrpc_string_new(&env, "127.0.0.1");
    PORT  = xmlrpc_int_new(&env, 8085);
    DATA  = xmlrpc_int_new(&env, 123);

    DATAP = xmlrpc_struct_new(&env);

    xmlrpc_struct_set_value(&env, DATAP, "ID", ID);
    xmlrpc_struct_set_value(&env, DATAP, "IP", IP);
    xmlrpc_struct_set_value(&env, DATAP, "PORT",  PORT);
    xmlrpc_struct_set_value(&env, DATAP, "DATA",  DATA);
        
    xmlrpc_DECREF(ID);
    xmlrpc_DECREF(IP);
    xmlrpc_DECREF(PORT);
    xmlrpc_DECREF(DATA);

    /* Make the call */
    xmlrpc_value * resultArray = xmlrpc_client_call(&env, serverUrl, methodName, "(iS)", (xmlrpc_int32) argVersion, DATAP);

    xmlrpc_value * OutID_t, *OutPORT_t, *OutDATA_t, *OutIP_t;
    xmlrpc_int OutID, OutPORT, OutDATA;
    char * OutIP;

    unsigned int const resultCt = xmlrpc_array_size(&env, resultArray);
    unsigned int i;
    
    node_t * resultnode = (node_t *) malloc(3*sizeof(node_t));

    for(i = 0; i < resultCt; ++i){
      xmlrpc_value * resultP;
      xmlrpc_array_read_item(&env, resultArray, i, &resultP);

      xmlrpc_struct_find_value(&env, resultP, "ID", &OutID_t);
      xmlrpc_struct_find_value(&env, resultP, "IP", &OutIP_t);
      xmlrpc_struct_find_value(&env, resultP, "PORT", &OutPORT_t);
      xmlrpc_struct_find_value(&env, resultP, "DATA", &OutDATA_t);
      
      xmlrpc_read_int(&env, OutID_t, &OutID);
      xmlrpc_read_string(&env, OutIP_t, &OutIP);
      xmlrpc_read_int(&env, OutPORT_t, &OutPORT);
      xmlrpc_read_int(&env, OutDATA_t, &OutDATA);
      
      resultnode[i].ID = OutID;
      strcpy(resultnode[i].IP, OutIP);
      resultnode[i].PORT = OutPORT;
      resultnode[i].DATA = OutDATA;
    }
    xmlrpc_env_clean(&env);
    xmlrpc_client_cleanup();


    return resultnode;
}

void getDataBlock(xmlrpc_env *   envP,
                 xmlrpc_value *  DataStructP,
                 xmlrpc_value ** OutDataStructPP) {

  xmlrpc_value * ID_t, * PORT_t, * DATA_t, * IP_t;
  xmlrpc_struct_find_value(envP, DataStructP, "ID", &ID_t);
  xmlrpc_struct_find_value(envP, DataStructP, "IP", &IP_t);
  xmlrpc_struct_find_value(envP, DataStructP, "PORT", &PORT_t);
  xmlrpc_struct_find_value(envP, DataStructP, "DATA", &DATA_t);

  xmlrpc_int ID, PORT, DATA;
  char* IP;

  xmlrpc_read_int(envP, ID_t, &ID);
  xmlrpc_read_string(envP, IP_t, &IP);
  xmlrpc_read_int(envP, PORT_t, &PORT);
  xmlrpc_read_int(envP, DATA_t, &DATA);
	      
  xmlrpc_DECREF(ID_t);
  xmlrpc_DECREF(IP_t);
  xmlrpc_DECREF(PORT_t);
  xmlrpc_DECREF(DATA_t);
  
  printf("The value of ID is %d\n", ID);
  printf("The value of ID is %s\n", IP);
  printf("The value of PORT is %d\n", PORT);
  printf("The value of DATA is %d\n", DATA);

  xmlrpc_value * ID_out, * IP_out, * PORT_out, * DATA_out, *DATAP_out;
  xmlrpc_value * ID1_out, * IP1_out, * PORT1_out, * DATA1_out, *DATAP1_out;
  xmlrpc_value * ID2_out, * IP2_out, * PORT2_out, * DATA2_out, *DATAP2_out;
  xmlrpc_value * structArray;

  structArray = xmlrpc_array_new(envP);

  ID_out = xmlrpc_int_new(envP, 78654);
  IP_out = xmlrpc_string_new(envP, "127.0.0.1");
  PORT_out  = xmlrpc_int_new(envP, 8090);
  DATA_out  = xmlrpc_int_new(envP, 45425);

  ID1_out = xmlrpc_int_new(envP, 78764);
  IP1_out = xmlrpc_string_new(envP, "127.0.0.1");
  PORT1_out  = xmlrpc_int_new(envP, 8091);
  DATA1_out  = xmlrpc_int_new(envP, 452135);

  ID2_out = xmlrpc_int_new(envP, 78123);
  IP2_out = xmlrpc_string_new(envP, "127.0.0.1");
  PORT2_out  = xmlrpc_int_new(envP, 8092);
  DATA2_out  = xmlrpc_int_new(envP, 45563);

  DATAP_out = xmlrpc_struct_new(envP);
  DATAP1_out = xmlrpc_struct_new(envP);
  DATAP2_out = xmlrpc_struct_new(envP);
  
  xmlrpc_struct_set_value(envP, DATAP_out, "ID", ID_out);
  xmlrpc_struct_set_value(envP, DATAP_out, "IP", IP_out);
  xmlrpc_struct_set_value(envP, DATAP_out, "PORT",  PORT_out);
  xmlrpc_struct_set_value(envP, DATAP_out, "DATA",  DATA_out);

  xmlrpc_struct_set_value(envP, DATAP1_out, "ID", ID1_out);
  xmlrpc_struct_set_value(envP, DATAP1_out, "IP", IP1_out);
  xmlrpc_struct_set_value(envP, DATAP1_out, "PORT",  PORT1_out);
  xmlrpc_struct_set_value(envP, DATAP1_out, "DATA",  DATA1_out);
  
  xmlrpc_struct_set_value(envP, DATAP2_out, "ID", ID2_out);
  xmlrpc_struct_set_value(envP, DATAP2_out, "IP", IP2_out);
  xmlrpc_struct_set_value(envP, DATAP2_out, "PORT",  PORT2_out);
  xmlrpc_struct_set_value(envP, DATAP2_out, "DATA",  DATA2_out);

  xmlrpc_array_append_item(envP, structArray, DATAP_out);
  xmlrpc_array_append_item(envP, structArray, DATAP1_out);
  xmlrpc_array_append_item(envP, structArray, DATAP2_out);

  xmlrpc_DECREF(ID_out);
  xmlrpc_DECREF(IP_out);
  xmlrpc_DECREF(PORT_out);
  xmlrpc_DECREF(DATA_out);
  xmlrpc_DECREF(ID1_out);
  xmlrpc_DECREF(IP1_out);
  xmlrpc_DECREF(PORT1_out);
  xmlrpc_DECREF(DATA1_out);
  xmlrpc_DECREF(ID2_out);
  xmlrpc_DECREF(IP2_out);
  xmlrpc_DECREF(PORT2_out);
  xmlrpc_DECREF(DATA2_out);
	
  *OutDataStructPP = structArray;
}



xmlrpc_value * std_getblock(xmlrpc_env *   envP,
               xmlrpc_value * paramArrayP,
               void *         serverInfo,
               void *         channelInfo) {

    xmlrpc_value * retvalP;
    xmlrpc_int32 CheckSum;
    xmlrpc_value * DataStructP;

    xmlrpc_decompose_value(envP, paramArrayP, "(iS)",
                           &CheckSum, &DataStructP);
    if (envP->fault_occurred)
        return NULL;

    if (CheckSum != 100) {
        xmlrpc_env_set_fault(envP, 0, "Parameter list version must be 1");
        return NULL;
    }

    getDataBlock(envP, DataStructP, &retvalP);
    
    xmlrpc_DECREF(DataStructP);

    if (envP->fault_occurred)
        return NULL;

    return retvalP;
}


void init_rpc_server(struct xmlrpc_method_info3 const * methodInfo, int portnum ){
    xmlrpc_server_abyss_parms serverparm;
    xmlrpc_server_abyss_t * serverP;
    xmlrpc_registry * registryP;
    xmlrpc_env env;
    xmlrpc_server_abyss_sig * oldHandlersP;

    xmlrpc_env_init(&env);

    xmlrpc_server_abyss_global_init(&env);
    dieIfFailed((const char*)"xmlrpc_server_abyss_global_init", &env);

    registryP = xmlrpc_registry_new(&env);
    dieIfFailed((const char*)"xmlrpc_registry_new", &env);

    xmlrpc_registry_add_method3(&env, registryP, methodInfo);
    dieIfFailed((const char*)"xmlrpc_registry_add_method3", &env);
    
    serverparm.config_file_name = NULL;
    serverparm.registryP        = registryP;
    serverparm.port_number      = portnum;

    xmlrpc_server_abyss_create(&env, &serverparm, XMLRPC_APSIZE(port_number), &serverP);
    dieIfFailed((const char*)"xmlrpc_server_abyss_create", &env);

    xmlrpc_server_abyss_setup_sig(&env, serverP, &oldHandlersP);
    dieIfFailed((const char*)"xmlrpc_server_abyss_setup_sig", &env);

    setupSigtermHandler(serverP);

    printf("Running XML-RPC server...\n");

    xmlrpc_server_abyss_run_server(&env, serverP);
    dieIfFailed((const char*)"xmlrpc_server_abyss_run_server", &env);

    restoreSigtermHandler();
    xmlrpc_server_abyss_restore_sig(oldHandlersP);
    xmlrpc_server_abyss_destroy(serverP);
    xmlrpc_registry_free(registryP);
    xmlrpc_server_abyss_global_term();
    xmlrpc_env_clean(&env);
}

