#include <Servo.h>
//#include <LiquidCrystal.h>
#include <dht_nonblocking.h>
#include <ShiftedLCD.h>
#include <SPI.h>

#define ENABLE 5
#define DIRA 3
#define DIRB 4

#define joystickY A1

static const int DHT_SENSOR_PIN = 2;
#define DHT_SENSOR_TYPE DHT_TYPE_11

DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
LiquidCrystal lcd(10);
Servo servo;

float temperature;
float humidity;

//int i;
//int pos  = 0;
int pos2 = 0;
int servoPos;

int button1 = 12;
int button2 = 8;
int button3 = 9;

int fanFlag = 0;

void setup(){
 Serial.begin(9600);
 servo.attach(7); 

 pinMode(ENABLE,OUTPUT);
 pinMode(DIRA,OUTPUT);
 pinMode(DIRB,OUTPUT);
 
 pinMode(button1, INPUT_PULLUP);  
 pinMode(button2, INPUT_PULLUP);
 pinMode(button3, INPUT_PULLUP);  
 //pinMode(button4, INPUT_PULLUP);

 lcd.begin(16, 2);
 lcd.setCursor(0,0);
 lcd.print("Temperature:");
 lcd.setCursor(0,1);
 lcd.print("Humidity:");
}

static bool measure_environment( float *temperature, float *humidity ){
  static unsigned long measurement_timestamp = millis( );
  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul ){
    if( dht_sensor.measure( temperature, humidity ) == true ){
      measurement_timestamp = millis( );
      return( true );
    }
  }
  return( false );
}

enum servoState {startS, moveServo, automove} servoState;
void servo_tick(){
  switch (servoState){
      case startS:
        servoState = moveServo;
        break;
    case moveServo:
        pos2 = analogRead(joystickY);
        if (pos2 > 480 && pos2 < 550){
             servo.write(servoPos);
        }
        else{
            while (pos2 >= 550){
                if (servoPos < 180){
                  servoPos++;
                }
                servo.write(servoPos);
                delay(15);
                pos2 = analogRead(joystickY);
            }
            while (pos2 <= 480){
              if (servoPos > 0){
                  servoPos--;
                }
              servo.write(servoPos);
              delay(15);
              pos2 = analogRead(joystickY);
            }
        }
        if (digitalRead(button3) == LOW && fanFlag == 1){
          servoState = automove; 
        }
        else{
          servoState = moveServo;
        }
        break;
      case automove:
        pos2 = analogRead(joystickY);
        if (pos2 < 480 || pos2 > 550){
             //.write(servoPos);
             servoState = moveServo;
        }
        else{
          while (servoPos < 180){
            servoPos++;
            servo.write(servoPos);
            delay(15);
          }
          while (servoPos > 0){
            servoPos--;
            servo.write(servoPos);
            delay(15);
          }
          servoState = automove;
        }
        break;
  }
}

enum fanState {fanStandby, fanOn} fanState;
void fan_tick(){
    switch(fanState){
      case fanStandby:
        fanFlag = 0;
        digitalWrite(ENABLE, LOW);

        if (digitalRead(button1) == LOW){
          fanState = fanOn;
        }
        else{
          fanState = fanStandby;
        }
        break;
      case fanOn:
        fanFlag = 1;
        digitalWrite(ENABLE, HIGH);
        digitalWrite(DIRA, HIGH);

        if (temperature > 26 && temperature < 30){
          analogWrite(ENABLE, 150);
        }
        else if (temperature > 30){
          analogWrite(ENABLE, 255);
        }
        else {
          analogWrite(ENABLE, 100);
        }
        
      
        if (digitalRead(button2) == LOW){
          fanState = fanStandby;
        }
        else{
          fanState = fanOn;
        }
        break;
    }
    
//  if (digitalRead(button1) == LOW){
//    fanFlag = 1;
//    digitalWrite(ENABLE, HIGH);
//    digitalWrite(DIRA, HIGH);
//    //analogWrite(ENABLE, 50);
//  }
//  if (digitalRead(button2) == LOW){
//    fanFlag = 0;
//    digitalWrite(ENABLE, LOW);
//    digitalWrite(DIRA, LOW);
//  }
}

enum tempState{start3, readTemp} tempState;
void temp_tick(){
  switch (tempState){
    case start3:
      tempState = readTemp;
      break;
    case readTemp:
      if( measure_environment( &temperature, &humidity ) == true )
        {
          Serial.print( "T = " );
          Serial.print( temperature, 1 );
          Serial.print( " deg. C, H = " );
          Serial.print( humidity, 1 );
          Serial.println( "%" );
        }
        tempState = readTemp;
      break;
  }
}

void lcd_tick(){  
    lcd.setCursor(12,0);
    lcd.print(temperature);
    lcd.setCursor(9,1);
    lcd.print(humidity);
}


void loop() {
  servo_tick();
  fan_tick();
  temp_tick();
  lcd_tick();
}
