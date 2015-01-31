# RSX_RoverArm
Code for controlling the rover's prototype arm.


Instructions for Rover_Arm_DefaultPositions:
 - Write a Python script that sends numbers 49 - 53 over the serial connection
 - 49 through 52 correspond to preset positions
 - 53 means manual control, so use the potentiometers (the knobs) to control the joints. 
 
Instructions for Rover_Arm_SerialControl
 - Plug in a joystick
 - Run the Arduino file
 - Run the python file
 
 - Each axis on the joystick controls a joint. For the controllers that look like traditional gamecube controllers, the axes are the degrees of
 freedom of the knobs (make sure the controller is set to analog, i.e. the red light is on). 
 - The buttons (1-4) are the default positions. 
 
 This file has more of the code in Python because it's easier than Arduino. 
 