#!/bin/bash
# Usage:
#       ./UARTplay.sh <file to play>

PORT="/dev/ttyUSB0"
BAUD="2000000"
VOLUME="0.5"
SAMPLERATE=44100

python src/UARTsetup.py $PORT $BAUD
ffmpeg -i "$1" -c:v none -c:a pcm_s16le -af "aeval=val(ch)*$VOLUME:c=same" -ac 1 -ar $SAMPLERATE -f s16le - | ./UARTaudio $SAMPLERATE $BAUD >$PORT
