//This code was written by Hashaam Zafar

#include <Adafruit_LiquidCrystal.h>

int placeholder = 0; 
int SAMPLING_TIME = 10;
int state = 0;

Adafruit_LiquidCrystal lcd_1(0);
const int SPEAKER_PIN = 3;
const int DETECTOR_PIN = A0;
const int MOTOR_PIN = 2;


void FAN(int state);
void ALARM();
int SIGNAL_AVERAGE();




void setup()
{
  lcd_1.begin(16, 2);
  lcd_1.print("Testing Alarm");
  
  Serial.begin(9600);

  //Sets up pins  
  pinMode(MOTOR_PIN, 	OUTPUT);
  pinMode(SPEAKER_PIN, 	OUTPUT);
  pinMode(DETECTOR_PIN, OUTPUT);
  analogWrite(MOTOR_PIN, 200);
}

void loop()
{
  int signal = SIGNAL_AVERAGE();

  if (signal > 15)
  {
    
    lcd_1.setCursor(0, 0);
    lcd_1.print("WARNING - HAZARD");
    
    ALARM();
    
    if (state == 0)
    {
      FAN(1);
      state = 1;
    }
  }
  
  else if (signal > 10)
  {
    lcd_1.setCursor(0, 0);
    lcd_1.print("Smoke   detected");
    
    ALARM();
    
    if (state == 0)
    {
      FAN(1);
      state = 1;
    }
  }
  
  else if (signal > 7)
  {
    lcd_1.setCursor(0, 0);
    lcd_1.print("Smoke   detected");
    
    if (state == 1)
    {
      FAN(0);
      state = 0;
    }  
  }
  
  else
  {
    lcd_1.setCursor(0, 0);
    lcd_1.print("The air is clear");
    
    if (state == 1)
    {
      FAN(0);
      state = 0;
    }
  }
}


/*
Function name: 	FAN
Purpose: 	Turns on or off fan, and displays the change.
Parameters: 	Takes an integer as an input for the fan to be turned on or off
*/
void FAN(int state)
{
  switch(state)
  {
    case 0:
      lcd_1.setCursor(0, 1);
      lcd_1.print("Turning Fan OFF");
      analogWrite(MOTOR_PIN, 255);
      break;
    
    case 1: 
      lcd_1.setCursor(0, 1);
      lcd_1.print("Turning Fan  ON");
      analogWrite(MOTOR_PIN, 0);
      break; 
    
    default:
      lcd_1.setCursor(0, 1);
      lcd_1.print("FAN ERROR");
      break;
  }
}

/*
Function name: 	ALARM
Purpose: 	Turns the alarm on for a few seconds
Parameters: 	NULL
*/
void ALARM()
{
  tone(SPEAKER_PIN,1000);
  delay(1000);
  noTone(SPEAKER_PIN);
  delay(1000);
}

/*
Function name: 	SIGNAL_AVERAGE
Purpose: 	Averages the signal for the assigned "Sample time "
Parameters: 	NULL
*/
int SIGNAL_AVERAGE()
{
  int sum = 0;
  //Signal Averaging
  for (int i = 0; i < SAMPLING_TIME; i++)
  {
    sum += analogRead(DETECTOR_PIN);
    delay(100);
  }
  return sum / SAMPLING_TIME;
}
  
  
