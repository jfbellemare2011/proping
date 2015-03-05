/***
 *                            _             
 *      _ __  _ __ ___  _ __ (_)_ __   __ _ 
 *     | '_ \| '__/ _ \| '_ \| | '_ \ / _` |
 *     | |_) | | | (_) | |_) | | | | | (_| |
 *     | .__/|_|  \___/| .__/|_|_| |_|\__, |
 *     |_|             |_|            |___/ 
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>

//----------------section timer-------
#include <time.h>

int sendingmail_freq_min;
int flag_timer_sendingmail = 0;

//--------------section reader file for message
//#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <errno.h>
#include <unistd.h>
#include <getopt.h>
//---------------------------------------------
//----------declaration general variable--------------------
char sendmail_mode[16];
char sendmail_to[512];
char sendmail_from[64];
char sendmail_subject[128];
#define BUFF_SIZE 4096
char sendmail_message[BUFF_SIZE];
char sendmail_host[15];
char sendmail_host_port[15];
int initial_sendingmail;

char *log_fpname_sendmail;
int sendmail_bool_mode;
int flag_ipdown_remember;
int sendingmail_freq_min;

//--------
const char * log_fpname;


	//---------------------------function thread task sendingmail_timer---------------------------------------------

sendingmail_timer()
{
	unsigned int x_hours=0;
	unsigned int x_minutes=0;
	unsigned int x_seconds=0;
	unsigned int x_milliseconds=0;
	unsigned int totaltime=0,count_down_time_in_secs=0,time_left=0;
        int count = 0;
	clock_t x_startTime,x_countTime;
	//count_down_time_in_secs = (sendingmail_freq_min*60);  // 1 minute is 60, 1 hour is 3600

 
    x_startTime=clock();  // start clock
    time_left = count_down_time_in_secs - x_seconds;   // update timer

	while (1) 
	{
		x_countTime=clock(); // update timer difference
		x_milliseconds= x_countTime - x_startTime;
		x_seconds=(x_milliseconds/(CLOCKS_PER_SEC))-(x_minutes*60);
		x_minutes=(x_milliseconds/(CLOCKS_PER_SEC))/60;
		x_hours=x_minutes/60;
                
		time_left=count_down_time_in_secs - x_seconds; // subtract to get difference 
                //printf( "\nYou have %d seconds left ( %d ) count down timer by TopCoder",time_left,count_down_time_in_secs);
                
                if(x_seconds == 60){
                    count++;
                    //printf( "\n  minutes %d", count);
                }
    
                if((count*60) >= sendingmail_freq_min){
                    count = 0;
                    x_startTime=clock();  // restart clock
                    flag_timer_sendingmail = 1; //JF flag to open timer door to sending mail
                }
	}
return;
}
		

   	//------------------------------------------------------------------------------









//------------function reader_tail---------------------------------------

#define _FILE_OFFSET_BITS 64
#define BUFF_SIZE 4096

FILE *openFile(const char *filePath)
{
  FILE *file;
  file= fopen(filePath, "r");
  if(file == NULL)
  {
    //fprintf(stderr,"Error opening file: %s\n",filePath);
    exit(errno);
  }
  return(file);
}

void printLine(FILE *file, off_t startline)
{
  int fd;
  fd= fileno(file);
  int nread;
  char buffer[BUFF_SIZE];
  lseek(fd,(startline + 1),SEEK_SET);
  while((nread= read(fd,buffer,BUFF_SIZE)) > 0)
  {
   /*  strcat(sendmail_message,"echo \"");
     strcat(sendmail_message,buffer);
     strcat(sendmail_message, "\" >> ./tmp_smtp_body.txt ");
     system(sendmail_message);
     strcpy(sendmail_message,"");*/
     //system(sendmail_message);
       
  
      
      
      
      
/***********************/
void strip(char *s) {
    char *p2 = s;
    while(*s != '\0') {
    	if(*s != '\t' && *s != '\n') {
    		*p2++ = *s++;
    	} else {
    		++s;
    	}
    }
    *p2 = '\0';
}
/***********************/  
strip(buffer);


    strcat(sendmail_message,buffer);
  
        //JF message is last 16 lines of log file
    //write(STDOUT_FILENO, buffer, nread); //JF
  }
return;
}

