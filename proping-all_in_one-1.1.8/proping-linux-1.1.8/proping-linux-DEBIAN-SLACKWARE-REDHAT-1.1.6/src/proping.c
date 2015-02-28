/***
 *		     ██▓███   ██▀███   ▒█████   ██▓███   ██▓ ███▄    █   ▄████ 
 *		    ▓██░  ██▒▓██ ▒ ██▒▒██▒  ██▒▓██░  ██▒▓██▒ ██ ▀█   █  ██▒ ▀█▒
 *		    ▓██░ ██▓▒▓██ ░▄█ ▒▒██░  ██▒▓██░ ██▓▒▒██▒▓██  ▀█ ██▒▒██░▄▄▄░
 *		    ▒██▄█▓▒ ▒▒██▀▀█▄  ▒██   ██░▒██▄█▓▒ ▒░██░▓██▒  ▐▌██▒░▓█  ██▓
 *		    ▒██▒ ░  ░░██▓ ▒██▒░ ████▓▒░▒██▒ ░  ░░██░▒██░   ▓██░░▒▓███▀▒
 *		    ▒▓▒░ ░  ░░ ▒▓ ░▒▓░░ ▒░▒░▒░ ▒▓▒░ ░  ░░▓  ░ ▒░   ▒ ▒  ░▒   ▒ 
 *		    ░▒ ░       ░▒ ░ ▒░  ░ ▒ ▒░ ░▒ ░      ▒ ░░ ░░   ░ ▒░  ░   ░ 
 *		    ░░         ░░   ░ ░ ░ ░ ▒  ░░        ▒ ░   ░   ░ ░ ░ ░   ░ 
 *		                ░         ░ ░            ░           ░       ░ 
 *		                                                               
 */

/* Copyright (C) 1997, 1999, 2000, 2001, 2004 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#ifndef _ARPA_INET_H
#define	_ARPA_INET_H	1

#include <features.h>
#include <netinet/in.h>		/* To define `struct in_addr'.  */

/* Type for length arguments in socket calls.  */
#ifndef __socklen_t_defined
typedef __socklen_t socklen_t;
# define __socklen_t_defined
#endif

__BEGIN_DECLS

/* Convert Internet host address from numbers-and-dots notation in CP
   into binary data in network byte order.  */
//JF modification *//   extern in_addr_t inet_addr (__const char *__cp) __THROW;

/* Return the local host address part of the Internet address in IN.  */
extern in_addr_t inet_lnaof (struct in_addr __in) __THROW;

/* Make Internet host address in network byte order by combining the
   network number NET with the local address HOST.  */
extern struct in_addr inet_makeaddr (in_addr_t __net, in_addr_t __host)
     __THROW;

/* Return network number part of the Internet address IN.  */
extern in_addr_t inet_netof (struct in_addr __in) __THROW;

/* Extract the network number in network byte order from the address
   in numbers-and-dots natation starting at CP.  */
extern in_addr_t inet_network (__const char *__cp) __THROW;

/* Convert Internet number in IN to ASCII representation.  The return value
   is a pointer to an internal array containing the string.  */



// jf modificaton */  extern char *inet_ntoa (struct in_addr __in) __THROW;



/* Convert from presentation format of an Internet number in buffer
   starting at CP to the binary network format and store result for
   interface type AF in buffer starting at BUF.  */
extern int inet_pton (int __af, __const char *__restrict __cp,
		      void *__restrict __buf) __THROW;

/* Convert a Internet address in binary network format for interface
   type AF in buffer starting at CP to presentation form and place
   result in buffer of length LEN astarting at BUF.  */
extern __const char *inet_ntop (int __af, __const void *__restrict __cp,
				char *__restrict __buf, socklen_t __len)
     __THROW;


/* The following functions are not part of XNS 5.2.  */
#ifdef __USE_MISC
/* Convert Internet host address from numbers-and-dots notation in CP
   into binary data and store the result in the structure INP.  */
extern int inet_aton (__const char *__cp, struct in_addr *__inp) __THROW;

/* Format a network number NET into presentation format and place result
   in buffer starting at BUF with length of LEN bytes.  */
extern char *inet_neta (in_addr_t __net, char *__buf, size_t __len) __THROW;

/* Convert network number for interface type AF in buffer starting at
   CP to presentation format.  The result will specifiy BITS bits of
   the number.  */
extern char *inet_net_ntop (int __af, __const void *__cp, int __bits,
			    char *__buf, size_t __len) __THROW;

/* Convert network number for interface type AF from presentation in
   buffer starting at CP to network format and store result int
   buffer starting at BUF of size LEN.  */
extern int inet_net_pton (int __af, __const char *__cp,
			  void *__buf, size_t __len) __THROW;

/* Convert ASCII representation in hexadecimal form of the Internet
   address to binary form and place result in buffer of length LEN
   starting at BUF.  */
extern unsigned int inet_nsap_addr (__const char *__cp,
				    unsigned char *__buf, int __len) __THROW;

/* Convert internet address in binary form in LEN bytes starting at CP
   a presentation form and place result in BUF.  */
extern char *inet_nsap_ntoa (int __len, __const unsigned char *__cp, char *__buf) __THROW;
#endif

__END_DECLS

#endif /* arpa/inet.h */


/************END OF INET.H MODIFIED*******************************************************************************/
/*****************************************************************************************************************/





/************BEGIN OF PROPING***********************************************************************************/

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include <time.h>
//#include <pthread> //Not on Linux just for Unix

#include <sys/param.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/signal.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
//#include "inet.h" // inclu on the top
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

char *option_argument;
char *trace_ip4;
int ret_ping_error;


char flag_word = 0;
char flag_ipdown = 0;
char verbose = 1;

char *option_name;
char *option_argument;
int task_c();

int flag_traceroute_start = 1;

const char *log_fpname;

/********************For ping.c bluffing and recovery****************/


char *bool_ping;
char *bool_finish;
int ping_error_disconnected;

/********************************************************************/

/***external variable of function file_conf_to_array*******/
char **words;
int j;
int max_arr;

/**************************************MAIN()*******************************************************************************/

