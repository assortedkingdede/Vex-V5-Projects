/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Benjamin.Eggers.CG                               */
/*    Created:      Fri Sep 23 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    2, 1, 11        
// Vision6              vision        6               
// Expander9            triport       9               
// RangeFinder9A        sonar         A, B            
// Controller1          controller                    
// GPS20                gps           20              
// ---- END VEXCODE CONFIGURED DEVICES ----

#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "vex.h"

using namespace vex;

int Brain_precision = 0, Console_precision = 0, Controller1_precision = 0, Vision6_objectIndex = 0;

float myVariable;

// "when started" hat block
int whenStarted1() {
  while (true) {
    // No Vision Sensor signature selected
    Vision6.takeSnapshot(Vision6__SIG_1);
    Controller1.Screen.print("Seeking");
    Drivetrain.setTurnVelocity(25.0, percent);
    Drivetrain.stop();
    if (Vision6.objectCount > 0) {
      Controller1.Screen.print("Detected");
      Controller1.rumble("....");
      Drivetrain.stop();
      if (Vision6.objects[Vision6_objectIndex].centerX > 80.0) {
        Drivetrain.turn(right);
      }
      if (Vision6.objects[Vision6_objectIndex].centerX < 20.0) {
        Drivetrain.turn(left);
      }
      if (Vision6.objects[Vision6_objectIndex].centerX > 60.0 && Vision6.objects[Vision6_objectIndex].centerX < 100.0) {
       // if (Vision6.objects[Vision6_objectIndex].width > 125.0) {
         // Drivetrain.drive(forward);
        //}
        //else {
          //Drivetrain.stop();
        //}
      }
    }
    else {
      Drivetrain.turn(right);
    }
  wait(5, msec);
  }
  return 0;
}


int main() {
  // set default print color to black
  printf("\033[30m");

  // wait for rotation sensor to fully initialize
  wait(30, msec);

  whenStarted1();
}
