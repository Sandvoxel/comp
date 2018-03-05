#include "util/motorEncoder.h"
#include <math.h>


int lastPos=0;

class pidControl : public MotorEncoder{
public:
  pidControl(unsigned char motorPort, unsigned char portTop, unsigned char portBottom, bool reverse);
  ~pidControl();

  void holdPos();
  void setWillHoldPos(bool WillHoldPos){willHoldPos=WillHoldPos;}
  void setRequesedPos(int Pos){requesedPos=Pos;}
  int getVelocity(){return velocity;}
  void setVelocity(int Velocity){velocity=Velocity;}
  void setPidValues(float pid_Kp, float  pid_Ki, float pid_Kd);
private:
  float pid_Kp = 2.0;
  float pid_Ki = 0.04;
  float pid_Kd = 0.0;
  TaskHandle velocityTask;
  int velocity=0;
  int requesedPos=0;
  bool willHoldPos=false;
};

void pidControl::setPidValues(float pid_Kp, float  pid_Ki, float pid_Kd){
  this -> pid_Kp = pid_Kp;
  this -> pid_Ki = pid_Ki;
  this -> pid_Kd = pid_Kd;
}

void updateVelocity(void *pram){
  pidControl *pidcontrol = static_cast<pidControl*>(pram);
  while (1) {
    pidcontrol -> setVelocity(pidcontrol ->getEncoderValue()-lastPos);
    lastPos = pidcontrol->getEncoderValue();
    pidcontrol -> holdPos();
    delay(50);
  }
}

void pidControl::holdPos(){
  float error=0.0;
  float piddrive=0.0;
  if(willHoldPos){
    printf("BD%f\n", piddrive);
    printf("BE%f\n", error);
      error = getEncoderValue() - requesedPos;
      if(0>error){
        piddrive = sqrtf(-error)*pid_Kp;
        piddrive = -piddrive;
      }else{
        piddrive = sqrtf(error)*pid_Kp;
      }
      printf("D%f\n", piddrive);
      printf("E%f\n", error);
      printf("EV%d\n", getEncoderValue());
      printf("RP%d\n", requesedPos);

      if(piddrive<127&&piddrive>-127){
        if(piddrive<10&&piddrive>-10){
          setSpeed(0);
        }else if(piddrive<20&&piddrive>-20){
          setSpeed(20);
        }else{
          setSpeed(piddrive);
        }
      }else{
        if(piddrive>0){
          setSpeed(127);
        }else{
          setSpeed(-127);
        }
      }
  }
}


pidControl::pidControl(unsigned char motorPort, unsigned char portTop, unsigned char portBottom, bool reverse) : MotorEncoder(motorPort, portTop, portBottom, reverse){
    this -> velocityTask = taskCreate(updateVelocity, TASK_DEFAULT_STACK_SIZE, this, TASK_PRIORITY_DEFAULT);
}

pidControl::~pidControl(){
  taskDelete(this -> velocityTask);
}
