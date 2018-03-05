#include "main.h"


class Motor
{
public:
  Motor(unsigned char motorPort);
  ~Motor();

  virtual void setSpeed(int speed);
  unsigned char getMotorPort(){return MotorPort;}
private:
  unsigned char MotorPort;
};


Motor::Motor(unsigned char motorPort)
{
  this -> MotorPort = motorPort;
}

Motor::~Motor()
{
}
void Motor::setSpeed(int speed){
  motorSet(MotorPort, speed);
};
