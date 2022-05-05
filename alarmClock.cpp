#include <Arduino.h>

const int m1 = 10;	//Sets pin 9 as a parameter for mosfet 1
const int m2 = 11;	//Sets pin 10 as a parameter for mosfet 2
const int m3 = 12;	//Sets pin 11 as a parameter for mosfet 3
const int m4 = 18;	//Sets pin 12 as a parameter for mosfet 4
const long interval = 10000; 	//Interval of 1000 gives a second
unsigned long previousMillis = 0;	//Millis variable to compare time elapsed
int min = 0;		//2-digit minute value
int min_dig1;	//1-digit minute value holding the minute
int min_dig2;	//1-digit minute value holding the 10th minute
int hour = 0;		//2-digit hour value
int hour_dig1 = 0;	//1-digit hour value holding hour
int hour_dig2 = 0;	//1-digit hour value holding the 10th hour
int time = 0;
int alarm_time = 0;
int alarm_min = 0;
int alarm_hour = 0;
bool alarm_on = true;
bool alarm_ringing = false;


void setup() //setup function maps pins
{
  pinMode (0, OUTPUT);	//Bit 0 on minute segments to decoder
  pinMode (1, OUTPUT);	//Bit 1 on minute segments to decoder
  pinMode (4, OUTPUT);	//Bit 2 on minute segments to decoder
  pinMode (A5, OUTPUT);	//Bit 3 on minute segments to decoder
  pinMode (6, OUTPUT);	//Bit 0 on hour segments to decoder
  pinMode (7, OUTPUT);	//Bit 1 on hour segments to decoder
  pinMode (8, OUTPUT);	//Bit 2 on hour segments to decoder
  pinMode (9, OUTPUT);	//Bit 3 on hour segments to decoder
  pinMode (10, OUTPUT);	//Output 10 controls NMOS 1
  pinMode (11, OUTPUT);	//Output 11 controls NMOS 2
  pinMode (12, OUTPUT);	//Output 12 controls NMOS 3
  pinMode (18, OUTPUT);	//Output 13 controls NMOS 4
  pinMode (13, OUTPUT);	//Output LED for testing alarm
  pinMode (A5, INPUT);	//Analog in for reading ambient light
  pinMode (5, OUTPUT);	//Analog write for PWM brightness on display
  pinMode (2, INPUT_PULLUP);	//Will trigger set time ISR
  pinMode (3, INPUT_PULLUP);	//Will trigger set alarm ISR
  pinMode (14, INPUT_PULLUP);	//Polling on A0 for input in time and alarm set
  pinMode (15, INPUT_PULLUP);	//Polling on A1 for input in time and alarm set
  pinMode (16, INPUT_PULLUP);	//Polling on A2 for input in time and alarm set
}

void select(int segm, int segh)
  //Takes in a number 1 or 2 and 3 or 4 and turns on that MOSFET for the displays
{
  switch(segm)
  {
    case 1:
    digitalWrite(m1, HIGH);	
    digitalWrite(m2, LOW);
    break;
    
    case 2:
    digitalWrite(m1, LOW);
    digitalWrite(m2, HIGH);
    break;
    
    default:
    digitalWrite(m1, LOW);
    digitalWrite(m2, LOW);
    break;
  }
  switch(segh)
  {
    case 3:
    digitalWrite(m3, HIGH);
    digitalWrite(m4, LOW);
    break;
    
    case 4:
    digitalWrite(m3, LOW);
    digitalWrite(m4, HIGH);
    break;
    
    default:
    digitalWrite(m3, LOW);
    digitalWrite(m4, LOW);
    break;
  }
}

