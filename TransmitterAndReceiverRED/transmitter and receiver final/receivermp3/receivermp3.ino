#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h>
#include <SFEMP3Shield.h>
#include <Bounce2.h> 

SdFat sd;
SFEMP3Shield MP3player;
int8_t current_track = 0;

 #define rfReceivePin A0  //RF Receiver pin = Analog pin 0
 #define ledPin 7        //Onboard LED = digital pin 7

 unsigned int data = 0;   // variable used to store received data
 const unsigned int upperThreshold = 70;  //upper threshold value



boolean toggle = true;

void setup () {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);

  if(!sd.begin(9, SPI_HALF_SPEED)) sd.initErrorHalt();
  if (!sd.chdir("/")) sd.errorHalt("sd.chdir");
  
  MP3player.begin();
  MP3player.setVolume(10,10);
  digitalWrite(ledPin, LOW);
  delay(1000);
}

void loop () {    
data=analogRead(rfReceivePin);    //listen for data on Analog pin 0
Serial.println(data);
     if (data>upperThreshold)
     {

       MP3player.playTrack(current_track);
       digitalWrite(ledPin, HIGH);

      
     }
}
