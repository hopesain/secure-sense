//Libraries
#include <Servo.h>
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7,6,5,4,3,2,1,HIGH);

// Sensors 
const int motion_sensor = 13;
const int trig_pin = 8;
const int echo_pin = 9;
const int button_pin = 5;
const int flame_sensor = 12;

// Actuators
const int speaker_pin = 2;
const int servo_pin = 11;

// States
const int INACTIVE = 0;
const int ACTIVE = 1;
const int WARNING = 2;
const int DANGER = 3;
const int INTRUSION = 4;
const int FLAME = 5;

// Variables.
int current_state = ACTIVE;
bool system_active = true;
bool last_button_state = HIGH;
unsigned long state_start_time = 0;
unsigned long state_hold_duration = 10000; 
int last_state = -1;
bool door_open = false;


// SERVO CONFIGURATION
Servo my_servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(button_pin, INPUT_PULLUP);

  pinMode(motion_sensor, INPUT);

  pinMode(trig_pin, OUTPUT);

  pinMode(echo_pin, INPUT);

  pinMode(speaker_pin, OUTPUT);

  pinMode(flame_sensor, INPUT);

  my_servo.attach(servo_pin);

  my_servo.write(0); 

  lcd.begin(16, 2);

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print("INTRODUCING");

  lcd.setCursor(0, 1);

  lcd.print("SECURE-SENSE");

  delay(5000);

}

void loop() {
  // put your main code here, to run repeatedly:
  checkButton();

  bool motion = digitalRead(motion_sensor);

  float distance = getDistance();

  bool flame = digitalRead(flame_sensor);

  updateState(motion, distance, flame);

  speakerBehaviour();

  handleDoor();

  displayData();

}

void checkButton() {
  bool button_state = digitalRead(button_pin);

  if (button_state == LOW && last_button_state == HIGH) {
    system_active = !system_active;

    if (!system_active) {
      current_state = INACTIVE;
    } 
    else {
      current_state = ACTIVE;
    }

    delay(200);
  }

  last_button_state = button_state;
}

float getDistance() {
  digitalWrite(trig_pin, LOW);

  delayMicroseconds(2);

  digitalWrite(trig_pin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trig_pin, LOW);


  long duration = pulseIn(echo_pin, HIGH);

  float distance = duration * 0.034 / 2;

  return distance;
}

void updateState(bool motion, float distance, bool flame) {
  unsigned long now = millis();
  
  if (!system_active) {
    current_state = INACTIVE;
    return;
  }

  if (flame) {
        current_state = FLAME;
        state_start_time = now; 
        return;
    }

  if (now - state_start_time < state_hold_duration) {
    return; 
  }

  if (motion) {
    current_state = INTRUSION;
    state_start_time = now;
    return;
  }

  if(distance > 0 && distance < 15) {
    current_state = DANGER;
    return;
  }

  if (distance >= 15 && distance < 30) {
    current_state = WARNING;
    return;
  }

  current_state = ACTIVE;
}

void speakerBehaviour() {
  if (current_state == ACTIVE || current_state == INACTIVE) {
    noTone(speaker_pin);
    return;
  }

  if (current_state == INTRUSION) {
    tone(speaker_pin, 1000);
    return;
  }

  if (current_state == DANGER) {
    tone(speaker_pin, 1000);

    delay(500);

    noTone(speaker_pin);

    delay(500);

    return;
  }

  if (current_state == WARNING) {
    tone(speaker_pin, 1000);

    delay(1000);

    noTone(speaker_pin);

    delay(1000);

    return;
  }

  if (current_state == FLAME) {
    tone(speaker_pin, 1000); 
    return;
}
}

void displayData() {
  if (current_state == last_state) {
    return;
  }

  lcd.clear();

  if (current_state == INACTIVE) {
    lcd.setCursor(0, 0);

    lcd.print("SYSTEM STATE");

    lcd.setCursor(0, 1);

    lcd.print("ACCESS GRANTED");
  }

  if (current_state == ACTIVE) {
    lcd.setCursor(0, 0);

    lcd.print("SYSTEM STATE");

    lcd.setCursor(0, 1);

    lcd.print("ACTIVE");
  }

  if (current_state == WARNING) {
    lcd.setCursor(0, 0);

    lcd.print("SYSTEM STATE");

    lcd.setCursor(0, 1);

    lcd.print("SOMEONE CLOSE");
  }

  if (current_state == DANGER) {
    lcd.setCursor(0, 0);

    lcd.print("SYSTEM STATE");

    lcd.setCursor(0, 1);

    lcd.print("TOO CLOSE");
  }

  if (current_state == INTRUSION) {
    lcd.setCursor(0, 0);

    lcd.print("SYSTEM STATE");

    lcd.setCursor(0, 1);

    lcd.print("MOTION DETECTED");

    delay(2000);

    lcd.clear();

    lcd.setCursor(0, 0);

    lcd.print("SYSTEM STATE");

    lcd.setCursor(0, 1);

    lcd.print("LOCKDOWN MODE");
  }

  if (current_state == FLAME) {
    lcd.setCursor(0, 0);

    lcd.print("SYSTEM STATE");

    lcd.setCursor(0, 1);

    lcd.print("FIRE DETECTED");
  }

  last_state = current_state;
}

void openDoor() {
    for (int angle = 0; angle <= 110; angle += 2) {
        my_servo.write(angle);
        delay(10);
    }
}

void closeDoor() {
    for (int angle = 110; angle >= 0; angle -= 2) {
        my_servo.write(angle);
        delay(10);
    }
}

void handleDoor() {
    if (current_state == INTRUSION && door_open) {
        closeDoor();
        door_open = false;
    }

    else if (current_state == ACTIVE && !door_open) {
        openDoor();
        door_open = true;
    }
}

