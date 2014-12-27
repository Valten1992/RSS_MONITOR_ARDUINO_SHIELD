#include "SIM900.h"
#include "Time.h"
#include <SoftwareSerial.h>

void setup()
{
   
  //Serial connection.
  Serial.begin(9600);
  Serial.println("GSM Shield testing.");
  //Start configuration of shield with baudrate.
  //For http uses is reccomended to use 4800 or slower.
  if (gsm.begin(9600))
    Serial.println("\nstatus=READY");
  else Serial.println("\nstatus=IDLE");
};

void loop()
{

  serialhwread(); //for inputting commands

  serialswread(); //for reading in data from the Arduino
  delay(60000);

};

void serialhwread()
{
  gsm.SimpleWriteln("AT+CSQ");
  delay(10);
}

void serialswread()
{
  String reply = "";
  char datain;
  while(gsm.available()>0) {
    datain=gsm.read();
    if(datain>0) {
      reply.concat(datain);
    }
     reply.replace(":",",");
     reply.replace("+CSQ","");
     reply.replace("OK","");
     reply.trim();
  }
  
   reply.concat('\r');
   Serial.print(reply);
}

int find_text(String needle, String haystack) {
  int foundpos = -1;
  for (int i = 0; (i < haystack.length() - needle.length()); i++) {
    if (haystack.substring(i,needle.length()+i) == needle) {
      foundpos = i;
    }
  }
  return foundpos;
}
