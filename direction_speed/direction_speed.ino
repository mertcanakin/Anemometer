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
float vel;
float diff;
float wind_speed;
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
    wind_speed = (2*3.14*0.0001*3600) / diff;         
  }

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
    
   } 

  // Calibration
  if(button_state == 1){
    counter = 0;
  }
  
  a_lastState = a_state; // Updates the previous state of the outputA with the current state
  direction();
  Serial.print(dir);
  Serial.print("  ***  ");
  Serial.println(wind_speed);
  
}
void direction(){
  mapped = counter * 12 % 360;
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