int main (int argc, char **argv)
{

//-----------Start, stop-----------------------
  char arg_restart[] = "restart";
  char arg_start[] = "start";
  char arg_stop[] = "stop";
  char arg_shellstart[] = "shellstart"; // It use the shell to start the process in this way, it can be stated in background easily

  #define KILLPROCESSUS "ps -e | grep proping | awk '{print $1}'| xargs kill -15"
  #define SHELLSTART "/usr/sbin/proping shellstart &"

	  if (argc == 1){		//Important; this is a way to do a restart by the init.d/service for redhat
	    system(SHELLSTART);
	    sleep(1);
	    exit(0);

	  }else if (argc != 2){
	    fprintf(stdout,"Usage : %s [start|stop]\n",*argv);
	    return -1;
	  
	  }else if (strcmp(argv[1],arg_restart)==0){
		printf("[restart] is not available, please use [start|stop]\n");
		exit(0);

	  }else if (strcmp(argv[1],arg_stop)==0){
	      puts (argv[1]);
	
		system(KILLPROCESSUS);
		exit(0);
	
	  }else if (strcmp(argv[1],arg_start)==0){
	      puts (argv[1]);

		system(SHELLSTART);
		sleep(1);
		exit(0);

	  }else if (strcmp(argv[1],arg_shellstart)==0){


//------------------------------------------------------

char case_name;

char sleep_ping[15];
char sleep_routine[15];
char ping_sleep_decimal = 0;
int sleep_routine_decimal= 0;

char option_verbose[15];

/*****sequencial loop of processus*********/

for(;;)
{
flag_word = 0;
flag_ipdown = 0;


/*******Reading array of *.conf line by line and put it in array function*************/

file_conf_to_array();		


/*------------------------------call sub_function to ping---------------------------------------------------------------------------------*/
int i0 = 0;
for (i0 = max_arr; i0 >= 0 ; i0--)  // Not equal for max_arr because refer at (j) of file_conf_to_array();
{
//printf("%s\n", option_name);
option_name = strtok(words[i0], "=\t\n\r" ) ;  // the spacer is get out

if(option_name != NULL && option_name[0] != '#' && option_name[0] == '*')
{	
/*------------------configure ping----------------------------*/
option_argument = strtok( NULL, " \t\n\r" ) ;

//printf("%s\n", option_name);	
//printf("%s\n", option_argument);	
//system("wall test1");



/*******starting of sub_functions*******/

ping_error_disconnected = 0;
trace_ip4 = NULL;

pinger_proping();

compare_ip_arguments();

flag_traceroute_start = 1;
}


/*----------------------------for loop priority0: find configuration options from array of file.conf----------------------------*/

//option_name = strtok(words[i0], "=\t\n\r" ) ;  // the spacer is get out

/*------------------configure option arguments -------------------------*/
if(option_name != NULL && option_name[0] != '#' && option_name[0] != '*'){

//printf("%s\n", option_name);

option_argument = strtok( NULL, " \t\n\r" ) ;


//printf("%s\n",option_argument);
case_name = option_name[0];

switch(case_name)
{
case 'A' :
//----------------
//if(option_name[0] != 'p' && option_name[19] != 'e'){
strcpy(sleep_ping, option_argument);

if(strcmp(sleep_ping,"1s")==0){
ping_sleep_decimal = 1;
}else if(strcmp(sleep_ping,"5s")==0){
ping_sleep_decimal = 5;
}else if(strcmp(sleep_ping,"10s")==0){
ping_sleep_decimal = 10;
}else if(strcmp(sleep_ping,"20s")==0){
ping_sleep_decimal = 20;
}
//----------------
case 'B' :
strcpy(sleep_routine, option_argument);

if(strcmp(sleep_routine,"1s")==0){
sleep_routine_decimal = 1;
}else if(strcmp(sleep_routine,"5m")==0){
sleep_routine_decimal = 300;
}else if(strcmp(sleep_routine,"10m")==0){
sleep_routine_decimal = 600;
}else if(strcmp(sleep_routine,"20m")==0){
sleep_routine_decimal = 1200;
}else if(strcmp(sleep_routine,"40m")==0){
sleep_routine_decimal = 2400;
}else if(strcmp(sleep_routine,"80m")==0){
sleep_routine_decimal = 4800;
}else if(strcmp(sleep_routine,"6h")==0){
sleep_routine_decimal = 21600;
}else if(strcmp(sleep_routine,"12h")==0){
sleep_routine_decimal = 43200;
}else if(strcmp(sleep_routine,"24h")==0){
sleep_routine_decimal = 86400;
}
case 'C' :
strcpy(option_verbose, option_argument);
if(strcmp(option_verbose,"on")==0){
verbose = 1;
}else if(strcmp(option_verbose,"off")==0){
verbose = 0;
}
case 'D' :

break;
case 'E' :

break;

}
// printf("Your grade is  %c\n", grade );
}
/*-----------------------------------------------------*/

if(option_name != NULL && option_name[0] != '#' && option_name[0] == '*'){
if(verbose == 1){
printf("\n!!! Sleeping %d secondes !!!\n", ping_sleep_decimal);
fprintf(stderr,"\n===================================================\n");
}
sleep(ping_sleep_decimal);  //Time between pings	
}
}
flag_word = 0;
flag_ipdown = 0;
if(verbose == 1){
printf("\n!!! Sleeping %d secondes !!! END OF LOOP  \n", sleep_routine_decimal);
}
sleep(sleep_routine_decimal);  //Time between the overall looping
}

//-------End of if start------
}
//----End of main()
return 0;
}


/*****************************function File.conf string to array******************************/

int i = 0;

int file_conf_to_array(void)
{

int lines_allocated = 130;
int max_line_len = 256;

/* Allocate lines of text */
words = (char **)malloc(sizeof(char*)*lines_allocated);

if (words==NULL)
{
//fprintf(stderr,"Out of memory (1).\n");
exit(1);
}

FILE *fp = fopen("/etc/proping/proping.conf", "r");
if (fp == NULL)
{
//fprintf(stderr,"Error opening file.\n");
exit(2);
}

int i;
for (i=0;1;i++)
{
int j;

/* Have we gone over our line allocation? */
if (i >= lines_allocated)
{
int new_size;

/* Double our allocation and re-allocate */
new_size = lines_allocated*2;
words = (char **)realloc(words,sizeof(char*)*new_size);
if (words==NULL)
{
//fprintf(stderr,"Out of memory.\n");
exit(3);
}
lines_allocated = new_size;
}
/* Allocate space for the next line */
words[i] = malloc(max_line_len);
if (words[i]==NULL)
{
//fprintf(stderr,"Out of memory (3).\n");
exit(4);
}
if (fgets(words[i],max_line_len-1,fp)==NULL)
break;

/* Get rid of CR or LF at end of line */
for (j=strlen(words[i])/*-1*/;j>=0 && (words[i][j]=='\n' || words[i][j]=='\r');j--)
;
words[i][j]='\0';
}


//printf("=========Thoses interfaces will be pinged.==================================\n");
for(j = 0; j < i; j++)

if(verbose == 1){
printf("%s", words[j]);
}

max_arr = j;

/* Good practice to free memory */
//    for (;i>=0;i--)
//        free(words[i]);
//    free(words);

return 0;
}


/*********************function hasching readfile********************************/

int pinger_proping(void)
{



/*****concatenate command for system(ping)****/

//#define PING_COMMAND_STRCAT1 "ping -c 3 "
//#define PING_COMMAND_STRCAT2 " > /dev/null"
//#define PING_COMMAND_STRCAT2 " -c 3"


#define TRACE_COMMAND_STRCAT2 " > ./tmptrace.txt"

//char ping_command_strcat[256] = "";


//strcat(ping_command_strcat, PING_COMMAND_STRCAT1); //
//printf("%s\n", option_argument);
//strcat(ping_command_strcat, option_argument); //---Concatenate for ping command
//strcat(ping_command_strcat, PING_COMMAND_STRCAT2);
//printf("%s\n", ping_command_strcat);

/**************ping*************************************/

//--------declaration for DATE-------------
time_t now = time(NULL);
struct tm * tm = localtime(&now);
//fprint("%s\n", ctime(&now))
//-------

if(verbose == 1){
printf("\nPinging of interfaces; %s %s at %s",option_name, option_argument, ctime(&now));
}


ret_ping_error = main_ping(/*argc_ping, argv_ping*/);


sleep(1);

if(bool_ping == NULL){
strcpy(bool_ping,"1");
}

if(strcmp(bool_ping,"0")==0) {
	if(verbose == 1){
	printf("\n OK! \n", option_argument);
	}

flag_word = 0;
}else{
flag_ipdown = 0;

//---------------------------for datetime and log files------------------------------------------------

//--------------catching date and time------------------


time_t now = time(NULL);
struct tm * tm = localtime(&now);

//--Exemple--
/* Date preformated */
//fprintf(stderr, "Date = %s\n", ctime(&now));

/* Use tm_year, tm_mday, tm_month, tm_hour, tm_min, tm_sec ou strftime: */
//char date[64];
//strftime(date, sizeof date, "%A, %B %d, %Y %H:%M:%S", tm);
//fprintf(stderr, "%s", date);
//-----------

char file_date_log[64];
char insidefile_date_log[64]; //external declaration
strftime(file_date_log, sizeof file_date_log, "proping_%B_%Y.log", tm);
strftime(insidefile_date_log, sizeof insidefile_date_log, "%A, %B %d, %Y %H:%M:%S", tm);

//---------------------Creating log_fp about date--------------------

//---Create a dating log path file--------
#define PATH_LOG_FILE "/var/log/proping/"
char file_log_path[256] = "";

strcat(file_log_path, PATH_LOG_FILE);
strcat(file_log_path, file_date_log);

//printf("%s",file_log_path);
//---
//---------
FILE *log_fp;
int log_exists;
log_fpname = file_log_path;

/*first check if the log_fp exists...*/
log_fp=fopen(log_fpname,"r");

//---------------------
//-----------
char propingwall[256] = "";
strcat(propingwall,"touch /tmp/propingwall.txt");
system(propingwall);

char wall_commandlog_strcat[256] = "";
strcat(wall_commandlog_strcat, "echo " );
strcat(wall_commandlog_strcat, insidefile_date_log);
strcat(wall_commandlog_strcat, "-----");
strcat(wall_commandlog_strcat, "!!!Warning !!! Interface Not reached ");
strcat(wall_commandlog_strcat, option_name);
strcat(wall_commandlog_strcat, option_argument);
//strcat(wall_commandlog_strcat, " > /tmp/propingwall.txt");
system(wall_commandlog_strcat);

char propingwall2[256] = "" ;
strcat(propingwall2, "wall /tmp/propingwall.txt");
//system(propingwall2);
//-----------


printf("Not reached!!! \007\n\n");


if(ret_ping_error == 2){

	fprintf(stderr,"\n !!! unresolved hostname to ipv4; (/etc/hosts file) or (DNS services) are empty or unreachable !!!\n");

	} else if(ping_error_disconnected == -3){ 

	printf("\n !!! Pinger machine network devices are down or the cables are disconnected  !!!\n");

		} else if(strcmp(bool_ping,"1")==0) {

		printf("Please wait for a maximum of 45s, the time to finish traceroute analysis!!!\n\n\n");
		}


//-----------
char echo_commandlog_strcat[256] = "";
strcat(echo_commandlog_strcat, "echo " );
strcat(echo_commandlog_strcat, insidefile_date_log);
strcat(echo_commandlog_strcat, "-----");

if(ret_ping_error == 2){

	  strcat(echo_commandlog_strcat, " !!! unresolved hostname to ipv4 - hosts file or DNS services are empty or unreachable !!! ");

	} else if(ping_error_disconnected == -3){

	strcat(echo_commandlog_strcat, "!!! Pinger machine network devices are down or the cables are disconnected  !!!");

		} else if(strcmp(bool_ping,"1")==0) {

			strcat(echo_commandlog_strcat, "!!!Warning !!! Interface Not reached!!! : ");
			strcat(echo_commandlog_strcat, option_name);
			strcat(echo_commandlog_strcat, option_argument);
		}

strcat(echo_commandlog_strcat, " >> ");
strcat(echo_commandlog_strcat, log_fpname);
//printf("\n\n%s\n\n",echo_commandlog_strcat );
system(echo_commandlog_strcat);
//-----------


//-----------------------------------------------------------------------------------------------

flag_word = 1;


/**************************FUNCTION thread; tracereroute*******************/

				//printf("\n\n%s\n\n",argv_trace);

	if((ret_ping_error == 2) || (ping_error_disconnected == -3)){
		//do Nothing to rest in true logical
	}else{

			int p = 0;
			void *task_d (){

				for ( i=0; i < 45 ; ++i){

				p++;
				  sleep(1);
				   if(i == 45){
				    int pthread_cancel (pthread_t task_c);
				     void pthread_exit ();	
				   }
				}	
			}//end of thread task_d
			/***********************/

			     if(p == 0){
					pthread_t tc;
					pthread_t td;
					flag_traceroute_start = 0;
					pthread_create (&tc, NULL, task_c, NULL);
				   	pthread_create (&td, NULL, task_d, NULL);
				     }
		
					sleep(46);
					int pthread_cancel (pthread_t task_c);
					int pthread_cancel (pthread_t task_d);
				     
	}

/************************************************************************************************/

//system(trace_command_strcat);
//strcat(trace_command_strcat, TRACE_COMMAND_STRCAT2);
//system(trace_command_strcat);

}

return (0);
}

