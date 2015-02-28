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
# Function: Generate a range of IP Addresses
# Version:  1.1
# Author:   sol@subnetzero.org v1.1
# Modified by: jfbellemare2011 v1.2
# 
#
# Convention for octets:  A.B.C.D

# Variable setup section...
#
# Split up IP addresses into seperate variables for each octet
IPLO=(`echo "$1" | awk '{split($1,a,"."); print a[1]" "a[2]" "a[3]" "a[4]}'`)
IPHI=(`echo "$2" | awk '{split($1,a,"."); print a[1]" "a[2]" "a[3]" "a[4]}'`)
#
# Put array contents into nicely named vars for less confusion
#



OCTA=${IPLO[0]}
OCTB=${IPLO[1]}
OCTC=${IPLO[2]}
OCTD=${IPLO[3]}
OCTAHI=${IPHI[0]}
OCTBHI=${IPHI[1]}
OCTCHI=${IPHI[2]}
OCTDHI=${IPHI[3]}
OCTDMAX=255             # Max default value for D Octet to loop to
FINISHED=0              # Variable used for loop state checking

INTERFACE_NUM=1

# Syntax sanity check; check all vars are populated etc
for i in 0 1 2 3
do
        if [ -z "${IPLO[$i]}" ] || [ -z "${IPHI[$i]}" ]; then
                echo "Usage: $0 [from ip] [to ip] !!!This range will be added in ./proping.conf!!!"
                exit 1
        elif [ "${IPLO[$i]}" -gt "255" ] || [ "${IPHI[$i]}" -gt "255" ];then
                echo "One of your values is broken (greater than 255)."
                exit 1
        fi

done

# Until FINISHED variable is set to 1, loop the loop.
# FINISHED var is used to determine when done as the increments
# to the vars in the loop will mean that when we get to the done
# statement, the values won't be the same as printed.
#
# The D Octet loop is the heart of this script, as it's easiest
# to check whether we've reached the target or not from here.
#
until [ "$FINISHED" -eq "1" ];
do
        # If first 3 octets match hi values, use OCTDHI as max value for 4th octet.
        if [ "$OCTA" -eq "$OCTAHI" ] && \
           [ "$OCTB" -eq "$OCTBHI" ] && \
           [ "$OCTC" -eq "$OCTCHI" ]; then
                OCTDMAX=$OCTDHI
        fi

#--------------------------------------------------------------------------------------------------------------------------------

FILE=./proping.conf

if [ -f $FILE ];
then
   echo "File $FILE exists."
else
   echo "File $FILE does not exist, we will create it."


echo "" >> ./proping.conf
printf "#==================EXEMPLE OF CONFIGURATION, Let's see in the configuration file /etc/proping/proping.conf=============================	\n" >> ./proping.conf
printf "#																	\n" >> ./proping.conf
printf "#	-Must use the file (sudo ./install) before running the service, do not forget to make an executive with (chmod 755).		\n" >> ./proping.conf
printf "#																	\n" >> ./proping.conf
printf "#	-If one of the configured interfaces is unreachable, a warning message will be issued on your terminal and by the beeper.	\n" >> ./proping.conf
printf "#																	\n" >> ./proping.conf
printf "#	-To start the service (sudo /usr/sbin/proping |start|stop|)									\n" >> ./proping.conf
printf "#	or																\n" >> ./proping.conf
printf "#	-Proping (Service restart |stop|start|restart|)											\n" >> ./proping.conf
printf "#																	\n" >> ./proping.conf
printf "#	-Log files will be created in (/var/log/proping/LOG_FILES.log)									\n" >> ./proping.conf
printf "#																	\n" >> ./proping.conf
printf "#	-You can stop the beeper through the system.											\n" >> ./proping.conf
printf "#																	\n" >> ./proping.conf
printf "#									__________________________________________________________	\n" >> ./proping.conf
printf "#*1)pc_admin_PINGER		=	192.168.2.2			||							||	\n" >> ./proping.conf
printf "#*2)switch_gateway		=	192.168.2.1			||	Free license					||	\n" >> ./proping.conf
printf "#*3)switch_to_router		=	192.168.1.4			||	designer: J-F Bellemare				||	\n" >> ./proping.conf
printf "#*4)switch_to_server		=	192.168.1.3			||							||	\n" >> ./proping.conf
printf "#*5)internal_router1		=	192.168.1.1			||	Thank you to C language community.		||	\n" >> ./proping.conf
printf "#*6)internal_server		=	192.168.1.2			||	For those who leave a small trace in this world.||	\n" >> ./proping.conf
printf "#									||______________________________________________________||	\n" >> ./proping.conf
printf "#*7)external_router1		=	192.168.0.3											\n" >> ./proping.conf
printf "#*8)external_server		=	192.168.0.2											\n" >> ./proping.conf
printf "#*9)prox_firewall_internal	=	192.168.0.1											\n" >> ./proping.conf
printf "#*10)prox_fwall_DMZ		=	192.168.0.4											\n" >> ./proping.conf
printf "#																	\n" >> ./proping.conf
printf "#*11)prox_firewall_wan		=	177.137.206.18											\n" >> ./proping.conf
printf "#*12)vpn_internal		=	178.157.106.19											\n" >> ./proping.conf
printf "#																	\n" >> ./proping.conf
printf "#					===========================									\n" >> ./proping.conf
printf "#						  Router1										\n" >> ./proping.conf
printf "#						 ______											\n" >> ./proping.conf
printf "#						| ---- |			  							\n" >> ./proping.conf
printf "#						||    ||			 							\n" >> ./proping.conf
printf "#						|_----_|										\n" >> ./proping.conf
printf "# SSh or Telnet server			      [5]_\__/_ [7]     									\n" >> ./proping.conf
printf "# and PC_admin_PINGER		    -----------	 	   \										\n" >> ./proping.conf
printf "# ______	      Cisco	   /			    \			Proxy							\n" >> ./proping.conf
printf "#| ---- |	      Switch   [3]/			     \		      Firewall				    -------[12]--[etc.]	\n" >> ./proping.conf
printf "#||    ||		 ---------			      \ 	     -----------	VPN    ___	   /			\n" >> ./proping.conf
printf "#|_----_|		|  _____\ |			       \	    |___|____|__|	Wan  _/	  \_	  /			\n" >> ./proping.conf
printf "# _\__/_ [1]---------[2]| /____ / |	   			\	    |_|_____|___|	   _/	    \____/			\n" >> ./proping.conf
printf "#	\		| \	  |				 \______[9]_|____|_____||[11]_____/		 \___			\n" >> ./proping.conf
printf "#	|		 --------- 		Server Ftp	 	    |_|_____|___|	  \_   Internet     _/			\n" >> ./proping.conf
printf "#	|Telnet		       [4]\		Server_Web	________[10]|____|_____||	    \_	     ______/			\n" >> ./proping.conf
printf "#	|SSH 			   \  	  	 ______	       /	    |  |     |	|	      \_____/				\n" >> ./proping.conf
printf "#	|			    \          	| ---- |      /		     -----------	/		/			\n" >> ./proping.conf
printf "#	\_>>> Wall Broadcast warning \	        ||    ||     /		 				/				\n" >> ./proping.conf
printf "#		at: Android	      \ 	|_----_|    /					   /	    /				\n" >> ./proping.conf
printf "#		at: Ios		       \______[6]_\__/_ [8]/										\n" >> ./proping.conf
printf "#		at: Other Pc														\n" >> ./proping.conf
printf "#																	\n" >> ./proping.conf
printf "#======================================================================================================================================	\n" >> ./proping.conf
printf "# \n" 																	>> ./proping.conf
printf "#------Your configured interfaces.\n" 													>> ./proping.conf
printf "#------Enter *NAME_INTERFACE = ip_address------\n" 											>> ./proping.conf
printf "\n" 																	>> ./proping.conf
printf "\n" 																	>> ./proping.conf
printf "*interface_Wan_vpn = 8.8.8.8\n" 													>> ./proping.conf
printf "\n" 																	>> ./proping.conf
printf "#-------\n" 																>> ./proping.conf
printf "\n" 																	>> ./proping.conf
printf "#By default there is 10 secondes sleeping between pings sequences.\n" 									>> ./proping.conf
printf "#The configurations can be "1s", "5s", "10s" or "20s" secondes between ping sequences.\n" 						>> ./proping.conf
printf "#Enter one of this option variables, if not, this option will be 0s; Warning the network should be saturated.\n" 			>> ./proping.conf
printf "\n" 																	>> ./proping.conf
printf "A)ping_sleep_intervale = 10s\n" 													>> ./proping.conf
printf "\n" 																	>> ./proping.conf
printf "\n" 																	>> ./proping.conf
printf "#By default there is 10m minutes sleeping between the overall routines\n" 								>> ./proping.conf
printf "#The configurations can be "1s", "5m", "10m", "20m", "40m", "80m", "6h", "12h" or "24h", to sleeping between itche overall routine,\n" 	>> ./proping.conf
printf "#Enter one of this option variables, if not, thi option will be 0s; Warning the network should be saturated.\n" 			>> ./proping.conf
printf "\n" 																	>> ./proping.conf
printf "B)sleeping_routine = 10m\n" 														>> ./proping.conf
printf "\n" 																	>> ./proping.conf
printf "\n" 																	>> ./proping.conf
printf "#The verbose mode allows you to follow step by step routine proping on the screen that was used to start the process.\n" 		>> ./proping.conf
printf "#The configurations can be "on" or "off"\n" 												>> ./proping.conf
printf "\n" 																	>> ./proping.conf
printf "C)verbose_mode = on\n" 															>> ./proping.conf
printf "\n" 																		>> ./proping.conf
printf "\n" 																		>> ./proping.conf
printf "#=================================================End of configuration file; /etc/proping/proping.conf=================================\n" 	>> ./proping.conf

