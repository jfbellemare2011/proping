#!/bin/bash 

yum "install" -y gcc

gcc ./src/install.c -o ./"install"
gcc ./src/proping.c -o ./proping
cp ./src/proping.conf ./proping.conf
cp ./src/proping.initd ./proping.initd

echo "C compiling ./src/install.c to ./install \n"
echo "C compiling ./src/proping.c to ./proping \n"
echo "Copy of ./src/proping.conf TO ./proping.conf \n"
echo "Copy of ./src/proping.initd TO ./proping.initd \n"