void displaym(int num)
//Displays a number in the minute segments
{
  switch(num)
  {
    case 0: 
    //Illuminates segments to display "0"
    digitalWrite(0, LOW);	//input bit 0 low
    digitalWrite(1, LOW);	//input bit 1 low
    digitalWrite(4, LOW);	//input bit 2 low
    digitalWrite(A3, LOW);	//input bit 3 low
    break;


    case 1:
    //Illuminates segments to display "1"
    digitalWrite(0, HIGH);	//input bit 0 high
    digitalWrite(1, LOW);	//input bit 1 low
    digitalWrite(4, LOW);	//input bit 2 low
    digitalWrite(A3, LOW);	//input bit 3 low
    break;

    case 2:
    //Illuminates segments to display "2"
    digitalWrite(0, LOW);	//input bit 0 low
    digitalWrite(1, HIGH);	//input bit 1 high
    digitalWrite(4, LOW);	//input bit 2 low
    digitalWrite(A3, LOW);	//input bit 3 low
    break;

    case 3:
    //Illuminates segments to display "3"
    digitalWrite(0, HIGH);	//input bit 0 high
    digitalWrite(1, HIGH);	//input bit 1 high
    digitalWrite(4, LOW);	//input bit 2 low
    digitalWrite(A3, LOW);	//input bit 3 low
    break;

    case 4:
    //Illuminates segments to display "4"
    digitalWrite(0, LOW);	//input bit 0 low
    digitalWrite(1, LOW);	//input bit 1 low
    digitalWrite(4, HIGH);	//input bit 2 high
    digitalWrite(A3, LOW);	//input bit 3 low
    break;

    case 5:
    //Illuminates segments to display "5"
    digitalWrite(0, HIGH);	//input bit 0 high
    digitalWrite(1, LOW);	//input bit 1 low
    digitalWrite(4, HIGH);	//input bit 2 high
    digitalWrite(A3, LOW);	//input bit 3 low
    break;


    case 6:
    //Illuminates segments to display "6"
    digitalWrite(0, LOW);	//input bit 0 low
    digitalWrite(1, HIGH);	//input bit 1 high
    digitalWrite(4, HIGH);	//input bit 2 high
    digitalWrite(A3, LOW);	//input bit 3 low
    break;


    case 7:
    //Illuminates segments to display "7"
    digitalWrite(0, HIGH);	//input bit 0 high
    digitalWrite(1, HIGH);	//input bit 1 high
    digitalWrite(4, HIGH);	//input bit 2 high
    digitalWrite(A3, LOW);	//input bit 3 low
    break;


    case 8:
    //Illuminates segments to display "8"
    digitalWrite(0, LOW);	//input bit 0 low
    digitalWrite(1, LOW);	//input bit 1 low
    digitalWrite(4, LOW);	//input bit 2 low
    digitalWrite(A3, HIGH);	//input bit 3 high
    break;

    case 9:
    //Illuminates segments to display "9"
    digitalWrite(0, HIGH);	//input bit 0 high
    digitalWrite(1, LOW);	//input bit 1 low
    digitalWrite(4, LOW);	//input bit 0 low
    digitalWrite(A3, HIGH);	//input bit 3 high
    break;


    default: // no matches
    num = 0;
    break;
  }
}

void displayh(int num)
//Displays a number on the hour segments
{
  switch(num)
  {
    case 0: 
    //Illuminates segments to display "0"
    digitalWrite(6, LOW);	//input bit 0 low
    digitalWrite(7, LOW);	//input bit 1 low
    digitalWrite(8, LOW);	//input bit 2 low
    digitalWrite(9, LOW);	//input bit 3 low
    break;


    case 1:
    //Illuminates segments to display "1"
    digitalWrite(6, HIGH);	//input bit 0 high
    digitalWrite(7, LOW);	//input bit 1 low
    digitalWrite(8, LOW);	//input bit 2 low
    digitalWrite(9, LOW);	//input bit 3 low
    break;

    case 2:
    //Illuminates segments to display "2"
    digitalWrite(6, LOW);	//input bit 0 low
    digitalWrite(7, HIGH);	//input bit 1 high
    digitalWrite(8, LOW);	//input bit 2 low
    digitalWrite(9, LOW);	//input bit 3 low
    break;

    case 3:
    //Illuminates segments to display "3"
    digitalWrite(6, HIGH);	//input bit 0 high
    digitalWrite(7, HIGH);	//input bit 1 high
    digitalWrite(8, LOW);	//input bit 2 low
    digitalWrite(9, LOW);	//input bit 0 low
    break;

    case 4:
    //Illuminates segments to display "4"
    digitalWrite(6, LOW);	//input bit 0 low
    digitalWrite(7, LOW);	//input bit 1 low
    digitalWrite(8, HIGH);	//input bit 2 high
    digitalWrite(9, LOW);	//input bit 3 low
    break;

    case 5:
    //Illuminates segments to display "5"
    digitalWrite(6, HIGH);	//input bit 0 high
    digitalWrite(7, LOW);	//input bit 1 low
    digitalWrite(8, HIGH);	//input bit 2 high
    digitalWrite(9, LOW);	//input bit 3 low
    break;


    case 6:
    //Illuminates segments to display "6"
    digitalWrite(6, LOW);	//input bit 0 low
    digitalWrite(7, HIGH);	//input bit 1 high
    digitalWrite(8, HIGH);	//input bit 2 high
    digitalWrite(9, LOW);	//input bit 3 low
    break;


    case 7:
    //Illuminates segments to display "7"
    digitalWrite(6, HIGH);	//input bit 0 high
    digitalWrite(7, HIGH);	//input bit 1 high
    digitalWrite(8, HIGH);	//input bit 2 high
    digitalWrite(9, LOW);	//input bit 3 low
    break;


    case 8:
    //Illuminates segments to display "8"
    digitalWrite(6, LOW);	//input bit 0 low
    digitalWrite(7, LOW);	//input bit 1 low
    digitalWrite(8, LOW);	//input bit 2 low
    digitalWrite(9, HIGH);	//input bit 3 high
    break;

    case 9:
    //Illuminates segments to display "9"
    digitalWrite(6, HIGH);	//input bit 0 high
    digitalWrite(7, LOW);	//input bit 1 low
    digitalWrite(8, LOW);	//input bit 2 low
    digitalWrite(9, HIGH);	//input bit 3 high
    break;

    default: // no matches
    num = 0;
    break;
  }
}