/**********function compare_ip_arguments() argument of ip address************************************************************/

int compare_ip_arguments(void)  
{
    if (flag_traceroute_start == 0){ //Note; because threading, this function is starting in same time of last thread
	sleep(46);
    }

//--------------creating log directory /var/log/proping------------------

#define MY_MASK 0755	//mkdir function mask
int code = mkdir("/var/log/proping", MY_MASK);


if (code == 0) {
	if(verbose == 1){
	printf("Log repertory has been created; /var/log/proping\n"); 
	}
} else {
//printf("Log repertory already exist\n"); 
}


//--------------catching date and time------------------


time_t now = time(NULL);
struct tm * tm = localtime(&now);

//--Exemple--
/* Date preformated */
//fprintf(stderr, "Date = %s\n", ctime(&now));

/* Use tm_year, tm_mday, tm_month, tm_hour, tm_min, tm_sec ou strftime: */
//char date[64];
//strftime(date, sizeof date, "%A, %B %d, %Y %H:%M:%S", tm);
//fprintf(stderr, "%s", date);
//-----------

char file_date_log[64];
char insidefile_date_log[64]; //external declaration
strftime(file_date_log, sizeof file_date_log, "proping_%B_%Y.log", tm);
strftime(insidefile_date_log, sizeof insidefile_date_log, "%A, %B %d, %Y %H:%M:%S", tm);

//---------------------Creating log_fp about date--------------------

//---Create a dating log path file--------
#define PATH_LOG_FILE "/var/log/proping/"
char file_log_path[256] = "";

strcat(file_log_path, PATH_LOG_FILE);
strcat(file_log_path, file_date_log);

//printf("%s",file_log_path);
//---
//---------
FILE *log_fp;
int log_exists;
const char * log_fpname = file_log_path;

/*first check if the log_fp exists...*/
log_fp=fopen(log_fpname,"r");

if (log_fp==NULL){
log_exists=0;
}else {
log_exists=1; fclose(log_fp);
}
/*...then open it in the appropriate way*/
if (log_exists==1)
{
//----------Concerve file open until the end of the loop----
//printf("log_fp exists!\n");
//log_fp=fopen(log_fpname,"a");

//fprintf(log_fp, "%s %s %s %d", "We", "are", "in", 2014); //It writes at the end of file option "a"
//fclose(log_fp);
//--------       
}
else
{
//printf("log_fp does not exist!\n");
log_fp=fopen(log_fpname,"w+b");
fclose(log_fp);
}
//-----------------------------------------------------------------------------------

char i = 0;
char h = 0;
char k = 0;

//--------------------------------------------------------


if(flag_word == 0){

} else if(flag_ipdown == 0){


//printf("String %d : %s\n",z+1,(*ptr_arr_downs)[z]);


char wall_command_strcat[256] = "";
strcat(wall_command_strcat, "echo !!!Warning!!! communication between " ); //---Concatenate for wall command

	if( (trace_ip4 != NULL) && (ret_ping_error != 2) && (ping_error_disconnected != -3) ){

		strcat(wall_command_strcat, trace_ip4);
	}else{
		strcat(wall_command_strcat,"!!!! UNKNOW DISCONNECTED DEVICE !!!");
	}
strcat(wall_command_strcat, " to interface ");
strcat(wall_command_strcat, option_name); //---
strcat(wall_command_strcat, option_argument);
strcat(wall_command_strcat, ", is stopped!!! You have to see if the interface is existing before searching the network problem, refer to the configuration file");
//strcat(wall_command_strcat, " > /tmp/propingwall.txt");
system(wall_command_strcat);

char propingwall[256] = "";
//strcat(propingwall, " wall /tmp/propingwall.txt");



if((trace_ip4 != NULL)&&(strcmp(option_argument,trace_ip4)==0)){

printf("\n!!!Warning !!! There are on the network, intermittent communications to join %s at %s. \n", option_argument, ctime(&now));

char echo_commandlog_strcat[256] = "";
strcat(echo_commandlog_strcat, "echo " );
strcat(echo_commandlog_strcat, insidefile_date_log);
strcat(echo_commandlog_strcat, "-----");
strcat(echo_commandlog_strcat, "!!!Warning !!! There are on the network, intermittent communications to join: ");
strcat(echo_commandlog_strcat, option_argument);
strcat(echo_commandlog_strcat, " >> ");
strcat(echo_commandlog_strcat, log_fpname);
//printf("\n\n%s\n\n",echo_commandlog_strcat );
system(echo_commandlog_strcat);


}else if(/* (trace_ip4 == NULL) || (strcmp(option_argument,trace_ip4)!=0) || (ping_error_disconnected == -3) || */(flag_ipdown == 0) ){

if(verbose == 1){
printf("\n\n\n=========warning!!!=========warning!!!=========warning!!!=========\n");
printf("   Down!!!							  	\n");
printf("		Down!!!				Down!!!		  	\n");
printf("		 		Down!!!				        \n");
}
//-------------------------------------------------------------------------------------
system(propingwall);



//--------------catching date and time------------------


time_t now = time(NULL);
struct tm * tm = localtime(&now);

//--Exemple--
/* Date preformated */
//fprintf(stderr, "Date = %s\n", ctime(&now));

/* Use tm_year, tm_mday, tm_month, tm_hour, tm_min, tm_sec ou strftime: */
//char date[64];
//strftime(date, sizeof date, "%A, %B %d, %Y %H:%M:%S", tm);
//fprintf(stderr, "%s", date);
//-----------

char file_date_log[64];
char insidefile_date_log[64]; //external declaration
strftime(file_date_log, sizeof file_date_log, "proping_%B_%Y.log", tm);
strftime(insidefile_date_log, sizeof insidefile_date_log, "%A, %B %d, %Y %H:%M:%S", tm);

//---------------------Creating log_fp about date--------------------

//---Create a dating log path file--------
#define PATH_LOG_FILE "/var/log/proping/"
char file_log_path[256] = "";

strcat(file_log_path, PATH_LOG_FILE);
strcat(file_log_path, file_date_log);

//printf("%s",file_log_path);
//---
//---------
FILE *log_fp;
int log_exists;
log_fpname = file_log_path;


//-------------
char wall_command_strcat[256] = "";
strcat(wall_command_strcat, "echo !!!Warning!!! communication between " ); //---Concatenate for wall command

	if ( (trace_ip4 != NULL) && (ret_ping_error != 2) && (ping_error_disconnected != -3) ){
		strcat(wall_command_strcat, trace_ip4);
	}else{
		strcat(wall_command_strcat,"!!!! UNKNOW DISCONNECTED DEVICE !!!");
	}

strcat(wall_command_strcat, " to interface ");
strcat(wall_command_strcat, option_name); //---
strcat(wall_command_strcat, option_argument);
strcat(wall_command_strcat, ", is stopped!!! You have to see if the interface is existing before searching the network problem, refer to the configuration file");

//#define ECHO "echo "
char echo_commandlog_strcat[256] = "";

strcat(echo_commandlog_strcat, "echo " );
strcat(echo_commandlog_strcat, insidefile_date_log);
strcat(echo_commandlog_strcat, "-----");
strcat(echo_commandlog_strcat, wall_command_strcat);
strcat(echo_commandlog_strcat, " >> ");
strcat(echo_commandlog_strcat, log_fpname);
//printf("\n\n%s\n\n",echo_commandlog_strcat );
system(echo_commandlog_strcat);
//------------


flag_ipdown = 1;
sleep(3);

#define BEEP "echo beep!!! \007"
for (h=0; h<=7; h++) {

system(BEEP);
sleep(2);
}

for (k=0; k<=7; k++) {
system(BEEP);
sleep(1);
}





//-------------------------------------------------------------------------------------

flag_ipdown = 1;
}
}

return(0);
}

