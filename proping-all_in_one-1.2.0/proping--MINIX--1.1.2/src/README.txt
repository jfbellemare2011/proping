#==================EXEMPLE OF CONFIGURATION, Let's see in the configuration file /etc/proping/proping.conf============
#   ██▓███   ██▀███   ▒█████   ██▓███   ██▓ ███▄    █   ▄████ 
#  ▓██░  ██▒▓██ ▒ ██▒▒██▒  ██▒▓██░  ██▒▓██▒ ██ ▀█   █  ██▒ ▀█▒
#  ▓██░ ██▓▒▓██ ░▄█ ▒▒██░  ██▒▓██░ ██▓▒▒██▒▓██  ▀█ ██▒▒██░▄▄▄░
#  ▒██▄█▓▒ ▒▒██▀▀█▄  ▒██   ██░▒██▄█▓▒ ▒░██░▓██▒  ▐▌██▒░▓█  ██▓
#  ▒██▒ ░  ░░██▓ ▒██▒░ ████▓▒░▒██▒ ░  ░░██░▒██░   ▓██░░▒▓███▀▒
#  ▒▓▒░ ░  ░░ ▒▓ ░▒▓░░ ▒░▒░▒░ ▒▓▒░ ░  ░░▓  ░ ▒░   ▒ ▒  ░▒   ▒ 
#  ░▒ ░       ░▒ ░ ▒░  ░ ▒ ▒░ ░▒ ░      ▒ ░░ ░░   ░ ▒░  ░   ░ 
#  ░░         ░░   ░ ░ ░ ░ ▒  ░░        ▒ ░   ░   ░ ░ ░ ░   ░ 
#              ░         ░ ░            ░           ░       ░ 
#   	
#	1-Let's you use the file (# bash./configure.bash), before running the service, do not forget to make an executive with (chmod 755).
#	
#	2-Must use the file (./install), before running the service, do not forget to make an executive with (chmod 755).
#
#	3-If one of the configured interfaces is unreachable, a warning message will be issued on your terminal and by the beeper.
#
#	4-To start the service (/usr/sbin/proping |start|stop|)
#	or
#	-service proping (|stop|start|)
#
#	-Log files will be created in (/var/log/proping/LOG_FILES.log) and configuration file (/etc/proping/proping.conf)
#
#	-You can stop the beeper through the system.
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
# and PC_admin_PINGER		    -----------	 	   \
# ______	      Cisco	   /			    \			Proxy
#| ---- |	      Switch   [3]/			     \		      Firewall				    -------[12]--[etc.]
#||    ||		 ---------			      \ 	     -----------	VPN    ___	   /
#|_----_|		|  _____\ |			       \	    |___|____|__|	Wan  _/	  \_	  /
# _\__/_ [1]---------[2]| /____ / |	   			\	    |_|_____|___|	   _/	    \____/
#	\		| \	  |				 \______[9]_|____|_____||[11]_____/		 \___
#	|		 --------- 		Server Ftp	 	    |_|_____|___|	  \_   Internet     _/
#	|Telnet		       [4]\		Server_Web	________[10]|____|_____||	    \_	     ______/
#	|SSH 			   \  	  	 ______	       /	    |  |     |	|	      \_____/
#	|			    \          	| ---- |      /		     -----------	/		/
#	\_>>> Wall Broadcast warning \	        ||    ||     /		 				/
#		at: Android	      \ 	|_----_|    /					   /	    /	
#		at: Ios		       \______[6]_\__/_ [8]/
#		at: Other Pc
#
#======================================================================================================================================
#
#------Your configured interfaces.
#------Enter *NAME_INTERFACE = ip_address------


*interface_Wan_vpn = 8.8.8.8


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


#=================================================End of configuration file; /etc/proping/proping.conf=================================
