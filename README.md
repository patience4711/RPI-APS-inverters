# APSystems inverters monitoring

![housing](https://user-images.githubusercontent.com/12282915/150977290-19a81da7-0c82-4eb8-9522-89a74197bcea.jpg)

A software for a Raspberry pi Zero and other Raspberry models to read the production of APS inverters yc600, qs1 and ds3. I should mention that the basics (the zigbee communication) has been reverse engineered by others who shared their results here: https://github.com/Koenkk/zigbee2mqtt/issues/4221<br>
A very important detail is the software running on the zigbee module, developped by @kadzsol. 
<br>**NEW april 2022** The DS3 inverter is implemented.<br><br>
For information on building and use please see the [WIKI](https://github.com/patience4711/RPI-APS-inverters/wiki)

## IMPORTANT TO KNOW
People keep asking for the ssh login, this is 'root' and 'mies'. Please be aware that this is known to the whole world now.
So **never** put the ssh port open 'to the world'<br><br>
The influx database system has the very annoying feature that it starts very slow, sometimes as much as 15 minutes after system boot. This means that you shouldn't backup or restore databases during this period!
The values displayed on the webpage are the values reported by the inverter. In case of an inverter reset, these values start at zero so they seem to be incorrect. In the database / charts however, the values will be correct so there is no need for actions by the user.
In case of a raspberry reboot there are initially no values written to the database, because it starts very slowly. This means that the chart of the power won't be correct. The energy value in the database will be correct the next day.

## PURPOSE
This project is intended for reading APS Systems inverters. The program can pair and poll YC600, QS1 and DS3 inverters, up to 9 pieces. The read values are: 
- displayed on a web page  
- sent via mosquitto in a Json format
- saved in a database for charts and statistics. 

## DOWNLOAD SD-CARD IMAGE
2022-06-30 A new sd-card image version RPI-ECU-v3_0 is available (see changelog). [RPI-ECU-3_0.zip](https://1drv.ms/u/s!AkMG5FvUwhedi1StG9734oOcMcRA?e=xlnuUq)<br>
This version works with the DS3 inverter.<br>

## DOWNLOAD SOFTWARE UPDATES

2022-06-30 A software update to version RPI-ECU-v3_0 is available (see changelog). Install this only when you currently use version 2_9<br>
[ecu_swupdate-v3_0.tar](https://1drv.ms/u/s!AkMG5FvUwhedi1WZSjk2R9WrGxhn?e=OZolFW) <br>
2022-06-23 A software update to version RPI-ECU-v2_9 is available (see changelog). Install this only when you currently use version 2_8<br>
[ecu_swupdate-v2_9.tar](https://1drv.ms/u/s!AkMG5FvUwhedi1N5HHSwSlxo3XOc?e=JTbYdM) <br>
2022-06-14 A software update to version RPI-ECU-v2_8 is available (see changelog). Install this only when you currently use version 2_7<br>
[ecu_swupdate_14-06-2022.tar](https://1drv.ms/u/s!AkMG5FvUwhedi0w0itFjZ4A_Jc-n?e=bhabdM) <br>
2022-06-08 A software update to version RPI-ECU-v2_7 is available (see changelog). Install this only when you currently use version 2_6<br>
[ecu_swupdate_08-06-2022.tar](https://1drv.ms/u/s!AkMG5FvUwhedi0r9yS7C6Spkopzg?e=x4y9IR) <br>
2022-05-31 A software update to version RPI-ECU-v2_6 is available (see changelog). Install this only when you currently use version 2_5<br>
[ecu_swupdate_31-05-2022.tar](https://1drv.ms/u/s!AkMG5FvUwhedi0nkRdw0J8sN6Oea?e=QA3ML6) <br>
2022-05-21 A software update to version RPI-ECU-v2_5 is available (see changelog). Install this only when you currently use version 2_4<br>
[ecu_swupdate_21-05-2022.tar](https://1drv.ms/u/s!AkMG5FvUwhedi0f-bOvnSD9lo95s?e=y6FRhJ) <br>
2022-04-21 A software update to version RPI-ECU-v2_4 is available (see changelog). Install this only when you currently use version 2_3<br>
[ecu_swupdate_21-04-2022.tar](https://1drv.ms/u/s!AkMG5FvUwhedizqYIS5MOefFfNyo?e=iCehez) <br>


2022-06-30 The new version RPI-ECU-v3_0 is available. This has to be installed by burning the disk image to an sdcard. Before you start please read the instructions. If you want to backup and restore your settings and databases, be sure you upgraded to version RPI-ECU-v2_3. And schedule some time after midnight to perform the migration. Please follow the steps in **installation via the sd-card image** , in particular it is important that you expand the filesystem first and than wait for influxdb is running, before restoring your backup!!. 

Please see 'CHANGELOG'
<br><br>

See it in action on youtube: https://youtu.be/oF-QE4GUGy8
<br><br>
In case someone wants to print the housing: https://1drv.ms/u/s!AkMG5FvUwhediwaPqGYXa7vMkXp8?e=kzkdHQ<br><br>
**Some webpages:**<br>
![compilation](https://user-images.githubusercontent.com/12282915/173093515-dbf569fb-15c9-4313-9357-b50f7c96683b.jpg)
<br><br>
## FEATURES:
- all inverter information such as temperature, dc voltage etc available
- energy production per solar panel displayed
- Easy wifi config portal
- Easy add, delete and pair inverters
- There are 3 different json formats, a special one for domoticz
- a very smart console to send zigbee commands and debug
- almost all processes show debug information, most pages have a frame for that.
- polled values are stored in a database
- charts of the production at multiple days are available
- There is a page with statistic data 
- The menu is only accessible from local network with login
- software can be updated by uploading and installing a tar achive

## (RE) INSTALLATION INSTRUCTIONS (see also the [WIKI](https://github.com/patience4711/RPI-APS-inverters/wiki/home) for further instructions) 
**installation via the sd-card image**<br>
**step 1**<br> Download the package, unzip and burn the image on an sd card. If you are new user of this software please continue with stap 3.<br>
**step 2**<br> You already are using this software then you can make a backup of your system and databases first. You should do this after midnight. 
The backup is primarily intended for system migrations and have to be restored the same day as it was made. If you restore it on a later date you will miss data. 
So complete the next steps before sunrise in order to get a smooth migration.<br>
**step 3**<br>
Visit the [WIKI](https://github.com/patience4711/RPI-APS-inverters/wiki/1-PUT-INTO-USE) for further instructions

## HARDWARE
What you need for this project is:
- a Raspberry zero 1.3 W (yes the W means wifi) ~11Euro or a goodold model 1 will work too.
- micro sd-card class 10, 8 or 16 gB (like in your phone)
- a cc2530 module, see photo, with the right firmware on it (see readme in the info folder of the download package.
- a 5V dc 3A powersupply see photo

estimates costs some 25 Euro.
The zigbeemodule should be flashed with a firmware that can be found here https://github.com/Koenkk/zigbee2mqtt/issues/4221.  

## WIRING ZIGBEE MODULES
you need 5 dupont cables.

**cc2530/31** (see wiki) <br>
p02 -> gpio14 ( pin 8 )<br>
p03 -> gpio15 ( pin 10 )<br>
rst -> gpio18 ( pin 12 )<br>
vcc -> 3.3V<br>
gnd -> g<br>
<br>

hardware:<br>
![rpi_minhw](https://user-images.githubusercontent.com/12282915/147755635-156ec891-1dfd-4ff3-a59e-979653e1f47a.jpg)
![pwrsup](https://user-images.githubusercontent.com/12282915/148765236-f1662888-5d44-43d7-a09e-abe379e6e89d.jpg)

![stats](https://user-images.githubusercontent.com/12282915/148557056-7ca1aa16-36bb-4352-a0fb-ba7e8e3b5ee5.jpg)
<br>

## TROUBLE SHOOTING
**You forgot your admin password.** 
If you type http://your_ecu_ip/recovery/recover.php you will enter a secret page where you
can drop your wifi credentials. At reboot the accesspoint **RadioAP** is started. 

## CHANGELOG
**version RPI-ECU-v3_0**  30 june 2022  upgrade archive or sd image
- removed the http poll trigger.
- changed the navigation and the appearance of some pages

**version RPI-ECU-v2_9**  23 june 2022  upgrade archive
- added a http requests to retrieve inverter data
- changed the main page (now a clickable list of all inverters and data)
- repaired a bug in the inverters administration (delete process)

**version RPI-ECU-v2_8**  13 june 2022  upgrade archive
- repaired a bug in the polling process of ds3 (wrong time value)
- removed a bug in the powercalculation of ds3

**version RPI-ECU-v2_7**  08 june 2022  upgrade archive
- added healthcheck of influxdb 
- fixed a bug in send a zigbeecommand

**version RPI-ECU-v2_6**  30 may 2022  upgrade archive
- removed limit of 20 in database query 
- added a value validation to prevent erratical energy values

**version RPI-ECU-v2_5**  27 may 2022  upgrade archive
- added dc current for the ds3 inverter
- improved powercalculation

**version RPI-ECU-v2_4**  19 april 2022  new sd image
- made the program suitable for the ds3 inverter
- extended database query and editing

**version RPI-ECU-v2_3**  22 march 20222 upgrade archive.
- repaired a bug with database editing

**version RPI-ECU-v2_2**  22 march 20222 upgrade archive.
- added a utility to edit database entries in 'invEnergy'

**version RPI-ECU-v2_1**  25 feb 20222 upgrade archive.
- repaired a bug with offset to sunrise / sunset
- restored a missing file for mqtt test.
- Some cosmetics

**version RPI-ECU-v2_0**  15 feb 20222 Only installable as sd-image.
- changed the process of gathering the total energy values. 
- ruled out the effect of disturbances (eclips, inverter resets, zigbee disturbances)
- added a tool to upload and show a photo of your powerplant.