/************END OF PROPING**********************************************************************************/
/*****************************************************************************************************************/



/************Begin of pinger**********************************************************************************/
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Mike Muuss.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

char copyright[] =
  "@(#) Copyright (c) 1989 The Regents of the University of California.\n"
  "All rights reserved.\n";
/*
 * From: @(#)ping.c	5.9 (Berkeley) 5/12/91
 */
char rcsid[] = "$Id: ping.c,v 1.22 1997/06/08 19:39:47 dholland Exp $";
char pkg[] = "netkit-base-0.10";

/*
 *			P I N G . C
 *
 * Using the InterNet Control Message Protocol (ICMP) "ECHO" facility,
 * measure round-trip-delays and packet loss across network paths.
 *
 * Author -
 *	Mike Muuss
 *	U. S. Army Ballistic Research Laboratory
 *	December, 1983
 *
 * Status -
 *	Public Domain.  Distribution Unlimited.
 * Bugs -
 *	More statistics could always be gathered.
 *	This program has to run SUID to ROOT to access the ICMP socket.
 */
/*
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/signal.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
//#include "inet.h" // inclu on the top
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
*/
/*
 * Note: on some systems dropping root makes the process dumpable or
 * traceable. In that case if you enable dropping root and someone
 * traces ping, they get control of a raw socket and can start
 * spoofing whatever packets they like. SO BE CAREFUL.
 */
#ifdef __linux__
#define SAFE_TO_DROP_ROOT
#endif

#if defined(__GLIBC__) && (__GLIBC__ >= 2)
#define icmphdr			icmp
				/**************************************************/
					//JF this defines are inclu on ip_icmp.h

/*#define ICMP_DEST_UNREACH	ICMP_UNREACH			
#define ICMP_NET_UNREACH	ICMP_UNREACH_NET
#define ICMP_HOST_UNREACH	ICMP_UNREACH_HOST
#define ICMP_PORT_UNREACH	ICMP_UNREACH_PORT
#define ICMP_PROT_UNREACH	ICMP_UNREACH_PROTOCOL
#define ICMP_FRAG_NEEDED	ICMP_UNREACH_NEEDFRAG
#define ICMP_SR_FAILED		ICMP_UNREACH_SRCFAIL
#define ICMP_NET_UNKNOWN	ICMP_UNREACH_NET_UNKNOWN
#define ICMP_HOST_UNKNOWN	ICMP_UNREACH_HOST_UNKNOWN
#define ICMP_HOST_ISOLATED	ICMP_UNREACH_ISOLATED
#define ICMP_NET_UNR_TOS	ICMP_UNREACH_TOSNET
#define ICMP_HOST_UNR_TOS	ICMP_UNREACH_TOSHOST
#define ICMP_SOURCE_QUENCH	ICMP_SOURCEQUENCH
#define ICMP_REDIR_NET		ICMP_REDIRECT_NET
#define ICMP_REDIR_HOST		ICMP_REDIRECT_HOST
#define ICMP_REDIR_NETTOS	ICMP_REDIRECT_TOSNET
#define ICMP_REDIR_HOSTTOS	ICMP_REDIRECT_TOSHOST
#define ICMP_TIME_EXCEEDED	ICMP_TIMXCEED
#define ICMP_EXC_TTL		ICMP_TIMXCEED_INTRANS
#define ICMP_EXC_FRAGTIME	ICMP_TIMXCEED_REASS
#define	ICMP_PARAMETERPROB	ICMP_PARAMPROB
#define ICMP_TIMESTAMP		ICMP_TSTAMP
#define ICMP_TIMESTAMPREPLY	ICMP_TSTAMPREPLY
#define ICMP_INFO_REQUEST	ICMP_IREQ
#define ICMP_INFO_REPLY		ICMP_IREQREPLY*/
				/**************************************************/

#else
#define ICMP_MINLEN	28
#define inet_ntoa(x) inet_ntoa(*((struct in_addr *)&(x)))
#endif


#define	DEFDATALEN	(64 - 8)	/* default data length */
#define	MAXIPLEN	60
#define	MAXICMPLEN	76
#define	MAXPACKET	(65536 - 60 - 8)/* max packet size */
#define	MAXWAIT		10		/* max seconds to wait for response */
#define	NROUTES		9		/* number of record route slots */

#define	A(bit)		rcvd_tbl[(bit)>>3]	/* identify byte in array */
#define	B(bit)		(1 << ((bit) & 0x07))	/* identify bit in byte */
#define	SET(bit)	(A(bit) |= B(bit))
#define	CLR(bit)	(A(bit) &= (~B(bit)))
#define	TST(bit)	(A(bit) & B(bit))

/* various options */
int options;
#define	F_FLOOD		0x001
#define	F_INTERVAL	0x002
#define	F_NUMERIC	0x004
#define	F_PINGFILLED	0x008
#define	F_QUIET		0x010
#define	F_RROUTE	0x020
#define	F_SO_DEBUG	0x040
#define	F_SO_DONTROUTE	0x080
#define	F_VERBOSE	0x100

/* multicast options */
int moptions;
#define MULTICAST_NOLOOP	0x001
#define MULTICAST_TTL		0x002
#define MULTICAST_IF		0x004

/*
 * MAX_DUP_CHK is the number of bits in received table, i.e. the maximum
 * number of received sequence numbers we can keep track of.  Change 128
 * to 8192 for complete accuracy...
 */
#define	MAX_DUP_CHK	(8 * 128)
int mx_dup_ck = MAX_DUP_CHK;
char rcvd_tbl[MAX_DUP_CHK / 8];

struct sockaddr whereto;	/* who to ping */
int datalen = DEFDATALEN;
int s;				/* socket file descriptor */
u_char outpack[MAXPACKET];
char BSPACE = '\b';		/* characters written for flood */
char DOT = '.';
static char *hostname;
static int ident;		/* process id to identify our packets */

/* counters */
static long npackets = 3; /* JF */		/* max packets to transmit  */
static long nreceived;		/* # of packets we got back */
static long nrepeats;		/* number of duplicates */
static long ntransmitted;	/* sequence # for outbound packets = #sent */
static int interval = 1;	/* interval between packets */

/* timing */
static int timing;		/* flag to do timing */
static long tmin = LONG_MAX;	/* minimum round trip time */
static long tmax = 0;		/* maximum round trip time */
static u_long tsum;		/* sum of all times, for doing average */

/* protos */
static char *pr_addr(u_long);
static int in_cksum_ping(u_short *addr, int len);
static void catcher(/*int*/);
//static void finish(int ignore);
/*static void*/int pinger(void);
static void fill(void *bp, char *patp);
static void usage_ping(void);
static void pr_pack(char *buf, int cc, struct sockaddr_in *from);
static void tvsub_ping(struct timeval *out, struct timeval *in);
static void pr_icmph(struct icmphdr *icp);
static void pr_retip(struct iphdr *ip);


