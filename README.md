# APSystems inverters monitoring

![housing](https://user-images.githubusercontent.com/12282915/150977290-19a81da7-0c82-4eb8-9522-89a74197bcea.jpg)

A software for a Raspberry pi Zero and other Raspberry models to read the production of APS inverters yc600, qs1 and ds3. I should mention that the basics (the zigbee communication) has been reverse engineered by others who shared their results here: https://github.com/Koenkk/zigbee2mqtt/issues/4221<br>
A very important detail is the software running on the zigbee module, developped by @kadzsol. 
<br><br>
For information on building and use please see the [WIKI](https://github.com/patience4711/RPI-APS-inverters/wiki)

See it in action on [YouTube](https://youtu.be/sTnKeFcmqhc)

## IMPORTANT TO KNOW
People keep asking for the ssh login, this is 'ecuuser' and 'ecuuser' as from v4_0. Please be aware that this is known to the whole world now.
So **never** put the ssh port open 'to the world' or even better, change this.<br><br>
The software can be updated by installing an upgrade tar file. Please see the wiki.

From outside your network you won't see the menu link. Maintenance can only be done from inside your own network.

The influx database system has the very annoying feature that it starts very slow, sometimes as much as 15 minutes after system boot. This means that you shouldn't backup or restore databases during this period!
The values displayed on the webpage are the values reported by the inverter. In case of an inverter reset, these values start at zero so they seem to be incorrect. In the database / charts however, the values will be correct so there is no need for actions by the user.
In case of a raspberry reboot there are initially no values written to the database, because it starts very slowly. This means that the chart of the power won't be correct. The energy value in the database will be correct the next day.

## PURPOSE
This project is intended for reading APS Systems inverters. The program can pair and poll YC600, QS1 and DS3 inverters, up to 9 pieces. The read values are: 
- displayed on a web page  
- sent via mosquitto in a Json format
- saved in a database for charts and statistics. 

## DOWNLOAD SD-CARD IMAGE
2025-01-27 A new sd-card image version [RPI-ECU-v4_4](https://1drv.ms/u/c/9d17c2d45be40643/EQ6i873HB09LjVMsZ4gpPMEBD10CEyRhfjxW_n2B0HDxEA?e=Yt5poF) is available (see changelog). 
<br>This has to be installed by burning the disk image to an sdcard. Before you start please read the instructions in the wiki or readme. If you want to backup and restore your settings and databases, be sure you currently have version RPI-ECU-v2_3 or above. And schedule some time after midnight to perform the migration. Please follow the steps in **installation via the sd-card image** , in particular it is important that you expand the filesystem first and than wait for influxdb is running, before restoring your backup!!.
<br>

## DOWNLOAD SOFTWARE UPDATES
2025-01-28: [ecu_swupdate-v4_4](https://github.com/patience4711/RPI-APS-inverters/blob/main/ecu_swupdate-v4_4.tar) is available (see changelog).
2024-09-02: [ecu_swupdate-v4_3](https://github.com/patience4711/RPI-APS-inverters/blob/main/ecu_swupdate-v4_3.tar) is available (see changelog). **IMPORTANT** Install updates with v4_x only when you are running version 4_0 or higher (please read [instructions here](https://github.com/patience4711/RPI-APS-inverters/issues/121) .<br>If you experience malformed webpages, please clear your browser cache (delete web history saved pictures and files)<br><br>

2023-01-12: [ecu_swupdate-v3_10.tar](https://github.com/patience4711/RPI-APS-inverters/blob/main/ecu_swupdate-v3_10.tar) is available (see changelog). **IMPORTANT** Install this only when you are running version 3_1 or higher (please see the expanation to version 3_1 below).<br>If you experience malformed webpages, please clear your browser cache (delete web history saved pictures and files)<br><br>

<br><br>
In case someone wants to print the housing: https://1drv.ms/u/s!AkMG5FvUwhediwaPqGYXa7vMkXp8?e=kzkdHQ<br><br>
**Some webpages:**<br>
![Examples](https://github.com/user-attachments/assets/0ad7d93f-2c64-440c-8f06-fcb0fc12b9ca)
<br>
## FEATURES:
- all inverter information such as temperature, dc voltage etc available
- energy production per solar panel displayed
- values are transferred via Mqtt in user defined json formats
- Easy wifi config portal
- Easy add, delete and pair inverters
- a very smart console to send zigbee commands and debug
- almost all processes show debug information, most pages have a frame for that.
- polled values are stored in a database
- charts of the production at multiple days are available
- There is a page with statistic data 
- The menu is only accessible from local network with login
- software can be updated by uploading and installing a tar achive
- data can be requested via a direct link like 'ip_of_ecu/recovery/getInverter.php?inv=x'

## (RE) INSTALLATION INSTRUCTIONS (see also the [WIKI](https://github.com/patience4711/RPI-APS-inverters/wiki/home) for further instructions) 
**installation via the sd-card image**<br>
**step 1**<br> Download the package, unzip and burn the image on an sd card. If you are new user of this software please continue with stap 3.<br>
**step 2**<br> You already are using this software then you can make a backup of your system and databases first. You should do this after midnight. 
The backup is primarily intended for system migrations and have to be restored the same day as it was made. If you restore it on a later date you will miss data. 
So complete the next steps before sunrise in order to get a smooth migration.<br>
**step 3**<br>
Visit the [WIKI](https://github.com/patience4711/RPI-APS-inverters/wiki/1-PUT-INTO-USE) for further instructions

## INSTALL ON AN EXISTING RPI SYSTEM ##
You need to have the imagefile mounted or working so that you can copy the relevant files. Please follow the instructions [here](https://github.com/patience4711/RPI-APS-inverters/issues/106#issuecomment-1916389701) provided by a user who installed it this way.

## HARDWARE
What you need for this project is:
- a Raspberry zero 1.3 W (yes the W means wifi) ~11Euro or a goodold model 1 will work too.
- micro sd-card class 10, 8 or 16 gB (like in your phone)
- a cc2530 module, see photo, with the right firmware on it (see readme in the info folder of the download package.
- a 5V dc 3A powersupply see photo

estimates costs some 25 Euro.
The zigbeemodule should be flashed with a firmware that can be found in the downloaded zip. Fore more info look [here]( https://github.com/Koenkk/zigbee2mqtt/issues/4221).  

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
**version RPI-ECU-v4_4** jan 28 2025
- added zram for better read/write performance and to spare the sdcard.

**version RPI-ECU-v4_3** dec 13 2024
- this version is identical to update v4_2c but hows the correct version nr.
- changed the way of retrieving system info (update v4_2c)

## CHANGELOG
**version RPI-ECU-v4_2** sept 2 2024
- changed the way of retrieving system info (update v4_2c)
- fixed a problem with selection of a chart date.
- fixed problems with version nr and fs info after database restore
- better performance on mobile devices

**version RPI-ECU-v4_1** aug 6 2024
- new up-to-date linux version
- better performance on mobile devices

**version RPI-ECU-v3_10** jan 9 2024 upgrade archive:
- optimized webinterface performance/appearance on mobile devices

**version RPI-ECU-v3_9** dec 22 2023 upgrade archive:
- fixed an error (panels 0 and 1 of yc600 were swapped).
- fixed a problem with send zigbee commands on rpi zero 2

**version RPI-ECU-v3_8** 9 oct 2023 upgrade archive:
- fixed a bug that confused dcv's for ds3 inverters

**version RPI-ECU-v3_7** 14 feb 2023 upgrade archive:
- added retainflag to Mosquitto.
- added the option to have a separate mqtt topic for each inverter.
 
**version RPI-ECU-v3_6** 03 oct 2022 upgrade archive:
- added 2 more mqtt json formats (values as float).
- added a zigbee signal quality value (shown in the journal).

**version RPI-ECU-v3_5** 13 aug 2022 upgrade archive:
- energy values now persistant until midnight, consequent with database and survive inverter resets.
- improved photo display, especially for mobile devices.

**version RPI-ECU-v3_4** 10 aug 2022 upgrade archive:
- fixed null values for energy due to inverter resets at sunset.
- added default picture, picture icon appears in the inverter details page.
- repaired a small bug in the inverter details page
- improved the navigation/cosmetics and chart of the daily energy.

**version RPI-ECU-v3_3** 27 july 2022 sdcard image and upgrade archive:
- installed zram-swap for better system performance
- added a memo utility to remember certain events
- check and restore some file privileges at bootup 
- prevent overwriting of the photo at swupgrade
- Decreased the sd-card writing by tweaking log settings
- moved a frequently written variable to ramdisk
- improved the navigation and the appearance of charts in small screens
- improved security by disabling page viewing for all o.t.t.w. pages
- improved the swupgrading process, now possible to replace whole directories.
- improved the datase backup and restore processes.
- added an option for authentication in mosquitto

**version RPI-ECU-v3_1**  12 july 2022  upgrade archive:
- prepare for a new software upgrade procedure

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


