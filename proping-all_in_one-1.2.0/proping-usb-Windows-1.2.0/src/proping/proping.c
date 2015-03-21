/***
 *                            _             
 *      _ __  _ __ ___  _ __ (_)_ __   __ _ 
 *     | '_ \| '__/ _ \| '_ \| | '_ \ / _` |
 *     | |_) | | | (_) | |_) | | | | | (_| |
 *     | .__/|_|  \___/| .__/|_|_| |_|\__, |
 *     |_|             |_|            |___/ 
 */
/************BEGIN OF PROPING***********************************************************************************/

//qt4/mingw/gcc.exe proping.c sendingmail.c -o proping -L c:/proping-windows.../proping/lib -l ws2_32


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <tchar.h>
//#include <stdio.h>
//#include <stdlib.h>
#include <ws2tcpip.h>
//#include <string.h>
//#include <time.h>

#include <windows.h>

DWORD WINAPI task_d ();

char *option_argument;
char *trace_ip4;
int ret_ping_error = 1;


char flag_word = 0;
char flag_ipdown = 0;
char verbose = 1;


/******sendingmaile and telnet section******/
char sendmail_mode[15];
char sendmail_to[15];
char sendmail_from[15];
char sendmail_subject[15];
char sendmail_message[15];
char sendmail_host[15];
char sendmail_host_port[15];
char sendmail_type[15];

int sendmail_bool_type;
int sendmail_bool_mode;
int flag_ipdown_remember = 1;
int sendingmail_freq_min = 5;
int initial_sendingmail = 1;
char *log_fpname_sendmail;
DWORD WINAPI sendingmail();
DWORD WINAPI sendingmail_timer();

/*******************************/

char *option_name;
char *option_argument;

int flag_traceroute_start = 1;

const char *log_fpname;

/********************For ping.c bluffing and recovery****************/



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


//-----------Start, stop, Stat-----------------------
  char arg_stat[] = "stat";
  char arg_stat1[] = "stat1";
  char arg_stat2[] = "stat2";
  
char arg_restart[] = "restart";
char arg_start[] = "start";
char arg_stop[] = "stop";
char arg_shellstart[] = "shellstart"; // It use the shell to start the process in this way, it can be stated in background easily

//#define KILLPROCESSUS "ps ax | grep proping | awk '{print $1}'| xargs kill -15"
#define SHELLSTART "proping shellstart"

