/***
 *     ██▓███   ██▀███   ▒█████   ██▓███   ██▓ ███▄    █   ▄████ 
 *    ▓██░  ██▒▓██ ▒ ██▒▒██▒  ██▒▓██░  ██▒▓██▒ ██ ▀█   █  ██▒ ▀█▒
 *    ▓██░ ██▓▒▓██ ░▄█ ▒▒██░  ██▒▓██░ ██▓▒▒██▒▓██  ▀█ ██▒▒██░▄▄▄░
 *    ▒██▄█▓▒ ▒▒██▀▀█▄  ▒██   ██░▒██▄█▓▒ ▒░██░▓██▒  ▐▌██▒░▓█  ██▓
 *    ▒██▒ ░  ░░██▓ ▒██▒░ ████▓▒░▒██▒ ░  ░░██░▒██░   ▓██░░▒▓███▀▒
 *    ▒▓▒░ ░  ░░ ▒▓ ░▒▓░░ ▒░▒░▒░ ▒▓▒░ ░  ░░▓  ░ ▒░   ▒ ▒  ░▒   ▒ 
 *    ░▒ ░       ░▒ ░ ▒░  ░ ▒ ▒░ ░▒ ░      ▒ ░░ ░░   ░ ▒░  ░   ░ 
 *    ░░         ░░   ░ ░ ░ ░ ▒  ░░        ▒ ░   ░   ░ ░ ░ ░   ░ 
 *                ░         ░ ░            ░           ░       ░ 
 *                                                               
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <pthread.h> 


//----------------section timer-------
#include <sys/time.h>
#include <signal.h>
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
int initial_sendingmail;
char *log_fpname_sendmail;

int sendmail_bool_mode;
int flag_ipdown_remember;
int sendingmail_freq_min;

//--------






	//---------------------------function thread task sendingmail_timer---------------------------------------------
		void timer_handler (int signum)
		{
		 static int count_timer = 0;
		 //printf ("timer expired %d times\n", count_timer);
			++count_timer;
			if(count_timer >= sendingmail_freq_min){
				flag_timer_sendingmail = 1; //JF flag to open timer door to sending mail
			   count_timer = 0;		//JF
			}
		//++ count_timer;
		}

		int sendingmail_timer()
		{
			
				 struct sigaction sa;
				 struct itimerval timer;

				 /* Install timer_handler as the signal handler for SIGVTALRM. */
				 memset (&sa, 0, sizeof (sa));

				 sa.sa_handler = &timer_handler;
				 sigaction (SIGVTALRM, &sa, NULL);

				 /* Configure the timer to expire after 250 msec... */
				 timer.it_value.tv_sec = 1;
				 timer.it_value.tv_usec = 0;
				 /* ... and every 250 msec after that. */
				 timer.it_interval.tv_sec = 1;
				 timer.it_interval.tv_usec = 0;
				 /* Start a virtual timer. It count_timers down whenever this process is
				   executing. */
				 setitimer (ITIMER_VIRTUAL, &timer, NULL);

				 /* Do busy work. */
		
				while (1);
			
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
     strcat(sendmail_message,buffer);	//JF message is last 16 lines of log file
    //write(STDOUT_FILENO, buffer, nread); //JF
  }
//printf("%s",sendmail_message);
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
                  
		  walkFile(file, atol("4")); //4 for 4 last line of the file, Warning, if lines are less, this is stacking!
return;
}
//----------------------------------------------------------------------------------












//------------function sendmail------------

	int sendmail(const char *to, const char *from, const char *subject, const char *message)
	{
	    int retval = -1;
	    FILE *mailpipe = popen("/usr/libexec/sendmail/sendmail -t", "w");
		    if (mailpipe != NULL) {
			fprintf(mailpipe, "To: %s\n", to);
			fprintf(mailpipe, "From: %s\n", from);
			fprintf(mailpipe, "Subject: %s\n\n", subject);
			fwrite(message, 1, strlen(message), mailpipe);
			fwrite(".\n", 1, 2, mailpipe);
			pclose(mailpipe);
			retval = 0;
		     }
		     else {
			 perror("Failed to invoke sendmail");
		     }
	
	strcpy(sendmail_message,"");	//It is important to flush the buffer, if not bug!!!
	flag_ipdown_remember = 1;
	flag_timer_sendingmail = 0;
	return;
	}
//-------------------------------------









//-------------------------------begin of threading task function, send mail---------------------------------------------

int *sendingmail(/*int argc, char** argv*/)
{
    
	for(;;)
	{
	sleep(1);
	
	if ((sendmail_bool_mode == 1) && (flag_ipdown_remember == 0) && ((flag_timer_sendingmail == 1)||(initial_sendingmail == 1) ) ){
		initial_sendingmail = 0;

	/*
	 *	printf("\n -----------sendingmail_freq_min= %d !!!!!!!!!!!!!!!!!!!!\n", sendingmail_freq_min);
	 * 	printf("\n -----------sendmail_bool_mode= %d !!!!!!!!!!!!!!!!!!!!\n", sendmail_bool_mode);
	 *	printf("\n -----------flag_ipdown_remember= %d !!!!!!!!!!!!!!!!!!!!\n", flag_ipdown_remember);
	 */

	//printf("\n -----------sendingmail_time= %d !!!!!!!!!!!!!!!!!!!!\n", sendingmail_time);
	    //sleep(sendingmail_time);//-timer in min to sending mail at different frequence in function of sec


				int argc;
				char *argv[5];

				/*
				    int i;

				    printf("argc = %d\n", argc);

				    for (i = 0; i < argc; i++)
					printf("argv[%d] = \"%s\"\n", i, argv[i]);
				*/
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

				strcpy(sendmail_message,""); //Flusch buffer
				reader();	// Filler of message in function of last line of log file
				argv[4]= sendmail_message;

			 sendmail(argv[1], argv[2], argv[3], argv[4]);

		}

	}
    
}
//-------------------------------end of function to send mail---------------------------------------------

