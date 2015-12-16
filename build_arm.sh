#!/bin/sh

export PATH=$PATH:/usr/local/Trolltech/QtEmbedded-4.8.5-arm/bin
qmake -spec qws/linux-arm-gnueabi-g++ -o Makefile *.pro
make 
make clean
rm -f Makefile
