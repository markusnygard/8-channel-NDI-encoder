# Runbook_8ch_NDI_encoder

## Install and compile Ubuntu FFmpeg NDI-encoder machine.
-------------------------
Install Ubuntu 22.04 Desktop with username: ndi(small letters), networkname should be the machinename you wish in the NDI network, and autoboot enabled
Disable lockscreensaver.

### Install Decklink "Desktop Video v.12.5"
Download from here:
```
https://www.blackmagicdesign.com/support/family/capture-and-playback
```
Install:
* desktopvideo
* desktopvideo-gui

Open desktopvideo (Decklink GUI) and setup card for 8 input.

### Install FFmpeg:
the FFmpeg with NDI-installation is for Luke Plassman (https://github.com/lplassman/FFMPEG-NDI)

```
sudo apt-get install git

git clone https://github.com/xxxxxxxxxx ffmpeg_runbook

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
chmod +X runbook.sh
./runbook.sh
```

### Make encodersript runable:
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

### FFmpeg examples:
----------------------

Direct RTSP URL:
```
* rtsp://wowzaec2demo.streamlock.net/vod/mp4:BigBuckBunny_115k.mov
```
Direct HTTP URL to sample file:
```
* http://www.wowza.com/_h264/BigBuckBunny_115k.mov
```

NewTek NDI streams:

find NDI-streams
```
* ffmpeg -f libndi_newtek -find_sources 1 -i dummy
```
Create a new copy of NDI-stream
```
* ffmpeg -f libndi_newtek -i 'NDI-TX3 (NDI_1)' -f libndi_newtek 'FFmpegNDI_1'
```
SDI Out from DeckLink:

* 720p50:
```
    * ffmpeg -r 50 -f libndi_newtek -i 'NDI-TX3 (NDI_1)' -buffer_size 1500M -an -f decklink 'DeckLink Duo (4)’
```
* 1080i:
```
    * ffmpeg -f libndi_newtek -i 'NDI-TX3 (NDI_1)' -buffer_size 3000M -an -f decklink -s 1920x1080 -r 25000/1000 'DeckLink Duo (4)'
```
Decklink encoder:
```
* ffmpeg -f decklink -i 'DeckLink Duo (1)' -f libndi_newtek 'NDI_1'
```


Output UDP strøm:
```
* ffmpeg -r 50 -i "udp://232.101.1.7:5500" -f libndi_newtek -pix_fmt uyvy422 -clock_video true KAOL_RTP_01
```

