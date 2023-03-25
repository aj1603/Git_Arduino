int sensor_1_pin = 3;
int sensor_2_pin = 4;
int led_pin = 10;
int motor_1_pin = 5;
int motor_2_pin = 6;
int sensor_1_val;
int sensor_2_val;
int working_time = 10000;
float state_time;
boolean sensor_read = true;

void setup() {
  Serial.begin(9600);
  pinMode(sensor_1_pin, INPUT);
  pinMode(sensor_2_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(motor_1_pin, OUTPUT);
  pinMode(motor_2_pin, OUTPUT);
}

void loop() {
  sensor_1_val = digitalRead(sensor_1_pin);
  Serial.println(sensor_1_val);
  if (sensor_1_val == 0 && sensor_read) {
    digitalWrite(motor_1_pin, HIGH);
    digitalWrite(motor_2_pin, LOW);
    delay(18000);
    digitalWrite(motor_1_pin, LOW);
    digitalWrite(motor_2_pin, LOW);
    sensor_read = false;
  }
  if (sensor_1_val == 1 && !sensor_read) {
    digitalWrite(motor_1_pin, LOW);
    digitalWrite(motor_2_pin, HIGH);
    delay(18000);
    digitalWrite(motor_1_pin, LOW);
    digitalWrite(motor_2_pin, LOW);
    sensor_read = true;
  }

  sensor_2_val = digitalRead(sensor_2_pin);
  if (sensor_2_val == 1) {
    digitalWrite(led_pin, HIGH);
    Serial.println("LED yandy");
  }
  else {
    digitalWrite(led_pin, LOW);
    Serial.println("LED ocdi");
  }
}
