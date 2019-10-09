// 6WD rover control code. FS-R9B. BTS7960 driver
// by Taewook, Kang. laputa99999@gmail.com. 2019.10.8
// MIT license
//
#define chA 22
#define chB 24

#define R_RPWM 2
#define R_LPWM 3
#define R_LEN  4
#define R_REN  5
#define L_LPWM 6
#define L_RPWM 7
#define L_LEN  8
#define L_REN  9

void setup() {
  pinMode(chA, INPUT);
  pinMode(chB, INPUT);

  for(int i = R_RPWM; i <= L_REN; i++)
    pinMode(i, OUTPUT);
  for(int i = R_RPWM; i <= L_REN; i++)
    digitalWrite(i, LOW);

  delay(1000);
  Serial.begin(9600);
}

void runMotor(int leftDrive, int leftReverse, int rightDrive, int rightReverse)
{
  digitalWrite(R_REN, HIGH);
  digitalWrite(R_LEN, HIGH);
  digitalWrite(L_REN, HIGH);
  digitalWrite(L_LEN, HIGH);
  delay(100);

  analogWrite(L_LPWM, leftDrive);        
  analogWrite(L_RPWM, leftReverse);        
  analogWrite(R_LPWM, rightDrive);
  analogWrite(R_RPWM, rightReverse);    
}

void loop() {
  int drive = pulseIn (chA, HIGH);     // drive, back
  int steering = pulseIn (chB, HIGH);  // left, right

  String data = "D = " + String(drive);
  Serial.print(data);
  data =  ", S = " + String(steering);
  Serial.print(data);

  int motorDrive = 0;
  int motorSteer = 0;

  motorDrive = map(drive, 1070, 1880, 0, 255);
  motorDrive = constrain(motorDrive, 0, 255);
  motorSteer = map(steering, 1040, 1880, 0, 255);
  motorSteer = constrain(motorSteer, 0, 255);
  
  data =  ", MD = " + String(motorDrive);
  Serial.print(data);
  data =  ", MS = " + String(motorSteer);
  Serial.println(data);
  
  bool forward = true;
  if(90 <= motorDrive && motorDrive <= 110)
  {
    motorDrive = 0;
  }
  else if(motorDrive > 110)
  {
    motorDrive = map(motorDrive, 110, 255, 0, 255);
    motorDrive = constrain(motorDrive, 0, 255);
  }
  else 
  {
    motorDrive = map(motorDrive, 0, 90, 255, 0);
    motorDrive = constrain(motorDrive, 0, 255);   
    forward = false; 
  }

  // |_rover__>>
  // 
  if(motorSteer == 0)   // if transmitter power off the motorSteer value is 0
  {
    runMotor(0, 0, 0, 0);
  }
  else if(100 <= motorSteer && motorSteer <= 140)    // go straight
  {
    runMotor(forward ? motorDrive : 0, forward ? 0 : motorDrive, 
             forward ? motorDrive : 0, forward ? 0 : motorDrive);
  }
  else if(motorSteer < 100) // turn left
  {
    runMotor(forward ? motorDrive : 0, forward ? 0 : motorDrive, 
             forward ? 0 : motorDrive, forward ? motorDrive : 0);
  }
  else  // turn right
  {
    runMotor(forward ? 0 : motorDrive, forward ? motorDrive : 0, 
             forward ? motorDrive : 0, forward ? 0 : motorDrive);
  }
}
