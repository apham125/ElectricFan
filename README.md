# Electric Fan

## Demo Link
https://drive.google.com/file/d/1Tj0V3OgtZw3m0Kds1e-zQ8zqHivNOcRi/view?usp=sharing

## Purpose 
The purpose of this project is to have a little machine that can tell you the temperature and keep you cool with a fan. The fan has varying speeds depending on the temperature and can be turned on and off. The fan is also able to move back and forth automatically or with a joystick the user controls. Sometimes when I use other fans, I want the fan to be pointing a certain direction but in order for it to face a certain way, I would either have to move the whole fan or turn on the auto move feature and stop it when it reaches the position I want. The fan I created is able to move its position easily with a joystick and even tells you the temperature and humidity of the room you are in.

## FUNCTIONALITY
To make my project, I taped a fan onto a servo motor. I connected the joystick to my project and made it so the y-axis of the joystick controls the servo back and forth. The servo has a range of 180 degrees. The servo motor is controlled by the joystick but there is a button that can make the servo turn back and forth automatically. To stop it moving automatically, just move the joystick and it will be back to normal.

The fan can be turned on and off with two buttons and the speed of the fan changes depending on what the temperature of the room is. If the temperature is over 30 degrees celsius then the fan will be on the fastest setting. If the temperature is between 26 degrees and 30 degrees celsius then the fan will be on medium speed. Anything below that will set the fan speed on its lowest setting. The automatic moving of the servo motor can only be triggered if the fan is on, however the joystick can be used to control the servo regardless of if the fan is on or off. There is a temperature and humidity sensor attached to my project that reads the room’s temperature in celsius. The readings are displayed on the lcd screen of my project and readings are measured every 4 seconds.
