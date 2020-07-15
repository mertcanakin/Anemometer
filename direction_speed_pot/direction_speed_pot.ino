// Wind Direction Part:
const int pot = A0;
int pot_value = 0;
int mapped = 0;
String dir;

// Wind Speed Part:
int sensor = 2;
float value = 0;
float rev = 0;
int rpm;
int oldtime = 0;
int time;
float wind_speed = 0;
const float pi = 3.1415;
const float r = 0.0001;


void isr() //interrupt service routine
{
rev++;
}
void setup() { 
  pinMode(pot, INPUT);
  attachInterrupt(0,isr,RISING);  //attaching the interrupt

  Serial.begin(9600);
  // initial state of the outputA
} 
void loop() { 

  direction();
  windspeed();    
  
  Serial.print(dir);
  Serial.print("  ***  ");
  Serial.println(wind_speed);  
  
}

void windspeed(){
  delay(1000);
  detachInterrupt(0);           //detaches the interrupt
  time=millis()-oldtime;        //finds the time 
  rpm=(rev/time)*60000;         //calculates rpm
  oldtime=millis();             //saves the current time
  rev=0;
  wind_speed = 2*pi*r*rpm*60;
  attachInterrupt(0,isr,RISING);

}
void direction(){
  //Potentiometer position is importan!!
  pot_value = analogRead(pot);
  mapped = pot_value % 100;
  if(mapped >=0 && mapped <=6 || mapped >95 && mapped <=99){
    dir = "N";
  }
  if(mapped >6 && mapped <=20){
    dir = "N-E";
  }
  if(mapped >22 && mapped <=30){
    dir = "E";
  }
  if(mapped >30 && mapped <=45){
    dir = "S-E";
  }
  if(mapped >45 && mapped <=54){
    dir = "S";
  }
  if(mapped >54 && mapped <=72){
    dir = "S-W";
  }
  if(mapped >72 && mapped <=82){
    dir = "W";
  }
  if(mapped >82 && mapped <=95){
    dir = "N-W";
  }
  
}