int main_ping(/*int argc, char *argv[3]*/){

//printf("\n %d **********************\n" ,nreceived );
		/******JF*******/

bool_ping = "1";
bool_finish = "0";
ntransmitted = 0;
nreceived = 0;

int argc;
argc = 2;

char *argv[3];
argv[0]= option_argument;
argv[1]= " ";
argv[2]= " ";
		/****JF***********/





	struct timeval timeout;
	struct hostent *hp;
	struct sockaddr_in *to;
	struct protoent *proto;
	struct in_addr ifaddr;
	int i;
	int ch, fdmask, hold, packlen, preload;
	u_char *datap, *packet;
	char *target, hnamebuf[MAXHOSTNAMELEN];
	u_char ttl, loop;
	int am_i_root;
#ifdef IP_OPTIONS
	char rspace[3 + 4 * NROUTES + 1];	/* record route space */
#endif

	static char *null = NULL;
	__environ = &null;
	am_i_root = (getuid()==0);

	/*
	 * Pull this stuff up front so we can drop root if desired.
	 */
	if (!(proto = getprotobyname("icmp"))) {
		(void)fprintf(stderr, "ping: unknown protocol icmp.\n");
		exit(2);
	}
	if ((s = socket(AF_INET, SOCK_RAW, proto->p_proto)) < 0) {
		if (errno==EPERM) {
			fprintf(stderr, "ping: ping must run as root\n");
		}
		else perror("ping: socket");
		exit(2);
	}

#ifdef SAFE_TO_DROP_ROOT
	setuid(getuid());
#endif

	preload = 0;
	datap = &outpack[8 + sizeof(struct timeval)];
	while ((ch = getopt(argc, argv, "I:LRc:dfh:i:l:np:qrs:t:v")) != EOF)
		switch(ch) {
		case 'c':
			npackets = atoi(optarg);
			if (npackets <= 0) {
				(void)fprintf(stderr,
				    "ping: bad number of packets to transmit.\n");
				exit(2);
			}
			break;
		case 'd':
			options |= F_SO_DEBUG;
			break;
		case 'f':
			if (!am_i_root) {
				(void)fprintf(stderr,
				    "ping: %s\n", strerror(EPERM));
				exit(2);
			}
			options |= F_FLOOD;
			setbuf(stdout, NULL);
			break;
		case 'i':		/* wait between sending packets */
			interval = atoi(optarg);
			if (interval <= 0) {
				(void)fprintf(stderr,
				    "ping: bad timing interval.\n");
				exit(2);
			}
			options |= F_INTERVAL;
			break;
		case 'l':
			if (!am_i_root) {
				(void)fprintf(stderr,
				    "ping: %s\n", strerror(EPERM));
				exit(2);
			}
			preload = atoi(optarg);
			if (preload < 0) {
				(void)fprintf(stderr,
				    "ping: bad preload value.\n");
				exit(2);
			}
			break;
		case 'n':
			options |= F_NUMERIC;
			break;
		case 'p':		/* fill buffer with user pattern */
			options |= F_PINGFILLED;
			fill(datap, optarg);
			break;
		case 'q':
			options |= F_QUIET;
			break;
		case 'R':
			options |= F_RROUTE;
			break;
		case 'r':
			options |= F_SO_DONTROUTE;
			break;
		case 's':		/* size of packet to send */
			datalen = atoi(optarg);
			if (datalen > MAXPACKET) {
				(void)fprintf(stderr,
				    "ping: packet size too large.\n");
				exit(2);
			}
			if (datalen <= 0) {
				(void)fprintf(stderr,
				    "ping: illegal packet size.\n");
				exit(2);
			}
			break;
		case 'v':
			options |= F_VERBOSE;
			break;
		case 'L':
			moptions |= MULTICAST_NOLOOP;
			loop = 0;
			break;
		case 't':
			moptions |= MULTICAST_TTL;
			i = atoi(optarg);
			if (i < 0 || i > 255) {
				printf("ttl %u out of range\n", i);
				exit(2);
			}
			ttl = i;
			break;
		case 'I':
			moptions |= MULTICAST_IF;
			{
				int i1, i2, i3, i4;
				char junk;

				if (sscanf(optarg, "%u.%u.%u.%u%c",
					   &i1, &i2, &i3, &i4, &junk) != 4) {
					printf("bad interface address '%s'\n",
					       optarg);
					exit(2);
				}
				ifaddr.s_addr = (i1<<24)|(i2<<16)|(i3<<8)|i4;
				ifaddr.s_addr = htonl(ifaddr.s_addr);
			}
			break;
		default:
			usage_ping();
		}
	argc -= optind;
//	argv += optind;

	if (argc != 1)
		usage_ping();
	target = *argv;

	memset(&whereto, 0, sizeof(struct sockaddr));
	to = (struct sockaddr_in *)&whereto;
	to->sin_family = AF_INET;
	if (inet_aton(target, &to->sin_addr)) {
		hostname = target;
	}
	else {
		hp = gethostbyname(target);
		if (!hp) {
			//(void)fprintf(stderr, "ping: unknown host %s\n", target);
			/**********JF**********************/
			//exit(2);
			return(2);
			/**********************************/
		}
		to->sin_family = hp->h_addrtype;
		if (hp->h_length > (int)sizeof(to->sin_addr)) {
			hp->h_length = sizeof(to->sin_addr);
		}
		memcpy(&to->sin_addr, hp->h_addr, hp->h_length);
		(void)strncpy(hnamebuf, hp->h_name, sizeof(hnamebuf) - 1);
		hostname = hnamebuf;
	}

	if (options & F_FLOOD && options & F_INTERVAL) {
		(void)fprintf(stderr,
		    "ping: -f and -i incompatible options.\n");
		exit(2);
	}

	if (datalen >= (int)sizeof(struct timeval)) /* can we time transfer */
		timing = 1;
	packlen = datalen + MAXIPLEN + MAXICMPLEN;
	packet = malloc((u_int)packlen);
	if (!packet) {
		(void)fprintf(stderr, "ping: out of memory.\n");
		exit(2);
	}
	if (!(options & F_PINGFILLED))
		for (i = 8; i < datalen; ++i)
			*datap++ = i;

	ident = getpid() & 0xFFFF;
	hold = 1;

	if (options & F_SO_DEBUG)
		(void)setsockopt(s, SOL_SOCKET, SO_DEBUG, (char *)&hold,
		    sizeof(hold));

	if (options & F_SO_DONTROUTE)
		(void)setsockopt(s, SOL_SOCKET, SO_DONTROUTE, (char *)&hold,
		    sizeof(hold));

	/* this is necessary for broadcast pings to work */
	setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char *)&hold, sizeof(hold));

	/* record route option */
	if (options & F_RROUTE) {
#ifdef IP_OPTIONS
	        memset(rspace, 0, sizeof(rspace));
		rspace[IPOPT_OPTVAL] = IPOPT_RR;
		rspace[IPOPT_OLEN] = sizeof(rspace)-1;
		rspace[IPOPT_OFFSET] = IPOPT_MINOFF;
		if (setsockopt(s, IPPROTO_IP, IP_OPTIONS, rspace,
		    sizeof(rspace)) < 0) {
			perror("ping: record route");
			exit(2);
		}
#else
		(void)fprintf(stderr,
		  "ping: record route not available in this implementation.\n");
		exit(2);
#endif /* IP_OPTIONS */
	}

	/*
	 * When pinging the broadcast address, you can get a lot of answers.
	 * Doing something so evil is useful if you are trying to stress the
	 * ethernet, or just want to fill the arp cache to get some stuff for
	 * /etc/ethers.
	 */
	hold = 48 * 1024;
	(void)setsockopt(s, SOL_SOCKET, SO_RCVBUF, (char *)&hold,
	    sizeof(hold));

/*#if 0*/
	if (moptions & MULTICAST_NOLOOP) {
		if (setsockopt(s, IPPROTO_IP, IP_MULTICAST_LOOP,
							&loop, 1) == -1) {
			perror ("can't disable multicast loopback");
			exit(92);
		}
	}
	if (moptions & MULTICAST_TTL) {
		if (setsockopt(s, IPPROTO_IP, IP_MULTICAST_TTL,
							&ttl, 1) == -1) {
			perror ("can't set multicast time-to-live");
			exit(93);
		}
	}
	if (moptions & MULTICAST_IF) {
		if (setsockopt(s, IPPROTO_IP, IP_MULTICAST_IF,
					&ifaddr, sizeof(ifaddr)) == -1) {
			perror ("can't set multicast source interface");
			exit(94);
		}
	}
