# Raspi-Station
Home Weather Station

## Prepairing your raspberry pi
### First you must update your raspberry:
```bash
sudo apt-get update
sudo apt-get upgrade
```
### Now you must download mostquitto protocol:
```bash
sudo apt-get install libmosquitto-dev libmosquittopp-dev libssl-dev
```
### Now you must download paho.mqtt.c library which is need to bulid c++ version
### Prepare a correct location for files:
```bash
mkdir ~/home/pi/git && cd ~/git
```
### Now fetch:
```bash
git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
cmake -DPAHO_BUILD_STATIC=TRUE -DPAHO_BUILD_SAMPLES=TRUE -DPAHO_WITH_SSL=TRUE
make
sudo make install
```
### Since this moment you will be able to build RaspiStation app.

## Build and run:
### To build this program, follow instructions:
```bash
mkdir build
cd build
cmake ../
make
```
### Now you can run program: 
```bash
./RaspiStation 
```





### Bibliography:
1. I used this repository to find a correct way of getting the data from my sensors: https://github.com/ControlEverythingCommunity
2. Base64 source code from: 
https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp
