//this program reeds an zigbee message from command line and sends it
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>
#include <fstream>
#include <stdbool.h>
#include "RSJparser.tcc"
#include <sstream>
using namespace std;

//char initCmd[254]={0};
char inMessage[512];
int readCounter = 0;
int fd;


// convert a char to Hex **********************************
int StrToHex(char str[])
{
    return (int)strtol(str, 0, 16);
}

// ************ calculate length of a message to send *****************
char* sLen(char Command[])
{
    char* bufferSln = new char[5];
    //so if command =2710AABBCC then strlen=10 /2 =5 -2 = 3
    sprintf(bufferSln, "%02X", (strlen(Command) / 2 - 2));
    delayMicroseconds(250); //give memset a little bit of time to empty all the buffers
    cout << "slen = " << bufferSln << "\n<br>" << endl;
    return bufferSln;
}

// *************  calculate  the checksum of the message ****************************
char *checkSum(char Command[])
{
    cout << "function checksum, input = " << Command << endl;
    cout << "input length = " << strlen(Command) << endl;
    char* bufCRC = new char[254];
    char bufCRCshadow[254] = {0};

    strncpy(bufCRC, Command, 2); 
    //delayMicroseconds(250);         

    for (uint8_t i = 1; i <= (strlen(Command) / 2 - 1); i++)
    {
        strncpy(bufCRCshadow, Command + i * 2, 2);
        //delayMicroseconds(250);
        sprintf(bufCRC, "%02X", StrToHex(bufCRC) ^ StrToHex(bufCRCshadow));
        //delayMicroseconds(250); 
    }
   cout << "function checksum, returned = " << bufCRC << endl;
    return bufCRC;
}


void sendZigbee(char sendString[] )
{
     // print the FE first
     serialPutchar(fd, 0xFE);
     cout << "serial -> 0xFE" << endl;

     //
     char bufferSend[3];
     for (uint8_t i = 0; i <= strlen(sendString) / 2 - 1; i++)
        {
         // we use 2 characters to make a byte
            strncpy(bufferSend, sendString + i * 2, 2);
            delayMicroseconds(250);                     //give memset a little bit of time to empty all the bu$
            serialPutchar(fd, StrToHex(bufferSend));        //turn the two chars to a byte and send this
            cout << "serial -> " << StrToHex(bufferSend) << endl;
        }
}


#include <fstream>
bool fexists(const std::string& filename) {
  std::ifstream ifile(filename.c_str());
  return (bool)ifile;
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
   delay(500); // to give the sender the time to write the data
   return true;
}


// *****************  format the incoming byte ***************************$
void processIncomingByte(int inByte)
{
char oneChar[10] = {0};
    sprintf(oneChar, "%02x", inByte);
    strncat(inMessage, oneChar, 2); // append
} // end of processIncomingByte


void readZigbee() {
  readCounter = 0;
  memset( &inMessage, 0, sizeof(inMessage) ); //zero out the
  delayMicroseconds(250);

  while ( serialDataAvail(fd) )
    {
      if (readCounter < 512)
      {
         processIncomingByte(serialGetchar(fd));
         readCounter += 1;
       }
       else
       {
         serialGetchar(fd); // just read to empty the serial buff$
       }

       if (serialDataAvail(fd) == 0)  // the buffer is empty
         {

         uint16_t iToUpper = 0; // has to be 16bit because the received me$

         while (inMessage[iToUpper])
          {
             inMessage[iToUpper] = toupper(inMessage[iToUpper]);
             iToUpper++;
          }
        }
     }
        // now we should have catched inMessage
     if (serialDataAvail(fd) == 0)
     {
          //  _waiting_for_response = false;
          //  _ready_to_send = true;
      }
    //cleanIncoming(); // check for F8 and remove it
}


int main (int argc, char **argv)
{

//   cout << "Content-type:text/html\r\n\r\n";
//   cout << "<html>\n";
//   cout << "<head>\n";
//   cout << "<title>RPI ECU PROGRAM</title>\n";
//   cout << "</head>\n";
//   cout << "<body>\n";
 cout << "Content-type:text/html\r\n<html><head><title>RPI ECU PROGRAM</title></head><body>\n";
   cout << "<h4>running testZigbee.cgi version 2023-12-27</h4>\n";

  char initCmd[30]={""};

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
    strcpy(initCmd, strcat(sLen(initCmd), initCmd));
    strcpy(initCmd, strncat(initCmd, checkSum(initCmd), sizeof(initCmd) + sizeof(checkSum(initCmd))));

    cout << "command incl. FE, len and crc = FE" << initCmd << "\n<br>" << endl;
           
    sendZigbee(initCmd);  
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
//exit(0);
}

/* sofar found that a globally defined oper works 
*/

