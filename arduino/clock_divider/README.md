# Fucking RULES!
1. Add setup() and testHardware() functions for EVERY class that represents a phyiscal component or a group of physical components. (we are too scared to try polymorphism on the NANO)
# Arduino with Platform IO

Platform io is allowing us to use clion to work on the arduino project.
Basically all you need to know is that the board configurations, frameworks, libraries etc. are all going to be specified within `platformio.ini`

Here is the current basic config for our nano

```.ini
[env:nanoatmega328]
platform = atmelavr
board = nanoatmega328
framework = arduino
```

## PlatformIO CLI commands

For each command, make sure you are in the same directory as this readme.

### Build and upload
`pio run -t upload`

### Log serial monitor from device
`pio device monitor`

### Run tests
`pio test`

### Weird Bitwise stuff I learned
```cpp
// This was in a function that ran over and over
static uint8_t oldAB = 0;
oldAB = oldAB << 2;
```

n this code snippet, `static uint8_t oldAB = 0;` declares a static variable named oldAB of type `uint8_t` 
(an unsigned 8-bit integer) and initializes it to 0. Being a static variable, oldAB will retain its value between 
function calls. It cannot be overwritten so even though it seems to be set over and over again.

The line oldAB <<= 2; is a bitwise left shift operation that shifts the value of oldAB two bits to the left, filling 
the two least significant bits with zeros.

#### Here's how it works:

If `oldAB` was `00000000` (which it is initially), after `oldAB <<= 2;`, it would still be `00000000.`

If `oldAB` was `00000010` (or `2` in decimal), after `oldAB <<= 2;`, it would become `00001000` (or 8 in decimal).

If `oldAB` was `10000000` (or `128` in decimal), after `oldAB <<= 2;`, the two most significant bits would be lost, 
and it would become `00000000`.

If oldAB was `11000011` (or `195` in decimal), after `oldAB <<= 2;`, it would become `00001100` (or `12` in decimal), 
losing the two most significant bits.

### Logical bitwise OR

```cpp
something |= something_else;
```
The numbers mash into each-other and 1 always wins.
```
1010 | 0101 becomes 1111
1001 | 0000 becomes 1001
1111 | 0000 becomes 1111
0000 | 0000 becomes 0000
```

### STATIC RAM vs. FLASHMEM
**SRAM** (Static Random Access Memory)
What it is: SRAM is volatile memory, meaning it loses its contents when power is lost. It's used for variables that are read and written during program execution.

Speed: Generally faster than flash memory for read and write operations.

Size: Typically much smaller than flash memory. For example, an Arduino Uno has 2KB of SRAM.

Analogue in a traditional computer: SRAM on a microcontroller is somewhat similar to the RAM (Random Access Memory) on a traditional computer, which is also volatile and used for storing data that needs to be quickly accessed during program execution.

**Flash Memory**
What it is: Flash memory is non-volatile, meaning it retains its contents even when the power is lost. It's used for storing the program code and can also be used for long-term storage of data.

Speed: Slower than SRAM, especially for write and erase operations. Read operations are generally fast enough for most applications.

Size: Typically much larger than SRAM. An Arduino Uno has 32KB of flash memory.

Analogue in a traditional computer: Flash memory on a microcontroller is somewhat similar to the hard drive or SSD on a traditional computer, where the operating system and programs are stored. The key difference is that hard drives and SSDs on a computer are much larger and can be read and written to more flexibly than the flash memory on a microcontroller.

In summary, SRAM is like the "working memory" that is fast but volatile and limited in size, while flash memory is more like "storage" that is slower but non-volatile and more abundant.