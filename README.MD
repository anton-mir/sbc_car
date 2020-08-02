
#### How to switch data set?
The user can choose which data set to run module for: car without information about air, car AirC device or box AirC device. By default you get car without information about air, but you can add argument ```--airc-device box``` when you run sbc-car module for AirC box device or ```--airc-device car``` to use module for car with AirC device.

For car without information about air:
```
cd ~/src/GL-SMARTCITY/sbc-platform/build/src/sbc-car/bin && ./obdgpslogger
```
For car AirC device:
```
cd ~/src/GL-SMARTCITY/sbc-platform/build/src/sbc-car/bin && ./obdgpslogger --airc-device car
```
For box AirC device:

```
cd ~/src/GL-SMARTCITY/sbc-platform/build/src/sbc-car/bin && ./obdgpslogger --airc-device box
```
#
OBDII/GPS Logging Tool


What?

Your car has lots of interesting things it can tell you from the
on-board computer while it's running. obdgpslogger is a small tool
to grab data from an OBDII device and log it to an sqlite database.
If you enable it [on by default, and a large part of this project's
point], then your gps position is also logged to the same database.


What are the other requirements?

Install gpsd first if you want gps support.
The GUI component requires FLTK and fluid.


How do I build this?

mkdir build
cd build
cmake .. # or ccmake .. to edit options
make
make install


And how do I run it?

obdgui # GUI for launching and getting live feedback from other tools
obdgpslogger [-s serialport] [-d sqlite database] # Actual logger
obd2kml [-d sqlite database] [-o output file] # Convert to Google Earth

More specific information is availble in --help or man pages


Chunky Kibbles
chunky@icculus.org
