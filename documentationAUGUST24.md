# Coral Reef Depth/Heading Sensor, Documentation 8-24-18


#### Dan Sturm, 609-712-7596, dsturm@princeton.edu, dansturm17@gmail.com - try them all. 
#### Robert Barlow, 802-595-9137, robert.barlow@stuents.olin.edu
#### Please don’t hesitate to reach out. 


Hey there! Thanks for taking up the “Reef Pin” project. Rob and I put a lot of work into this summer and care a lot about it, so we appreciate the work you’re going to put into it. This google doc is our attempt to document all the work we’ve done this summer so that you can pick up easily where we left off. 

I’ll start by saying that you should feel free to reach out to either of us at any time when working on this. As much documentation as we do or do not provide, there’s going to be a lot of intuition and experience that we leave out - it’s hard to condense two months of work into one document. Even if you don’t have any specific questions just hit us up. I (Dan) probably know a bit more about the code while Rob knows more about the mechanical stuff (aka waterproofing and encasing). 



### Potting

Potting is quite simple. 

- Thread the bolt through the corner of the mold, and hot glue the surrounding area to reseal the mold. 
- Spray a coating layer of mold release onto the mold and exposed threads of the bolt-
- Screw on the nut
- Set the PCB in the mold, making sure that the QI receiver is as close as possible to the bottom of the mold without touching it (I like to use 3 dots of hot glue on the bottom). 
- Mix epoxy. Be sure to stir enough! 10 minutes at a minimum. Having the epoxy not cure is the worst thing, don’t let it happen to you.
- Pour epoxy into the mold around the pcb. Be careful once the epoxy fills above the pcb- don’t pour too much. Be sure to not cover the pressure sensor.
- Stop filling when everything is covered except for the pressure sensor & displays. The pressure sensor is the most important part- if you get epoxy on the top you’re screwed. Be careful.
- Let cure for ~12 hours

### Finishing

I haven’t quite perfected finishing yet, but here are some tips:

- Normal spray-paint looks bad
- The epoxy can be sanded or dremeled if one is really careful. 
- If you scratch the 7 segment displays, the surface blueish can be sanded away to reveal a white plastic front
- LEDs can be sanded down if the PCB isn’t level





### To Do (Suggestions):
- Replace LED 7 Segment drivers with shift registers like the ones on the LED ring
- Button debouncing with a simple RC circuit - add this. Very easy 
- Actually study in detail how all the internal clocks/registers and interrupts on the MSP work 
- Static current leakage in normal led driver
- Add in LVC (Low voltage cutoff) circuit
- Fix charging circuitry
- Rubberized coating/surface finish. Try Plasti-Dip coating?
- Include some sort of data recording & reporting system


### Electronic Hardware:
Most of the hardware can be understood from the PCB files and the BOM. Some notes: 
- In choosing what decoupling capacitors to put in the design, we just followed datasheets directly. Don't forget to put them in - Rob and I spent two days straight trying to figure out why a multilexed 7-segment LED driver couldn't light up more than 2-3 segments at a time, and the issue was that we were missing a capacitor from Vcc to GND. Perhaps a capacitor should be added directly by the battery. 
- The charging circuitry was taken from [this website](http://blog.zakkemble.co.uk/a-lithium-battery-charger-with-load-sharing/). If you decide to create a super-minimalist system, you could probably do without it by not powering any LEDs during charging (thus almost no load). However, it would be nice to power LEDs while charging to show charge status. 
- Also about the charging circuitry: I chose the PMOS mostly because of its super low <R><\ds> (resistance from drain to source while on). I chose the diode because of its low leakage current plus low forward voltage drop. 
- Be super scrutinous and thorough when looking at datasheets. Not doing this can lead to big annoying problems, especially with the cost and delay of ordering hardware. For example, Rob and I originally ordered common-anode 7-segment displays but common cathode 7-segment LED drivers. 
- LED Drivers: These are important and easy to screw up. One big decision to make is if you want to multiplex your 7-segment displays (click [here](https://www.embeddedadventures.com/Tutorials/tutorials_detail/113) to learn more about that if you aren't familiar). The advantage of this is that it eliminates a lot of wires, making PCB design easier, and making the PCB itself simpler and easier to solder. The downside is that only one 7-segment can be powered at a time, so if you're powering four 7-segment displays from the same multiplexed driver, they'll be at just a quarter of their maximum brightness. Note that it really isn't much work to write to individual segments instead of writing individual digits - what I mean by this is multiplexed LED segments don't provide much of an advantage from a software perspective, so don't really take that into consideration. 
- More about LED drivers: Note that most of the power in our system goes is being used by LED lighting/displays. This is going into both powering the LEDs themselves (providing light) and into the current limiting resistors (wasting power). So basically, a lot of the power being drawn from our battery is going into wasting power/generating heat (note that for the LEDs, the 3.3V stepdown is essentially just a current limiting resistor - the voltage drop goes into heat). Some LED drivers (multiplexed and not) work by just providing a switch for each LED (like [this](https://www.mouser.com/ProductDetail/Texas-Instruments/TPIC2810DR?qs=sGAEpiMZZMsE420DPIasPsdcJrrA9GC0BswO9DibV04%3d)), while some actually act as a constant current source, often programmable via I2C or an external resistor (like [this](https://www.mouser.com/ProductDetail/ISSI/IS31FL3236A-TQLS4-TR?qs=sGAEpiMZZMsE420DPIasPiM9oR8qGawYXca3T2WBryCYSmWSOlSEXw%3d%3d)). For the second type, although it isn't obvious exactly how they provide constant current, the _worst case_ scenario in terms of power usage is that it acts just a variable resistor for current limiting. Perhaps it provides the current with a switching regulator (much less power wasted as heat), we don't know. So my point is that LED drivers that provide constant current can be advantageous. Under the same logic, if you use one, consider powering it with battery voltage instead of the 3.3V regulator that the sensors and microcontroller feed off of because this could reduce power wasted by current limiting resistors/the 3.3V regulator. Of course, it might not be that simple (for example you might not want to connect it straight up to the battery), but it's worth testing out. Let me or Eric know if this doesn't make sense. 
- For Rob and I, soldering was a big issue. Soldering most SMD parts is really hard (SOICs aren't too bad). Rob and I spent a lot of time trying to solder certain parts, often to no success. As a result, most parts in the current BOM/PCB are through-hole. This isn't necessarily bad (our board doesn't need to do anything super difficult or high-frequency) but they do take up a lot of space. In creating a smaller PCB, going for more SMD parts might be an advantage. It seems like there is good access to reflow ovens near here - there's one in CalIt2 and one in the Structural Engineering building, probably some more that I don't know about (I don't go here). Rob and I tried to use one for soldering parts but didn't have enough time or previous experience to be successful. If you're willing to learn to use the reflow oven and have good access to it through the year, you could consider using a wider range of parts. In general, ask Eric for advice/general consideration about soldering stuff - it's one of many things he's very good at and could teach you about. Also, if you aren't familiar with soldering XYZ, [here's](https://octopart.com/blog/archives/2017/03/octopart-guide-ic-packages) a pretty good document about different types of packages. 
- Single Resistors = 
