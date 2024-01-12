// this program reads a zigbee message from command line
// adds slen and crc, sends it and reads the answer
// modifications dec 2023 : the buffersize in slen
// removed the delayMicroseconds on several places
// simplified the readZigbee and removed processIncomingByte 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <fstream>
//#include <stdbool.h>
//#include "RSJparser.tcc"
#include <sstream>
using namespace std;

char inMessage[512];
int readCounter = 0;
int fd;


// ******** convert a char to Hex **************
int StrToHex(char str[])
{
    return (int)strtol(str, 0, 16);
}

string checkSumString(char Command[])
{
char bufferCRC[254] = {0};
char bufferCRC_2[254] = {0};

    strncpy(bufferCRC, Command, 2); //as starting point perhaps called "seed" use the first two chars from "Command"
    delayMicroseconds(250);         //give memset a little bit of time to empty all the buffers

    for (uint8_t i = 1; i <= (strlen(Command) / 2 - 1); i++)
    {
        strncpy(bufferCRC_2, Command + i * 2, 2); //use every iteration the next two chars starting with char 2+3
        sprintf(bufferCRC, "%02X", StrToHex(bufferCRC) ^ StrToHex(bufferCRC_2));
     }
    return string(bufferCRC);
}

void sendZigbee(char sendString[] )
{
     // print the FE first
     serialPutchar(fd, 0xFE);
     char bufferSend[3];
     for (uint8_t i = 0; i <= strlen(sendString) / 2 - 1; i++)
        {
         // we use 2 characters to make a byte
            strncpy(bufferSend, sendString + i * 2, 2);
         // turn the two chars to a byte and send this
            serialPutchar(fd, StrToHex(bufferSend)); 
        }
}


// **********   wait for serail available ********************************
bool waitSerialAvailable()
{
  //We start with a delay
  unsigned long wait = millis();
  while ( serialDataAvail(fd) == 0 )
      {
      if ( millis() - wait > 2000) return false; // return false after 200
      }
  // if we are here there is something available
   delay(500); // to give the sender the time to complete writing
   return true;
}


// ******* read incoming date from serial buffer**********
void readZigbee() {
  readCounter = 0;
  memset( &inMessage, 0, sizeof(inMessage) ); //zero out the
  char oneChar[10] = {0};

  while ( serialDataAvail(fd) )
    {
      if (readCounter < 512)
      {
          sprintf(oneChar, "%02X", serialGetchar(fd)); // always uppercase
          strncat(inMessage, oneChar, 2);
          readCounter += 1;
       }
       else
       {
          // only read to make the serial buffer empty
          serialGetchar(fd); 
       }

    }
}


int main (int argc, char **argv)
{
   cout << "Content-type:text/html\r\n<html><head><title>RPI ECU PROGRAM</title></head><body>\n";
   cout << "<h4>running testZigbee.cgi version 2024-jan-12</h4>\n";

   char initCmd[30]={""};
   char bufferSend[254]={0};
   
   if(argc > 1)
   {
        strncpy(initCmd, argv[1], strlen(argv[1]));
   } else {
       cout << "error: no argument supplied\n<br>";
       return(3);
   }

    cout << "testZigbee running with arg "<< initCmd << "\n<br>" << endl;   
    //if(which == 1){normalOps = true;}

    if (wiringPiSetup () == -1) /* initializes wiringPi setup */
    {
      
      cout << "unable to start wiringPi\n<br>" << endl;
      return 1;  
    }
       else 
    {
    cout << "wiringPi started\n<br>" << endl;
    }

// start the serial port
//int serial_port;
//  int fd;
  if ((fd = serialOpen("/dev/serial0", 115200)) < 0)
  {
    cout << "unable to open serial_port serial0\n<br>" << endl;
    return(0);
  }
  // construct the command now we put len and checksum

 //    strncpy(initCmd, strncat(sLen(initCmd), initCmd, sizeof(sLen(initCmd)) + sizeof(initCmd)));
   sprintf(bufferSend, "%02X", (strlen(initCmd) / 2 - 2)); //now contains a hex representation of the length 
   strcat(bufferSend, initCmd); // now put slen and the rest together
   strcat(bufferSend, checkSumString(bufferSend).c_str());
   //strcpy(initCmd, strcat(sLen(initCmd), initCmd));
   // strcpy(initCmd, strncat(initCmd, checkSum(initCmd), sizeof(initCmd) + sizeof(checkSum(initCmd))));

    cout << "command incl. FE, len and crc = FE" << bufferSend << "\n<br>" << endl;
           
    sendZigbee(bufferSend);  
    delay(3);
    waitSerialAvailable();
// test the loopback
    readZigbee();
    if(readCounter > 2) 
    {
       cout << "inMessage = " << inMessage << "\n<br>" << endl;
    } else {
       cout << "no answer\n<br>" << inMessage << endl;
    } 
  
 
  serialClose(fd);
  return 0;

}


