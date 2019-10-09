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
#define L_RPWM 6
#define L_LPWM 7
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
  
  digitalWrite(R_REN, HIGH);
  digitalWrite(R_LEN, HIGH);
  digitalWrite(L_REN, HIGH);
  digitalWrite(L_LEN, HIGH);
  delay(100);

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
  if(100 <= motorSteer && motorSteer <= 140)    // go straight
  {
    analogWrite(L_LPWM, forward ? 0 : motorDrive);  // Send PWM signal to motor B        
    analogWrite(L_RPWM, forward ? motorDrive : 0);  // Send PWM signal to motor B        
    analogWrite(R_LPWM, forward ? motorDrive : 0);  // Send PWM signal to motor A
    analogWrite(R_RPWM, forward ? 0 : motorDrive);  // Send PWM signal to motor A
  }
  else if(motorSteer < 100) // turn left
  {
    analogWrite(L_LPWM, forward ? 0 : motorDrive);         
    analogWrite(L_RPWM, forward ? motorDrive : 0);         
    analogWrite(R_LPWM, forward ? 0 : motorDrive); 
    analogWrite(R_RPWM, forward ? motorDrive : 0); 
  }
  else  // turn right
  {
    analogWrite(L_LPWM, forward ? motorDrive : 0);         
    analogWrite(L_RPWM, forward ? 0 : motorDrive);         
    analogWrite(R_LPWM, forward ? motorDrive : 0); 
    analogWrite(R_RPWM, forward ? 0 : motorDrive); 
  }
}