/*#endif*/

	if (to->sin_family == AF_INET)
		if(verbose == 1){
		(void)printf("PING %s (%s): %d data bytes\n", hostname,
		    inet_ntoa(*(struct in_addr *)&to->sin_addr.s_addr),
		    datalen);
		}
	else
		if(verbose == 1){
		(void)printf("PING %s: %d data bytes\n", hostname, datalen);
		}
	//(void)signal(SIGINT, finish);
	//(void)signal(SIGALRM, catcher);

	while (preload--){		/* fire off them quickies */
		pinger();
	}
	
		//if ((options & F_FLOOD) == 0)
	//JF		//catcher(0);
		//(void)signal(SIGALRM, catcher);		/* start things going */



/****************************************************************************/
	int c = 0;
	int p = 0;
/*******thread timer to close loop (for;;) pinger catcher in case of blocking*******/
	void *task_b (){

		for ( i=0; i < 6 ; ++i){

		p++;
		  sleep(1);
		   if(i == npackets + 1){
		    int pthread_cancel (pthread_t task_a);
		     void pthread_exit ();	
		   }
		}	
	}//end of thread task_b
	/***********************/

/*******thread pinger catcher in loop (for;;) *******/
       
       void *task_a (){

	for ( i=0; i < 5 ; i++) {
		struct sockaddr_in from;
		register int cc;
		size_t fromlen;


//pinger();
		//if (options & F_FLOOD) {

		ping_error_disconnected = pinger();

		sleep(1);
		c++;
			timeout.tv_sec = 0;
			timeout.tv_usec = 10000;
			fdmask = 1 << s;
			if (select(s + 1, (fd_set *)&fdmask, (fd_set *)NULL,
			    (fd_set *)NULL, &timeout) < 1)
				continue;
		//}
		fromlen = sizeof(from);
		if ((cc = recvfrom(s, (char *)packet, packlen, 0,
		    (struct sockaddr *)&from, &fromlen)) < 0) {
			if (errno == EINTR)
				continue;
			perror("ping: recvfrom");
			continue;
		}
		pr_pack((char *)packet, cc, &from);
		//if (npackets && nreceived >= npackets)
			//break;
			if (c == 3){
			finish_ping_proping(0);
			}
	}

      }//end of function thread task_a
     /************************************************************/
	
		     if(p == 0){
			pthread_t ta;
			pthread_t tb;
			pthread_create (&ta, NULL, task_a, NULL);
		   	pthread_create (&tb, NULL, task_b, NULL);
		     }
		if( bool_ping == NULL ){
			bool_ping = "1";
		}
	/* NOTREACHED */
sleep(4);
int pthread_cancel (pthread_t task_b);
int pthread_cancel (pthread_t task_a);
return(0);
}

/*
 * catcher --
 *	This routine causes another PING to be transmitted, and then
 * schedules another SIGALRM for 1 second from now.
 *
 * bug --
 *	Our sense of time will slowly skew (i.e., packets will not be
 * launched exactly at 1-second intervals).  This does not affect the
 * quality of the delay and loss statistics.
 */
static void catcher(/*int ignore*/)
{
(void)signal(SIGALRM, catcher); // Don't touch this JF


	int waittime_ping;
	//(void)ignore;
	pinger();

	//(void)signal(SIGALRM, catcher); // Don't touch this JF

	if (!npackets || ntransmitted < npackets){

		alarm((u_int)interval);
	} else {
		if (nreceived) {
			waittime_ping = 2 * tmax / 1000;
			if (!waittime_ping)
				waittime_ping = 1;
			if (waittime_ping > MAXWAIT)
				waittime_ping = MAXWAIT;
		}else {
			waittime_ping = MAXWAIT;

		//(void)signal(SIGALRM,bluff_function);
		//(void)alarm((u_int)waittime_ping);
			finish_ping_proping();
		}

	}
return;
}

#if !defined(__GLIBC__) || (__GLIBC__ < 2)
#define icmp_type type
#define icmp_code code
#define icmp_cksum checksum
#define icmp_id un.echo.id
#define icmp_seq un.echo.sequence
#define icmp_gwaddr un.gateway
#endif /* __GLIBC__ */

#define ip_hl ihl
#define ip_v version
#define ip_tos tos
#define ip_len tot_len
#define ip_id id
#define ip_off frag_off
#define ip_ttl ttl
#define ip_p protocol
#define ip_sum check
#define ip_src saddr
#define ip_dst daddr

/*
 * pinger --
 * 	Compose and transmit an ICMP ECHO REQUEST packet.  The IP packet
 * will be added on by the kernel.  The ID field is our UNIX process ID,
 * and the sequence number is an ascending integer.  The first 8 bytes
 * of the data portion are used to hold a UNIX "timeval" struct in VAX
 * byte-order, to compute the round-trip time.
 */
/*static void*/
int pinger(void)
{
	register struct icmphdr *icp;
	register int cc;
	int i;

	icp = (struct icmphdr *)outpack;
	icp->icmp_type = ICMP_ECHO;
	icp->icmp_code = 0;
	icp->icmp_cksum = 0;
	icp->icmp_seq = ntransmitted++;
	icp->icmp_id = ident;			/* ID */

	CLR(icp->icmp_seq % mx_dup_ck);

	if (timing)
		(void)gettimeofday((struct timeval *)&outpack[8],
		    (struct timezone *)NULL);

	cc = datalen + 8;			/* skips ICMP portion */

	/* compute ICMP checksum here */
	icp->icmp_cksum = in_cksum_ping((u_short *)icp, cc);

	i = sendto(s, (char *)outpack, cc, 0, &whereto,
	    sizeof(struct sockaddr));

	if (i < 0 || i != cc)  {
		if (i < 0)
/*
			perror("ping: sendto");
		(void)printf("ping: wrote %s %d chars, ret=%d\n",
		    hostname, cc, i);
*/
		/******JF********/
		return(-3);
		/****************/

	}
	if (!(options & F_QUIET) && options & F_FLOOD)
		(void)write(STDOUT_FILENO, &DOT, 1);
}

/*
 * pr_pack --
 *	Print out the packet, if it came from us.  This logic is necessary
 * because ALL readers of the ICMP socket get a copy of ALL ICMP packets
 * which arrive ('tis only fair).  This permits multiple copies of this
 * program to be run without having intermingled output (or statistics!).
 */
