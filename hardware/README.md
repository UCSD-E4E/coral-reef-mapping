### Electronic Hardware:
Most of the hardware can be understood from the PCB files and the BOM. Some notes: 
- In choosing what decoupling capacitors to put in the design, we just followed datasheets directly. Don't forget to put them in - Rob and I spent two days straight trying to figure out why a multilexed 7-segment LED driver couldn't light up more than 2-3 segments at a time, and the issue was that we were missing a capacitor from Vcc to GND. Perhaps a capacitor should be added directly by the battery. 
- The charging circuitry was taken from [this website](http://blog.zakkemble.co.uk/a-lithium-battery-charger-with-load-sharing/). If you decide to create a super-minimalist system, you could probably do without it by not powering any LEDs during charging (thus almost no load). However, it would be nice to power LEDs while charging to show charge status. 
- Also about the charging circuitry: I chose the PMOS mostly because of its super low R_ds (resistance from drain to source while on). I chose the diode because of its low leakage current plus low forward voltage drop. More on the charging circuitry down at the bottom. 
- Be super scrutinous and thorough when looking at datasheets. Not doing this can lead to big annoying problems, especially with the cost and delay of ordering hardware. For example, Rob and I originally ordered common-anode 7-segment displays but common cathode 7-segment LED drivers. 
- LED Drivers: These are important and easy to screw up. One big decision to make is if you want to multiplex your 7-segment displays (click [here](https://www.embeddedadventures.com/Tutorials/tutorials_detail/113) to learn more about that if you aren't familiar). The advantage of this is that it eliminates a lot of wires, making PCB design easier, and making the PCB itself simpler and easier to solder. The downside is that only one 7-segment can be powered at a time, so if you're powering four 7-segment displays from the same multiplexed driver, they'll be at just a quarter of their maximum brightness. Note that it really isn't much work to write to individual segments instead of writing individual digits - what I mean by this is multiplexed LED segments don't provide much of an advantage from a software perspective, so don't really take that into consideration. Another thing to consider - the current LED driver is designed to put 
- Rob and I didn't get the chance to test our product in the ocean, where it would be used. We had multiplexed displays that were plenty visible under a foot of sink water, but obviously conditions will be different in the ocean where this will be used. So basically, the way to decide whether or not to multiplex the LEDs will be to actually test the multiplexed setup in the ocean. If it's bright enough, then great, if it isn't bright enough, then driving segments individually might be best. It gets more nuanced though - for example, Mouser has a [super bright 0.8 inch 7-segment display](https://www.mouser.com/ProductDetail/Kingbright/SA08-11SYKWA?qs=FRBiz4Wv1YOL2F%2FlHTLVYw%3D%3D) that seems to be identical to what we currently have, just common-anode instead of common-cathode. I don't remember seeing any 7-segment common-anode LED drivers, so the only way to use this would be to drive individual segments (perhaps search again for 7-segment common-cathode multiplexer drivers). This 7-segment display being so bright in a way defeats the purpose of doing individual segment driving. Altneratively, Newark Electronics has a [common-cathode version](https://www.newark.com/kingbright/sc08-11sekwa/display-0-8-cmn-cathode-orange/dp/83T3153) of the super bright 0.8 inch 7-segment, but it's only available from their UK stock, so although we could multiplex it with our current drivers, shipping it will be expensive and take a long time. Similar considerations must be taken into account for the smaller (0.56 inch) 7-segment display. Mouser actually has a [super bright common cathode 0.56 inch 7-segment display](https://www.mouser.com/datasheet/2/216/SC56-11SYKWA-245798.pdf) (and [here](https://www.mouser.com/ProductDetail/Kingbright/SC56-21SYKWA?qs=sGAEpiMZZMvkC18yXH9iIr%252bjuzoF1SlxA2zhJkFBqVo%3d)), so either could be used for multiplexing or individual driving. Both of those are single LEDs instead of three put together (what we current use) which is a very minor pain but no big deal. Newark has [one](https://www.newark.com/kingbright/bc56-11sykwa/display-led-0-56-yellow-common/dp/96W6817) with all three put together, but it's the same deal with UK stock. In general, I've found that KingBright has bright and well documented displays ([Mouser](https://www.mouser.com/Kingbright/Optoelectronics/Displays/LED-Displays-Accessories/_/N-6j73b?P=1z0ystyZ1z0yt3tZ1z0zl4cZ1z0wul7Z1z0z63x), [Newark](https://www.newark.com/w/c/optoelectronics-displays/displays/led-displays/7-segment-led-displays/prl/results?led-color=orange|yellow). I pretty much only looked into their through hole parts since Mouser's SMD parts all seem to be pretty small, and since all of Newark's parts require UK shipping, but we decide to ship from the UK or get smaller segments, then that's worth looking into. One last thing while we're talking about 7-segment display brightness - if we have some 7-segment that's more than bright enough, consider PWMing it to bring down amperage. This is important becuase not all (perhaps few) LED drivers have programmable current. 
- LED 7-segment height - yet another thing we spent a while looking thinking about. Bigger 7-segment displays are nice but can be difficult to fit onto the PCB, and aren't always as available in as many options. We started out by using ones that were an inch tall, but these require 4.2V (each segment has two LEDs in series), which is tough because only a fully charged li-ion battery will give 4.2V, and once LED forward voltage falls, current and thus brightness fall fast. 0.8 inches is a good height for the main display because the 0.8 inch displays require just ~2.2 volts, and because we can fit 4 of these displays across a 100 mm PCB. 0.56 is a good size for the secondary display because idk why not... actually though, it fits nice and is a standard size, meaning there's a lot of options (such as the super bright ones). 
- More about LED drivers: Note that most of the power in our system goes is being used by LED lighting/displays. This is going into both powering the LEDs themselves (providing light) and into the current limiting resistors (wasting power). So basically, a lot of the power being drawn from our battery is going into wasting power/generating heat (note that for the individual LEDs, the 3.3V stepdown is essentially just a current limiting resistor - the voltage drop goes into heat). Some LED drivers (multiplexed and not) work by just providing a switch for each LED (like [this](https://www.mouser.com/ProductDetail/Texas-Instruments/TPIC2810DR?qs=sGAEpiMZZMsE420DPIasPsdcJrrA9GC0BswO9DibV04%3d)), while some actually act as a constant current source, often programmable via I2C or an external resistor (like [this](https://www.mouser.com/ProductDetail/ISSI/IS31FL3236A-TQLS4-TR?qs=sGAEpiMZZMsE420DPIasPiM9oR8qGawYXca3T2WBryCYSmWSOlSEXw%3d%3d)). For the second type, although it isn't obvious exactly how they provide constant current, the _worst case_ scenario in terms of power usage is that it acts just a variable resistor for current limiting. Perhaps it provides the current with a switching regulator (much less power wasted as heat), we don't know. So my point is that LED drivers that provide constant current can be advantageous. Under the same logic, if you use one, consider powering it with battery voltage instead of the 3.3V regulator that the sensors and microcontroller feed off of because this could reduce power wasted by current limiting resistors/the 3.3V regulator. Of course, it might not be that simple (for example you might not want to connect it straight up to the battery), but it's worth testing out. Let me or Eric know if this doesn't make sense. 
- For Rob and I, soldering was a big issue. Soldering most SMD parts is really hard (SOICs aren't too bad). Rob and I spent a lot of time trying to solder certain parts, often to no success. As a result, most parts in the current BOM/PCB are through-hole. This isn't necessarily bad (our board doesn't need to do anything super difficult or high-frequency) but they do take up a lot of space. In creating a smaller PCB, going for more SMD parts might be an advantage. It seems like there is good access to reflow ovens near here - there's one in CalIt2 and one in the Structural Engineering building, probably some more that I don't know about (I don't go here). Rob and I tried to use one for soldering parts but didn't have enough time or previous experience to be successful. If you're willing to learn to use the reflow oven and have good access to it through the year, you could consider using a wider range of parts. In general, ask Eric for advice/general consideration about soldering stuff - it's one of many things he's very good at and could teach you about. Also, if you aren't familiar with soldering XYZ, [here's](https://octopart.com/blog/archives/2017/03/octopart-guide-ic-packages) a pretty good document about different types of packages. 
- Speaking of soldering, the [current magnetometer](https://www.mouser.com/ProductDetail/STMicroelectronics/LIS3MDLTR?qs=hnsWAVXnr6EbLE48dGN9Pg%3d%3d) is a nightmare. It has this LGA package that's super hard to solder, even with a reflow oven + microscope. Also hard to debug the soldering because you can't see the pads too well. Rob managed to solder it with the heatgun a couple times, but it was hard and didn't work a ton. Also it has 12 pins, not a big deal, but more than we need. I searched the Mouser magnetometer section fairly thoroughly and think that we should pick one of [these](https://www.mouser.com/Infineon/Sensors/Magnetic-Sensors/Board-Mount-Hall-Effect-Magnetic-Sensors/_/N-6g7qo?P=1z0z5kkZ1y929arZ1z0z7ptZ1z0zl9uZ1y929asZ1yzncuaZ1yzmnh9&Rl=6g7qoZgjdh8pZ1z0vxlvZ1y9ictkSGT&Ns=Operating+Supply+Current%7c1&FS=True) - they seem to be the only I2C magnetometers that measure field strength in three axes that don't have an LGA (or worse) package. Unforunately Mouser doesn't let you filter by I2C ability, but I'm pretty sure these are the ones we should be checking out. 
- The sensors, micro, and potentially LEDs will run off voltage coming from a voltage regulator. We originally used a 3.3V regulator, but it'll probably be better to use a 3.0V regulator. 3.0V is at the bottom of the li-ion's range, so we probably don't want it to get down to there anyways, but by regulating down to 3.0V instead of 3.3V we'll get just a tad more operation out of the battery (it wouldn't make sense to feed a >3.3V battery into a 3.3V regulator).  
- I2C - I2C (Inter IC) is a means of communicating between different ICs. Specifically, it allows one to communicate between muptiple devices with just two wires. We use it in this project to get data to the micro from the sensors, and to get data from the micro to the LED drivers. The web has a lot about I2C so I'm not going to talk about it much here, but know that it's super important - if you're looking for any part that needs to produce and/or receive information, make sure it can run I2C. Note that this is not the same as SPI or other means of serial communication (although they are similar, and often a device that can do those can do I2C / vice-versa). Finding I2C devices isn't always easy since some electronics parts websites (such as Mouser) don't let you filter based on whether or not a device can do it. On a site like Mouser you can try typing I2C into the "search withing results" section, but note that that won't include all the devices that have I2C ([this](https://www.mouser.com/Sensors/Magnetic-Sensors/Board-Mount-Hall-Effect-Magnetic-Sensors/_/N-6g7qo?Keyword=I2C) gets some of the I2C magnetometers but not all). 
- Single Resistors = 
- Some info on LEDs - every LED you buy will report brightness in either "lumens" (lm) or "millicandelas" (mcd). Lumens is the unit of luminous flux - the total power of light that one will perceive to be viewing when looking at that LED. Note that this is differenet from the radiant flux, which is the measure of the total amount of light energy being emitted by the LED, because the (human) eye reacts differently to different wavelengths of light - X lumens of red light will appear brighter than X lumens of purple light. This is due to the different types of light sensors that compose the eye (google for more info). In this sense, luminuous flux can be thought of as the total of amount of light energy produced by the LED multiplied by a scaling factor indicative of how sensitive the eye is to light of that wavelength/color. Read more [here](https://en.wikipedia.org/wiki/Luminous_flux). Candelas is the unit of luminuous intensity - the amount of energy/light intensity per unit two-dimensional angle one will perceive to be viewing when looking at that LED. If this doesn't make sense, think about it like this - imagine we has an LED emitting light in some direction. Now imagine that we take an invisible cone of angle theta and place its tip exactly where the light is coming out of the LED. A human will percieve a certain power of light to be coming through that cone (again, this will depend on the wavelenght). As theta increases (decreases), the perceived power of light will increase (decrease), no? Roughly speaking, the ratio of this perceived power of light to two-dimensional theta is what luminuous intensity is. Read more [here](https://en.wikipedia.org/wiki/Luminous_intensity). (Also sorry for being so vague about "two-dimensional angles", read more [here](https://en.wikipedia.org/wiki/Steradian)). Every LED emits light at a different "viewing angle" - usually defined to mean double the angle between the two vectors at which light intensity is at 1) its peak value and 2) half the peak value (read [here](http://www.directsignwholesale.com/blog/2015/what-led-viewing-angle)). So basically, some LEDs emit light in a narrow beam, while some emit light in a really broad beam (the broadest possible beam would be emitting light equally in all directions). In general, narrow-beam LEDs will have higher luminuous intensities and lower luminuous fluxes, so datasheets will report luminuous intensity. Similarly, wide-beam LEDs will have lower luminuous intensities and high luminuous fluxes, so datasheets will report luminuous flux. The datasheets only report one number :(, so they report the one that makes the LED look better. You can convert between luminuous flux and intensity (lumens and candelas) [here](https://www.rapidtables.com/calc/light/candela-to-lumen-calculator.html).
- The above information is somewhat important in this project because it uses a lot of LEDs in the LED ring. Viewing angle is important because it is not obvious what viewing angle will make viewing easiest for the divers to see the board. A large viewing angle could perhaps help them see it from non-direct angles, but if a diver tries to view the module from an indirect angle, they won't be able to really tell where in the ring the lit LED is. This will make the LED ring will be somewhat pointless at that angle, so there's no need to find LEDs with large enough viewing angles to accomodate this. Overall, we'll have to do some experimentation here to find the ideal viewing angle, perhaps underwater, perhaps not. Another thing to think about with the brightness is power usage. At first we weren't looking for super bright LEDs becuase we figured that we didn't need super bright ones. However, that isn't the best way to think about it; when thinking about LED brightness take these things into consideration: 1) It might not hurt to have LEDs shining super bright. It all depends on how things actually look underwater. In general, brighter is better (if we're ignoring power usage, which we shouldn't), but if the LED ring LEDs are too bright they might obscure the numeric display, so we have to be careful about that. So the first thing that should happen is we should find whatever is the ideal brightness and angle of LED ring LEDs. Once we have that, we want to be able to produce that brightness with as little current as possible. This is where getting super-bright LEDs might come in handy. Usually when people think about super bright LEDs they're talking about using them to get super bright light. However, we could use them to get a normal-level brightness because they will achieve that with very low current. The brightness that a "normal" LED might achieve at 20 mA, a super-bright LED might achieve at 5 mA - this could make battery life go way up. Note that super-bright LEDs might be more available in some viewing angles (for example, you'll find a lot more super-bright ones at 30 degrees than 70 degrees). So maybe, if you like the idea of getting super bright LEDs so we can get the desired brightness at a low current, then get LEDs of the wrong angle if they are brighter than ones of the right angle. Just when you're looking at datasheets, if you find an LED with super high brightness, make sure you check out what the forward current is - if it takes 100 mA to get the rated brightness, that probably isn't desirable. 
- How the charging circuitry works: the goal of the charging circuitry is to make it so that when the charger is connected, the path fron the battery to the rest of the circuit (sensors, microcontroller, LEDs, etc) is open (charge can't flow) and that when the charger is disconnected, that path is closed (charge can flow). This is done with a PMOS transistor. Real quick if you don't know a ton about transistors (in this case MOSFETs) - a PMOS is a three terminal device where when one terminal, the "gate", is given a high voltage, the other two terminals (source and drain) are unconnected, and when this gate is given a low voltage, the source and drain are connected. ([Here's](https://www.elprocus.com/mosfet-as-a-switch-circuit-diagram-free-circuits/) a bit more info on MOSFETs if you want).... to be finished later