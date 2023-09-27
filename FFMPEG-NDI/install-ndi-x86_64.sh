#!/usr/bin/env sh

set -eu
echo "Downloading NDI libraries..."
sudo bash ../ffmpeg_runbook/FFMPEG-NDI/download_NDI_SDK.sh

echo "Installing NDI libraries..."
sudo cp -R "NDI SDK for Linux"/include/* /usr/include/
sudo cp -R "NDI SDK for Linux"/lib/x86_64-linux-gnu/* /usr/lib/

echo "Done"
