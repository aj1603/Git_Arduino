#include <Stepper.h>
const int power_pin = 2;       //Power pin control for turn on and turn off conveyur power;
const int power_pin_2 = 3;       //Power pin control for turn on and turn off conveyur power;
const int cap_sensor = A0;      //Capasitive sensor for glass
const int ind_sensor = A1;      //Inductive sensor for metal
const int IR_sensor_1 = 5;     //IR sensor for conveyor
const int IR_sensor_2 = 6;     //IR sensor for garbage

// Stepper motor angle control
const int stepsPerRevolution = 6500;
const int first_state = 2000;
const int second_state = 4000;

// Stepper motor pins
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

int IR_sensor_1_val;
int IR_sensor_2_val;
int cap_sensor_val;
int ind_sensor_val;

// State keeper of thing existence
int object_detected = 0;

long working_time = 120000;
unsigned long stop_time;

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(60);
  pinMode(power_pin, OUTPUT);
  pinMode(power_pin_2, OUTPUT);
  pinMode(cap_sensor, INPUT);
  pinMode(ind_sensor, INPUT);
  pinMode(IR_sensor_1, INPUT);
  pinMode(IR_sensor_2, INPUT);
}

void loop() {
  // konveyer ochuryar
  IR_sensor_1_val = digitalRead(IR_sensor_1);

  // chykandygyny barlayar
  IR_sensor_2_val = digitalRead(IR_sensor_2);

  if (IR_sensor_1_val == 0) {
    stop_time = millis();
    digitalWrite(power_pin, HIGH);
    digitalWrite(power_pin_2, LOW);
    delay(25);
    digitalWrite(power_pin, LOW);
    digitalWrite(power_pin_2, LOW);
    // Serial.println("Conveyor is working");
  }

  if ( millis() - working_time >= stop_time) {
    digitalWrite(power_pin, LOW);
    digitalWrite(power_pin_2, HIGH);
    delay(25);
    digitalWrite(power_pin, LOW);
    digitalWrite(power_pin_2, LOW);
    //    /Serial.println("Conveyor does not working");
  }

  // plastic duyyar
  cap_sensor_val = analogRead(cap_sensor);
  Serial.println(cap_sensor_val);
  // metal duyyar
  ind_sensor_val = analogRead(ind_sensor);
  Serial.println(ind_sensor_val);

  if (cap_sensor_val >= 800) {
    object_detected = 2;
  } else if (ind_sensor_val >= 600) {
    object_detected = 1;
//    delay(2500);/
  }
  Serial.println(object_detected);

  if (object_detected > 0 && IR_sensor_2_val == 0) {
    //Serial.println(object_detected);
    switch (object_detected) {
      case 1:
        angle_1();
        break;
      case 2:
        angle_2();
        break;
      default:
        //Serial.println("No action needed or go to main state");
        break;
    }
  }
}

//This function for second garbage
void angle_1() {
  // Serial.println("Second garbage");
  myStepper.step(-first_state);
  delay(5000);

  //  /Serial.println("First garbage");
  myStepper.step(first_state);
  delay(5000);
  object_detected = 0;
}

//This function for third garbage
void angle_2() {
  //  /Serial.println("Third garbage");
  myStepper.step(-second_state);
  delay(5000);

  //  /Serial.println("First garbage");
  myStepper.step(second_state);
  delay(5000);
  object_detected = 0;
}



//  if (cap_sensor_val == 0 && ind_sensor_val == 1) {
//    ind_state = ind_sensor_val;
//    IR_sensor_2_val = digitalRead(IR_sensor_2);
//    if (ind_state == 1 && IR_sensor_2_val == 0) {
//      Serial.println(ind_state);
//      angle_1();
//      Serial.println("UCUNJI GUTA OWRULDI");
//    }
//    ind_state = 0;
//    Serial.println(ind_state);
//  }

//  if (cap_sensor_val == 0 || cap_sensor_val == 1  && ind_sensor_val == 0) {
//    IR_sensor_2_val = digitalRead(IR_sensor_2);
//    if (IR_sensor_2_val == 0) {
//      angle_2();
//      Serial.println("UCUNJI GUTA OWRULDI");
//    }
//  }
//
//  if (cap_sensor_val == 1 && ind_sensor_val == 1) {
//    IR_sensor_2_val = digitalRead(IR_sensor_2);
//    if (IR_sensor_2_val == 0) {
//      Serial.println("BRINJI GUTA OWRULDI");
//      angle_2();
//    }
//  }
//  if ( millis() - working_time >= stop_time) {
//      digitalWrite(power_pin, LOW);
//      Serial.println("Conveyor does not working");
//    }
//}
