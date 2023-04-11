/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Benjamin.Eggers.CG                               */
/*    Created:      Tue Oct 18 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Inertial11           inertial      11              
// Vision6              vision        6               
// GPS20                gps           20              
// Drivetrain           drivetrain    1, 2            
// Launcher             motor         10              
// Turret               motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void fire() {
  Launcher.setMaxTorque(110, percent);
  Launcher.setVelocity(110, percent);
  Launcher.spinFor(forward, 3, seconds);
}

void shootStop(){
  Launcher.stop();
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Controller1.ButtonA.pressed(fire);
  Controller1.ButtonB.pressed(shootStop);
}
