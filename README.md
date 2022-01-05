# Keystroke32
STM32F103 based board to transform (some) old laptop keyboards into proper USB keyboards. If you like laptop keyboards in general or just miss your old laptop keyboard, this could be a fun project for you!


## TESTED WITH KEYBOARDS:

In general, the keyboards need to have a flex cable with 1mm pitch connector and maximum of 27 active pins (26 pins if you want to use SCROLL LOCK led). If your keyboard has more pins than that, it's very likely that some of the pins are not connected. If those inactive pins are at the edge of the connector, you can simply (very carefully) cut the edge of the connector with scissors. The board has a 30-pin connector with 3 left-most pins disconnected. So if your keyboard matches that, no cutting is needed.

Some boards have the connector with pins facing up, some with pins facing down, so make sure you have the correct connector before you solder it on the board ;)


## MAPPING:
To map the keys, there's a mapping mode in the sketch, just uncomment "#define MAPPING_MODE" at line 29. All it does is - it outputs every pushed key in the serial console in a arduino-compatible format. So just go through all buttons (I suggest going row by row) and once you're done, just copy & paste the output to the mappedPins variable in the sketch. After that, you can start adding functions to the keys - all relevant functions should be in the comment in the sketch. You can also use the predefined keyboards as an example.

## Possible issues:
- if some of the keys don't work, try to unplug the keyboard, clean the pins with isopropyl alcohol, and replug.
