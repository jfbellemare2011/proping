#!/bin/bash 
#			   ██▓███   ██▀███   ▒█████   ██▓███   ██▓ ███▄    █   ▄████ 
#			  ▓██░  ██▒▓██ ▒ ██▒▒██▒  ██▒▓██░  ██▒▓██▒ ██ ▀█   █  ██▒ ▀█▒
#			  ▓██░ ██▓▒▓██ ░▄█ ▒▒██░  ██▒▓██░ ██▓▒▒██▒▓██  ▀█ ██▒▒██░▄▄▄░
#			  ▒██▄█▓▒ ▒▒██▀▀█▄  ▒██   ██░▒██▄█▓▒ ▒░██░▓██▒  ▐▌██▒░▓█  ██▓
#			  ▒██▒ ░  ░░██▓ ▒██▒░ ████▓▒░▒██▒ ░  ░░██░▒██░   ▓██░░▒▓███▀▒
#			  ▒▓▒░ ░  ░░ ▒▓ ░▒▓░░ ▒░▒░▒░ ▒▓▒░ ░  ░░▓  ░ ▒░   ▒ ▒  ░▒   ▒ 
#			  ░▒ ░       ░▒ ░ ▒░  ░ ▒ ▒░ ░▒ ░      ▒ ░░ ░░   ░ ▒░  ░   ░ 
#			  ░░         ░░   ░ ░ ░ ░ ▒  ░░        ▒ ░   ░   ░ ░ ░ ░   ░ 
#			              ░         ░ ░            ░           ░       ░ 
#
apt-get install -y gcc glibc*
yum install -y gcc glibc*

gcc ./src/install.c -o ./"install"
gcc -pthread ./src/proping.c ./src/traceroute.c -o ./proping
cp ./src/proping.conf ./proping.conf
cp ./src/proping.initd ./proping.initd

echo "C compiling ./src/install.c to ./install \n"
echo "C compiling -pthread ./src/proping.c ./src/traceroute.c -o ./proping \n"
echo "Copy of ./src/proping.conf TO ./proping.conf \n"
echo "Copy of ./src/proping.initd TO ./proping.initd \n"
