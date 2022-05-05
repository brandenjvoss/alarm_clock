#include <Arduino.h>

int button_state = 0; //holds button state as either high or low
int button_count = 0; //holds number of button presses


const int a = 5;	//Initializes each segment to its corresponding letter as per handout
const int b = 6;	//Sets pin 6 as a parameter for segment b
const int c = 0;	//Sets pin 0 as a parameter for segment c
const int d = 1;	//Sets pin 1 as a parameter for segment d
const int e = 8;	//Sets pin 8 as a parameter for segment e
const int f = 4;	//Sets pin 4 as a parameter for segment f
const int g = 3;	//Sets pin 3 as a parameter for segment g

void count() //ISR 
{
  button_count++; // Increments button count once for each interrupt
}

void setup() //setup function maps pins
{
  pinMode (0, OUTPUT);	//Segment c is an from output pin 0
  pinMode (1, OUTPUT);	//Segment d is an from output pin 1
  pinMode (8, OUTPUT);	//Segment e is an from output pin 8
  pinMode (3, OUTPUT);	//Segment g is an from output pin 3
  pinMode (4, OUTPUT);	//Segment f is an from output pin 4
  pinMode (5, OUTPUT);	//Segment a is an from output pin 5
  pinMode (6, OUTPUT);	//Segment 6 is an from output pin 6
  pinMode (2, INPUT);	//Interrupt input pin 
  attachInterrupt(digitalPinToInterrupt(2), count, RISING); //Initiates pin2 as a risingedge ISR
}

void loop() //loop function 
{
  button_state = digitalRead(2); //Read interrupt
  
  switch (button_count) //Case variable is the button count. Button pessed twice is case 2...
  {
    case 0:
    //Illuminates segments to display "0"
    digitalWrite(a, HIGH);	//segment a high
    digitalWrite(b, HIGH);	//segment b high
    digitalWrite(c, HIGH);	//segment c high
    digitalWrite(d, HIGH);	//segment d high
    digitalWrite(e, HIGH);	//segment e high
    digitalWrite(f, HIGH);	//segment f high
    digitalWrite(g, LOW);	//segment g low
    break;
    
    case 1:
    //Illuminates segments to display "1"
    digitalWrite(a, LOW);	//segment a low
    digitalWrite(b, HIGH);	//segment b high
    digitalWrite(c, HIGH);	//segment c high
    digitalWrite(d, LOW);	//segment d low
    digitalWrite(e, LOW);	//segment e low
    digitalWrite(f, LOW);	//segment f low
    digitalWrite(g, LOW);	//segment g low
    break;
    
    case 2:
    //Illuminates segments to display "2"
    digitalWrite(a, HIGH);	//segment a high
    digitalWrite(b, HIGH);	//segment b high
    digitalWrite(c, LOW);	//segment c low
    digitalWrite(d, HIGH);	//segment d high
    digitalWrite(e, HIGH);	//segment e high
    digitalWrite(f, LOW);	//segment f low
    digitalWrite(g, HIGH);	//segment g high
    break;
    
    case 3:
    //Illuminates segments to display "3"
    digitalWrite(a, HIGH);	//segment a high
    digitalWrite(b, HIGH);	//segment b high
    digitalWrite(c, HIGH);	//segment c high
    digitalWrite(d, HIGH);	//segment d high
    digitalWrite(e, LOW);	//segment e low
    digitalWrite(f, LOW);	//segment f low
    digitalWrite(g, HIGH);	//segment g high
    break;
    
    case 4:
    //Illuminates segments to display "4"
    digitalWrite(a, LOW);	//segment a low
    digitalWrite(b, HIGH);	//segment b high
    digitalWrite(c, HIGH);	//segment c high
    digitalWrite(d, LOW);	//segment d low
    digitalWrite(e, LOW);	//segment e low
    digitalWrite(f, HIGH);	//segment f high
    digitalWrite(g, HIGH);	//segment g high
    break;
    
    case 5:
    //Illuminates segments to display "5"
    digitalWrite(a, HIGH);	//segment a high
    digitalWrite(b, LOW);	//segment b low
    digitalWrite(c, HIGH);	//segment c high
    digitalWrite(d, HIGH);	//segment d high
    digitalWrite(e, LOW);	//segment e low
    digitalWrite(f, HIGH);	//segment f high
    digitalWrite(g, HIGH);	//segment g high
    break;
    
    case 6:
    //Illuminates segments to display "6"
    digitalWrite(a, HIGH);	//segment a high
    digitalWrite(b, LOW);	//segment b low
    digitalWrite(c, HIGH);	//segment c high
    digitalWrite(d, HIGH);	//segment d high
    digitalWrite(e, HIGH);	//segment e high
    digitalWrite(f, HIGH);	//segment f high
    digitalWrite(g, HIGH);	//segment g high
    break;
    
    case 7:
    //Illuminates segments to display "7"
    digitalWrite(a, HIGH);	//segment a high
    digitalWrite(b, HIGH);	//segment b high
    digitalWrite(c, HIGH);	//segment c high
    digitalWrite(d, LOW);	//segment d low
    digitalWrite(e, LOW);	//segment e low
    digitalWrite(f, LOW);	//segment f low
    digitalWrite(g, LOW);	//segment g low
    break;
    
    case 8:
    //Illuminates segments to display "8"
    digitalWrite(a, HIGH);	//segment a high
    digitalWrite(b, HIGH);	//segment b high
    digitalWrite(c, HIGH);	//segment c high
    digitalWrite(d, HIGH);	//segment d high
    digitalWrite(e, HIGH);	//segment e high
    digitalWrite(f, HIGH);	//segment f high
    digitalWrite(g, HIGH);	//segment g high
    break;
    
    case 9:
    //Illuminates segments to display "9"
    digitalWrite(a, HIGH);	//segment a high
    digitalWrite(b, HIGH);	//segment b high
    digitalWrite(c, HIGH);	//segment c high
    digitalWrite(d, LOW);	//segment d low
    digitalWrite(e, LOW);	//segment e low
    digitalWrite(f, HIGH);	//segment f high
    digitalWrite(g, HIGH);	//segment g high
    break;
    
    default:
    //Sets button count to zero if no other states are met.
    //This displays zero and happens after the counter gets past 9
    button_count = 0;
    break;
  }
  
}
