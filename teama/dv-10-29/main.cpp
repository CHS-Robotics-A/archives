/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       arpita_gupta                                              */
/*    Created:      Wed Jul 06 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// p2                   digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
vex::competition    Competition;

int runoff(int parameter) {
  if (parameter > 100){
    parameter = 100;
  }
  else if (parameter < -100){
    parameter = -100;
  }
  return parameter;
}

int overFlow(int input){
  if (input < 30 && input > 0){
    input = 0;
  } else if (input > -30 && input < 0){
    input = 0;
  }
  return input;
}

vex::motor intakeRight = vex::motor(vex::PORT7);
vex::motor intakeLeft = vex::motor(vex::PORT9,true);
vex::motor flywheel1 = vex::motor(vex::PORT10);
vex::motor flywheel2 = vex::motor(vex::PORT8,true);//Towards the Back, closer to the intake

vex::motor RightFront = vex::motor(vex::PORT17);
vex::motor RightBack = vex::motor(vex::PORT15); //doesn't work
vex::motor LeftFront = vex::motor(vex::PORT18, true);
vex::motor LeftBack = vex::motor(vex::PORT13, true); //doesn't work

//void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  //vexcodeInit();
//}

int axis3 = 0;
int axis1 = 0;
int axis4 = 0;
int count = 0, X1 = 0, X2 = 0, Y1 = 0;



void usercontrol(void) {
  // User control code here, inside the loop
  
  while (1) {

    axis3 = Controller1.Axis3.position();
    axis1 = Controller1.Axis1.position();
    axis4 = Controller1.Axis4.position();
    Y1=axis3;
    X1=axis4;
    X2=axis1;

    RightFront.spin(vex::directionType::fwd, runoff(overFlow(Y1-X2-X1)),vex::velocityUnits::pct);
    RightBack.spin(vex::directionType::fwd,runoff(overFlow(Y1-X2+X1)),vex::velocityUnits::pct);
    LeftFront.spin(vex::directionType::fwd,runoff(overFlow(Y1+X2+X1)),vex::velocityUnits::pct);
    LeftBack.spin(vex::directionType::fwd,runoff(overFlow(Y1+X2-X1)),vex::velocityUnits::pct);
    wait(20, msec);



    if (Controller1.ButtonR1.pressing()){
      intakeRight.spin(vex::directionType::fwd,127,vex::velocityUnits::pct);
      intakeLeft.spin(vex::directionType::fwd,127,vex::velocityUnits::pct);
    }
    if (Controller1.ButtonR2.pressing()){
      intakeRight.spin(vex::directionType::fwd,0,vex::velocityUnits::pct);
      intakeLeft.spin(vex::directionType::fwd,0,vex::velocityUnits::pct); 
    }



  if (Controller1.ButtonL1.pressing()){
      flywheel1.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
      flywheel2.spin(vex::directionType::fwd,100,vex::velocityUnits::pct);
    }
    if (Controller1.ButtonL2.pressing()){
      flywheel1.stop(vex::brakeType::coast);
      flywheel2.stop(vex::brakeType::coast);
    }


    if(Controller1.ButtonX.pressing()){
      p2.set(true);
    }
    if(Controller1.ButtonB.pressing()){
      p2.set(false);
    }
    }
 
}


int main() {
  // Set up callbacks for autonomous and driver control periods.
  //Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  //pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }

  
}