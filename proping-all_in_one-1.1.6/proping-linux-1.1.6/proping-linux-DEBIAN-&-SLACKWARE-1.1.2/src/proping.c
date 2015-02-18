#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char flag_word = 0;
char flag_ipdown = 0;
char verbose = 1;

char *option_name;
char *option_argument;
char *trace_ip4;

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
#define KILLTRACEROUTE "ps -e | grep traceroute | awk '{print $1}'| xargs kill -15"
#define SHELLSTART "/usr/sbin/proping shellstart &"

if (argc == 1){			//Important; this is a way to do a restart by the init.d/service for redhat
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

system(KILLTRACEROUTE);
system(KILLPROCESSUS);
exit(0);

}else if (strcmp(argv[1],arg_start)==0){
puts (argv[1]);

//#define PROCFS "mount -t procfs proc /proc"
//system(PROCFS);
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

pinger();

compare_ip_arguments();
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

int pinger(void)
{
/*****concatenate command for system(ping)****/

#define PING_COMMAND_STRCAT1 "ping -c 3 "
#define PING_COMMAND_STRCAT2 " > /dev/null"
//	#define PING_COMMAND_STRCAT2 " -c 3"
#define TRACE_COMMAND_STRCAT1 "traceroute -m 15 "
#define TRACE_COMMAND_STRCAT2 " > /tmp/tmptrace.txt"

char ping_command_strcat[256] = "";
char trace_command_strcat[256] = "";	

strcat(ping_command_strcat, PING_COMMAND_STRCAT1); //
//printf("%s\n", option_argument);
strcat(ping_command_strcat, option_argument); //---Concatenate for ping command
strcat(ping_command_strcat, PING_COMMAND_STRCAT2);
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
int ret=system(ping_command_strcat);  // It have to concerve variable in INT if not then don't function
//printf("\nResult : %d\n\n",ret);
sleep(1);

if(ret == 0){
if(verbose == 1){
printf("OK! \n", option_argument);
}
flag_word = 0;

}else{

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
const char * log_fpname = file_log_path;

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
strcat(wall_commandlog_strcat, " > /tmp/propingwall.txt");
system(wall_commandlog_strcat);

char propingwall2[256] = "" ;
strcat(propingwall2, "wall /tmp/propingwall.txt");
system(propingwall2);
//-----------


if(verbose == 1){
printf("Not reached!!! \007\n\n");

printf("Please wait for the time to finish traceroute analysis!!!\n\n\n");
} // onside is vorbose only



char echo_commandlog_strcat[256] = "";
strcat(echo_commandlog_strcat, "echo " );
strcat(echo_commandlog_strcat, insidefile_date_log);
strcat(echo_commandlog_strcat, "-----");
strcat(echo_commandlog_strcat, "!!!Warning !!! Interface Not reached!!! : ");
strcat(echo_commandlog_strcat, option_name);
strcat(echo_commandlog_strcat, option_argument);
strcat(echo_commandlog_strcat, " >> ");
strcat(echo_commandlog_strcat, log_fpname);
//printf("\n\n%s\n\n",echo_commandlog_strcat );
system(echo_commandlog_strcat);



//-----------------------------------------------------------------------------------------------





flag_word = 1;

strcat(trace_command_strcat, TRACE_COMMAND_STRCAT1); //

strcat(trace_command_strcat, option_argument); //---Concatenate for traceroute command
system(trace_command_strcat);
strcat(trace_command_strcat, TRACE_COMMAND_STRCAT2);

system(trace_command_strcat);




}

return 0;
}

/**********function compare_ip_arguments() argument of ip address************************************************************/

int compare_ip_arguments(void)
{


//--------------creating log directory /var/log/proping------------------

#define MY_MASK 0755	//mkdir function mask
int code = mkdir("/var/log/proping", MY_MASK);

if (code == 0) {
printf("Log repertory has been created; /var/log/proping\n"); 

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



//---------------------------
down_traceroute();
//---------------------------


//printf("String %d : %s\n",z+1,(*ptr_arr_downs)[z]);


char wall_command_strcat[256] = "";
strcat(wall_command_strcat, "echo !!!Warning!!! communication between " ); //---Concatenate for wall command
strcat(wall_command_strcat, trace_ip4);
strcat(wall_command_strcat, " to interface ");
strcat(wall_command_strcat, option_name); //---
strcat(wall_command_strcat, option_argument);
strcat(wall_command_strcat, ", is stopped!!! You have to see if the interface is existing before searching the network problem, refer to the configuration file");
strcat(wall_command_strcat, " > /tmp/propingwall.txt");
system(wall_command_strcat);

char propingwall[256] = "";
strcat(propingwall, " wall /tmp/propingwall.txt");



if(strcmp(option_argument,trace_ip4)==0){

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

} else if (strcmp(option_argument,trace_ip4)!=0){
if(verbose == 1){
printf("\n\n\n=========warning!!!=========warning!!!=========warning!!!=========\n");
printf("   Down!!!							  	\n");
printf("		Down!!!				Down!!!		  	\n");
printf("		 		Down!!!				        \n");
}
//-------------------------------------------------------------------------------------
system(propingwall);

//-------------
char wall_command_strcat[256] = "";
strcat(wall_command_strcat, "echo !!!Warning!!! communication between " ); //---Concatenate for wall command
strcat(wall_command_strcat, trace_ip4);
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


/**********function down_traceroute() to find the begin of the down******************************************************************/


int down_traceroute(void)
{

char **array_trace;
int g;
int lines_allocated = 130;
int max_line_len = 256;

/* Allocate lines of text */
array_trace = (char **)malloc(sizeof(char*)*lines_allocated);

if (array_trace==NULL)
{
fprintf(stderr,"Out of memory (1).\n");
exit(1);
}

FILE *fp = fopen("/tmp/tmptrace.txt", "r");
if (fp == NULL)
{
fprintf(stderr,"Error opening file.\n");
exit(2);
}

int i;
for (i=0;1;i++)
{
int g;

/* Have we gone over our line allocation? */
if (i >= lines_allocated)
{
int new_size;

/* Double our allocation and re-allocate */
new_size = lines_allocated*2;
array_trace = (char **)realloc(array_trace,sizeof(char*)*new_size);
if (array_trace==NULL)
{
fprintf(stderr,"Out of memory.\n");
exit(3);
}
lines_allocated = new_size;
}
/* Allocate space for the next line */
array_trace[i] = malloc(max_line_len);
if (array_trace[i]==NULL)
{
fprintf(stderr,"Out of memory (3).\n");
exit(4);
}
if (fgets(array_trace[i],max_line_len-1,fp)==NULL)
break;

/* Get rid of CR or LF at end of line */
for (g=strlen(array_trace[i])/*-1*/;g>=0 && (array_trace[i][g]=='\n' || array_trace[i][g]=='\r');g--)
;
array_trace[i][g]='\0';
}

//----------------------------Fusion between array and hashing-------------------------------------

char *ptr;
char target[]= "("; //In file ping_result.txt, we testing the word received to know if interface ip is up
char *trace_ip1;
char *trace_ip2;
char *trace_ip3;
//	  char *trace_ip4;    //It have to declarate it as extern global variable

//    int g;
//printf("Thoses interfaces will be scanned.\n");
for(g = 0; g < i; g++){
//	printf("%s", array_trace[g]);

//--------------------------------------------------------------------------------------------------------
if( i != g ){
ptr = strstr(array_trace[g], target);
//sleep(3);

if(ptr){
//	printf("\nThe substring starts at the %d char", ptr-buff);
//	printf(ptr,"\n"); 

}
if(ptr != NULL){

//----------It's olding on the last ip address, up, finded------------
trace_ip1 = strtok(ptr, "(" );
trace_ip2 = strtok( trace_ip1, ")" ) ;

trace_ip3 = strtok( trace_ip2, "m" ) ;
trace_ip4 = strtok( trace_ip3, " " ) ;
//-------------------------------------

}
}
//printf("%s\n",trace_ip4,"\n");

/* Good practice to free memory */
//    for (;i>=0;i--)
//        free(array_trace[i]);
//    free(array_trace);
}

return 0;
}
/*******************************************************************END OF PAGE******************************************************************************/
