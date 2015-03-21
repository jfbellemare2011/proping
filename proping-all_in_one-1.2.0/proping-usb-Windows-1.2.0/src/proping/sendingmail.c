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
char *log_fpname_sendmail;
int sendmail_bool_type;
int initial_sendingmail;
int initial_timer = 0;
int sendmail_bool_mode;
int flag_ipdown_remember;
int sendingmail_freq_min;

//--------
const char * log_fpname;


	//---------------------------function thread task sendingmail_timer---------------------------------------------

sendingmail_timer()
{

	while(initial_timer == 0)
	{
	sleep(1);
	}

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
   

/******old function to strip message to parsing in -BODY no in -bodyfile*******/
/*void strip(char *s) {
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
strip(buffer);*/
/***********************/

    strcat(sendmail_message,buffer);
    //write(STDOUT_FILENO, buffer, nread); //JF

  }

 /*****************************/ 

      FILE *fp;
      int i;
   
      /* open the file */
      fp = fopen("./tmp/stat.txt", "w");
      if (fp == NULL) {
         printf("I couldn't open ./tmp/stat.txt for writing.\n");
         return;
      }
      /* write to the file */
         fprintf(fp, "%s",sendmail_message);
   
      /* close the file */
      fclose(fp);
   
      return;
 
  /*****************************/
  
  
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

	//--------creating log directory and file via system ./tmp/stat.txt------------------
	/*********/
	//#define MY_MASK 0755	//mkdir function mask
	int code = mkdir("./tmp");

	if (code == 0) {
		//if(verbose == 1){
		printf("./tmp repertory has been created;\n"); 
		//}
	} else {
	//printf("Log repertory already exist\n"); 
	}

	#define CMD_STATISTIC "powershell ./proping.exe stat > ./tmp/stat.txt"
	system(CMD_STATISTIC);
	/*********/

		  #define PATH_STATFILE "./tmp/stat.txt"
			/*********count line of statistic file***********/
			    FILE *fpIn;
			    int lines = 0;
			    char buf[BUFSIZ];
			 
			    if ((fpIn = fopen(PATH_STATFILE,"r")) == NULL) {
				perror ("Could not open file: ");
				return;
			    }
			 
			    while (fgets(buf,sizeof(buf),fpIn) != NULL){
				lines++;
			    }
			/**************************************/
		/***To rest under 10 lines****/
                  if (lines > 20){
			lines = 20;
		  }
		/*****************************/

		  FILE *file;
		  file= openFile(PATH_STATFILE); //The reference of log_fpname is in other file from proping.c,
                                                       // it is to catch date time of the log file
		  walkFile(file, lines); //as tail command for 20 last line of the file, Warning, if lines are less, this is stacking!
			//  walkFile(file, atol(lines)); if lines was a string
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
            strcat(sendsmtp_command_strcat, " /BODYFILE \"");
            strcat(sendsmtp_command_strcat, "./tmp/stat.txt");
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
                initial_timer = 1;
	//printf("\n -----------sendingmail_freq_min= %d !!!!!!!!!!!!!!!!!!!!\n", sendingmail_freq_min);
	//printf("\n -----------sendmail_bool_mode= %d !!!!!!!!!!!!!!!!!!!!\n", sendmail_bool_mode);
	//printf("\n -----------flag_ipdown_remember= %d !!!!!!!!!!!!!!!!!!!!\n", flag_ipdown_remember);

	//printf("\n -----------sendingmail_time= %d !!!!!!!!!!!!!!!!!!!!\n", sendingmail_time);
                        
                    /************************************/
			if(sendmail_bool_type == 1){
                                reader();
                        
				char cmdpowershell_sendingmail[2048] = "";
                                
				strcat(cmdpowershell_sendingmail,"powershell Send-MailMessage");
				strcat(cmdpowershell_sendingmail," -SMTPServer ");
                                strcat(cmdpowershell_sendingmail,"\'");
				strcat(cmdpowershell_sendingmail, sendmail_host );
                                strcat(cmdpowershell_sendingmail,"\'");
				strcat(cmdpowershell_sendingmail," -Port ");
                                strcat(cmdpowershell_sendingmail,"\'");
				strcat(cmdpowershell_sendingmail, sendmail_host_port );
                                strcat(cmdpowershell_sendingmail,"\'");
                                strcat(cmdpowershell_sendingmail," -From ");
                                strcat(cmdpowershell_sendingmail,"\'");
				strcat(cmdpowershell_sendingmail, sendmail_from);
                                strcat(cmdpowershell_sendingmail,"\'");
                                strcat(cmdpowershell_sendingmail," -To ");
                                strcat(cmdpowershell_sendingmail,"\'");        
				strcat(cmdpowershell_sendingmail, sendmail_to);
                                strcat(cmdpowershell_sendingmail,"\'");                               
                                strcat(cmdpowershell_sendingmail," -Subject ");
                                strcat(cmdpowershell_sendingmail,"\'");
				strcat(cmdpowershell_sendingmail, sendmail_subject);
                                strcat(cmdpowershell_sendingmail,"\'");
                                strcat(cmdpowershell_sendingmail," -Body ");
                                strcat(cmdpowershell_sendingmail," \" \' \" ");
                                strcat(cmdpowershell_sendingmail,"To see the attachments!");
				strcat(cmdpowershell_sendingmail," \"\'\"" );
                                strcat(cmdpowershell_sendingmail," -Attachments");
                                strcat(cmdpowershell_sendingmail," \"\'\"");
                                strcat(cmdpowershell_sendingmail,"./tmp/stat.txt");
				strcat(cmdpowershell_sendingmail," \"\'\" > ./tmp/null" );


				int ret_powershell = system(cmdpowershell_sendingmail);

					sleep(10); //
                                //printf("\n -----------ret_powershell= %d !!!!!!!!!!!!!!!!!!!!\n", ret_powershell);


					strcpy(sendmail_message,""); //Flusch buffer
					flag_ipdown_remember = 1;
					flag_timer_sendingmail = 0;

			/************************************/
				printf("\n===================================================\n");
				printf("\nA warning mail is sending via telnet !!!\n");
				printf("to; %s \n", sendmail_to);
				printf("from; %s \n", sendmail_from);
				printf("subject; %s \n", sendmail_subject);
				printf("\n===================================================\n");
                                
                                if (ret_powershell == 0){
                
                                printf("\n===================================================\n");
                                printf("\n Email; sent successfully!!!\n");
                                }else{
                                printf("\n Email; message not send!!!\n\n");
                                printf("\n It is important to use powershell v.3.0 and over!!!\n\n");
                                }
                                printf("\n===================================================\n");
			/************************************/
			}

			if(sendmail_bool_type == 0){
				int argc;
				char *argv[5];

				printf("\n===================================================\n");
				printf("\nA warning mail is sending via sendsmtp !!!\n");
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
    
}
//-------------------------------end of function to send mail---------------------------------------------