void
pr_pack(char *buf, int cc, struct sockaddr_in *from)
{
	register struct icmphdr *icp;
	register int i;
	register u_char *cp,*dp;
/*#if 0*/
	register u_long l;
	register int j;
	static int old_rrlen;
	static char old_rr[MAX_IPOPTLEN];
/*#endif*/
	struct iphdr *ip;
	struct timeval tv, *tp;
	long triptime = 0;
	int hlen, dupflag;

	(void)gettimeofday(&tv, (struct timezone *)NULL);

	/* Check the IP header */
	ip = (struct iphdr *)buf;
	hlen = ip->ip_hl << 2;
	if (cc < datalen + ICMP_MINLEN) {
		if (options & F_VERBOSE)
			(void)fprintf(stderr,
			  "ping: packet too short (%d bytes) from %s\n", cc,
			  inet_ntoa(*(struct in_addr *)&from->sin_addr.s_addr));
		return;
	}

	/* Now the ICMP part */
	cc -= hlen;
	icp = (struct icmphdr *)(buf + hlen);
	if (icp->icmp_type == ICMP_ECHOREPLY) {
		if (icp->icmp_id != ident)
			return;			/* 'Twas not our ECHO */
		++nreceived;
		if (timing) {
#ifndef icmp_data
			tp = (struct timeval *)(icp + 1);
#else
			tp = (struct timeval *)icp->icmp_data;
#endif
			tvsub_ping(&tv, tp);
			triptime = tv.tv_sec * 10000 + (tv.tv_usec / 100);
			tsum += triptime;
			if (triptime < tmin)
				tmin = triptime;
			if (triptime > tmax)
				tmax = triptime;
		}

		if (TST(icp->icmp_seq % mx_dup_ck)) {
			++nrepeats;
			--nreceived;
			dupflag = 1;
		} else {
			SET(icp->icmp_seq % mx_dup_ck);
			dupflag = 0;
		}

		if (options & F_QUIET)
			return;

		if (options & F_FLOOD)
			(void)write(STDOUT_FILENO, &BSPACE, 1);
		else {
			if(verbose == 1){
			(void)printf("%d bytes from %s: icmp_seq=%u", cc,
			   inet_ntoa(*(struct in_addr *)&from->sin_addr.s_addr),
			   icp->icmp_seq);
			}
			if(verbose == 1){
			(void)printf(" ttl=%d", ip->ip_ttl);
			}
			if (timing)
				if(verbose == 1){
				(void)printf(" time=%ld.%ld ms", triptime/10,
						triptime%10);
			}
			if (dupflag)
				(void)printf(" (DUP!)");
			/* check the data */
#ifndef icmp_data
			cp = ((u_char*)(icp + 1) + 8);
#else
			cp = (u_char*)icp->icmp_data + 8;
#endif
			dp = &outpack[8 + sizeof(struct timeval)];
			for (i = 8; i < datalen; ++i, ++cp, ++dp) {
				if (*cp != *dp) {
	(void)printf("\nwrong data byte #%d should be 0x%x but was 0x%x",
	    i, *dp, *cp);
					cp = (u_char*)(icp + 1);
					for (i = 8; i < datalen; ++i, ++cp) {
						if ((i % 32) == 8)
							(void)printf("\n\t");
						(void)printf("%x ", *cp);
					}
					break;
				}
			}
		}
	} else {
		/* We've got something other than an ECHOREPLY */
		if (!(options & F_VERBOSE))
			return;
		(void)printf("%d bytes from %s: ", cc,
		    pr_addr(from->sin_addr.s_addr));
		pr_icmph(icp);
	}

/*#if 0*/
	/* Display any IP options */
	cp = (u_char *)buf + sizeof(struct iphdr);

	for (; hlen > (int)sizeof(struct iphdr); --hlen, ++cp)
		switch (*cp) {
		case IPOPT_EOL:
			hlen = 0;
			break;
		case IPOPT_LSRR:
			(void)printf("\nLSRR: ");
			hlen -= 2;
			j = *++cp;
			++cp;
			if (j > IPOPT_MINOFF)
				for (;;) {
					l = *++cp;
					l = (l<<8) + *++cp;
					l = (l<<8) + *++cp;
					l = (l<<8) + *++cp;
					if (l == 0)
						(void)printf("\t0.0.0.0");
				else
					(void)printf("\t%s", pr_addr(ntohl(l)));
				hlen -= 4;
				j -= 4;
				if (j <= IPOPT_MINOFF)
					break;
				(void)putchar('\n');
			}
			break;
		case IPOPT_RR:
			j = *++cp;		/* get length */
			i = *++cp;		/* and pointer */
			hlen -= 2;
			if (i > j)
				i = j;
			i -= IPOPT_MINOFF;
			if (i <= 0)
				continue;
			if (i == old_rrlen
			    && cp == (u_char *)buf + sizeof(struct iphdr) + 2
			    && !memcmp((char *)cp, old_rr, i)
			    && !(options & F_FLOOD)) {
				(void)printf("\t(same route)");
				i = ((i + 3) / 4) * 4;
				hlen -= i;
				cp += i;
				break;
			}
			old_rrlen = i;
			memcpy(old_rr, cp, i);
			(void)printf("\nRR: ");
			for (;;) {
				l = *++cp;
				l = (l<<8) + *++cp;
				l = (l<<8) + *++cp;
				l = (l<<8) + *++cp;
				if (l == 0)
					(void)printf("\t0.0.0.0");
				else
					(void)printf("\t%s", pr_addr(ntohl(l)));
				hlen -= 4;
				i -= 4;
				if (i <= 0)
					break;
				(void)putchar('\n');
			}
			break;
		case IPOPT_NOP:
			(void)printf("\nNOP");
			break;
		default:
			(void)printf("\nunknown option %x", *cp);
			break;
		}
/*#endif*/
	if (!(options & F_FLOOD)) {
		(void)putchar('\n');
		(void)fflush(stdout);
	}
}

/*
 * in_cksum_ping --
 *	Checksum routine for Internet Protocol family headers (C Version)
 */
