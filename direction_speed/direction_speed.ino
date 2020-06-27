// Wind Direction Part:
#define outputA 8
#define outputB 9
#define button 7

int counter = 0; 
int a_state;
int a_lastState;  
int button_state = 0;
String dir;
int mapped;

// Wind Speed Part:
int sensor = A0;
float time1;
float time2;
float diff;
float wind_speed;
const float r = 0.0001; //10 cm to km
const float pi = 3.1415;

void setup() { 
  pinMode(outputA,INPUT);
  pinMode(outputB,INPUT);
  pinMode(button, INPUT);
  pinMode(sensor,INPUT);

  Serial.begin(9600);
  // initial state of the outputA
  a_lastState = digitalRead(outputA);   
} 
void loop() { 

  // Wind Direction Calculation:
  a_state = digitalRead(outputA); // Current state of the outputA
  button_state = digitalRead(button);
  
  // If the previous and the current state of the outputA are different, that means a Pulse has occured
  if (a_state != a_lastState){     
    // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
    if (digitalRead(outputB) != a_state) { 
      counter ++;
    } else {
      counter --;
    }
   mapped = counter * 12 % 360; 
   } 
  

  // Calibration
  if(button_state == 1){
    counter = 0;
  }
  direction();
  windspeed();    

  a_lastState = a_state; // Updates the previous state of the outputA with the current state

  Serial.print(dir);
  Serial.print("  ***  ");
  Serial.println(wind_speed);  
  
  
}


void windspeed(){

  // Wind Speed Calculation:
  if(analogRead(sensor)<980)
  {
    time1 = millis();
    delay(30);
  }
  if(analogRead(sensor)>980)
  {
    time2 = millis();
    diff = (time2-time1); 
    diff = diff / 1000;
    wind_speed = (2 * pi * r * 3600)/diff;    
  }
  
}
void direction(){
/*
  //mapped = counter % 30;   

  if((mapped >= -1 && mapped <= 0) || (mapped <= -1&& mapped >= -28) || (mapped >= 0 && mapped <=2) || (mapped >27 && mapped <=30))  {
    dir = "N";
  }
  if((mapped >2 && mapped <= 6) || (mapped > -28 && mapped <= -23)){
    dir = "N-E";
  }
  if((mapped > 6 && mapped <= 9) || (mapped > -23 && mapped <= -20)){
    dir = "E";
  }
  if((mapped > 9 && mapped <= 13) || (mapped > -20 && mapped <= -16)){
    dir = "S-E";
  }
  if((mapped > 13 && mapped <= 16) || (mapped > -15 && mapped <= -13)){
    dir = "S";
  }
  if((mapped > 16 && mapped <= 21) || (mapped > -13 && mapped <= -8)){
    dir = "S-W";
  }
  if((mapped > 21 && mapped <= 24) || (mapped > -8 && mapped <= -5)){
    dir = "W";
  }
  if((mapped > 24 && mapped <= 27) || (mapped > -5 && mapped <= -2)){
    dir = "N-W";
  }
*/
  
  if((mapped >= -24 && mapped <= 0) || (mapped <= -336 && mapped >= -359) || (mapped >= 0 && mapped <=24))  {
    dir = "N";
  }
  if((mapped >24 && mapped <= 72) || (mapped > -336 && mapped <= -288)){
    dir = "N-E";
  }
  if((mapped > 72 && mapped <= 108) || (mapped > -288 && mapped <= -252)){
    dir = "E";
  }
  if((mapped > 108 && mapped <= 156) || (mapped > -252 && mapped <= -216)){
    dir = "S-E";
  }
  if((mapped > 156 && mapped <= 204) || (mapped > -216 && mapped <= -168)){
    dir = "S";
  }
  if((mapped > 204 && mapped <= 264) || (mapped > -168 && mapped <= -120)){
    dir = "S-W";
  }
  if((mapped > 264 && mapped <= 300) || (mapped > -120 && mapped <= -72)){
    dir = "W";
  }
  if((mapped > 300 && mapped <= 359) || (mapped > -72 && mapped <= -25)){
    dir = "N-W";
  }

}
