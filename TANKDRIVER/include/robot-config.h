using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor Motor3;
extern controller Controller1;
extern motor Left;
extern motor Right;
extern motor_group MotorGroup10;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );