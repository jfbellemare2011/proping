#!/bin/bash
#
#-------------------------------------------zonefile_TO_proping_converter------------------------------------------------------
#
# Author:   jfbellemare2011 v1.0
#

FILE_IN=(`echo "$1"`)

        if [ -z "$FILE_IN" ]; then
                echo "Usage: [ give me a ( .zone ) file !]"
                exit 1
        fi

#--------------------------------------------------------------------------------------------------------------------------------


echo "" > proping.conf
printf "#==================EXAMPLE OF CONFIGURATION, Let's see in the configuration file /etc/proping/proping.conf=============================	\n" >> ./proping.conf
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
#---------------

# zone_file to ./proping.conf

VAR=(`grep -E 'IN.*A' $FILE_IN | grep -v 'CNAME\|AAAA\|SOA' | awk '{$1000="*_";$1001="="; print $1000,$1,$1001,$4 }' >> ./proping.conf `)

#---------------
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

#--------------------------------------------------------------------------------------------------------------------------------


echo "The address DNS of .zone file ( $FILE_IN ) has been converted to (./proping.conf)!"


#--------------------------------------------------------------------------------------------------------------------------------


exit 0
