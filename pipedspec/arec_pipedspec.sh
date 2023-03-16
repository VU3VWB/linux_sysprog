#!/bin/bash
arecord -r 48000 -c 2 -f S16_LE -D plughw:CARD=USB,DEV=0 | ./inp_pipe
