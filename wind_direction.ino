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
    Serial.println(counter);
  } 

  // Calibration
  if(button_state == 1){
    counter = 0;
  }

  a_lastState = a_state; // Updates the previous state of the outputA with the current state
}

void direction(){
  int mapped = counter * 12 % 360;

  if(mapped == 0){
    Serial.println("N");
  }
  if((mapped == 48) || (mapped == -312)){
    Serial.println("N-E");
  }
  if((mapped == 96) || (mapped == -264)){
    Serial.println("E");
  }
  if((mapped == 144) || (mapped == -216)){
    Serial.println("S-E");
  }
  if((mapped == 180) || (mapped == -180)){
    Serial.println("S");
  }
  if((mapped == 216) || (mapped == -144)){
    Serial.println("S-W");
  }
  if((mapped == 276) || (mapped == -84)){
    Serial.println("W");
  }
  if((mapped == 312) || (mapped == -48)){
    Serial.println("N-W");
  }
}
