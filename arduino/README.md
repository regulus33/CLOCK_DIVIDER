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