if (argc == 1){			//Important; this is a way to do a restart by the init.d/service for redhat
system(SHELLSTART);
Sleep(1000);
exit(0);

}else if (argc != 2){
fprintf(stdout,"Usage : %s [start]\n",*argv);
return -1;

}else if (strcmp(argv[1],arg_stat)==0 || strcmp(argv[1],arg_stat1)==0 || strcmp(argv[1],arg_stat2)==0){
statistic(argc,argv);
exit(0);

}else if (strcmp(argv[1],arg_restart)==0){
printf("[restart] is not available, please use [start|stop]\n");
exit(0);

}else if (strcmp(argv[1],arg_stop)==0){
puts (argv[1]);
printf("|ctrl-c| please\n");
exit(0);

}else if (strcmp(argv[1],arg_start)==0){
puts (argv[1]);

//#define PROCFS "mount -t procfs proc /proc"
//system(PROCFS);
system(SHELLSTART);
Sleep(1000);
exit(0);

}else if (strcmp(argv[1],arg_shellstart)==0){


//----start task sendingmail_timer-------

CreateThread(NULL, 0, sendingmail_timer, NULL, 0, NULL);

//----start task sendingmail-------
	
CreateThread(NULL, 0, sendingmail, NULL, 0, NULL);
    
//------------------------------------------------------

char case_name;

char sleep_ping[15];
char sleep_routine[15];
char frequency_of_sending[15];
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
break;
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
break;

case 'C' :
strcpy(option_verbose, option_argument);

	if(strcmp(option_verbose,"on")==0){
	verbose = 1;
	}else if(strcmp(option_verbose,"off")==0){
	verbose = 0;
	}
break;

case 'D' :
strcpy(sendmail_mode, option_argument);

	if(strcmp(sendmail_mode,"on")==0){
	sendmail_bool_mode = 1;
	}else if(strcmp(sendmail_mode,"off")==0){
	sendmail_bool_mode = 0;
	}
break;

case 'E' :
strcpy(sendmail_to, option_argument);
break;

case 'F' :
strcpy(sendmail_from, option_argument);
break;

case 'G' :
strcpy(sendmail_subject, option_argument);

break;

case 'H' :
	strcpy(frequency_of_sending, option_argument);

	if(strcmp(frequency_of_sending,"5m")==0){
	sendingmail_freq_min = (5*60);
	}else if(strcmp(frequency_of_sending,"10m")==0){
	sendingmail_freq_min = (10*60);
	}else if(strcmp(frequency_of_sending,"20m")==0){
	sendingmail_freq_min = (20*60);
	}else if(strcmp(frequency_of_sending,"40m")==0){
	sendingmail_freq_min = (40*60);
	}else if(strcmp(frequency_of_sending,"80m")==0){
	sendingmail_freq_min = (80*60);
	}else if(strcmp(frequency_of_sending,"6h")==0){
	sendingmail_freq_min = (360*60);
	}else if(strcmp(frequency_of_sending,"12h")==0){
	sendingmail_freq_min = (720*60);
	}else if(strcmp(frequency_of_sending,"24h")==0){
	sendingmail_freq_min = (1440*60);
	}
break;

case 'I' :
strcpy(sendmail_host, option_argument);

break;
case 'J' :
strcpy(sendmail_host_port, option_argument);

break;

case 'K' :
strcpy(sendmail_type, option_argument);

	if(strcmp(sendmail_type,"powershell")==0){
	sendmail_bool_type = 1;
	}else if(strcmp(sendmail_type,"sendsmtp")==0){
	sendmail_bool_type = 0;
	}
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

FILE *fp = fopen("./proping.conf", "r");
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

char ping_command_strcat[256] = "";
#define PING_COMMAND_STRCAT1 "ping -n 3 "
strcat(ping_command_strcat, PING_COMMAND_STRCAT1);
strcat(ping_command_strcat, option_argument); //

ret_ping_error = system(ping_command_strcat);


sleep(1);


if(ret_ping_error == 0) {
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
strftime(insidefile_date_log, sizeof insidefile_date_log, "%A , %m_%B %d , %Y %HH%Mm%Ss", tm);

//---------------------Creating log_fp about date--------------------

//---Create a dating log path file--------
#define PATH_LOG_FILE "./log/"
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
//strcat(propingwall,"touch ./propingwall.txt");
//system(propingwall);

char wall_commandlog_strcat[256] = "";
strcat(wall_commandlog_strcat, "echo " );
strcat(wall_commandlog_strcat, insidefile_date_log);
strcat(wall_commandlog_strcat, "-----");
strcat(wall_commandlog_strcat, "!!!Warning !!! Interface Not reached ");
strcat(wall_commandlog_strcat, option_name);
strcat(wall_commandlog_strcat, option_argument);
//strcat(wall_commandlog_strcat, " > ./propingwall.txt");
system(wall_commandlog_strcat);

char propingwall2[256] = "" ;
strcat(propingwall2, "wall ./propingwall.txt");
//system(propingwall2);
//-----------


printf("Not reached!!! \007\n\n");


if(ret_ping_error == 2){

	fprintf(stderr,"\n !!! unresolved hostname to ipv4; (/etc/hosts file) or (DNS services) are empty or unreachable !!!\n");

	} else if(ping_error_disconnected == -3){ 

	printf("\n !!! Pinger machine network devices are down or the cables are disconnected  !!!\n");

		} else if(ret_ping_error == 1) {

		printf("Please wait for a maximum of 2min, the time to finish tracert analysis!!!\n\n\n");
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

		} else if(ret_ping_error == 1) {

			strcat(echo_commandlog_strcat, "!!!Warning !!! Interface Not reached!!! : ");
			strcat(echo_commandlog_strcat, option_name);
			strcat(echo_commandlog_strcat, option_argument);
		}

strcat(echo_commandlog_strcat, " >> ");
strcat(echo_commandlog_strcat, log_fpname);
//printf("\n\n%s\n\n",echo_commandlog_strcat );
//system(echo_commandlog_strcat);
//-----------


//-----------------------------------------------------------------------------------------------

flag_word = 1;


/**************************FUNCTION thread; tracert*******************/

				//printf("\n\n%s\n\n",argv_trace);

	if((ret_ping_error == 2) || (ping_error_disconnected == -3)){
		//do Nothing to rest in true logical
	}else{
        DWORD WINAPI task_c ();
			int p = 0;
			DWORD WINAPI task_d(){
			

				for ( i=0; i < 50 ; ++i){

				p++;
				  sleep(1);
				   if(i == 50){
				    TerminateThread(task_c, 0);
				     TerminateThread(task_d, 0);	
				   }
				}	
			}//end of thread task_d
			/***********************/

			     if(p == 0){
					
				flag_traceroute_start = 0;
				CreateThread(NULL, 0, task_c, NULL, 0, NULL);
			   	CreateThread(NULL, 0, task_d, NULL, 0, NULL);
			     }
		
					sleep(51);
					TerminateThread(task_c, 0);
                                        TerminateThread(task_d, 0);
				     
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
int code = mkdir("./log", MY_MASK);


if (code == 0) {
	if(verbose == 1){
	printf("Log repertory has been created; ./log\n"); 
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
strftime(insidefile_date_log, sizeof insidefile_date_log, "%A , %m_%B %d , %Y %HH%Mm%Ss", tm);

//---------------------Creating log_fp about date--------------------

//---Create a dating log path file--------
#define PATH_LOG_FILE "./log/"
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
//strcat(wall_command_strcat, " > ./propingwall.txt");
system(wall_command_strcat);

char propingwall[256] = "";
//strcat(propingwall, " wall ./propingwall.txt");



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

char file_date_log2[64];
char insidefile_date_log2[64]; //external declaration
strftime(file_date_log2, sizeof file_date_log2, "proping_%B_%Y.log", tm);
strftime(insidefile_date_log2, sizeof insidefile_date_log2, "B %HH%Mm%Ss C %Y E %m_%B G %d R %A I", tm);

//---------------------Creating log_fp about date--------------------

//---Create a dating log path file--------
#define PATH_LOG_FILE2 "./log/"
char file_log_path2[256] = "";

strcat(file_log_path2, PATH_LOG_FILE2);
strcat(file_log_path2, file_date_log2);

//printf("%s",file_log_path2);
//---


//---------
FILE *log_fp;
int log_exists;
const char *log_fpname2;

log_fpname2 = file_log_path2;
                        /*------------extract log_fpname of subfunction-----------------*/
                            log_fpname_sendmail="NULL";

			    log_fpname_sendmail=malloc((strlen(log_fpname2)+1)*sizeof(char));
			    strcpy(log_fpname_sendmail,log_fpname2);
                        /*--------------------------------------------------------------*/
//-------------

char wall_command_strcat[256] = "";
strcat(wall_command_strcat, " " ); //---Concatenate for wall command

	if ( (trace_ip4 != NULL) && (ret_ping_error != 2) && (ping_error_disconnected != -3) ){
		strcat(wall_command_strcat, trace_ip4);
	}else{
		strcat(wall_command_strcat,"!_unknow_disconnected_device_!");
	}

strcat(wall_command_strcat, " - ");
strcat(wall_command_strcat, option_name); //---
strcat(wall_command_strcat, " + "); //---
strcat(wall_command_strcat, option_argument);
strcat(wall_command_strcat, " P"); //---

//#define ECHO "echo "
char echo_commandlog_strcat[256] = "";

strcat(echo_commandlog_strcat, "echo " );
strcat(echo_commandlog_strcat, insidefile_date_log2);
strcat(echo_commandlog_strcat, " ");
strcat(echo_commandlog_strcat, wall_command_strcat);
strcat(echo_commandlog_strcat, " >> ");
strcat(echo_commandlog_strcat, log_fpname2);
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

flag_ipdown_remember = 0; // Remember a down for sendingmail thread task




//-------------------------------------------------------------------------------------

flag_ipdown = 1;
}
}

return(0);
}

/************END OF PROPING**********************************************************************************/
/*****************************************************************************************************************/

/**********************BEGIN OF TRACERT*************************************/
/***************************************************************************/


/*******JF**********/
int argc;
char *argv[3];
/*******************/

#define ECHO_REPLY 0
#define DEST_UNREACHABLE 3
#define ECHO_REQUEST 8
#define TTL_EXCEEDED 11

#define MAX_PING_PACKET_SIZE 1024
#define MAX_PING_DATA_SIZE (MAX_PING_PACKET_SIZE + sizeof(IPv4Header))
#define PACKET_SIZE 32
#define ICMP_MIN_SIZE 8

/* we need this for packets which have the 'dont fragment'
 * bit set, as they can get quite large otherwise */
#define MAX_REC_SIZE 200

/* pack the structures */
#include <pshpack1.h>



/* IPv4 Header, 20 bytes */
typedef struct IPv4Header
{
    BYTE h_len:4;
    BYTE version:4;
    BYTE tos;
    USHORT length;
    USHORT id;
    USHORT flag_frag;
    BYTE ttl;
    BYTE proto;
    USHORT checksum;
    ULONG source;
    ULONG dest;
} IPv4_HEADER, *PIPv4_HEADER;

/* ICMP Header, 8 bytes */
typedef struct ICMPHeader
{
    BYTE type;
    BYTE code;
    USHORT checksum;
    USHORT id; // not used in time exceeded
    USHORT seq; // not used in time exceeded
} ICMP_HEADER, *PICMP_HEADER;

/* ICMP Echo Reply Header */
typedef struct EchoReplyHeader
{
    struct ICMPHeader icmpheader;
} ECHO_REPLY_HEADER, *PECHO_REPLY_HEADER;

#include <poppack.h>

typedef struct _APPINFO
{
    SOCKET icmpSock;                // socket descriptor
    SOCKADDR_IN source, dest;       // source and destination address info
    PECHO_REPLY_HEADER SendPacket;   // ICMP echo packet
    PIPv4_HEADER RecvPacket;         // return reveive packet

    BOOL bUsePerformanceCounter;    // whether to use the high res performance counter
    LARGE_INTEGER TicksPerMs;       // number of millisecs in relation to proc freq
    LARGE_INTEGER TicksPerUs;       // number of microsecs in relation to proc freq
    LONGLONG lTimeStart;            // send packet, timer start
    LONGLONG lTimeEnd;              // receive packet, timer end

    BOOL bResolveAddresses;         // -d  MS ping defaults to true.
    INT iMaxHops;                   // -h  Max number of hops before trace ends
    INT iHostList;                  // -j  Source route
    INT iTimeOut;                   // -w  time before packet times out

} APPINFO, *PAPPINFO;
 
 
 
 //#define TRACERT_DBG
 

 CHAR cHostname[256];            // target hostname
 CHAR cDestIP[18];               // target IP
 
 
 static VOID
 DebugPrint(LPTSTR lpString, ...)
 {
 #ifdef TRACERT_DBG
     va_list args;
     va_start(args, lpString);
     _vtprintf(lpString, args);
     va_end(args);
 #else
     UNREFERENCED_PARAMETER(lpString);
 #endif
 }
 
 
 static VOID
 Usage(VOID)
 {
     _tprintf(_T("\nUsage: tracert [-d] [-h maximum_hops] [-j host-list] [-w timeout] target_name\n\n"
                 "Options:\n"
                 "    -d                 Do not resolve addresses to hostnames.\n"
                 "    -h maximum_hops    Maximum number of hops to search for target.\n"
                 "    -j host-list       Loose source route along host-list.\n"
                 "    -w timeout         Wait timeout milliseconds for each reply.\n\n"));
 
     _tprintf(_T("NOTES\n-----\n"
            "- Setting TTL values is not currently supported in ReactOS, so the trace will\n"
            "  jump straight to the destination. This feature will be implemented soon.\n"
            "- Host info is not currently available in ReactOS and will fail with strange\n"
            "  results. Use -d to force it not to resolve IP's.\n"
            "- For testing purposes, all should work as normal in a Windows environment\n\n"));
 }
 
 
 static BOOL
 ParseCmdline(/*int argc, LPCTSTR argv[],*/PAPPINFO pInfo)
 {

argc = 2;
argv[1]=option_argument;

     INT i;
 
     if (argc < 2)
     {
        Usage();
        return FALSE;
     }
     else
     {
         for (i = 1; i < argc; i++)
         {
             if (argv[i][0] == _T('-'))
             {
                 switch (argv[i][1])
                 {
                     case _T('d'):
                         pInfo->bResolveAddresses = FALSE;
                     break;
 
                     case _T('h'):
                         _stscanf(argv[i+1], _T("%d"), &pInfo->iMaxHops);
                     break;
 
                     case _T('j'):
                         _tprintf(_T("-j is not yet implemented.\n"));
                     break;
 
                     case _T('w'):
                         _stscanf(argv[i+1], _T("%d"), &pInfo->iTimeOut);
                     break;
 
                     default:
                     {
                         _tprintf(_T("%s is not a valid option.\n"), argv[i]);
                         Usage();
                         return FALSE;
                     }
                 }
             }
             else
                /* copy target address */
                _tcsncpy(cHostname, argv[i], 255);
         }
     }
 
     return TRUE;
 }
 
 
 static WORD
 CheckSum(PUSHORT data,
          UINT size)
 {
     DWORD dwSum = 0;
 
     while (size > 1)
     {
         dwSum += *data++;
         size -= sizeof(USHORT);
     }
 
     if (size)
         dwSum += *(UCHAR*)data;
 
     dwSum = (dwSum >> 16) + (dwSum & 0xFFFF);
     dwSum += (dwSum >> 16);
 
     return (USHORT)(~dwSum);
 }
 
 
 static VOID
 SetupTimingMethod(PAPPINFO pInfo)
 {
     LARGE_INTEGER PerformanceCounterFrequency;
 
     /* check if performance counters are available */
     pInfo->bUsePerformanceCounter = QueryPerformanceFrequency(&PerformanceCounterFrequency);
 
     if (pInfo->bUsePerformanceCounter)
     {
         /* restrict execution to first processor on SMP systems */
         if (SetThreadAffinityMask(GetCurrentThread(), 1) == 0)
             pInfo->bUsePerformanceCounter = FALSE;
 
         pInfo->TicksPerMs.QuadPart  = PerformanceCounterFrequency.QuadPart / 1000;
         pInfo->TicksPerUs.QuadPart  = PerformanceCounterFrequency.QuadPart / 1000000;
     }
     else
     {
         pInfo->TicksPerMs.QuadPart = 1;
         pInfo->TicksPerUs.QuadPart = 1;
     }
 }
 
 
 static BOOL
 ResolveHostname(PAPPINFO pInfo)
 {
     HOSTENT *hp;
     ULONG addr;
 
     ZeroMemory(&pInfo->dest, sizeof(pInfo->dest));
 
     /* if address is not a dotted decimal */
     if ((addr = inet_addr(cHostname))== INADDR_NONE)
     {
        if ((hp = gethostbyname(cHostname)) != 0)
        {
           //CopyMemory(&pInfo->dest.sin_addr, hp->h_addr, hp->h_length);
           pInfo->dest.sin_addr = *((struct in_addr *)hp->h_addr);
           pInfo->dest.sin_family = hp->h_addrtype;
        }
        else
        {
           _tprintf(_T("Unable to resolve target system name %s.\n"), cHostname);
           return FALSE;
        }
     }
     else
     {
         pInfo->dest.sin_addr.s_addr = addr;
         pInfo->dest.sin_family = AF_INET;
     }
 
     _tcscpy(cDestIP, inet_ntoa(pInfo->dest.sin_addr));
 
     return TRUE;
 }
 
 
 static LONGLONG
 GetTime(PAPPINFO pInfo)
 {
     LARGE_INTEGER Time;
 
     /* Get the system time using preformance counters if available */
     if (pInfo->bUsePerformanceCounter)
     {
         if (QueryPerformanceCounter(&Time))
         {
             return Time.QuadPart;
         }
     }
 
     /* otherwise fall back to GetTickCount */
     Time.u.LowPart = (DWORD)GetTickCount();
     Time.u.HighPart = 0;
 
     return (LONGLONG)Time.u.LowPart;
 }
 
 
 static BOOL
 SetTTL(SOCKET sock,
        INT iTTL)
 {
     if (setsockopt(sock,
                    IPPROTO_IP,
                    IP_TTL,
                    (const char *)&iTTL,
                    sizeof(iTTL)) == SOCKET_ERROR)
     {
        DebugPrint(_T("TTL setsockopt failed : %d. \n"), WSAGetLastError());
        return FALSE;
     }
 
     return TRUE;
 }
 
 
 static BOOL
 CreateSocket(PAPPINFO pInfo)
 {
     pInfo->icmpSock = WSASocket(AF_INET,
                                 SOCK_RAW,
                                 IPPROTO_ICMP,
                                 0,
                                 0,
                                 0);
 
     if (pInfo->icmpSock == INVALID_SOCKET)
     {
         INT err = WSAGetLastError();
         DebugPrint(_T("Could not create socket : %d.\n"), err);
 
         if (err == WSAEACCES)
         {
             _tprintf(_T("\n\nYou must have access to raw sockets (admin) to run this program!\n\n"));
         }
 
         return FALSE;
     }
 
     return TRUE;
 }
 
 
 static VOID
 PreparePacket(PAPPINFO pInfo,
               USHORT iSeqNum)
 {
     /* assemble ICMP echo request packet */
     pInfo->SendPacket->icmpheader.type     = ECHO_REQUEST;
     pInfo->SendPacket->icmpheader.code     = 0;
     pInfo->SendPacket->icmpheader.checksum = 0;
     pInfo->SendPacket->icmpheader.id       = (USHORT)GetCurrentProcessId();
     pInfo->SendPacket->icmpheader.seq      = htons((USHORT)iSeqNum);
 
     /* calculate checksum of packet */
     pInfo->SendPacket->icmpheader.checksum  = CheckSum((PUSHORT)&pInfo->SendPacket->icmpheader,
                                                        sizeof(ICMP_HEADER) + PACKET_SIZE);
 }
 
 
 static INT
 SendPacket(PAPPINFO pInfo)
 {
     INT iSockRet;
 
     DebugPrint(_T("\nsending packet of %d bytes... "), PACKET_SIZE);
 
     /* get time packet was sent */
     pInfo->lTimeStart = GetTime(pInfo);
 
     iSockRet = sendto(pInfo->icmpSock,              //socket
                       (char *)&pInfo->SendPacket->icmpheader,//buffer
                       sizeof(ICMP_HEADER) + PACKET_SIZE,//size of buffer
                       0,                            //flags
                       (SOCKADDR *)&pInfo->dest,     //destination
                       sizeof(pInfo->dest));         //address length
 
     if (iSockRet == SOCKET_ERROR)
     {
         if (WSAGetLastError() == WSAEACCES)
         {
             /* FIXME: Is this correct? */
             _tprintf(_T("\n\nYou must be an administrator to run this program!\n\n"));
             WSACleanup();
             HeapFree(GetProcessHeap(), 0, pInfo);
           //JF  exit(-1);
             
                    
             return(-1);
         }
         else
         {
             DebugPrint(_T("sendto failed %d\n"), WSAGetLastError());
         }
     }
     else
     {
         DebugPrint(_T("sent %d bytes\n"), iSockRet);
     }
 
     return iSockRet;
 }
 
 
 static BOOL
 ReceivePacket(PAPPINFO pInfo)
 {
     TIMEVAL timeVal;
     FD_SET readFDS;
     INT iSockRet = 0, iSelRet;
     INT iFromLen;
     BOOL bRet = FALSE;
 
     iFromLen = sizeof(pInfo->source);
 
     DebugPrint(_T("Receiving packet. Available buffer, %d bytes... "), MAX_PING_PACKET_SIZE);
 
     /* monitor icmpSock for incomming connections */
     FD_ZERO(&readFDS);
     FD_SET(pInfo->icmpSock, &readFDS);
 
     /* set timeout values */
     timeVal.tv_sec  = pInfo->iTimeOut / 1000;
     timeVal.tv_usec = pInfo->iTimeOut % 1000;
 
     iSelRet = select(0,
                      &readFDS,
                      NULL,
                      NULL,
                      &timeVal);
 
     if (iSelRet == SOCKET_ERROR)
     {
         DebugPrint(_T("select() failed in sendPacket() %d\n"), WSAGetLastError());
     }
     else if (iSelRet == 0) /* if socket timed out */
     {
         _tprintf(_T("   *  "));
     }
     else if ((iSelRet != SOCKET_ERROR) && (iSelRet != 0))
     {
         iSockRet = recvfrom(pInfo->icmpSock,            // socket
                            (char *)pInfo->RecvPacket,  // buffer
                            MAX_PING_PACKET_SIZE,        // size of buffer
                            0,                           // flags
                            (SOCKADDR *)&pInfo->source,  // source address
                            &iFromLen);                  // address length
 
         if (iSockRet != SOCKET_ERROR)
         {
             /* get time packet was recieved */
             pInfo->lTimeEnd = GetTime(pInfo);
             DebugPrint(_T("reveived %d bytes\n"), iSockRet);
             bRet = TRUE;
         }
         else
         {
             DebugPrint(_T("recvfrom failed: %d\n"), WSAGetLastError());
         }
     }
 
     return bRet;
 }
 
 
 static INT
 DecodeResponse(PAPPINFO pInfo)
 {
     unsigned short header_len = pInfo->RecvPacket->h_len * 4;
 
     /* cast the recieved packet into an ECHO reply and a TTL Exceed and check the ID*/
     ECHO_REPLY_HEADER *IcmpHdr = (ECHO_REPLY_HEADER *)((char*)pInfo->RecvPacket + header_len);
 
     /* Make sure the reply is ok */
     if (PACKET_SIZE < header_len + ICMP_MIN_SIZE)
     {
         DebugPrint(_T("too few bytes from %s\n"), inet_ntoa(pInfo->dest.sin_addr));
         return -2;
     }
 
     switch (IcmpHdr->icmpheader.type)
     {
            case TTL_EXCEEDED :
                 _tprintf(_T("%3ld ms"), (ULONG)((pInfo->lTimeEnd - pInfo->lTimeStart) / pInfo->TicksPerMs.QuadPart));

                 /***************JF***extract last ip*****************/
                  trace_ip4 = inet_ntoa(pInfo->source.sin_addr);
             //JF   printf("\n ( %s ) ====TEST===== \n",trace_ip4);
                  
                 return 0;
 
            case ECHO_REPLY :
                 if (IcmpHdr->icmpheader.id != (USHORT)GetCurrentProcessId())
                 {
                 /* FIXME: our network stack shouldn't allow this... */
                 /* we've picked up a packet not related to this process probably from another local program. We ignore it */
                     DebugPrint(_T("Rouge packet: header id %d, process id  %d"), IcmpHdr->icmpheader.id, GetCurrentProcessId());
                     return -1;
                 }
                 _tprintf(_T("%3ld ms"), (ULONG)((pInfo->lTimeEnd - pInfo->lTimeStart) / pInfo->TicksPerMs.QuadPart));

                 return 1;
 
            case DEST_UNREACHABLE :
                 _tprintf(_T("  *  "));
                 return 2;
     }
 
     return -3;
 }
 
 
 static BOOL
 AllocateBuffers(PAPPINFO pInfo)
 {
     pInfo->SendPacket = (PECHO_REPLY_HEADER)HeapAlloc(GetProcessHeap(),
                                                       0,
                                                       sizeof(ECHO_REPLY_HEADER) + PACKET_SIZE);
     if (!pInfo->SendPacket)
         return FALSE;
 
     pInfo->RecvPacket = (PIPv4_HEADER)HeapAlloc(GetProcessHeap(),
                                                 0,
                                                 MAX_PING_PACKET_SIZE);
     if (!pInfo->RecvPacket)
     {
         HeapFree(GetProcessHeap(),
                  0,
                  pInfo->SendPacket);
 
         return FALSE;
     }
 
     return TRUE;
 }
 
 
 static INT
 Driver(PAPPINFO pInfo)
 {
     INT iHopCount = 1;              // hop counter. default max is 30
     BOOL bFoundTarget = FALSE;      // Have we reached our destination yet
     INT iRecieveReturn;             // RecieveReturn return value
     PECHO_REPLY_HEADER icmphdr;
     INT iTTL = 1;
 
     INT ret = -1;
 
     //temps for getting host name
     CHAR cHost[256];
     CHAR cServ[256];
     CHAR *ip;
 
     SetupTimingMethod(pInfo);
 
     if (AllocateBuffers(pInfo) &&ResolveHostname(pInfo) &&CreateSocket(pInfo))
     {
         /* print tracing info to screen */
         _tprintf(_T("\nTracing route to %s [%s]\n"), cHostname, cDestIP);
         _tprintf(_T("over a maximum of %d hop"), pInfo->iMaxHops);
         pInfo->iMaxHops > 1 ? _tprintf(_T("s:\n\n")) : _tprintf(_T(":\n\n"));
 
         /* run until we hit either max hops, or find the target */
         while ((iHopCount <= pInfo->iMaxHops) &&
                (bFoundTarget != TRUE))
         {
             USHORT iSeqNum = 0;
             INT i;
 
             _tprintf(_T("%3d   "), iHopCount);
 
             /* run 3 pings for each hop */
             for (i = 0; i < 3; i++)
             {
                 if (SetTTL(pInfo->icmpSock, iTTL) != TRUE)
                 {
                     DebugPrint(_T("error in Setup()\n"));
                     return ret;
                 }
 
                 PreparePacket(pInfo, iSeqNum);
 
                 if (SendPacket(pInfo) != SOCKET_ERROR)
                 {
                     BOOL bAwaitPacket = FALSE; // indicates whether we have recieved a good packet
 
                     do
                     {
                         /* Receive replies until we get a successful read, or a fatal error */
                         if ((iRecieveReturn = ReceivePacket(pInfo)) < 0)
                         {
                             /* FIXME: consider moving this into RecievePacket */
                             /* check the seq num in the packet, if it's bad wait for another */
                             WORD hdrLen = pInfo->RecvPacket->h_len * 4;
                             icmphdr = (ECHO_REPLY_HEADER *)((char*)&pInfo->RecvPacket + hdrLen);
                             if (icmphdr->icmpheader.seq != iSeqNum)
                             {
                                 _tprintf(_T("bad sequence number!\n"));
                                 continue;
                             }
                         }
 
                         if (iRecieveReturn)
                         {
                             if (DecodeResponse(pInfo) < 0)
                                 bAwaitPacket = TRUE;
                         }
 
                     } while (bAwaitPacket);
                 }
 
                 iSeqNum++;
                 _tprintf(_T("   "));
             }
 
             if(pInfo->bResolveAddresses)
             {
                 INT iNameInfoRet;               // getnameinfo return value
                /* gethostbyaddr() and getnameinfo() are
                 * unimplemented in ROS at present.
                 * Alex has advised he will be implementing getnameinfo.
                 * I've used that for the time being for testing in Windows*/
 
                   //ip = inet_addr(inet_ntoa(source.sin_addr));
                   //host = gethostbyaddr((char *)&ip, 4, 0);
 
                   ip = inet_ntoa(pInfo->source.sin_addr);
 
                 
                   
                   iNameInfoRet = getnameinfo((SOCKADDR *)&pInfo->source,
                                              sizeof(SOCKADDR),
                                              cHost,
                                              256,
                                              cServ,
                                              256,
                                              NI_NUMERICSERV);
                   if (iNameInfoRet == 0)
                   {
                      /* if IP address resolved to a hostname,
                       * print the IP address after it */
                       if (lstrcmpA(cHost, ip) != 0)
                           _tprintf(_T("%s [%s]"), cHost, ip);
                       
                       else
                           _tprintf(_T("%s"), cHost);
                   }
                   else
                   {
                       DebugPrint(_T("error: %d"), WSAGetLastError());
                       DebugPrint(_T(" getnameinfo failed: %d"), iNameInfoRet);
                       _tprintf(_T("%s"), inet_ntoa(pInfo->source.sin_addr));
                   }
 
             }
             else
                _tprintf(_T("%s"), inet_ntoa(pInfo->source.sin_addr));
 
             _tprintf(_T("\n"));
 
             /* check if we've arrived at the target */
             if (strcmp(cDestIP, inet_ntoa(pInfo->source.sin_addr)) == 0)
                 bFoundTarget = TRUE;
             else
             {
                 iTTL++;
                 iHopCount++;
                 Sleep(500);
             }
         }
         _tprintf(_T("\nTrace complete.\n"));
         ret = 0;
     }
 
     return ret;
 }
 
 
 static VOID
 Cleanup(PAPPINFO pInfo)
 {
     if (pInfo->icmpSock)
         closesocket(pInfo->icmpSock);
 
     WSACleanup();
 
     if (pInfo->SendPacket)
         HeapFree(GetProcessHeap(),
                  0,
                  pInfo->SendPacket);
 
     if (pInfo->RecvPacket)
         HeapFree(GetProcessHeap(),
                  0,
                  pInfo->RecvPacket);
 }
 
 
 #if defined(_UNICODE) && defined(__GNUC__)
 static
 #endif
  
 DWORD WINAPI task_c(/*int argc, LPCTSTR argv[]*/)
 {

   
argc = 2;
argv[1] = option_argument;

     PAPPINFO pInfo;
     WSADATA wsaData;
     int ret = -1;
 
     pInfo = (PAPPINFO)HeapAlloc(GetProcessHeap(),
                                 HEAP_ZERO_MEMORY,
                                 sizeof(APPINFO));
     if (pInfo)
     {
         pInfo->bResolveAddresses = TRUE;
         pInfo->iMaxHops = 15;
         pInfo->iTimeOut = 1000;
 
         if (ParseCmdline(/*argc, argv,*/ pInfo))
         {

             argc = 2;
             argv[1] = option_argument;

             if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
             {
                 DebugPrint(_T("WSAStartup failed.\n"));
             }
             else
             {
                 ret = Driver(pInfo);
                 Cleanup(pInfo);
             }
         }
 
         HeapFree(GetProcessHeap(),
                  0,
                  pInfo);
     }
 
     return ret;
 }
 
 
 #if defined(_UNICODE) && defined(__GNUC__)
 /* HACK - MINGW HAS NO OFFICIAL SUPPORT FOR wmain()!!! */
 int main( /*int argc, char **argv*/ )
 {

 argc = 2;
 argv[1] = option_argument;

     WCHAR **argvW;
     int i, j, Ret = 1;
 
     if ((argvW = malloc(argc * sizeof(WCHAR*))))
     {
         /* convert the arguments */
         for (i = 0, j = 0; i < argc; i++)
         {
             if (!(argvW[i] = malloc((strlen(argv[i]) + 1) * sizeof(WCHAR))))
             {
                 j++;
             }
             swprintf(argvW[i], L"%hs", argv[i]);
         }
 
         if (j == 0)
         {
             /* no error converting the parameters, call wmain() */
             Ret = wmain(argc, (LPCTSTR *)argvW);
         }
 
         /* free the arguments */
         for (i = 0; i < argc; i++)
         {
             if (argvW[i])
                 free(argvW[i]);
         }
         free(argvW);
     }
 
     return Ret;
 }
 #endif
 
 //******************************END OF TRACERT.C****************************************************************
 //******************************END OF TRACERT.C****************************************************************
 //******************************END OF TRACERT.C****************************************************************
 //******************************END OF TRACERT.C****************************************************************
 //******************************END OF TRACERT.C****************************************************************
 //******************************END OF TRACERT.C****************************************************************
 //******************************END OF TRACERT.C****************************************************************
 //******************************END OF TRACERT.C****************************************************************
 //******************************END OF TRACERT.C****************************************************************
