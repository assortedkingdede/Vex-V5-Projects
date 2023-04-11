using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern controller Controller1;
extern signature Vision6__SIG_1;
extern signature Vision6__SIG_2;
extern signature Vision6__SIG_3;
extern signature Vision6__SIG_4;
extern signature Vision6__SIG_5;
extern signature Vision6__SIG_6;
extern signature Vision6__SIG_7;
extern vision Vision6;
extern smartdrive Drivetrain;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );