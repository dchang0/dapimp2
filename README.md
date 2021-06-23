# dapimp2
Mikey Sklar's DA PIMP 2 reworked into Revision 2.0 to use an OMRON A8L-21-12N2 rocker switch instead of the discontinued Schurter rocker switch.

DANGER: LETHAL SHOCK HAZARD
DO NOT BUILD OR OPERATE THIS CIRCUIT UNLESS YOU TAKE FULL RESPONSIBILITY FOR ITS USE OR MISUSE

IMPORTANT:

This schematic and PCB has not yet been tested in real life. That is to say, I have not actually ordered this PCB and assembled it into a working DA PIMP 2 Rev. 2.0.
DO NOT order the PCBs using the included gerber files unless you have inspected the schematic and the gerber files and decided that you are confident the PCB will work.

Both the schematic and the PCB pass the design check rules, but that doesn't mean it will work.

If you do find that it works or that it doesn't, please open an Issue in this GitHub project, and I will attempt to fix the issue with the PCB. I do not, however, provide any support for the DA PIMP 2, and neither does Mikey. If you need help assembling it, then I suggest you ask for assistance from others on the original Instructables page.

Note that I redrew the schematic and re-created the PCB layout entirely free of charge, so please do not yell at me or complain if the design has an error. I'm doing this only to contribute to the Open Hardware community.

ASSEMBLY INSTRUCTIONS:

Mikey wrote these instructions long ago. The instructions for this Rev. 2.0 PCB are roughly the same. The main differences are the location of the ALPS slide switch and the substitution of an OMRON rocker switch for the original, discontinued Schurter rocker switch.

https://www.instructables.com/DP2-Da-Pimp-2-Assembly-Instructions/

BILL OF MATERIALS:

Included is an Excel spreadsheet with substitute parts for the ones on Mikey's original BoM. I have not ordered this newer BoM in years, so the parts may or may not be current and may or may not need substitutions. The prices are almost certainly waaaaaay off.

IMPORTANT: 

CONN1 is a 5.5mm x 2.1mm DC barrel jack. You are supposed to assemble CONN1 CABLE: a 5.5mm x 2.1mm barrel plug Y-cable to red and black mini alligator clips. However, neither Mouser nor Digikey carries the two-conductor red/black wire needed to assemble the Y-cable. I thus provided the part numbers for the parts I could find but left the part number blank for the 0.5m of two-conductor red/black wire.

I also provided CONN1 CABLE (ALT), which is/was an ebay listing that sells the cables pre-assembled. I have no affiliation with the ebay seller. The listing might not even exist any more, but there are tons of sellers on ebay and Amazon that sell the same thing.

SCHEMATIC: 

Also included is a redrawn schematic. It should be electrically identical to Mikey's original DA PIMP 2 schematic except for the diode, which Mikey got backwards. My schematic corrects the polarity.

GERBER FILES:

The gerber files for the PCB are included in a zip file, ready for you to use to order PCBs with.
The PCB size is 61mm W x 96mm H x 1.6mm D.

FIRMWARE:

Mikey's original firmware file is included. Again, I have not actually assembled this PCB in real life, so there is a chance it won't work. But it should work, since the microcontroller is the same and the wiring is the same. Double-check the schematic if you are not sure.

I am also including Mikey's C source code so that you can modify the firmware.

ONCE AGAIN:

DANGER: LETHAL SHOCK HAZARD
DO NOT BUILD OR OPERATE THIS CIRCUIT UNLESS YOU TAKE FULL RESPONSIBILITY FOR ITS USE OR MISUSE
