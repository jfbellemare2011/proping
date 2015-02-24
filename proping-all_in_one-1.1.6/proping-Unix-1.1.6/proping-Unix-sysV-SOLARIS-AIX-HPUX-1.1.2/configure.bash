#!/bin/bash 

/usr/sfw/bin/gcc ./src/install.c -o ./"install"
/usr/sfw/bin/gcc ./src/proping.c -o ./proping
cp ./src/proping.conf ./proping.conf

echo "C compiling ./src/install.c to ./install \n"
echo "C compiling ./src/proping.c to ./proping \n"
echo "Copy of ./src/proping.conf TO ./proping.conf \n"
