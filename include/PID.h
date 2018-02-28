#include "main.h"

void PidStableisedMotor(int speed, unsigned char channel) {
  motorSet(channel ,speed);
}
