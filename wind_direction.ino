#define outputA 8
#define outputB 9
#define button 7

int counter = 0; 
int a_state;
int a_lastState;  
int button_state = 0;

void setup() { 
  pinMode(outputA,INPUT);
  pinMode(outputB,INPUT);
  pinMode(button, INPUT);
   
  Serial.begin(9600);
  // initial state of the outputA
  a_lastState = digitalRead(outputA);   
} 
void loop() { 
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
    direction();
  } 

  // Calibration
  if(button_state == 1){
    counter = 0;
  }

  a_lastState = a_state; // Updates the previous state of the outputA with the current state
}

void direction(){
  int mapped = counter * 12 % 360;

  if((mapped >= -24 && mapped <= 0) || (mapped <= -336 && mapped >= -359) || (mapped >= 0 && mapped <=24))  {
    Serial.println("N");
  }
  if((mapped >24 && mapped <= 72) || (mapped > -336 && mapped <= -288)){
    Serial.println("N-E");
  }
  if((mapped > 72 && mapped <= 108) || (mapped > -288 && mapped <= -252)){
    Serial.println("E");
  }
  if((mapped > 108 && mapped <= 156) || (mapped > -252 && mapped <= -216)){
    Serial.println("S-E");
  }
  if((mapped > 156 && mapped <= 204) || (mapped > -216 && mapped <= -168)){
    Serial.println("S");
  }
  if((mapped > 204 && mapped <= 264) || (mapped > -168 && mapped <= -120)){
    Serial.println("S-W");
  }
  if((mapped > 264 && mapped <= 300) || (mapped > -120 && mapped <= -72)){
    Serial.println("W");
  }
  if((mapped > 300 && mapped <= 359) || (mapped > -72 && mapped <= -25)){
    Serial.println("N-W");
  }
}
