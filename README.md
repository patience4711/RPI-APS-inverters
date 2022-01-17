# APSystems inverters monitoring
A software for a raspberry pi zero to read the production of APS inverters yc600 and qs1. I should mention that the basics (the zigbee communication) has been reverse engineered by others who shared their results here: https://github.com/Koenkk/zigbee2mqtt/issues/4221<br>
A very important detail is the software running on the zigbee module, developped by @kadzsol.  

This project is intended for reading APS Systems inverters. The program can pair and poll YC600 and QS1 inverters, up to 9 pieces. The read values are: 
- displayed on a web page  
- sent via mosquitto in a Json format
- saved in a database for charts and statistics. 

The program has a lot of smart features. All settings can be done via the webinterface. It has a console that can be used for debugging and sending/receiving zigbee messages.

dowload the image: https://1drv.ms/u/s!AkMG5FvUwhedin3Wqj9XmK1bHAlk?e=gYdbyx

See it in action on youtube: under construction
Some webpages
![pages_rpiecu](https://user-images.githubusercontent.com/12282915/147755570-db00c49e-3033-42b2-bb68-8bbb9a003e33.jpg)
In case someone wants to print the housing: under construction<br><br>

## FEATURES:
- all inverter information such as temperature, dc voltage etc available
- energy production per solar panel displayed
- Easy wifi config portal
- Easy add, delete and pair inverters
- There are 3 different json formats, a special one for domoticz
- a very smart console to send zigbee commands and debug
- polled values are stored in a database
- charts of the production at multiple days are available
- There is a page with statistic data available
- The menu is only accessible from local network with login

## INSTALLATION
Download the package and burn the image on an sd card.
<br>Boot up. Open the wifi settings on your computer/tablet/phone. 
After a while you will see an accesspoint **RadioAP**. Connect to it with the paswd 'rpiradio'.
<br>Now browse to http://192.168.4.1 and enter your wifi credentials as well as a userename/password
for the security of your webpages. Click save and wait for the reboot button to appear. Click it.
**note:** The security credentials are needed to get access to the settings of your ECU. For security reasons
only from inside your local network.

<br>Next the raspberry reboots and tries to connect to your wifi. This may take a while!
You can find your raspberry ip address by browsing to http://rpiecu.local.
Or open your router's webpage to see the connected devices to find the ip address.
Or use a wifi analizer tool on your phone/tablet.

## FACTORY RESET
When i make an image of the system there are settings and data present that belong to my inverters. 
So you should start by wiping all present inverterdata (Console). This is also true when upgrading to a new version.
The newest version will have a means to backup settings and data that can be restored ater a software upgrade.

## SETTINGS
You should expand the filesystem, go to menu, log in with the provided credentials and go to **'->menu ->system ->expand fs'**
<br>After the reboot, the filesystem makes use of the entire sdcard. <br>Check the timezone.
<br>In the menuitem 'settings' you have to enter the coordinates of your location. Now your system can determine
sunset and sunrise. <br>Also enter the id nr for the zigbee coordinator, this must be a 12 character string, like D6B3011B9780<br>
<br>Enter an offset to sunrise and sunset were the polling should start. Usually at sunrise the inverter is not yet started, <br>
it may even restart a couple of times when the power is alternately below or above the threshold value. To rule this out<br>
you could set an offset of about 10 minutes.  

## START THE ZIGBEE SYSTEM
Check first the hardware, than go to "console" and try to start the zigbee coordinator. With the healthcheck you can see if this succeeded.
If success you can configure an inverter, go to the menu ínverters and fill up / save the form.
Now you can try to pair this inverter.  
If success, this inverter will be polled automatically every 5 minutes. The data is displayed in the frontpage abd charts,
and is send via Mosquitto. At reboot all processed will be started automatically. 

## HARDWARE
What you need for this project is:
- a Raspberry zero 1.3 W (yes the W means wifi) ~11Euro
- micro sd-card class 10, 8 or 16 gB (like in your phone)
- a cc2530 module, see photo
- a 5V dc 3A powersupply see photo

estimates costs some 25 Euro.
The zigbeemodule should be flashed with a firmware that can be found here https://github.com/Koenkk/zigbee2mqtt/issues/4221.  

## WIRING ZIGBEE MODULES
you need 5 dupont cables.

**cc2530**<br>
p2 -> gpio14 ( pin 8 )<br>
p3 -> gpio15 ( pin 10 )<br>
rst -> gpio18 ( pin 12 )<br>
vcc -> 3.3V<br>
gnd -> g<br>
<br>
**cc2531** (not tested by me!)<br>
dd -> gpio14 ( pin 8 )<br>
dc -> gpio15 ( pin 10 )<br>
rst -> gpio18 ( pin 12 )<br>
vcc -> 3.3V<br>
gnd -> g<br>
if this doesn't work try to swap dd and dc<br>
<br>
![RPI-ECU_WIRING](https://user-images.githubusercontent.com/12282915/148555017-c3e7a36f-6595-415f-95c7-0eb32400f2bb.jpg)

hardware:<br>
![rpi_minhw](https://user-images.githubusercontent.com/12282915/147755635-156ec891-1dfd-4ff3-a59e-979653e1f47a.jpg)
![pwrsup](https://user-images.githubusercontent.com/12282915/148765236-f1662888-5d44-43d7-a09e-abe379e6e89d.jpg)

![stats](https://user-images.githubusercontent.com/12282915/148557056-7ca1aa16-36bb-4352-a0fb-ba7e8e3b5ee5.jpg)
<br>
## CHANGELOG
version RPI-ECU-v1_1 (planned 21 jan 2022)
- added backup of settings and databases
- added upload/install of software upgrade package
- added some new features in the charts and statistics