fi
#--------------------------------------------------------------------------------------------------------------------------------


        # Loop octet D up to OCTDMAX 255 unless above criteria satisfied
        while [ "$OCTD" -le "$OCTDMAX" ];
        do
                # Print out current IP
                sed -i "1i*interface$INTERFACE_NUM = $OCTA.$OCTB.$OCTC.$OCTD" proping.conf
                # Check if this is the last IP to print
                if [ "$OCTA" -eq "$OCTAHI" ] && \
                   [ "$OCTB" -eq "$OCTBHI" ] && \
                   [ "$OCTC" -eq "$OCTCHI" ] && \
                   [ "$OCTD" -eq "$OCTDHI" ]; then
                        FINISHED=1
                fi
                OCTD=$(( $OCTD + 1 ))

		INTERFACE_NUM=$(( $INTERFACE_NUM + 1 ))
        done

        # Now D loop has completed, set C + 1 and reset D to 0
        OCTC=$(( $OCTC + 1 ))
        OCTD="0"

        # if C is over 255 then set B + 1 and reset C to 0
        if [ "$OCTC" -gt "255" ]; then
                OCTB=$(( $OCTB + 1 ))
                OCTC="0"
        fi

        # If B is over 255 then set A + 1 and reset B to 0
        if [ "$OCTB" -gt "255" ]; then
                OCTA=$(( $OCTA + 1 ))
                OCTB="0"
        fi

        # If A is over 255 for whatever reason then set FINISHED=1
        if [ "$OCTA" -gt "255" ]; then
                FINISHED=1
        fi

echo "The address has been added!"

done

#--------------------------------------------------------------------------------------------------------------------------------



exit 0
