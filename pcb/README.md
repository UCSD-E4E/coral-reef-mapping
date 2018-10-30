# PCB Work

### Note - In general, all PCB designs that get fabbed should be uploaded here. 

**8-24-18 -** 
The current PCB design (1.1) is close to functional. It is very similar to 1.0, but with different 7-segment displays, plus a couple different parts. It is 127 mm x 127 mm. This is problematic in that board prices go way down when the dimensions hit 100 mm x 100 mm. It is also problematic in that the magneometer's pads are super close together, so minimum trace spacing has to be 5 mm, which makes the board more expensive. Also, cost aside, soldering this magnetomer is a pain and hard to do right. 

The next step in the PCB domain is to create a new PCB (let's call it 2.0) that will be smaller and will have a different magnetometer. It will also have battery discharge protection circuitry, and probably some other changes. In order to make the small size feasible, we'll probably have to transistion to physically smaller parts. I think SMD parts are the answer here - we can find SMD resistors, capacitors, LEDs, LED drivers, and microcontroller. It seems to me like a lot of these parts come in a variety of sizes (for example, maybe there's 10+ standard sizes of SMD capacitors), so we probably just want to find whatever is the smallest size we think we can easily solder. Some of this info is reiterated in the hardware section if you want to read more. 
