/****************************************************
 * 433 mhz pansmitter for remote CHACON 54672
 * 
 * compile by :    g++ 433tx.cpp -o 433tx -lwiringPi
 *
 * start by:  ./433tx 0 TimingsFile.txt   
 * 0 is the GPIO.0 pin #   ( physical pin 11 )
 * TimingsFile.txt contains  UP/DOWN timings to reproduce (in uS and one by line) 
 *
 */

#include <wiringPi.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sstream>
#include <sys/resource.h>
#include <unistd.h>

using namespace std;

int pos=0;
int taille=0;
int state=0;
unsigned long ndelay=0;



// transmitter pin  
int pin;

//debugging purpose
void log(string a){
cout << a << endl;
}

//again
string longToString(long mylong){
    string mystring;
    stringstream mystream;
    mystream << mylong;
    return mystream.str();
}





int main (int argc, char** argv)
{
	// prioritize the process
	int which = PRIO_PROCESS;
	id_t pid;
	int priority = -10;
	int ret;
	pid = getpid();
	ret = setpriority(which, pid, priority);

	FILE *ptr;
   	char str[50];
   	int i=0;
   	
	// max # of  timings  
	// actually, I have an average of 550  values 
   	int temps[800];   

    	if (argc != 3) {
       	     printf("Usage: %s 0 TimingsFile.txt \n", argv[0]);
       	     return -1;
             }

	ptr = fopen(argv[2], "r");
 
    	if (NULL == ptr) {
              perror("Error");       	      
	      return -1;
    	      }
 
	// Read all values in temps[] array
	// and i variable will contain value number 
    	while (fgets(str, 8, ptr) != NULL) {
		temps[i]=atoi(str);
		i++;
    		}

 
    	fclose(ptr);

	pin = atoi(argv[1]);


    	if(wiringPiSetup() == -1)
    		{
        		log("Wiring PI library not found");
        		return -1;
    		}
    		
   	// initialize transmitter pin
	pinMode(pin, OUTPUT);

	taille=i;
	//log("array size ="+longToString(taille));
		

	// parse all timings values
	for (int x(0); x<taille; ++x)
		{
		//log(temps[x]) ; // display actual timing
		//log(x) ; // display index of value

		// reverse state
		state = !state;
        	digitalWrite(pin, state);

		usleep(temps[x]); // wait required time
			
		}	


	digitalWrite(pin, LOW);


	return 0;
}


