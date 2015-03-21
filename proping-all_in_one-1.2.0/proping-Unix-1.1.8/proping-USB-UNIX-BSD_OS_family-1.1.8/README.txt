#==================EXEMPLE OF CONFIGURATION, Let's see in the configuration file ./proping.conf=============================
#			   ██▓███   ██▀███   ▒█████   ██▓███   ██▓ ███▄    █   ▄████ 
#			  ▓██░  ██▒▓██ ▒ ██▒▒██▒  ██▒▓██░  ██▒▓██▒ ██ ▀█   █  ██▒ ▀█▒
#			  ▓██░ ██▓▒▓██ ░▄█ ▒▒██░  ██▒▓██░ ██▓▒▒██▒▓██  ▀█ ██▒▒██░▄▄▄░
#			  ▒██▄█▓▒ ▒▒██▀▀█▄  ▒██   ██░▒██▄█▓▒ ▒░██░▓██▒  ▐▌██▒░▓█  ██▓
#			  ▒██▒ ░  ░░██▓ ▒██▒░ ████▓▒░▒██▒ ░  ░░██░▒██░   ▓██░░▒▓███▀▒
#			  ▒▓▒░ ░  ░░ ▒▓ ░▒▓░░ ▒░▒░▒░ ▒▓▒░ ░  ░░▓  ░ ▒░   ▒ ▒  ░▒   ▒ 
#			  ░▒ ░       ░▒ ░ ▒░  ░ ▒ ▒░ ░▒ ░      ▒ ░░ ░░   ░ ▒░  ░   ░ 
#			  ░░         ░░   ░ ░ ░ ░ ▒  ░░        ▒ ░   ░   ░ ░ ░ ░   ░ 
#			              ░         ░ ░            ░           ░       ░ 
#	1- Optional; if you want to compile the script, proping. Let's you use the file (./configure.sh), before running the service, do not forget to make an executive with (chmod 755). Let's doing command     # sh ./configure.sh
#
#	-Pass in SuperUser mode and copy the directory proping to a place that allows the execution of the script.
#	 For example within the memory of the device ex; /mnt/usb/proping-usb-linux*/
#
#	-( PROPING-USB-UNIX ) can be executed with a live-cd-UNIX.
#
#	-Must use the file (./proping) before running the service, do not forget to make an executive with (chmod 755).
#
#	-If one of the configured interfaces is unreachable, a warning message will be issued on your terminal and by email.
#
#	-To start the service (./proping |start|stop| ) ; script is a deamon background use stop to finish execution
#
#	-Log files will be created in (./log/LOG_FILES.log)
#
#									
#									__________________________________________________________
#*1)pc_admin_PINGER		=	192.168.2.2			||							||
#*2)switch_gateway		=	192.168.2.1			||	Free license					||
#*3)switch_to_router		=	192.168.1.4			||	designer: J-F Bellemare				||
#*4)switch_to_server		=	192.168.1.3			||							||
#*5)internal_router1		=	192.168.1.1			||	Thank you to C language community.		||
#*6)internal_server		=	192.168.1.2			||	For those who leave a small trace in this world.||
#									||______________________________________________________||
#*7)external_router1		=	192.168.0.3
#*8)external_server		=	192.168.0.2
#*9)prox_firewall_internal	=	192.168.0.1
#*10)prox_fwall_DMZ		=	192.168.0.4
#
#*11)prox_firewall_wan		=	177.137.206.18
#*12)vpn_internal		=	178.157.106.19
#
#					===========================
#						  Router1
#						 ______	
#						| ---- |			  
#						||    ||			 	
#						|_----_|			
# SSh or Telnet server			      [5]_\__/_ [7]     
# and Android_PINGER   		    -----------	 	   \
# ______	      Cisco	   /			    \			Proxy
#| ---- |	      Switch   [3]/			     \		      Firewall		               --[12]--
#||    ||		 ---------			      \ 	     -----------	VPN    ___	   /
#|_----_|		|  _____\ |			       \	    |___|____|__|	Wan  _/	  \_	  /
# _\__/_ [1]---------[2]| /____ / |	   			\	    |_|_____|___|	   _/	    \____/
#	\		| \	  |				 \______[9]_|____|_____||[11]_____/		 \___
#	|adb		 --------- 		Server Ftp	 	    |_|_____|___|	  \_   Internet     _/
#	|Telnet		       [4]\		Server_Web	________[10]|____|_____||	    \_	     ______/
#	|SSH 			   \  	  	 ______	       /	    |  |     |	|	      \_____/
#	|			    \          	| ---- |      /		     -----------	/		/
#	\_>>> Broadcast warning      \	        ||    ||     /		 				/
#		at: Android	      \ 	|_----_|    /					   /	    /	
#		at: Ios		       \______[6]_\__/_ [8]/
#		at: Other Pc
#
#======================================================================================================================================
#
#------Your configured interfaces.
#------Enter *NAME_INTERFACE = ip_address------


*interface_Wan_vpn = 4.4.4.4


#-------

#By default there is 10 secondes sleeping between pings sequences.
#The configurations can be "1s", "5s", "10s" or "20s" secondes between ping sequences.
#Enter one of this option variables, if not, this option will be 0s; Warning the network should be saturated.

A)ping_sleep_intervale = 10s


#By default there is 10m minutes sleeping between the overall routines
#The configurations can be "1s", "5m", "10m", "20m", "40m", "80m", "6h", "12h" or "24h", to sleeping between itche overall routine,
#Enter one of this option variables, if not, thi option will be 0s; Warning the network should be saturated.

B)sleeping_routine = 10m


#The verbose mode allows you to follow step by step routine proping on the screen that was used to start the process.
#The configurations can be "on" or "off"

C)verbose_mode = on

#The sendmail  mode, "on" "off", allows to start or stop sending warning mail of telecommunication network problems tcp/ip, by the processus ( /usr/libexec/sendmail/sendmail ).
#The configurations can be "on" or , by default, "off"
#For sendmail_TO, sendmail_FROM and sendmail_SUBJECT options, they are explained below.
#Note; It is important to remove the spacers in the labels seen below !!!

D)sendmail_mode = off
E)sendmail_to = jf@localhost,user2@localhost,user3@localhost
F)sendmail_from = proping_machine1
G)sendmail_subject = The_communication_network_tcp/ip_is_interrupted

#Setting the frequency warning sending mail. Only, if there is a break in the network of telecommunication tcp / ip.
#frequency sending of warning mail, can be; "5m", "10m", "20m", "40m", "80m", "6h", "12h" or "24h"--By default this is 5m

H)frequency_of_sending_mail = 5m

#=================================================End of configuration file; /etc/proping/proping.conf=================================
