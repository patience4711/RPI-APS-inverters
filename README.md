# RPI-APS-inverters
a software for a raspberry pi zero to read the production of aps inverters yc600 and qs1

This project is intended for reading APS Systems inverters. The program can pair and poll YC600 and QS1 inverters, up to 9 pieces. The read values are 
- displayed on a web page  
- sent via mosquitto in a Json format
- saved in a database for charts an statistics. 

The program has a lot of smart features. All settings can be done via the webinterface. It has a console that can be used for debugging and sending/receiving zigbee messages.

dowload the image: https://1drv.ms/u/s!AkMG5FvUwhedinrexy9cvl4PkxX5?e=tLeRt0

See it in action on youtube: under construction

In case someone wants to print the housing: under construction

## FEATURES
all inverter information such as temperature, etc available
production per solar panel displayed
Easy wifi config portal
Easy add, delete and pair inverters
automatic polling or on demand via mqtt or http
There are 3 different json formats, a special one for domoticz
a very smart console to send zigbee commands and debug
charts of the production at multiple days are available

## INSTALLATION
Download the package and burn the image on an sd card.
Boot up. Open the wifi settings on your computer/tablet/phone. 
After a while you will see an accesspoint RadioAP. Connect to it wit the paswd rpiradio.
Now browse to http://192.168.4.1 and enter your wifi credentials as well as a userename/password
for the security of your webpages. Click save and wait for the reboot button to appear. Click it.
Now the raspberry reboots and connects to your wifi. This may take a while!
You can find your raspberry ip address by browsing to http://rpiecu.local.
Or open your routers webpage to see the connected devices to find the ip address

## SETTINGS
You can expand the filesystem, go to menu, log in with the provided credentials and go to <system><expand fs>
After the reboot, the filsystem makes use of the whole sdcard. Check the timezone.
In the menuitem settings you have to enter the coordinates of your location. Now your system can determine
sunset and sunrise.

## HARDWARE
It is nothing more than a Raspberry pi Zero and a prepared cc2530, cc2531 zigbee module. And a powersupply. 
The zigbeemodule should be flashed with a firmware that can be found here https://github.com/Koenkk/zigbee2mqtt/issues/4221.  

An image file of this software can be found here: under construction ( testing some new features )

hardware:
![rpi_minhw](https://user-images.githubusercontent.com/12282915/147755635-156ec891-1dfd-4ff3-a59e-979653e1f47a.jpg)

Some webpages
![pages_rpiecu](https://user-images.githubusercontent.com/12282915/147755570-db00c49e-3033-42b2-bb68-8bbb9a003e33.jpg)
