#!/bin/bash

###############################################################################
#Written by Luke Harrison.
 
# The MIT License (MIT)

# Copyright (c) 2017

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Make sure that we are in the correct directory
cd /home/pi

echo ""
echo "Starting mod installation..............................."
echo ""

echo ""
echo "Updating packages required for the mod."
echo ""

# Make sure that we have all the latest refs to updates
sudo apt-get update

# Get the required libs for the python script to function
sudo apt-get -y install python-pip
sudo apt-get -y install python3-dev python3-rpi.gpio

echo ""
echo "Creating the python script that drives the mod."
echo ""


# Check for a python script and erase if one exists
if [ -f shutpi.py ]; then
    sudo rm shutpi.py
fi

cat >shutpi.py <<'END_SCRIPT'
# !/bin/python

# Simple script for shutting down the Raspberry Pi using a line from the BX

# by Luke Harrison

import RPi.GPIO as GPIO

import threading

import time

import os

# Setup the pin with internal pullups enabled and pin in reading mode.

GPIO.setmode(GPIO.BCM)

GPIO.setup(4, GPIO.IN, pull_up_down=GPIO.PUD_DOWN) #Pull down instead of relying in the weak pullup from the motherboard

# Function to double check edge value after 1.6s
def DoubleCheck():
    if GPIO.input(4):
        os.system("sudo shutdown -h now")

# Initial function on edge.
def Shutdown(channel):
    t = threading.Timer(1.6, DoubleCheck)
    t.start()
    #os.system("sudo shutdown -h now")


# Allow time for the power to settle after initial boot.

time.sleep(10)

# Add our function to execute when the button pressed event happens

GPIO.add_event_detect(4, GPIO.RISING, callback=Shutdown, bouncetime=1750)


# Now wait!

while 1:
    time.sleep(1)
END_SCRIPT

echo""
echo "Providing execcution rights to the script."
echo""

# Give the script execution rights
sudo chmod 755 shutpi.py

echo ""
echo "Adding the script to the boot sequence."
echo ""

# Add it to the rc.local so that it will start on boot

if grep -Fq "/home/pi/shutpi.py" /etc/rc.local
then
    # Nothing to do
    :
else
    # Not there so let's add it
    sudo sed -i -e '$i \sudo python3 /home/pi/shutpi.py &\n' /etc/rc.local
fi

echo ""
echo "Mod complete."
echo ""
echo "Please reboot your pi using 'sudo reboot' for the mod to become active."
echo ""
echo "Enjoy."
echo ""
