# Keystroke32
STM32F103 based board to reuse (some) old laptop keyboards


Tested with keyboards:

In general, the keyboards need to have a flex cable with 1mm pitch connector and maximum of 27 active pins (26 pins if you want to use SCROLL LOCK led). If your keyboard has more pins than that, it's very likely that some of the pins are not connected. If those inactive pins are at the edge of the connector, you can simply (very carefully) cut the edge of the connector with scissors. The board has a 30-pin connector with 3 left-most pins disconnected. So if your keyboard matches that, no cutting is needed.

Some boards have the connector with pins facing up, some with pins facing down, so make sure you have the correct connector before you solder it on the board ;)
