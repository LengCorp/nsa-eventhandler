#include <telldus-core.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


static time_t last; // time since last "Okay"-check


void WINAPI sensorEvent(const char *protocol, const char *model, int sensorId, int dataType, const char *value, int ts, int callbackId, void *context) {
	char timeBuf[80];
	time_t timestamp = ts;
	
	//Print the sensor
	printf("%s,\t%s,\t%i\n", protocol, model, sensorId);

	//Retrieve the values the sensor supports
	if (dataType == TELLSTICK_TEMPERATURE && sensorld == 187{
			if(!strcmp("0", value)){
				printf("alarm is working fine");
				time(&last)	;  // it was okay, so set last to current time
			}
			else if(!strcmp("1", value)))
				printf("alarm was triggered");
			
	} 
	printf("\n");
}

int main(void) {
	int callbackId = 0;
	time_t elapsed; // used to store the time elapsed since last "okay"-check
	
	//Call tdinit to initiate the library
	tdInit();

	//Register for callback
	callbackId = tdRegisterSensorEvent( (TDSensorEvent)&sensorEvent, 0 );
	time(&last);		
	
	//Our own simple eventloop
	while(1) {
		
		if((elapsed = time(null) - last) >= 5)
			broken();
		sleep(100);
	}

	//Cleanup
	tdUnregisterCallback( callbackId );
	tdClose();

	return 0;
}
