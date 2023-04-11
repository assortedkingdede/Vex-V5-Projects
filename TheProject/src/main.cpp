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
// Vision10             vision        10              
// Arm                  motor         4               
// Hand                 motor         5               
// Expander9            triport       9               
// RangeFinder9A        sonar         A, B            
// GPS20                gps           20              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

event checkRed = event();
event checkMagenta = event();
event checkGreen = event();
event checkDistance = event();

void detection(){
  //Move forward based on distance from target, account for length of robot.
  wait(1, seconds);
  double travel = RangeFinder9A.distance(inches);
  double move = travel - 20;
  Drivetrain.driveFor(forward, move, inches);
}

void visionLocation() {
  printf("CenterX: ");
  printf("%.2f", (double)Vision10.largestObject.centerX); 
  printf("\n");
  printf("CenterY: ");
  printf("%.2f", (double)Vision10.largestObject.centerY);
  printf("\n");
}

void targetObject() {
  int TARGET = 150; 
  int error = Vision10.largestObject.centerY - TARGET;  //How far off center is the item.

    // simple P control with a limit of 50
    int drive = error;
    if( drive > 50 ) drive = 50;
    if( drive < -50 ) drive = -50;

    // object is found and centered
    if( Vision10.largestObject.centerY > (TARGET-15) && Vision10.largestObject.centerY < (TARGET+15) ) {
      Drivetrain.stop();
    }
    else {
      Drivetrain.turnToRotation(drive, degrees); //What does drive do?
      detection(); 
    }
}

void hasMagentaCallback() { //Add target object somewhere when ready
  Brain.Screen.setFont(mono40);
  Brain.Screen.clearLine(1, black);
  Brain.Screen.setCursor(Brain.Screen.row(), 1);
  Brain.Screen.setCursor(1, 1);
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Vision10.takeSnapshot(Vision10__SIG_1);
  if (Vision10.objectCount > 0) {
    Brain.Screen.print("Magenta Object Found");
    Controller1.Screen.print("Magenta Object Found");
  } else {
    Brain.Screen.print("No Magenta Object");
    Controller1.Screen.print("No Magenta Object");
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Drivetrain.setDriveVelocity(50, percent);
  targetObject();
  //checkMagenta(hasMagentaCallback);
  
  while (true) {
    checkMagenta.broadcastAndWait();
    wait(1, seconds);
  }
}
