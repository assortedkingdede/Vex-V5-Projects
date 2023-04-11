/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       James                                                     */
/*    Created:      16 Feb 2019                                               */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Vision6              vision        6               
// Drivetrain           drivetrain    2, 1, 11        
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;

int   screen_origin_x = 150;
int   screen_origin_y = 20;
int   screen_width    = 316;
int   screen_height   = 212;

// function to draw a single object
void drawObject( vision::object &obj, vex::color c ) {
    int labelOffset = 0;
    
    Brain.Screen.setPenColor( vex::color::yellow );
    Brain.Screen.drawRectangle( screen_origin_x + obj.originX, screen_origin_y + obj.originY, obj.width, obj.height, c );
    Brain.Screen.setFont( vex::fontType::mono12 );
    
    if( obj.originX > 280 )
      labelOffset = -40;
    if( obj.originY > 10 )
      Brain.Screen.printAt( screen_origin_x + obj.originX + labelOffset, screen_origin_y + obj.originY-3, "Sig %o", obj.id );
    else
      Brain.Screen.printAt( screen_origin_x + obj.originX + labelOffset, screen_origin_y + obj.originY+10, "Sig %o", obj.id );
}

// function to draw all objects found
void drawObjects( vision &v, vex::color c, bool clearScreen ) {
    if( clearScreen ) {
      Brain.Screen.setPenColor( vex::color::black );
      Brain.Screen.drawRectangle( screen_origin_x, screen_origin_y, screen_width, screen_height, vex::color::black );
    }
    
    for(int i=0;i<v.objectCount;i++)
      drawObject( v.objects[i], c );
}

bool turning = false;

#define TARGET  150

void eventButtonY() {
  while(1) {
    // get latest objects
    int numberObjects = Vision6.takeSnapshot(Vision6__SIG_1);

    if( numberObjects > 0 ) {
      // make a copy
      vex::vision::object obj = Vision6.objects[0];

      if( obj.centerY != 0 && obj.width > 20 && obj.height > 20 ) {
        int error = obj.centerY - TARGET;

        // simple P control
        int drive = error;
        if( drive > 50 ) drive = 50;
        if( drive < -50 ) drive = -50;

        // object is found and centered
        if( obj.centerY > (TARGET-15) && obj.centerY < (TARGET+15) ) {
          Drivetrain.turnToRotation(0, degrees);
        }
        else {
          Drivetrain.turnToRotation(drive, degrees);
        }
      } 
    }
    else {
      // look for object
      Drivetrain.turnToRotation(50, degrees);
    }

    vex::this_thread::sleep_for(50);
  }
}

int main() {        
    // Draw an area representing the vision sensor field of view
    Brain.Screen.clearScreen( vex::color::black );
    Brain.Screen.setPenColor( vex::color::green );
    Brain.Screen.drawRectangle( screen_origin_x-1, screen_origin_y-1, screen_width+2, screen_height+2 );

    Controller1.ButtonY.pressed( eventButtonY );

    while(1) {
      // request any objects with signature 1
      int numberObjects = Vision6.takeSnapshot(Vision6__SIG_1);
      
      Brain.Screen.setPenColor( vex::color::white );
      Brain.Screen.setFont( mono20 );
      Brain.Screen.setCursor( 2, 2 );
      Brain.Screen.print( "Sig 1 %2d", (int)numberObjects );
      Brain.Screen.setCursor( 3, 2 );
      Brain.Screen.print( "C %4d", Vision6.objects[0].centerY  );

      // draw any objects found
      drawObjects( Vision6, vex::color::blue, true );

      // run 10 times/second
      this_thread::sleep_for(100);      
    }   
}