void set_alarm()
{
  int iter = 0;
  alarm_on == true;
  alarm_hour = time/100;
  alarm_min = time%100;
  //Set the alarm time
  while(iter == 0)
  {
    select(0, 4);	//Sets MOSFET 4 high others low
    //Adjust 10th hour
    if(digitalRead(15) == LOW)
    {
      //Increment hour by 10
      delay(100);
      alarm_hour = alarm_hour + 10;
      delay(100);
      if(alarm_hour >= 24)
      {
        alarm_hour = alarm_hour - 24;
      }
    }
    if(digitalRead(16) == LOW)
    {
      //Decrement hour by 10
      delay(100);
      alarm_hour = alarm_hour - 10;
      delay(100);
      if(alarm_hour < 0)
      {
        alarm_hour = alarm_hour + 24;
      }
    }
    
    //Display number
    displayh(alarm_hour/10);
    delay(100);

    if(digitalRead(14) == LOW)
    {
      delay(100);
      iter++;
      delay(100);
    }
  }//While(iter == 0)

  while(iter == 1)
  {
    select(0, 3);	//Sets MOSFET 3 high others low
    
    //Adjust hour
    if(digitalRead(15) == LOW)
    {
      //Increment hour by 1
      delay(100);
      alarm_hour++;
      delay(100);
      if(alarm_hour >= 24)
      {
        alarm_hour = alarm_hour - 24;
      }
    }
    if(digitalRead(16) == LOW)
    {
      //Decrement hour by 1
      delay(100);
      alarm_hour--;
      delay(100);
      if(alarm_hour < 0)
      {
        alarm_hour = alarm_hour + 24;
      }
    }
    
	//Display number
    displayh(alarm_hour%10);
    delay(10);
    
    if(digitalRead(14) == LOW)
    {
      delay(100);
      iter++;
      delay(100);
    }
  }//While(iter == 1)

  while(iter == 2)
  {
    select(2, 0);	//Sets MOSFET 2 high others low
    //Adjust 10th minute

    if(digitalRead(15) == LOW)    
    {
      //Increment minute by 10
      delay(100);
      alarm_min = alarm_min + 10;
      delay(100);
      if(alarm_min >= 60)
      {
        alarm_min = alarm_min - 60;
      }
    }
    if(digitalRead(16) == LOW)
    {
      //Decrement minute by 10
      delay(100);
      alarm_min = alarm_min - 10;
      delay(100);
      if(alarm_min < 0)
      {
        alarm_min = alarm_min + 60;
      }
    }
	//Display number
    displaym(alarm_min/10);
    delay(10);

    if(digitalRead(14) == LOW)
    {
      delay(100);
      iter++;
      delay(100);
    }
  }//While(iter == 2)

  while(iter == 3)
  {
    select(1, 0);	//Sets MOSFET 1 high others low

    //Adjust minute
    if(digitalRead(15) == LOW)
    {
      //Increment minute by 1
      delay(100);
      alarm_min++;
      delay(100);
      if(alarm_min >= 60)
      {
        alarm_min = alarm_min - 60;
      }
    }
    if(digitalRead(16) == LOW)
    {
      //Decrement minute by 1
      delay(100);
      alarm_min--;
      delay(100);
      if(alarm_min < 0)
      {
        alarm_min = alarm_min + 60;
      }
    }
    
	//Display number
    displaym(alarm_min%10);
    delay(10);
    if(digitalRead(14) == LOW)
    {
      delay(100);
      iter++;
      delay(100);
    }
  }//While(iter == 3)
  //Sets individual digits to new time
  alarm_time = alarm_hour*100 + alarm_min;
}

