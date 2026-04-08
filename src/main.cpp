#include <Arduino.h>
#include "shiftOut.h"

const int OE_PIN    = 10; // OE (Output Enable) - Pin 13 del 74HC595
const int LATCH_PIN = 9;  // RCLK (latch)       - Pin 12 del 74HC595
const int CLOCK_PIN = 8;  // SRCLK (reloj)      - Pin 11 del 74HC595
const int MReset_PIN = 7; // MR (Master Reset)  - Pin 10 del 74HC595
const int DATA_PIN  = 6;  // SER (datos)        - Pin 14 del 74HC595
const int BUTTON_ROTATE_PIN = 5;  
const int BUTTON_LEFT_PIN = 4;
const int BUTTON_RIGHT_PIN = 3;
const int BUTTON_DOWN_PIN = 2;

//--------------------------------------------------------------void setup
void setup() {
  //ajust baud rate
  Serial.begin(115200);

  //set pin outputs and inputs
  pinMode(OE_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(MReset_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);

  //set initial states
  digitalWrite(OE_PIN, LOW);
  digitalWrite(LATCH_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);
  digitalWrite(MReset_PIN, HIGH);
  digitalWrite(DATA_PIN, LOW);
}
//--------------------------------------------------------------void loop
void loop() {
  //Matrix aux to manual change data
  int principalMatrix[16][8] = {{0,1,1,1,0,1,0,1},// 0
                                {0,1,0,1,0,1,0,1},// 1
                                {0,1,1,1,0,1,0,1},// 2
                                {0,1,0,0,0,1,1,1},// 3
                                {0,0,0,0,0,0,0,0},// 4
                                {0,1,1,1,0,1,1,1},// 5
                                {0,0,1,0,0,1,0,1},// 6
                                {0,0,1,0,0,1,0,1},// 7
                            /**/{0,1,1,1,0,1,1,1},/* 8 */
                                {0,0,0,0,0,0,0,0},// 9
                                {0,0,0,0,0,0,0,0},// 10
                                {0,0,0,0,0,0,0,0},// 11
                                {0,0,0,0,0,0,0,0},// 12
                                {1,1,1,1,1,1,1,1},// 13 
                                {1,0,0,1,1,0,0,1},// 14
                                {0,1,1,0,0,1,1,0}};//15
  

    superShiftOut2(principalMatrix, DATA_PIN, CLOCK_PIN, LATCH_PIN);
    
}