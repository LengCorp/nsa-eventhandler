#include <telldus-core.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "sql.c"

static int callbackId = 0;
static int comingFromCallback = 0;
static int sinceLast = 0;
static int paused = 0;

void registerTelldus();
void qTelldus();

void WINAPI sensorEvent(const char *protocol, const char *model, int sensorId, int dataType, const char *value, int ts, int callbackId, void *context) {
    //prints when not equal to  90, so not cool
    if(sensorId != 187)
	return;	
    
    if(strcmp("90.0",value) && !comingFromCallback){
	comingFromCallback = 1;
	
	paused = 1;
	//tdUnregisterCallback( callbackId );
	if(getLastTriggerFromSQL() == 1){
	    sendTriggerToSQL();
	    triggerdLoop();
	}
	paused = 0;
    }
    // prints when not -27, soo... cool
    else if(strcmp("-27.0", value) && !comingFromCallback){
	sinceLast = 0;
    }
}

void registerTelldus(){
    tdInit();
    callbackId = tdRegisterSensorEvent((TDSensorEvent)&sensorEvent, 0);
}

void qTelldus(){
    tdUnregisterCallback(callbackId);
    tdClose();
}

int main(void) {
    printf("starting up...\n");
    createConnectionSQL();
    
    //Register for callback
    registerTelldus();
    printf("Done \n");
    //Our own simple eventloop
    
    while(1) {
	if(!paused){
	    sinceLast+=1;
	    if(comingFromCallback){
		sinceLast = 0;
		comingFromCallback = 0;
	    }
	    if(sinceLast > 5){
		sendTriggerToSQL();
		triggerdLoop();
	    }
	}
	sleep(1);
    }
    
    
    //Cleanup
    
    qTelldus();
    mysql_close(connection);
    
    return 0;
}

