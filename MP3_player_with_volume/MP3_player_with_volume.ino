#include <SD.h>                      // need to include the SD library
//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>


TMRpcm tmrpcm;   // create an object for use in this sketch


int volumeDown=2;
int volumeUp=3;
int prev=5;
int pp=6;
int next=7;

int pauseState=0;
unsigned long time = 0;
int temp=1;
void setup(){
  
  pinMode(pp,INPUT_PULLUP);
  pinMode(next,INPUT_PULLUP);
  pinMode(prev,INPUT_PULLUP);
  pinMode(volumeDown,INPUT_PULLUP);
  pinMode(volumeUp,INPUT_PULLUP);
  
  tmrpcm.speakerPin = 10; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  //Complimentary Output or Dual Speakers:
  //pinMode(10,OUTPUT); Pin pairs: 9,10 Mega: 5-2,6-7,11-12,46-45 
  
  Serial.begin(115200);
  pinMode(13,OUTPUT); //LED Connected to analog pin 0
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not

  }
  else{
    if(tmrpcm.isPlaying() && millis() - time > 50 ) {      
      digitalWrite(13,!digitalRead(13));
      time = millis();    
  }
  else if(millis() - time > 500)
  {     
    digitalWrite(13,!digitalRead(13)); 
    time = millis(); 
  }
  Serial.println("SD ok");
     if(temp==1)
  {
    tmrpcm.play("music.wav",0);
    Serial.println("music.wav");
    
  }
    else if(temp==2)
    {
      tmrpcm.play("song1.wav",0);
      Serial.println("song1.wav");
    }
    else if(temp==3)
    {
    
      tmrpcm.play("song2.wav");
      Serial.println("song2.wav");
    }
    else if(temp==4)
    {
      tmrpcm.play("song3.wav");
      Serial.println("song3.wav");
    }
    else if(temp==5)
    {
      tmrpcm.play("song4.wav");
      Serial.println("song4.wav");
    }
    else if(temp==6){
      temp=1;
      Serial.println("music.wav");
      tmrpcm.play("music.wav");

    
    tmrpcm.setVolume(4); 
      
  }
  //the sound file "music" will play each time the arduino powers up, or is reset
}


}
void loop(){  

  while(digitalRead(volumeUp)==0) 
    if(digitalRead(volumeUp)==0){
      
      tmrpcm.volume(1); 
      delay(200);
      break;
    }
     while(digitalRead(volumeDown)==0)
      if(digitalRead(volumeDown)==0){
      
      tmrpcm.volume(0); 
      delay(200);
      break;
      } 
      
  //blink the LED manually to demonstrate music playback is independant of main loop
  if(tmrpcm.isPlaying() && millis() - time > 50 ) {      
      digitalWrite(13,!digitalRead(13));
      time = millis();    
  }
  else if(millis() - time > 500)
  {     
    digitalWrite(13,!digitalRead(13)); 
    time = millis(); 
  }
while(digitalRead(pp)==0 or digitalRead(next)==0 or digitalRead(prev)==0)
  {
    if(digitalRead(pp)==0)
    {
      tmrpcm.pause();
      pauseState++;
      if(pauseState==1)
      {
      Serial.println("Pause");
        if(temp==1)
      Serial.print(" song1 ");
      else if(temp==2)
      Serial.print(" song2 ");
      else if(temp==3)
      Serial.print(" song3 ");
      else if(temp==4)
      Serial.print(" song4 ");
      }
      else if(pauseState==2){
      Serial.println("Playing");
      if(temp==1)
      Serial.print(" song1 ");
      else if(temp==2)
      Serial.print(" song2 ");
      else if(temp==3)
      Serial.print(" song3 ");
      else if(temp==4)
      Serial.print(" song4 ");
      }
      while(digitalRead(pp)==0)
      delay(200);
      
    } 
    else if(digitalRead(next)==0)
    {
      if(temp<7)
      temp=temp+1;
      while(digitalRead(next)==0)
     delay(200);
      song();
    }
    else if(digitalRead(prev)==0)
    {
        if(temp==1)
        temp=5;
        else if(temp<7)
        temp=temp-1; 
        while(digitalRead(prev)==0)
        delay(200);
        song();
    }
    
  }

  /*if(Serial.available()){    
    switch(Serial.read()){
    case 'd': tmrpcm.play("music"); break;
    case 'P': tmrpcm.play("temple"); break;
    case 't': tmrpcm.play("catfish"); break;
    case 'p': tmrpcm.pause(); break;
    case '?': if(tmrpcm.isPlaying()){ Serial.println("A wav file is being played");} break;
    case 'S': tmrpcm.stopPlayback(); break;
    case '=': tmrpcm.volume(1); break;
    case '-': tmrpcm.volume(0); break;
    case '0': tmrpcm.quality(0); break;
    case '1': tmrpcm.quality(1); break;
    default: break;
    }
  }*/

}
void song (){
  if(temp==1)
  {
    tmrpcm.play("music.wav");
    Serial.println("music.wav");
  }
    else if(temp==2)
    {
      tmrpcm.play("song1.wav");
      Serial.println("song1.wav");
    }
    else if(temp==3)
    {
      tmrpcm.play("song2.wav");
      Serial.println("song2.wav");
    }
    else if(temp==4)
    {
      tmrpcm.play("song3.wav");
      Serial.println("song3.wav");
    }
    else if(temp==5){
 
      Serial.println("song3.wav");
      tmrpcm.play("song3.wav");  
    }
    else if(temp==6){
      temp=1; 
      Serial.println("music.wav");
      tmrpcm.play("music.wav");  
    }
  }