void set_time()
{
  int iter = 0;
  hour = time/100;
  min = time%100;
  //Set the time
  while(iter == 0)
  {
    select(0, 4);	//Sets MOSFET 4 high others low
    //Adjust 10th hour
    if(digitalRead(15) == LOW)
    {
      //Increment hour by 10
      delay(100);
      hour = hour + 10;
      delay(100);
      if(hour >= 24)
      {
        hour = hour - 24;
      }
    }
    if(digitalRead(16) == LOW)
    {
      //Decrement hour by 10
      delay(100);
      hour = hour - 10;
      delay(100);
      if(hour < 0)
      {
        hour = hour + 24;
      }
    }

    //Display number
    displayh(hour/10);
    delay(100);

    if(digitalRead(14) == LOW)
    {
      delay(100);
      iter++;
      delay(100);
    }
  }//While(iter == 0)

  while(iter == 1)
  {
    select(0, 3);	//Sets MOSFET 3 high others low
    time = hour*100 + min;
    hour_dig1 = hour%10;
    hour_dig2 = hour/10;
    min_dig1 = min%10;
    min_dig2 = min/10;
  	digitalWrite(13, LOW);//TESTING
    //Adjust hour
    if(digitalRead(15) == LOW)
    {
      //Increment hour by 1
      delay(100);
      hour++;
      delay(100);
      if(hour >= 24)
      {
        hour = hour - 24;
      }
    }
    if(digitalRead(16) == LOW)
    {
      //Decrement hour by 1
      delay(100);
      hour--;
      delay(100);
      if(hour < 0)
      {
        hour = hour + 24;
      }
    }

    //Display number
    displayh(hour%10);
    delay(10);
    
    if(digitalRead(14) == LOW)
    {
      delay(100);
      iter++;
      delay(100);
    }
  }//While(iter == 1)

  while(iter == 2)
  {
    select(2, 0);	//Sets MOSFET 2 high others low
    //Adjust 10th minute

    if(digitalRead(15) == LOW)    
    {
      //Increment minute by 10
      delay(100);
      min = min + 10;
      delay(100);
      if(min >= 60)
      {
        min = min - 60;
      }
    }
    if(digitalRead(16) == LOW)
    {
      //Decrement minute by 10
      delay(100);
      min = min - 10;
      delay(100);
      if(min < 0)
      {
        min = min + 60;
      }
    }
    
    //Display number
    displaym(min/10);
    delay(10);
    if(digitalRead(14) == LOW)
    {
      delay(100);
      iter++;
      delay(100);
    }
  }//While(iter == 2)

  while(iter == 3)
  {
    select(1, 0);	//Sets MOSFET 1 high others low
    
    //Adjust minute
    if(digitalRead(15) == LOW)
    {
      //Increment minute by 1
      delay(100);
      min++;
      delay(100);
      if(min >= 60)
      {
        min = min - 60;
      }
    }
    if(digitalRead(16) == LOW)
    {
      //Decrement minute by 1
      delay(100);
      min--;
      delay(100);
      if(min < 0)
      {
        min = min + 60;
      }
    }
    
    //Display number
    displaym(min%10);
    delay(10);
    if(digitalRead(14) == LOW)
    {
      delay(100);
      iter++;
      delay(100);
    }
  }//While(iter == 3)
  //Sets individual digits to new time
  time = hour*100 + min;
  hour_dig1 = hour%10;
  hour_dig2 = hour/10;
  min_dig1 = min%10;
  min_dig2 = min/10;
}

void loop() //loop function 
{
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    min++;
    
    if(min >= 60)
    {
      min = 0;	//Wraps minute around
      hour++;	//Increments hour
      if (hour >= 24)
      {
        hour = 0;	//Resets hour to zero on wraparound in 24hour mode
      }
      hour_dig1 = hour%10;
      hour_dig2 = hour/10;
    }
    min_dig1 = min%10;	//Calculates minute value
    min_dig2 = min/10;	//Calculates 10th minute value
    time = hour*100 + min;
    //Check alarm step
    if(alarm_on == true &&  time == alarm_time)
    {
      buzzer();   
    }
    
  }//End Timekeeper
  if(digitalRead(14) == LOW && alarm_on == true && alarm_ringing == true)
  {
    alarm_on = false;
    noTone(13);
    delay(100);
  }
  
  if(digitalRead(15) == LOW && alarm_on == true && alarm_ringing == true)
  {
    noTone(13);
    alarm_time = (alarm_time + 3);
    delay(100);
  }
  
  int adc = analogRead(5);
  adc = map(adc, 45, 1010, 50, 255);
  analogWrite(5, adc);
  attachInterrupt(digitalPinToInterrupt(2), set_time, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), set_alarm, FALLING);
  select(1,3);
  displaym(min_dig1);
  displayh(hour_dig1);
  delay(10);
  
  select(2,4);
  displaym(min_dig2);
  displayh(hour_dig2);
  delay(10);
}

void buzzer()
{
  tone(13, 100);
  alarm_ringing = true;
}
