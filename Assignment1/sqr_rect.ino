#include <Romi32U4.h>
#include <PololuRPiSlave.h>

Romi32U4Motors motors;
Romi32U4Encoders encoders;
Romi32U4ButtonB buttonB;

void setup() {
  Serial.begin(57600);

  // put your setup code here, to run once:
  buttonB.waitForButton();

  // Delay so that the robot does not move away while the user is
  // still touching it.
  delay(1000);
  ledYellow(false);
  ledGreen(true);
  ledRed(false);
}

float _debug_linear_ms = 0.25;
float _debug_angle_rs = 0.0;
void _DEBUG_PID_CONTROL() {
  static float _linear_ms_change = 0.1;
  set_twist_target(_debug_linear_ms, _debug_angle_rs);
}

void loop() {

  _DEBUG_PID_CONTROL();
  // put your main code here, to run repeatedly:
   ledYellow(1);
  for (int speed = 0; speed <= 100; speed++)
  {
    motors.setLeftSpeed(speed);
  }

  // Run right motor forward.
  ledRed(1);
  for (int speed = 0; speed <= 100; speed++)
  {
    motors.setRightSpeed(speed);
  }
  delay(1000);
   for (int speed = 100; speed >= 0; speed--)
  {
    motors.setRightSpeed(speed);
    motors.setLeftSpeed(speed);
    
  }
  delay(1000);

  ledRed(1);
  for (int speed = 0; speed <= 100; speed++)
  {
    motors.setRightSpeed(speed);
  }
  delay(1000);
  if (everyNmillisec(10)) {
    // ODOMETRY
    calculateOdom();
    doPID();
  }

}