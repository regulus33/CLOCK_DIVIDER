## Preprocessor directives
We need them to deal with the fact that we are copying files and renaming
them between 


`/include` and `arduino/main/include`

`MACROS` at least in the `#ifndef` statements are these big empty variable things. 

They are literally there just to prevent double includes...

Here's how we would do it if we wanted to not redefine the same thing over and over
AND we wanted different things to happen in diferent environments. **YOU CAN NEST:**

```cpp
#ifdef ARDUINO
    #ifndef ARDUINO_CLAWK_BUFFER_H
    #define ARDUINO_CLAWK_BUFFER_H

    // BUT SERIOUSLY DON'T DO THIS

    #endif // ARDUINO_CLAWK_BUFFER_H
#else
    #ifndef CLAWK_BUFFER_HPP
    #define CLAWK_BUFFER_HPP

    // BETTER TO JUST HAVE ONE MACRO FOR THIS KIND OF PREPROCESSOR DIRECTIVE

    #endif // CLAWK_BUFFER_HPP
#endif
```

## This project uses gtest

It expects to have on the project root a directory called `googletest`
You can just git pull gtest repo to googletest

## Format doc in clion

`command + option + L`

## Wrap around iteration

modulo always returns the 0 if left of operand is evenly divisible by right side otherwise it returns
the remainder 15 % 5 = 0 but 15 % 6 is 3. This allows us to create a boundary around any incrementally
bumped numbers. Because, every time you increment until you hit a multiple of 5, like 25 30 etc, you go
back to 0.
```
1 % 5 == 1
2 % 5 == 2
3 % 5 == 3
4 % 5 == 4
5 % 5 == 0
6 % 5 == 1
7 % 5 == 2
8 % 5 == 3
9 % 5 == 4
10 % 5 == 0
backwards
0 % 5 == 5
```
