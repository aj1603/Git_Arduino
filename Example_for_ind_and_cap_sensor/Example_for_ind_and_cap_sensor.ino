int sensorInd = A0; 
int sensorpin = 2;
int indValue;
int i = 0;
float Pipe_Pos = 0.0;
float Gate_Pos = 0.0;
int n = 0;
long duration;
int distance;
float metalDetected;
void setup() {
//  pinMode(trigPin, OUTPUT); // trigPin=output
//  pinMode(echoPin, INPUT); // echoPin = input
  Serial.begin(9600); // Starts the serial communication
//  Pipe_Pos = Pipe_Servo.read();
//  Gate_Pos = Gate_Servo.read();
  Serial.println("Motor_PIPE Position");
  Serial.println(Pipe_Pos);
  Serial.println("Motor_GATE Position");
  Serial.println(Gate_Pos);
  delay(5000);

//  Pipe_Servo.attach(11);
//  if (Pipe_Pos < 90) {
//
//    for (i = Pipe_Pos; i <= 90; i = i + 1) {
//      Pipe_Servo.write(i);
//      delay(15);
//    }
//  }
//
//  else {
//    for (i = Pipe_Pos; i >= 90; i = i - 1) {
//      Pipe_Servo.write(i);
//      delay(15);
//
//    }
//  }
  delay(1000); //Delay (wait) for servo pipe to go to the bin.
  //Next rotate the gate servo.
  //And control the speed of Gate Servo.
//  Gate_Servo.attach(10);
  for (n = 0; n <= 45; n = n + 1) { //Choose the right angle for Gate servo
//    Gate_Servo.write(n);
    delay(20); //Controll the speeed of Gate servo
  }
  delay(1000); //Delay (wait) and then bring back the Gate_Servo to its
  //initial position.
  //Bring Back Gate_Servo to initial position
  //So from actual position 2-> n=45; we go backwards up to n=0.
  for (n = 45; n >= 0; n = n - 1) {
//    Gate_Servo.write(n);
    delay(25); //Control the speed of Gate servo
  }
  delay(5000);
  //--System Initialization--//
  // Codes that run only once]
}
void loop() {
  //delay(100);
  delay(3000);
  // Clears the trigPin
//  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);//
  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(trigPin, HIGH);
  delayMicroseconds(30);//it was 1
//  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
//  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  indValue = analogRead(sensorInd); //Save value that is read from the analog pin A0 to the variable indValue
  delay(10);
  int sensorstate = digitalRead(sensorpin); // Digital value for Capacitive S.
  delay(500);
  metalDetected = (float)indValue * 100 / 1024.0; //from analog value
  delay(50);
//  Pipe_Pos = Pipe_Servo.read(); //Read the actual position of Pipe servo
//  Gate_Pos = Gate_Servo.read(); //Read the actual position of Gate servo
  //**METAL DETECTED**/
//  / if (indValue >= 250 && sensorstate == 1 && distance <= 14)
    if (indValue >= 250) {
      Serial.println("Metal Detected");
//      Pipe_Pos = Pipe_Servo.read(); //Read the last value given to Pipe servo
//      Gate_Pos = Gate_Servo.read(); //Read the last value given to Pipe servo
      Serial.println("Motor_PIPE Position");
      Serial.println(Pipe_Pos);
      Serial.println("Motor_GATE Position");
      Serial.println(Gate_Pos);
      Serial.println("Motor to metal bin");
      delay(100);
      //Wait for some time after the measurements and move servo to
      //the corresponding bin
      //For initial position of servo_gate/PIPE in this case the read function will give us the last position of servo
      //in degree
      //Go to the second position of the PIPE servo @90 degree
      //To control the speed of the servo we do this for loop.
      //We have 2 cases 1; when pipe is somewhere in position greater then 90, in this particular case we want to go to 90 so we have to loop back.
      //The other case is to loop forward i=i+1, (meaning to increase the angle in incremental manner).

      if (Pipe_Pos < 90) {
        for (i = Pipe_Pos; i <= 90; i = i + 1) {
//          Pipe_Servo.write(i);
          delay(15);
        }
      }

      else {
        for (i = Pipe_Pos; i >= 90; i = i - 1) {
//          Pipe_Servo.write(i);
          delay(15);

        }
      }
      delay(1000); //Delay (wait) for servo pipe to go to the bin.
      //Next rotate the gate servo.
      //And control the speed of Gate Servo.
      for (n = 0; n <= 45; n = n + 1) {
//        Gate_Servo.write(n);
        delay(20);
      }
      delay(1000); //Delay (wait) and then bring back the Gate_Servo to its initial position.
      //Bring Back Gate_Servo to initial position
      //So from actual position 2--> n=45; we go backwards up to n=0.
      for (n = 45; n >= 0; n = n - 1) {
//        Gate_Servo.write(n);
        delay(25);
      }

      //**METAL DETECTED**//
      //**PLASTIC DETECTED**//

    }
    else if (indValue <= 250 && sensorstate == 1 && distance <= 15) { //NO NO state
      delay(100);
      Serial.println("Plastic Detected");
//      Pipe_Pos = Pipe_Servo.read(); //Read the last value given to Pipe servo
//      Gate_Pos = Gate_Servo.read(); //Read the last value given to Pipe servo
      Serial.println("Motor_PIPE Position");
      Serial.println(Pipe_Pos);
      Serial.println("Motor_GATE Position");
      Serial.println(Gate_Pos);
      Serial.println("Motor to Plastic Bin");
      delay(100);
      //Wait for some time after the measurements and move servo to
      //the corresponding bin

      //For initial position of servo_gate/PIPE in this case the read function will give us the last position of servo
      //in degree
      //Go to the second position of the gate Pipe_Servo in degree (145) for Plastic
      //To control the speed of the servo we do this for loop.
      //We have 2 cases 1; when pipe is somewhere in position greater then 145, in this particular case we want to go to 145 so we have to loop back.
      //The other case is to loop forward i=i+1, (meaning to increase the angle in incremental manner)until we reach the desired angle.

      if (Pipe_Pos < 145) {
        for (i = Pipe_Pos; i <= 145; i = i + 1) {
//          Pipe_Servo.write(i);
          delay(15);
        }
      }

      else {
        for (i = Pipe_Pos; i >= 145; i = i - 1) {
//          Pipe_Servo.write(i);
          delay(15);

        }
      }
      delay(1000); //Delay (wait) for servo pipe to go to the bin.
      //Next rotate the gate servo.//This remains the same for all other cases
      //And control the speed of Gate Servo.
      for (n = 0; n <= 45; n = n + 1) {
//        Gate_Servo.write(n);
        delay(20);
      }
      delay(1000); //Delay (wait) and then bring back the Gate_Servo to its
      //initial position.
      //Bring Back Gate_Servo to initial position
      //So from actual position 2--> n=45; we go backwards up to n=0.
      for (n = 45; n >= 0; n = n - 1) { //Choose the right angle for Gate servo
//        Gate_Servo.write(n);
        delay(25); //Controll the speeed of Gate servo (it can be a litle faster now)
      }
      //delay(100);

    }
  //**PLASTIC DETECTED**//
  //**GLASS DETECTED**//
    else if (indValue <= 250 && sensorstate != 1 && distance <= 14) {
      Serial.println("Glass Detected");
//      Pipe_Pos = Pipe_Servo.read(); //Read the last value given to Pipe servo
//      Gate_Pos = Gate_Servo.read(); //Read the last value given to Pipe servo
      Serial.println("Motor_PIPE Position");
      Serial.println(Pipe_Pos);
      Serial.println("Motor_GATE Position");
      Serial.println(Gate_Pos);
      Serial.println("Motor to Glass Bin");
      delay(1000);
      //Wait for some time after the measurements and move servo to
      //the corresponding bin
      //For initial position of servo_gate/PIPE in this case the read function will give us the last position of servo in degree
      //Go to the second position of the Pipe_Servo @25 degree for Glass
      //To control the speed of the servo we do this for loop.
      //We have 2 cases; when pipe is somewhere in position greater then 90, in this particular case we want to go to 25 so we have to loop back.
      //The other case is to loop forward i=i+1, (meaning to increase the angle in incremental manner).
      //Actually in this case we can have only one case when angle is greater then 25, but however! :P
      if (Pipe_Pos < 25) {
        for (i = Pipe_Pos; i <= 25; i = i + 1) {
//          Pipe_Servo.write(i);
          delay(15);
        }
      }

      else {
        for (i = Pipe_Pos; i >= 25; i = i - 1) {
//          Pipe_Servo.write(i);
          delay(15);

        }
      }
      delay(1000); //Delay (wait) for servo pipe to go to the bin.
      //Next rotate the gate servo.//This remains the same for all other cases
      //And control the speed of Gate Servo.
      for (n = 0; n <= 45; n = n + 1) {
//        Gate_Servo.write(n);
        delay(20);
      }
      delay(1000); //Delay (wait) and then bring back the Gate_Servo to its
      //initial position.
      //Bring Back Gate_Servo to initial position
      //So from actual position n=45; we go backwards up to n=0.
      for (n = 45; n >= 0; n = n - 1) {
//        Gate_Servo.write(n);
        delay(25);
      }
      Serial.println("Motor_PIPE Position");
      Serial.println(Pipe_Pos);
      Serial.println("Motor_GATE Position");
      Serial.println(Gate_Pos);
    }
}
