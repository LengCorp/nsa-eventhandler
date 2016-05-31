# nsa_eventhandler
The eventhandler project for the NSA UNO. Check out our [WIKI](https://github.com/LengCorp/nsa_eventhandler/wiki)!

## What it is
This project is part of the larger NSA UNO project, which is an alarm system for the home. 
This is the alarm unit, which through Radio Frequency, sends oregon protocol messages to communicate with an 
Telldus Tellstick Duo.

## How it works
* When the unit is on, and working properly, it will receive data from the nsa-arduino system using the Telldus-core API.
* When the alarm is triggered, it will receive the temperature -27 that will send the a trigger to the database and then wait for a restart of the alarm-system through the nsa-homepage.
* The unit will also receive the temperature 90 to know that the nsa-arduino system is running and connected. this data should be recieved every 5 seconds.