static int in_cksum_ping(u_short *addr, int len)
{
	register int nleft = len;
	register u_short *w = addr;
	register int sum = 0;
	u_short answer = 0;

	/*
	 * Our algorithm is simple, using a 32 bit accumulator (sum), we add
	 * sequential 16 bit words to it, and at the end, fold back all the
	 * carry bits from the top 16 bits into the lower 16 bits.
	 */
	while (nleft > 1)  {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if (nleft == 1) {
		*(u_char *)(&answer) = *(u_char *)w ;
		sum += answer;
	}

	/* add back carry outs from top 16 bits to low 16 bits */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return(answer);
}

/*
 * tvsub_ping --
 *	Subtract 2 timeval structs:  out = out - in.  Out is assumed to
 * be >= in.
 */
static void
tvsub_ping(register struct timeval *out, register struct timeval *in)
{
	if ((out->tv_usec -= in->tv_usec) < 0) {
		--out->tv_sec;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}

/*
 * finish --
 *	Print out statistics, and give up.
 */
//static void finish(int ignore){	// JF Just to give everything to eat and bluffing signal who stop deamon
//}

int finish_ping_proping(void){
	//(void)ignore;

	//(void)signal(SIGINT, SIG_IGN);
	(void)putchar('\n');
	(void)fflush(stdout);

	if(verbose==1){
	 (void)printf("--- %s ping statistics ---\n", hostname);
	 (void)printf("%ld packets transmitted, ", ntransmitted);
	 (void)printf("%ld packets received, ", nreceived);
	}

	if (nrepeats)
		(void)printf("+%ld duplicates, ", nrepeats);
	if (ntransmitted)
		if (nreceived > ntransmitted)
			(void)printf("-- somebody's printing up packets!");
		else 
			if(verbose==1){
			(void)printf("%d%% packet loss",
			    (int) (((ntransmitted - nreceived) * 100) /
			    ntransmitted));
			}
	(void)putchar('\n');
	if (nreceived && timing)
		if(verbose==1){
		(void)printf("round-trip min/avg/max = %ld.%ld/%lu.%ld/%ld.%ld ms\n",
			tmin/10, tmin%10,
			(tsum / (nreceived + nrepeats))/10,
			(tsum / (nreceived + nrepeats))%10,
			tmax/10, tmax%10);
		}
	if (nreceived != 0){

		//exit(0); /*JF*/
/****************************JF; Extract and recover string over the sub-function ************/

			char *bool_ping_return[5];
			bool_ping_return[0] = "0";

			    bool_ping=NULL;
			    bool_ping=malloc((strlen(*bool_ping_return)+1)*sizeof(char));
			    strcpy(bool_ping,*bool_ping_return);
		//printf("\n\n= %s =test1 bool_ping======\n",bool_ping);

//*******************************************************************************************/
	}else{
/****************************JF; Extract and recover string over the sub-function ************/
		//exit(1); /*JF*/

			char *bool_ping_return[5];
			/*JF*/	bool_ping_return[0] = "1";

			    bool_ping=NULL;
			    bool_ping=malloc((strlen(*bool_ping_return)+1)*sizeof(char));
			    strcpy(bool_ping,*bool_ping_return);

		//printf("\n\n= %s =test3 bool_ping======\n",bool_ping);

				/**********************/
				char *bool_finish_return[5];
			/*JF*/	bool_finish_return[0] = "1";

			    bool_finish=NULL;
			    bool_finish=malloc((strlen(*bool_finish_return)+1)*sizeof(char));
			    strcpy(bool_finish,*bool_finish_return);

		//printf("\n\n= %s =test3 bool_finish======\n",bool_finish);		
				/**********************/

/*******************************************************************************************/
	}
return;
}


#ifdef notdef
static char *ttab[] = {
	"Echo Reply",		/* ip + seq + udata */
	"Dest Unreachable",	/* net, host, proto, port, frag, sr + IP */
	"Source Quench",	/* IP */
	"Redirect",		/* redirect type, gateway, + IP  */
	"Echo",
	"Time Exceeded",	/* transit, frag reassem + IP */
	"Parameter Problem",	/* pointer + IP */
	"Timestamp",		/* id + seq + three timestamps */
	"Timestamp Reply",	/* " */
	"Info Request",		/* id + sq */
	"Info Reply"		/* " */
};
#endif

/*
 * pr_icmph --
 *	Print a descriptive string about an ICMP header.
 */
static void
pr_icmph(struct icmphdr *icp)
{
	switch(icp->icmp_type) {
	case ICMP_ECHOREPLY:
		(void)printf("Echo Reply\n");
		/* XXX ID + Seq + Data */
		break;
	case ICMP_DEST_UNREACH:
		switch(icp->icmp_code) {
		case ICMP_NET_UNREACH:
			(void)printf("Destination Net Unreachable\n");
			break;
		case ICMP_HOST_UNREACH:
			(void)printf("Destination Host Unreachable\n");
			break;
		case ICMP_PROT_UNREACH:
			(void)printf("Destination Protocol Unreachable\n");
			break;
		case ICMP_PORT_UNREACH:
			(void)printf("Destination Port Unreachable\n");
			break;
		case ICMP_FRAG_NEEDED:
			(void)printf("frag needed and DF set\n");
			break;
		case ICMP_SR_FAILED:
			(void)printf("Source Route Failed\n");
			break;
		case ICMP_NET_UNKNOWN:
			(void)printf("Network Unknown\n");
			break;
		case ICMP_HOST_UNKNOWN:
			(void)printf("Host Unknown\n");
			break;
		case ICMP_HOST_ISOLATED:
			(void)printf("Host Isolated\n");
			break;
		case ICMP_NET_UNR_TOS:
			printf("Destination Network Unreachable At This TOS\n");
			break;
		case ICMP_HOST_UNR_TOS:
			printf("Destination Host Unreachable At This TOS\n");
			break;
#ifdef ICMP_PKT_FILTERED
		case ICMP_PKT_FILTERED:
			(void)printf("Packet Filtered\n");
			break;
#endif
#ifdef ICMP_PREC_VIOLATION
		case ICMP_PREC_VIOLATION:
			(void)printf("Precedence Violation\n");
			break;
#endif
#ifdef ICMP_PREC_CUTOFF
		case ICMP_PREC_CUTOFF:
			(void)printf("Precedence Cutoff\n");
			break;
#endif
		default:
			(void)printf("Dest Unreachable, Unknown Code: %d\n",
			    icp->icmp_code);
			break;
		}
		/* Print returned IP header information */
#ifndef icmp_data
		pr_retip((struct iphdr *)(icp + 1));
#else
		pr_retip((struct iphdr *)icp->icmp_data);
#endif
		break;
	case ICMP_SOURCE_QUENCH:
		(void)printf("Source Quench\n");
#ifndef icmp_data
		pr_retip((struct iphdr *)(icp + 1));
#else
		pr_retip((struct iphdr *)icp->icmp_data);
#endif
		break;
	case ICMP_REDIRECT:
		switch(icp->icmp_code) {
		case ICMP_REDIR_NET:
			(void)printf("Redirect Network");
			break;
		case ICMP_REDIR_HOST:
			(void)printf("Redirect Host");
			break;
		case ICMP_REDIR_NETTOS:
			(void)printf("Redirect Type of Service and Network");
			break;
		case ICMP_REDIR_HOSTTOS:
			(void)printf("Redirect Type of Service and Host");
			break;
		default:
			(void)printf("Redirect, Bad Code: %d", icp->icmp_code);
			break;
		}
		(void)printf("(New addr: %s)\n",
			     inet_ntoa(icp->icmp_gwaddr));
#ifndef icmp_data
		pr_retip((struct iphdr *)(icp + 1));
#else
		pr_retip((struct iphdr *)icp->icmp_data);
#endif
		break;
	case ICMP_ECHO:
		(void)printf("Echo Request\n");
		/* XXX ID + Seq + Data */
		break;
	case ICMP_TIME_EXCEEDED:
		switch(icp->icmp_code) {
		case ICMP_EXC_TTL:
			(void)printf("Time to live exceeded\n");
			break;
		case ICMP_EXC_FRAGTIME:
			(void)printf("Frag reassembly time exceeded\n");
			break;
		default:
			(void)printf("Time exceeded, Bad Code: %d\n",
			    icp->icmp_code);
			break;
		}
#ifndef icmp_data
		pr_retip((struct iphdr *)(icp + 1));
#else
		pr_retip((struct iphdr *)icp->icmp_data);
#endif
		break;
	case ICMP_PARAMETERPROB:
		(void)printf("Parameter problem: IP address = %s\n",
			inet_ntoa (icp->icmp_gwaddr));
#ifndef icmp_data
		pr_retip((struct iphdr *)(icp + 1));
#else
		pr_retip((struct iphdr *)icp->icmp_data);
#endif
		break;
	case ICMP_TIMESTAMP:
		(void)printf("Timestamp\n");
		/* XXX ID + Seq + 3 timestamps */
		break;
	case ICMP_TIMESTAMPREPLY:
		(void)printf("Timestamp Reply\n");
		/* XXX ID + Seq + 3 timestamps */
		break;
	case ICMP_INFO_REQUEST:
		(void)printf("Information Request\n");
		/* XXX ID + Seq */
		break;
	case ICMP_INFO_REPLY:
		(void)printf("Information Reply\n");
		/* XXX ID + Seq */
		break;
#ifdef ICMP_MASKREQ
	case ICMP_MASKREQ:
		(void)printf("Address Mask Request\n");
		break;
#endif
#ifdef ICMP_MASKREPLY
	case ICMP_MASKREPLY:
		(void)printf("Address Mask Reply\n");
		break;
#endif
	default:
		(void)printf("Bad ICMP type: %d\n", icp->icmp_type);
	}
}

/*
 * pr_iph --
 *	Print an IP header with options.
 */
static void
pr_iph(struct iphdr *ip)
{
	int hlen;
	u_char *cp;

	hlen = ip->ip_hl << 2;
	cp = (u_char *)ip + 20;		/* point to options */

	(void)printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src      Dst Data\n");
	(void)printf(" %1x  %1x  %02x %04x %04x",
	    ip->ip_v, ip->ip_hl, ip->ip_tos, ip->ip_len, ip->ip_id);
	(void)printf("   %1x %04x", ((ip->ip_off) & 0xe000) >> 13,
	    (ip->ip_off) & 0x1fff);
	(void)printf("  %02x  %02x %04x", ip->ip_ttl, ip->ip_p, ip->ip_sum);
	(void)printf(" %s ", inet_ntoa(*((struct in_addr *) &ip->ip_src)));
	(void)printf(" %s ", inet_ntoa(*((struct in_addr *) &ip->ip_dst)));
	/* dump and option bytes */
	while (hlen-- > 20) {
		(void)printf("%02x", *cp++);
	}
	(void)putchar('\n');
}

/*
 * pr_addr --
 *	Return an ascii host address as a dotted quad and optionally with
 * a hostname.
 */
static char *
pr_addr(u_long l)
{
	struct hostent *hp;
	static char buf[256];

	if ((options & F_NUMERIC) ||
	    !(hp = gethostbyaddr((char *)&l, 4, AF_INET)))
		(void)snprintf(buf, sizeof(buf), "%s",
			       inet_ntoa(*(struct in_addr *)&l));
	else
		(void)snprintf(buf, sizeof(buf), "%s (%s)", hp->h_name,
		    inet_ntoa(*(struct in_addr *)&l));
	return(buf);
}

/*
 * pr_retip --
 *	Dump some info on a returned (via ICMP) IP packet.
 */
static void
pr_retip(struct iphdr *ip)
{
	int hlen;
	u_char *cp;

	pr_iph(ip);
	hlen = ip->ip_hl << 2;
	cp = (u_char *)ip + hlen;

	if (ip->ip_p == 6)
		(void)printf("TCP: from port %u, to port %u (decimal)\n",
		    (*cp * 256 + *(cp + 1)), (*(cp + 2) * 256 + *(cp + 3)));
	else if (ip->ip_p == 17)
		(void)printf("UDP: from port %u, to port %u (decimal)\n",
			(*cp * 256 + *(cp + 1)), (*(cp + 2) * 256 + *(cp + 3)));
}

static void
fill(void *bp1, char *patp)
{
	register int ii, jj, kk;
	int pat[16];
	char *cp, *bp = (char *)bp1;

	for (cp = patp; *cp; cp++)
		if (!isxdigit(*cp)) {
			(void)fprintf(stderr,
			    "ping: patterns must be specified as hex digits.\n");
			exit(2);
		}
	ii = sscanf(patp,
	    "%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x%2x",
	    &pat[0], &pat[1], &pat[2], &pat[3], &pat[4], &pat[5], &pat[6],
	    &pat[7], &pat[8], &pat[9], &pat[10], &pat[11], &pat[12],
	    &pat[13], &pat[14], &pat[15]);

	if (ii > 0)
		for (kk = 0; kk <= MAXPACKET - (8 + ii); kk += ii)
			for (jj = 0; jj < ii; ++jj)
				bp[jj + kk] = pat[jj];
	if (!(options & F_QUIET)) {
		(void)printf("PATTERN: 0x");
		for (jj = 0; jj < ii; ++jj)
			(void)printf("%02x", bp[jj] & 0xFF);
		(void)printf("\n");
	}
}

static void
usage_ping(void)
{
	(void)fprintf(stderr,
	    "usage: ping [-LRdfnqrv] [-c count] [-i wait] [-l preload]\n\t[-p pattern] [-s packetsize] [-t ttl] [-I interface address] host\n");
	exit(2);
}
/****************END OF PINGER*********************************************************************/
