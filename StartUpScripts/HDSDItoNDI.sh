while true; do 
	/home/ndi/ffmpeg/ffmpeg -err_detect explode -f decklink -i 'DeckLink Quad ('$1')' -f libndi_newtek $2
	echo "Input ""$1"" crashed: returncode §?" >&2
	sleep 2
done
