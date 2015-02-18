#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>

#include <time.h>


int main(void){
//--------------creating log directory /var/log/proping------------------

 #define MY_MASK 0755	//mkdir function mask
 int code = mkdir("/var/log/proping", MY_MASK);

 if (code == 0) {
 	printf("Log repertory has been created; /var/log/proping\n"); 

 } else {
 	//printf("Log repertory already exist\n"); 
 }

//--------------creating conf directory /etc/proping------------------
	int code2 = mkdir("/etc/proping", MY_MASK);

	 if (code2 == 0) {
	 	printf("Configuration repertory has been created; /var/log/proping\n"); 

	 } else {
	 	//printf("/etc/proping repertory already exist\n"); 
	 }
	

//------------------Backup configuration files---------------------------

/*
	The program uses block I/O to copy a file.
*/
//-------------------------------------
	int c;
	char path_source_file[64];
	char path_destination_file[64];
	char date[64];

	time_t now = time(NULL);
        struct tm * tm = localtime(&now);

	strcpy(path_source_file, "/etc/proping/proping.conf");

    //-----file path with date--

	strcpy(path_destination_file, "/etc/proping/proping.conf.");
        strftime(date, sizeof date, "%B_%d_%Y_%H:%M:%S", tm);
	strcat(path_destination_file, date); //---Concatenate for backup conf file in function of time
        #define BACKUP ".back"
	strcat(path_destination_file, BACKUP); //---Concatenate for backup conf file in function of time

printf("%s",path_destination_file );
    //-------
	FILE  *input, *output;
//-------------------------------------

	  
  	  //fprintf(stderr, "Date = %s\n", ctime(&now));

	printf("\n***Binary File Copy - /etc/proping/proping.conf to /etc/proping/proping.conf.date.back ***\n");
	//printf("Input File:");
	//gets(s);
	input = fopen(path_source_file, "r");

	if (!input){
		printf("Unable to open input file not exist, we will create it\n");


			strcpy(path_source_file, "proping.conf");
			strcpy(path_destination_file, "/etc/proping/proping.conf");


			printf("\n***Binary File Copy - /etc/proping/proping.conf ***\n");
			//printf("Input File:");
			//gets(s);
			input = fopen(path_source_file, "r");

			if (!input){
				printf("Unable to open input file\n");
				exit(0);
			}

			//printf("Output File:");
			//gets(s);
			output = fopen(path_destination_file, "wb");

			if (!output){
				printf("Unable to open output file\n");
				exit(0);
			}

			while ((c = fgetc(input)) != EOF)
				fputc(c, output);
			close(input);
			close(output);

			chmod(path_destination_file,0000755);

	}

	//printf("Output File:");
	//gets(s);
	output = fopen(path_destination_file, "wb");

	if (!output){
		printf("Unable to open output file\n");
		exit(0);
	}

	while ((c = fgetc(input)) != EOF)
		fputc(c, output);
	close(input);
	close(output);

	chmod(path_destination_file,0000755);

//-----------------------------------------------------------------------

/*
	The program uses block I/O to copy a file.
*/


	strcpy(path_source_file, "proping.conf");
	strcpy(path_destination_file, "/etc/proping/proping.conf");


	printf("\n***Binary File Copy - /etc/proping/proping.conf ***\n");
	//printf("Input File:");
	//gets(s);
	input = fopen(path_source_file, "r");

	if (!input){
		printf("Unable to open input file\n");
		exit(0);
	}

	//printf("Output File:");
	//gets(s);
	output = fopen(path_destination_file, "wb");

	if (!output){
		printf("Unable to open output file\n");
		exit(0);
	}

	while ((c = fgetc(input)) != EOF)
		fputc(c, output);
	close(input);
	close(output);

	chmod(path_destination_file,0000755);
//-----------------------------------------------------------------------

/*
	The program uses block I/O to copy a file.
*/


	strcpy(path_source_file, "proping");
	strcpy(path_destination_file, "/usr/sbin/proping");


	printf("\n***Binary File Copy - /usr/sbin/proping ***\n");
	//printf("Input File:");
	//gets(s);
	input = fopen(path_source_file, "r");

	if (!input){
		printf("Unable to open input file\n");
		exit(0);
	}

	//printf("Output File:");
	//gets(s);
	output = fopen(path_destination_file, "wb");

	if (!output){
		printf("Unable to open output file\n");
		exit(0);
	}

	while ((c = fgetc(input)) != EOF)
		fputc(c, output);
	close(input);
	close(output);

	 chmod(path_destination_file,0000755);
//-----------------------------------------------------------------------


/* 
	The program uses block I/O to copy a file.
*/

	strcpy(path_source_file, "proping.initd");
	strcpy(path_destination_file, "/etc/init.d/proping");


	printf("\n***Binary File Copy - /etc/init.d/proping ***\n");
	//printf("Input File:");
	//gets(s);
	input = fopen(path_source_file, "r");

	if (!input){
		printf("Unable to open input file\n");
		exit(0);
	}

	//printf("Output File:");
	//gets(s);
	output = fopen(path_destination_file, "wb");

	if (!output){
		printf("Unable to open output file\n");
		exit(0);
	}

	while ((c = fgetc(input)) != EOF)
		fputc(c, output);
	close(input);
	close(output);

 	chmod(path_destination_file,0000755);


//-----------------------------------------------------------------------

return 0;
}







