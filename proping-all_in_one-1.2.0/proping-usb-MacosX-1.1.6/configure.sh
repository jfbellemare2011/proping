#!/bin/sh
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
gcc ./src/proping.c ./src/tracert.c -o ./proping 2> ./err.txt
cp  ./src/proping.conf ./proping.conf 2> ./err.txt

echo C compiling ./src/proping.c ./src/tracert.c ./src/ping.c to ./proping \n
echo Copy of ./src/proping.conf TO ./proping.conf \n
