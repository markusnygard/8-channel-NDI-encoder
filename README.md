# Runbook_8ch_NDI_encoder

## Install and compile Ubuntu FFmpeg NDI-encoder machine.
-------------------------
Install Ubuntu 22.04 Desktop with username: ndi(small letters), networkname should be the machinename you wish in the NDI network, and autoboot enabled
Disable lockscreensaver.
Caution: Ubuntu 24.04 has at this point (8 june 2024) a problem installing Decklink-drivers, so don't use it before that issue is solved
The NDI is updated to NDIv6 (8 june 2024)

### Install Decklink "Desktop Video v.14.0"
Download from here:
```
https://www.blackmagicdesign.com/support/family/capture-and-playback
```
Install:
* desktopvideo
* desktopvideo-gui

Open desktopvideo (Decklink GUI) and setup card for 8 input.

### Install FFmpeg:
the FFmpeg with NDI-installation is from Luke Plassman (https://github.com/lplassman/FFMPEG-NDI)

```
sudo apt-get install git

git clone https://github.com/markusnygard/8-channel-NDI-encoder.git ffmpeg_runbook

cd ffmpeg_runbook/StartUpScripts
```
edit the encodernames in nano
```
nano encode8HDSDI.sh
```
if you are using another Decklink-card than Quad2 then edit the cardname in nano
```
nano HDSDItoNDI.sh
```
Run script:
```
cd ..
chmod +x runbook.sh
./runbook.sh
```
During the installasion there 2 accurencies where you have to answer Yes
```
```
### Make encoderscript runable:
```
chmod +X /home/ndi/runffmpeg/encode8HDSDI.sh
```

### Enable SRT lib:
Edit:
```
sudo nano /etc/ld.so.conf
```
Add line in file: 
```
include /usr/local/lib
```
Save and run:
```
sudo ldconfig
```

reboot machine


--------------------------------------------------

### Info:
----------------------

This is a project that is a updated version of "8-channel NDI runbook"
made and publish by danish TV2 and Olzzon.
The FFmpeg-NDI implementation is made by Luke Plassman
and can be found on his github (https://github.com/lplassman/FFMPEG-NDI) 
and the FFmpeg is from the official FFmpeg repo and this repo should comply with all licences.
```