void walkFile(FILE *file, long nlines)
{
  off_t fposition;
  fseek(file,0,SEEK_END);
  fposition= ftell(file);
  off_t index= fposition;
  off_t end= fposition;
  long countlines= 0;
  char cbyte;

  for(index; index >= 0; index --)
  {
    cbyte= fgetc(file);
    if (cbyte == '\n' && (end - index) > 1)
    {
      countlines ++;
      if(countlines == nlines)
      {
    break;
      }
     }
    fposition--;
    fseek(file,fposition,SEEK_SET);
  }
  printLine(file, fposition);
  fclose(file);
return;
}


void reader(/*int argc, char *argv[]*/)
{

 // printf ("\n --- log_fpname_sendmail; %s ---\n", log_fpname_sendmail);
		  FILE *file;
		  file= openFile(log_fpname_sendmail); //The reference of log_fpname is in other file from proping.c,
                                                       // it is to catch date time of the log file
                  
		  walkFile(file, atol("4")); //16 for sixteen last line of the file
return;
}
//----------------------------------------------------------------------------------












//------------function sendmail------------

	int sendmail(const char *to, const char *from, const char *subject, const char *message)
	{
                    
            char sendsmtp_command_strcat[4096] = "";
            strcat(sendsmtp_command_strcat, "SendSMTP.exe /nos /host ");
            strcat(sendsmtp_command_strcat, sendmail_host);
            strcat(sendsmtp_command_strcat, " /port " );
            strcat(sendsmtp_command_strcat, sendmail_host_port);
            strcat(sendsmtp_command_strcat, " /from " );
            strcat(sendsmtp_command_strcat, from);
            strcat(sendsmtp_command_strcat, " /to ");
            strcat(sendsmtp_command_strcat, to); 
            strcat(sendsmtp_command_strcat, " /subject "); 
            strcat(sendsmtp_command_strcat, subject);
            strcat(sendsmtp_command_strcat, " /BODY \"");
            strcat(sendsmtp_command_strcat, message);
            strcat(sendsmtp_command_strcat, "\"");

            //strcat(sendsmtp_command_strcat, log_fpname);

                         //  printf("\n %s !!!\n",message);

            int send_smtp_return = system(sendsmtp_command_strcat);
            if (send_smtp_return == 0){
                
                printf("\n===================================================\n");
                printf("\n Email; sent successfully!!!\n");
                }else{
                printf("\n Email; message not send!!!\n\n");
                }
                printf("\n===================================================\n");

            
	flag_ipdown_remember = 1;
	flag_timer_sendingmail = 0;
	return;
	}
//-------------------------------------









//-------------------------------begin of threading task function, send mail---------------------------------------------

sendingmail(/*int argc, char** argv*/)
{
    
    
    while(1)
	{
	sleep(1);
        
	if ((sendmail_bool_mode == 1) && (flag_ipdown_remember == 0) && ((flag_timer_sendingmail == 1)||(initial_sendingmail == 1) ) ){
		initial_sendingmail = 0;

	//printf("\n -----------sendingmail_freq_min= %d !!!!!!!!!!!!!!!!!!!!\n", sendingmail_freq_min);
	//printf("\n -----------sendmail_bool_mode= %d !!!!!!!!!!!!!!!!!!!!\n", sendmail_bool_mode);
	//printf("\n -----------flag_ipdown_remember= %d !!!!!!!!!!!!!!!!!!!!\n", flag_ipdown_remember);

	//printf("\n -----------sendingmail_time= %d !!!!!!!!!!!!!!!!!!!!\n", sendingmail_time);


				int argc;
				char *argv[5];

				printf("\n===================================================\n");
				printf("\nA warning mail is sending !!!\n");
				printf("to; %s \n", sendmail_to);
				printf("from; %s \n", sendmail_from);
				printf("subject; %s \n", sendmail_subject);
				printf("\n===================================================\n");

				argc = 5;
				argv[1]= sendmail_to;
				argv[2]= sendmail_from;
				argv[3]= sendmail_subject;

				strcpy(sendmail_message,""); //Flusch body message
				reader();	// Filler of message in function of last line of log file
				argv[4]= sendmail_message;

			 sendmail(argv[1], argv[2], argv[3], argv[4]);

		}

	}
    
}
//-------------------------------end of function to send mail---------------------------------------------

