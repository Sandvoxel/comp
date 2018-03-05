#include "util/Motor.h"

class MotorEncoder : public Motor
{
public:
  MotorEncoder(unsigned char motorPort, unsigned char portTop, unsigned char portBottom, bool reverse);
  ~MotorEncoder();
  void setSpeed(int speed);
  int getEncoderValue();
private:
  Encoder encoder;
};
//Used to set motor speed
void MotorEncoder::setSpeed(int speed){
  motorSet(this -> getMotorPort(), speed);
}
//Used to get the encoders value
int MotorEncoder::getEncoderValue(){
  return encoderGet(encoder);
}
//The constructor that takes the
MotorEncoder::MotorEncoder(unsigned char motorPort, unsigned char portTop, unsigned char portBottom, bool reverse) :
Motor(motorPort)
{
  this -> encoder = encoderInit(portTop, portBottom, reverse);
  encoderReset(this -> encoder);
}

MotorEncoder::~MotorEncoder()
{
}
