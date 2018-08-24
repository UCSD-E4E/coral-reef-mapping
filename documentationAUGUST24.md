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
- In choosing what capacitors to put in the design, we just followed datasheets directly. Perhaps a capacitor could be added directly by the battery? 
- The charging circuitry was gained [this website](http://blog.zakkemble.co.uk/a-lithium-battery-charger-with-load-sharing/). If you decide to create a super-minimalist system, you could probably do without it by not powering any LEDs during charging (thus almost no load). However, it would be nice to power LEDs while charging to show charge status.   
