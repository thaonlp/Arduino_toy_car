#include <SoftwareSerial.h> // import the serial library

#define ON HIGH
#define OFF LOW

#define MAX 255
#define MIN 0

//Define motor pins
const int motorFrontA  = 8; // Pin 8 of L298
const int motorFrontB  = 9;  // Pin 9 of L298

const int motorBackA  = 10; // Pin 10 of L298
const int motorBackB  = 11;  // Pin 11 of L298

//Bluetooth Receive, Transmit (RX, TX)
const int bt_RX = 5;
const int bt_TX = 6;
int btData;

//Buzzer & Speaker to Arduino UNO
const int buzzer = 2 ;

//LEDs
const int LED_L = 3;
const int LED_R = 4;

SoftwareSerial bl_hc06 (bt_RX, bt_TX);
void init_bluetooth() {
  bl_hc06.begin(9600);
  bl_hc06.println("HC06 Bluetooth device init!");
}

void init_LED() {
  pinMode(LED_L, OUTPUT);
  pinMode(LED_R, OUTPUT);
}

void init_buzzer() {
  pinMode(buzzer, OUTPUT);
}

void init_motor() {
  pinMode(motorFrontA, OUTPUT);
  pinMode(motorFrontB, OUTPUT);
  pinMode(motorBackA, OUTPUT);
  pinMode(motorBackB, OUTPUT);
}

void light_action(int state) {
  digitalWrite(LED_L ,state);
  digitalWrite(LED_R ,state);
}

void buzzer_action (int state) {
    if (state == ON) {
        tone(buzzer, 300);
        delay(1000);
        noTone(buzzer);
        delay(300);
        tone(buzzer, 600);
        delay(300);
    }
    else
        noTone(buzzer);
}


// Motor Function
void run_forward() {
  analogWrite(motorBackA,MAX);
  analogWrite(motorBackB,MIN);
}

void run_backward() {
  analogWrite(motorBackA,MIN);
  analogWrite(motorBackB,MAX);
}

void turn_left() {
  analogWrite(motorFrontA,MIN);
  analogWrite(motorFrontB,MAX);
}

void turn_right() {
  analogWrite(motorFrontA,MAX);
  analogWrite(motorFrontB,MIN);
}

void go_straight() {
  analogWrite(motorFrontA,MIN);
  analogWrite(motorFrontB,MIN);
}

void stop_car() {
  analogWrite(motorBackA,MIN);
  analogWrite(motorBackB,MIN);
}

void setup() {
  // put your setup code here, to run once:
  // initialize the digital pin as an output.
  init_bluetooth();
  init_LED();
  init_buzzer();
  init_motor();
}

void loop() {
    if (bl_hc06.available()){
        btData=bl_hc06.read();

        switch (btData) {
        case 'a': //Light on
            light_action(ON);
            break;
        case 'b': //Light off
            light_action(OFF);
            break;
        case 'c': //Buzzer on
            buzzer_action(ON);
            break;
        case 'd': //Buzzer off
            buzzer_action(OFF);
            break;
        case 'e': //Go Straight
            go_straight();
            break;
        case 'f': //Turn Left
            turn_left();
            break;
        case 'g': //Turn Right
            turn_right();
            break;
        case 'h': //Go Forward
            run_forward();
            break;
        case 'i': //Go Backward
            run_backward();
            break;
        case 'j': //Stop
            stop_car();
            break;
        }
    }
    delay(100);// prepare for next data ...
}
