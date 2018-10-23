### Code:
The code is organized as follows:
- All of our (programmable) devices are integrated along the I2C bus, so that is a central feature of all the code. 
- For each device, there's a .h file declaring functions and some constants, and then a .c function implementing all of them.
- The code isn't super pretty. Issues are discussed below. 
- I'm not a CS student so please pardon any other issues you see. Stuff might be implemented in sub-optimal ways (things more important than just the naming), so don't be afraid to change stuff if you're good at microcontroller programming. 
