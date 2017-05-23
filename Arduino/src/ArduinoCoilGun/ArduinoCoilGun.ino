#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

const int pinCarga = 13; //Charge capacitors RELAY
const int pinDisparo = 12; //Connect the capacitors to the coil RELAY2
const int TouchSensor = 8; //Touch sensor
const int Buzzer = 9;
boolean state = false;
boolean firetrigger = false;
int minutes = 0; //start min
int seconds = 59; //start seconds

void setup() {
  // put your setup code here, to run once:
  pinMode(pinCarga, OUTPUT);
  pinMode(pinDisparo, OUTPUT);
  pinMode(TouchSensor, INPUT);
  pinMode(Buzzer,OUTPUT);
  digitalWrite(pinCarga,HIGH);
  digitalWrite(pinDisparo,HIGH);
  lcd.begin(16,2);
 

}

void loop() {   
  
    lcd.print("TO-START!");
    lcd.setCursor(0,0);
    lcd.print("TOUCH ");
    if(digitalRead(TouchSensor)==HIGH){
      state = true;
    }
    else{
      delay(50);
    }
    if(state == true){
      chargeandshoot();
    }
}

void stepDown(){
 if (seconds > 0) {
  seconds -= 1;
 }
 else {
  trigger();
 }
}

void trigger() {
 lcd.clear(); // clears the screen and buffer
 lcd.setCursor(4, 1); // set timer position on lcd for end.
 lcd.println("!!FIRE");
 delay(1000);
 lcd.display();
 firetrigger = true;
}

void chargeandshoot(){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("CARGANDO!");
      Serial.println("Cargando condensadores");
      digitalWrite(pinDisparo,HIGH);
      digitalWrite(pinCarga,LOW);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("FINAL COUNTDOWN!!!");
      while(!firetrigger){
          lcd.setCursor(4, 2);
          lcd.print(minutes);
          lcd.print(":");
          (seconds < 10) ? lcd.print("0") : NULL;
          lcd.print(seconds);
          lcd.display();
          stepDown();
          delay(1000);
       }
       //Fire buzzer countdown
      tone(Buzzer,1000);
      delay(1000);
      noTone(Buzzer);
      delay(1000);
      tone(Buzzer,1000);
      delay(1000);
      noTone(Buzzer);
      delay(1000);
      tone(Buzzer,1000);
      delay(1000);
      noTone(Buzzer);
      delay(1000);
      //FIRE!!!!
      digitalWrite(pinCarga,HIGH);
      digitalWrite(pinDisparo, LOW);
      Serial.println("Fuego!!");
      delay(4000);
      //SHUTDOWN BOTH RELAY CHANNELS
      digitalWrite(pinCarga,HIGH);
      digitalWrite(pinDisparo,HIGH);
      state = false;
      firetrigger = false;
      seconds = 59;
      delay(2000);
      lcd.clear();
}



