#!/bin/bash
arecord -r 48000 -c 2 -D hw:CARD=Generic_1,DEV=0 | ./stdout2shmbuf