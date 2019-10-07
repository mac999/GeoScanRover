#define chA 22
#define chB 24
#define enA 9
#define in1 4
#define in2 5
#define enB 10
#define in3 6
#define in4 7

void setup() {
  pinMode(chA, INPUT);
  pinMode(chB, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

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

  if(100 <= motorSteer && motorSteer <= 140)
  {
    digitalWrite(in1, LOW);     // Set Motor A forward
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if(motorSteer < 100)
  {
    digitalWrite(in1, HIGH); 
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else
  {
    digitalWrite(in1, LOW);  
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  analogWrite(enA, motorDrive); // Send PWM signal to motor A
  analogWrite(enB, motorDrive); // Send PWM signal to motor B    
}
