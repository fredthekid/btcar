//#include <Servo.h>
//Servo steer;
#include <SoftwareSerial.h>
SoftwareSerial mySerial (5, 6);

const int front_LED [2] = {7, 8};
const int back_LED [2] = {12, 13};

const int buzzerPin = 3;
void setup(){
 mySerial.begin(9600);
 Serial.begin(115200);
 pinMode(3, OUTPUT);
 //steer.attach(3);
   pinMode(7,OUTPUT);
   pinMode(8,OUTPUT);
   pinMode(9,OUTPUT);
   pinMode(10,OUTPUT);
   pinMode(11,OUTPUT);
   pinMode(12,OUTPUT);
  TCCR1A	= 0b11110010;		// Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM, Fast PWM mode
  TCCR1B	= 0b00011010;		// input noise canceler, input capture rising edge, 1 prescale
  ICR1	= 42000;     					// set period of PWM signal
OCR1A	= 3000;					// set high time of output PWM signal
OCR1B	= 3000;					// set high time of output PWM signal
}

void loop(){
  char Reg_value= mySerial.read();
  
  Serial.println(Reg_value, BIN);
  char accel = Reg_value&0x03;
  //char steer_value = Reg_value & 0xF8;
  //steer_value >> 3;
  //steer.write(map(steer_value, 0, 31, 0, 179));
  
  switch(accel){
    case 1: Forward();
            break;
    case 2: Reverse();
            break;
    default:Stop();
  }
  
  if((0x04&Reg_value) == 4)
  {
    tone(buzzerPin,523,2000);
  }
  else
  {
    noTone(buzzerPin);
  }
 // delay(1000);
 //analogWrite(steer, map(analogRead(0),0,1023,0,255));
 //OCR1A = map(analogRead(0),0,1023,3000,6000);
}

void Stop(void){
  OCR1A	= 3000;	
  OCR1B	= 3000;	
 for(int i = 0; i<2; i++)
 {
 digitalWrite(front_LED[i], LOW);
 digitalWrite(back_LED[i], LOW);
 
 }
  
}

void Forward(void){
  OCR1A	= 3400;	
  OCR1B	= 2600;	
   for(int i = 0; i<2; i++)
 {
 digitalWrite(front_LED[i], HIGH);
 digitalWrite(back_LED[i], LOW);
 }
}

void Reverse(void){
  OCR1A	= 2600;	
  OCR1B	= 3400;	
   for(int i = 0; i<2; i++)
 {
 digitalWrite(back_LED[i], HIGH);
 digitalWrite(front_LED[i], LOW);
 }
  
}
