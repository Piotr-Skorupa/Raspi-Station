# Raspi-Station
Home Weather Station

## Prepairing your raspberry pi 
### First you must download mostquitto protocol:
- sudo apt-get install libmosquitto-dev libmosquittopp-dev libssl-dev
### Now you must download paho.mqtt.c library which is need to bulid c++ version
### Prepare a correct location for files:
- mkdir ~/home/pi/git && cd ~/git
### Now fetch:
- git clone https://github.com/eclipse/paho.mqtt.c.git
- cd paho.mqtt.c
- cmake -DPAHO_BUILD_STATIC=TRUE -DPAHO_BUILD_SAMPLES=TRUE -DPAHO_WITH_SSL=TRUE
- make
- sudo make install
### Since this moment you will be able to build RaspiStation app.

## Build:
### To build this program, follow instructions:
- mkdir build
- cd build
- cmake ../
- make
### Now you can run program: 
./RaspiStation 






### Bibliography:
1. I used this repository to find correct way to getting data from my sensors: https://github.com/ControlEverythingCommunity