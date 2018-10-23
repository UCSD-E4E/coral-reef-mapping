### Code:
The code is organized as follows:
- All of our (programmable) devices are integrated along the I2C bus, so that is a central feature of all the code. 
- For each device, there's a .h file declaring functions and some constants, and then a .c function implementing all of them.
- The code isn't super pretty. Issues are discussed below. 
- I'm not a CS student so please pardon any other issues you see. Stuff might be implemented in sub-optimal ways (things more important than just the naming), so don't be afraid to change stuff if you're good at microcontroller programming. 

Things to note: 
- The function names aren't great; sorry about that. I'm a bit of a neat freak but never got around to organizing all the function and variable names to follow some nice rules. I would reccomend doing something like the following for naming functions: "device name in camelCase" + "\_" + "purpose of function in camelCase". I meant to do this but ran out of time. And of course, this is your project now and not mine so name your functions however you want.
- Depth sensor code - I don't think this code works, sorry about that. It's pretty close though, there's just some bug I didn't have time to catch because I can't test anything now that I'm not on campus. The depth sensor is interesting; 
