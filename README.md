There are now 2 versions of this project:

The older, v1 is a much simpiler one relies on an external device to display time, along with only 1 light sensor to check if you are ready of not. It is also much less accurate.
The newer, v2 of the project uses 2 light sensors, an optional joystick module to adjust an rgb light, aswell as reset and start inspection. It uses an lcd display to print out your time, along with the "elapsedMillis" library to be much, much more accurate with time. Also, accidental resets are quite hard.

Both project were coded to run on an arduino uno. It only needs 5V of power.

How to use:
In any way conveievable, upload your code to your microcontroller. Press the non reset button, and then place your fingers/hands against the light sensor(s) (https://solarbotics.com/product/17092/). Then let go and it should start. Then to stop place finger against sensor.
