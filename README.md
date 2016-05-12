# ROS-Weather
Uses Weather API to display local weather through Arduino-based LEDs

**RUNNNING**

In order to run my program, first open weather.ino on the Arduino IDE. Make sure
that the Arduino IDE's settings match the actual Arduino specifications. Ensure 
that the LEDs are attached to serial port USB1, and that the baud rate is set to
115200. Make sure that Pololu is an included library for the Arduino. Compile 
the project, and send it to the Arduino. Afterwards, on the terminal, go into 
the "src" directory. Run the command "python weather.py", and then the program 
should run accordingly.
