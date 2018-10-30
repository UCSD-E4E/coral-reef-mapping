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
##### This will hopefully provide some direction to whoever works on this project next. Some of these suggestions are more important than others
- Test all the code and begin to integrate it. This is most logical starting point for someone taking on this project, because 1) it will offer familiarity with where the project is at and what the current system can do, and 2) it will make clear what tasks need to be taken up in the future. 
	- So, not urgent but the logical starting place 
- Revise the hardware and make a new PCB. Once whoever takes up this project gains familiarity with the code and modifies it in whatever way is needed, this is probably the next logical step. Elements of this include the following. More details can be found in the PCB and hardware sections.  
	1) Maybe replace LED 7 Segment drivers with shift registers like the ones on the LED ring (see hardware section). This might be helpful, might not be. Not urgent
	2) Button debouncing with a simple RC circuit - add this (see hardware section). There's a good chance this isn't needed; also a good chance that we'll eliminate buttons if we change the overall power setup of the system. So play it by ear
	3) Static current leakage in normal (non-multiplexed) led driver (see hardware section)
	4) This sucks, but whether or not it really needs to be addressed depends again on how the overall power setup ends up, so play it by ear
	5) Add in LVC (Low voltage cutoff) circuit. Not urgent, but important
	6) Test charging circuitry. Not urgent but important
- Rubberized coating/surface finish. Try Plasti-Dip coating?
- Include some sort of data recording & reporting system
- Make decisions about the system overview 


### Electronic Hardware:
##### Notes about the hardware can be found in the hardware section. 


### About the Code
##### Most of the code should make sense. It isn't perfect but what's there works for the most part. In the section on code I have some stuff about everything that's going on. 


