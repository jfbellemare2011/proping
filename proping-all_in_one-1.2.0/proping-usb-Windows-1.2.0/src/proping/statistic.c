/***
 *                            _             
 *      _ __  _ __ ___  _ __ (_)_ __   __ _ 
 *     | '_ \| '__/ _ \| '_ \| | '_ \ / _` |
 *     | |_) | | | (_) | |_) | | | | | (_| |
 *     | .__/|_|  \___/| .__/|_|_| |_|\__, |
 *     |_|             |_|            |___/ 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char *array_statistic[512][512];
int lines_allocated = 1024;
#define PATH_STATISTIC "./log/statistic.log"

int statistic(int argc, char **argv)
{

char arg_stat[] = "stat";
char arg_stat1[] = "stat1";
char arg_stat2[] = "stat2";

 /*if (argc == 1){		//Important; this is a way to do a restart by the init.d/service for redhat
     fprintf(stdout,"Usage : %s [stat|stat1|stat2]\n",*argv);
     sleep(1);
     exit(0);
 }*/
/********************************************************************************/

/*******Format logs files to statistic files********/
char cmd_statistic_strcat[256]="";
strcat(cmd_statistic_strcat,"powershell type ./log/proping*.log > ./log/statistic.log");
system(cmd_statistic_strcat);


/****to assure data in file********/
    FILE *fpIn2;
    int lines2 = 0;
    char buf2[BUFSIZ];
 
    if ((fpIn2 = fopen("./log/statistic.log","r")) == NULL) {
        perror ("Could not open file: ");
        exit(0);
    }
 
    while (fgets(buf2,sizeof(buf2),fpIn2) != NULL){
        lines2++;
    }
    
    
    if( (lines2 < 2) && (strcmp(argv[1],"stat")!=0) ){
    printf("\n\n Sorry, to build a statistical table we need more of a single line of information. Refer to your log file, please.\n; Number of line = %d \n\n",lines2);    
        exit(0);
    }

/********File to array**********/

//int lines_allocated = 1024;
int max_line_len = 128;

    /* Allocate lines of text */
    char **words = (char **)malloc(sizeof(char*)*lines_allocated);
    if (words==NULL)
        {
        fprintf(stderr,"Out of memory (1).\n");
        exit(1);
        }

    FILE *fp = fopen(PATH_STATISTIC, "r+");
    if (fp == NULL)
        {
        fprintf(stderr,"Error opening file.\n");
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
                fprintf(stderr,"Out of memory.\n");
                exit(3);
                }
            lines_allocated = new_size;
            }
        /* Allocate space for the next line */
        words[i] = malloc(max_line_len);
        if (words[i]==NULL)
            {
            fprintf(stderr,"Out of memory (3).\n");
            exit(4);
            }
        if (fgets(words[i],max_line_len-1,fp)==NULL)
            break;

        /* Get rid of CR or LF at end of line */
        for (j=strlen(words[i])-1;j>=0 && (words[i][j]=='\n' || words[i][j]=='\r');j--)
            ;
        words[i][j+1]='\0';
        }
    /* Close file */
    fclose(fp);

    int j;
    for(j = 0; j < i; j++){
	//printf("%d\n", i); // line number
        //printf("%s\n", words[j]);
     }
    /* Good practice to free memory 
    for (;i>=0;i--)
        free(words[i]);
    free(words);*/

  
/*******************Array formated to store haching array[x][y] *************************/

	int g;
	char *array_statistic[4096][13];

	for(g = 0; g < i; g++){
		//printf("%s\n", words[g]);

		/*******************************/
		int z;
		for(z = 0; z < 11; z++)
		{
		
		char *target[16] = {"B","H","m","s","C","E","G","R","I","-","+","P"};
		char *ptr;
		char *stat_limitor1;
		char stat_limitor1_copy[1];


		ptr = strstr(words[g], target[z]);
		
			//if(ptr){	//JF get out protection

				//if(ptr != NULL){	//JF get out protection
			
				stat_limitor1 = strtok(ptr, target[z+1] );
				//printf("target=(%s)-----------------------\n",target[z],"\n");
				//printf("target+1=(%s)-----------------------\n",target[z+1],"\n");
				strcpy(stat_limitor1_copy,"");
				strcpy(stat_limitor1_copy,stat_limitor1);

				/******to delete delimiter and spacer*********/
					void strip(char *s1)   {
					    char *p1 = s1;
					    while(*s1 != '\0') {


				if( *s1 != 'B' && *s1 != 'H' && *s1 != 'm' && *s1 != 's' &&*s1 != 'C' && *s1 != 'E' && *s1 != 'G' &&  *s1 != 'R' && *s1 != 'I' && *s1 != 'K' &&  *s1 != 'L' &&  *s1 != 'P' && *s1 != ' ') {
					    		*p1++ = *s1++;
			 	} else {
					 ++s1;
				 	}
					}
					 *p1 = '\0';
					}
					strip(stat_limitor1_copy);

					/***********************/  
			
		/*****function extract at exterior stat_limitor to general variable array[x][y]*********/

		 void strcpy_i( char **dst, char *src )
		 {
		    *dst=(char *)malloc((strlen(src)+1)*sizeof(char));
		    char *tmp=*dst;
		    while((*tmp++=*src++)!='\0');
		 }
			   	    char *d=NULL;
				    strcpy_i(&d,stat_limitor1_copy);
				
				  //  array_statistic[g][z] = d;

			//****************************JF; Extract string addr last address***

			    array_statistic[g+1][z+1]=malloc((strlen(d)+1)*sizeof(char));
			    strcpy(array_statistic[g+1][z+1],d);

			    //array_statistic[g][0]= "";
			    //printf("%d-%d =(%s) ",g,z,array_statistic[g][z+1]);

			//********************************************************************

		
				// }  //JF get out protection
			//}  //JF get out protection

		}
	}
/*************************************************************/


/*********count line of statistic file***********/


 
    FILE *fpIn;
    int lines = 0;
    char buf[BUFSIZ];
 
    if ((fpIn = fopen(PATH_STATISTIC,"r")) == NULL) {
        perror ("Could not open file: ");
        return EXIT_FAILURE;
    }
 
    while (fgets(buf,sizeof(buf),fpIn) != NULL){
        lines++;
    }
    //printf("This file contains %d lines\n",lines);
	lines++; // because script work in real number x=1 y=0 not 0 for x

/**************************************/






		/*****Add a limitor at end of array ";" to general variable array on[ lines + 1][y]*********/
		int u;
			for (u = 0; u <= 12 ; u++){
			void strcpy_i( char **dst, char *src )
			{
			*dst=(char *)malloc((strlen(src)+1)*sizeof(char));
			char *tmp=*dst;
			while((*tmp++=*src++)!='\0');
			}
			    char *d=NULL;
			    strcpy_i(&d,";");// possition lines by default, have a spacer

			  //  array_statistic[g][z] = d;

			//****************************JF; Extract string addr last address***
	
			array_statistic[lines][u]=malloc((strlen(d)+1)*sizeof(char)); 
			strcpy(array_statistic[lines][u],d);
			}

		/************Add a limitor at end of array ";" to general variable array on[j_t_lines][12]*****/

				for (j = 1 ; j < lines ; j++)
				{
					/*****convert int to sting******/
					char string[16];
					sprintf(string, "%s", ";");
					/*******************************/

					//********JF; Extract string addr count_ip to general variable***********
					 void strcpy_i2( char **dst, char *src )
					 {
					    *dst=(char *)malloc((strlen(src)+1)*sizeof(char));
					    char *tmp=*dst;
					    while((*tmp++=*src++)!='\0');
					 }
					   	    char *d=NULL;
						    strcpy_i2(&d,string);
			

					    array_statistic[j][12]=malloc((strlen(d)+1)*sizeof(char));
					    strcpy(array_statistic[j][12],d); // (j - 1) to display on the last ip
					    //array_statistic[g][0]= "";
					    //printf("%d-%d =(%s) ",g,z,array_statistic[g][z+1]);
				}

			/***********************************************************************************/







/**********************************************************************/
void sorting_order(char **argv){

/***define array position***/
#define Yr	5
#define Mt	6
#define Day	7
#define src_interup 9
#define Hrs	1
#define Min	2
#define Sec	3
#define IP	11



    char temp[64];
    int i, j, u, v;
    char *array_statistic_temp[1][16];

/**********sorting by date order for array string**************/

	for (v = 0; v < 6 ; v++)
	{
	    for (i = 1; i < lines - 1 ; i++) // i = 1 because, ignore line 0 is bad data, bad sampling
	    {
		for (j = i + 1; j < lines ; j++)
		{
		    if ((strcmp(array_statistic[i][Yr], array_statistic[j][Yr]) > 0)){ // [y] at 1 = sorting by seconde
		    }else if((strcmp(array_statistic[i][Yr], array_statistic[j][Yr]) == 0) && (strcmp(array_statistic[i][Mt], array_statistic[j][Mt]) > 0)){

		     }else if((strcmp(array_statistic[i][Yr], array_statistic[j][Yr]) == 0) && (strcmp(array_statistic[i][Mt], array_statistic[j][Mt]) == 0) && (strcmp(array_statistic[i][Day], array_statistic[j][Day]) > 0)){

		      }else if((strcmp(array_statistic[i][Yr], array_statistic[j][Yr]) == 0) && (strcmp(array_statistic[i][Mt], array_statistic[j][Mt]) == 0) && (strcmp(array_statistic[i][Day], array_statistic[j][Day]) == 0) && (strcmp(array_statistic[i][Hrs], array_statistic[j][Hrs]) > 0)){

		       }else if((strcmp(array_statistic[i][Yr], array_statistic[j][Yr]) == 0) && (strcmp(array_statistic[i][Mt], array_statistic[j][Mt]) == 0) && (strcmp(array_statistic[i][Day], array_statistic[j][Day]) == 0) && (strcmp(array_statistic[i][Hrs], array_statistic[j][Hrs]) == 0) && (strcmp(array_statistic[i][Min], array_statistic[j][Min]) > 0)){

			}else if((strcmp(array_statistic[i][Yr], array_statistic[j][Yr]) == 0) && (strcmp(array_statistic[i][Mt], array_statistic[j][Mt]) == 0) && (strcmp(array_statistic[i][Day], array_statistic[j][Day]) == 0) && (strcmp(array_statistic[i][Hrs], array_statistic[j][Hrs]) == 0) && (strcmp(array_statistic[i][Min], array_statistic[j][Min]) == 0) && (strcmp(array_statistic[i][Sec], array_statistic[j][Sec]) > 0)){

				for (u = 1; u < 12 ; u++){
				strcpy(temp, array_statistic[i][u]);
				array_statistic_temp[1][u] = temp;
				//printf("%s ", array_statistic_temp[1][u]);
		
				strcpy(array_statistic[i][u], array_statistic[j][u]);
				strcpy(array_statistic[j][u], array_statistic_temp[1][u]);
				array_statistic_temp[1][u] = "";

				}
		    	}
		}
	    }
	}
/*****************/







/****give a interruption IP count******/
//*****************function counting interruption ip******************************
	void counting_ips(void){
			
/****sort by ip number*********/
    char temp[64];
    int i, j, u, v;
    char *array_statistic_temp[1][16];

    for (i = 1; i < lines - 1 ; i++) // i = 1 because, ignore line 0 is bad data, bad sampling
    {
        for (j = i + 1; j < lines ; j++)
        {
            if ((strcmp(array_statistic[i][IP], array_statistic[j][IP]) > 0)) // [y] at 1 = sorting by seconde
            {
		for (u = 1; u < 12 ; u++){
                strcpy(temp, array_statistic[i][u]);
		array_statistic_temp[1][u] = temp;
		//printf("%s ", array_statistic_temp[1][u]);
		
		strcpy(array_statistic[i][u], array_statistic[j][u]);
		strcpy(array_statistic[j][u], array_statistic_temp[1][u]);
		array_statistic_temp[1][u] = "";
		}
            }
        }
    }
/*************************/

	    for (i = 1; i < lines - 1 ; i++) // i = 1 because, ignore line 0 is bad data, bad sampling
	    {	
		for (j = i + 1; j <= lines ; j++)
		{
		if((strcmp(array_statistic[i][IP], array_statistic[j][IP]) != 0) || (array_statistic[j][IP] == ";")){


					/*****convert int to sting******/
					char string[16];
					sprintf(string, "%d", ( j - i ));
					/*******************************/

					//********JF; Extract string addr count_ip to general variable***********
					 void strcpy_i2( char **dst, char *src )
					 {
					    *dst=(char *)malloc((strlen(src)+1)*sizeof(char));
					    char *tmp=*dst;
					    while((*tmp++=*src++)!='\0');
					 }
					   	    char *d=NULL;
						    strcpy_i2(&d,string);
			

					    array_statistic[j - 1][12]=malloc((strlen(d)+1)*sizeof(char));
					    strcpy(array_statistic[j - 1][12],d); // (j - 1) to display on the last ip
					    //array_statistic[g][0]= "";
					    //printf("%d-%d =(%s) ",g,z,array_statistic[g][z+1]);

				i = j; // Important to move (i) for next count
			}
		}

	    }

	}


/*******Delete data and fill******/

	    for (i = 1; i <= lines - 1 ; i++) // i = 1 because, ignore line 0 is bad data, bad sampling
	    {

		    if ((strcmp(array_statistic[i][12], ";") == 0)){ // [y] at 1 = sorting by seconde
			
				/*for (u = 1; u < 12 ; u++){
					strcpy(array_statistic[i][u],"-");
				}*/

		  	}else if((strcmp(array_statistic[i][12], ";") != 0)){ 

		    	/*	for (u = 1; u <= 9 ; u++){
					strcpy(array_statistic[i][u],"-");
				}*/
		    	}
		
	    }
/*****************/




/**********sorting descending order for array string in function of number IP defect**************/
    for (i = 1; i < lines - 1 ; i++) // i = 1 because, ignore line 0 is bad data, bad sampling
    {
        for (j = i + 1; j < lines ; j++)
        {
            if ((strcmp(array_statistic[i][12], array_statistic[j][12]) > 0)) // [y] at 1 = sorting by seconde
            {
		for (u = 1; u <= 12 ; u++){
                strcpy(temp, array_statistic[i][u]);
		array_statistic_temp[1][u] = temp;
		//printf("%s ", array_statistic_temp[1][u]);
		
		strcpy(array_statistic[i][u], array_statistic[j][u]);
		strcpy(array_statistic[j][u], array_statistic_temp[1][u]);
		array_statistic_temp[1][u] = "";
		}
            }
        }
    }
/*****************************************************/


	//****************end function counting_ips****************************
	if (strcmp(argv[1],arg_stat1)==0){
	counting_ips();
	}









/****give a source interruption IP count******/
	void counting_source_interrupt(void){
			
/****sort by ip number*********/
    char temp[64];
    int i, j, u, v;
    char *array_statistic_temp[1][16];

    for (i = 1; i < lines - 1 ; i++) // i = 1 because, ignore line 0 is bad data, bad sampling
    {
        for (j = i + 1; j < lines ; j++)
        {
            if ((strcmp(array_statistic[i][src_interup], array_statistic[j][src_interup]) > 0)) // [y] at 1 = sorting by seconde
            {
		for (u = 1; u < 12 ; u++){
                strcpy(temp, array_statistic[i][u]);
		array_statistic_temp[1][u] = temp;
		//printf("%s ", array_statistic_temp[1][u]);
		
		strcpy(array_statistic[i][u], array_statistic[j][u]);
		strcpy(array_statistic[j][u], array_statistic_temp[1][u]);
		array_statistic_temp[1][u] = "";
		}
            }
        }
    }
/*************************/

	    for (i = 1; i < lines - 1 ; i++) // i = 1 because, ignore line 0 is bad data, bad sampling
	    {	
		for (j = i + 1; j <= lines ; j++)
		{
		if((strcmp(array_statistic[i][src_interup], array_statistic[j][src_interup]) != 0) || (array_statistic[j][IP] == ";")){


					/*****convert int to sting******/
					char string[16];
					sprintf(string, "%d", ( j - i ));
					/*******************************/

					//********JF; Extract string addr count_ip to general variable***********
					 void strcpy_i2( char **dst, char *src )
					 {
					    *dst=(char *)malloc((strlen(src)+1)*sizeof(char));
					    char *tmp=*dst;
					    while((*tmp++=*src++)!='\0');
					 }
					   	    char *d=NULL;
						    strcpy_i2(&d,string);
			

					    array_statistic[j - 1][12]=malloc((strlen(d)+1)*sizeof(char));
					    strcpy(array_statistic[j - 1][12],d); // (j - 1) to display on the last ip
					    //array_statistic[g][0]= "";
					    //printf("%d-%d =(%s) ",g,z,array_statistic[g][z+1]);

				i = j; // Important to move (i) for next count
			}
		}

	    }

	}


/*******fill endler******/

	    for (i = 1; i <= lines - 1 ; i++) // i = 1 because, ignore line 0 is bad data, bad sampling
	    {

		    if ((strcmp(array_statistic[i][12], ";") == 0)){ // [y] at 1 = sorting by seconde
			
				/*for (u = 1; u < 12 ; u++){
					strcpy(array_statistic[i][u],"-");
				}*/

		  	}else if((strcmp(array_statistic[i][12], ";") != 0)){ 

		    	/*	for (u = 1; u <= 9 ; u++){
					strcpy(array_statistic[i][u],"-");
				}*/
		    	}
		
	    }
/*****************/




/**********sorting descending order for array string in function of number IP defect**************/
    for (i = 1; i < lines - 1 ; i++) // i = 1 because, ignore line 0 is bad data, bad sampling
    {
        for (j = i + 1; j < lines ; j++)
        {
            if ((strcmp(array_statistic[i][12], array_statistic[j][12]) > 0)) // [y] at 1 = sorting by seconde
            {
		for (u = 1; u <= 12 ; u++){
                strcpy(temp, array_statistic[i][u]);
		array_statistic_temp[1][u] = temp;
		//printf("%s ", array_statistic_temp[1][u]);
		
		strcpy(array_statistic[i][u], array_statistic[j][u]);
		strcpy(array_statistic[j][u], array_statistic_temp[1][u]);
		array_statistic_temp[1][u] = "";
		}
            }
        }
    }
/*****************************************************/
	//****************end function counting_ips****************************
	if (strcmp(argv[1],arg_stat2)==0){
	counting_source_interrupt();
	}




} // end sorting order
	sorting_order(argv);
/************************************/




	/*******read array_statistic***********/
		void reader_stat_count_ip(void)
		{
			int h;
printf("\033[2J");
printf("\n\nPROPING, SORTING STATISTICAL TABLE by HOSTS IP;\n");
printf("%35s %14s %14s\n\n","|Host name|","|Ping ip|","|Number of interruptions|");
			for(h = 1; h <= lines ; h++){ // ignore line 0 is bad data, bad sampling no data NULL
				int y;
				//for(y = 10; y <= 12 ; y++){ 
					if((array_statistic[h][y] != NULL)&&(strcmp(array_statistic[h][12],";") != 0)){


			printf ("%35s %14s %14s", array_statistic[h][10],array_statistic[h][11],array_statistic[h][12]);

			
						//printf("%d-%d =(%s) ",h,y,array_statistic[h][y]);
					}	
				//}
				if(strcmp(array_statistic[h][12],";") != 0){
				  printf("\n");
				}
			}
			printf("\n");
printf("%35s %14s %14s\n\n","|Host name|","|Ping ip|","|Number of interruptions|");
printf("PROPING, SORTING STATISTICAL TABLE by HOSTS IP;\n\n");
		}

	  if (strcmp(argv[1],arg_stat1)==0){
			reader_stat_count_ip();
	  }
		/********************************/



	/*******read array_statistic***********/
		void reader_source_interrupt(void)
		{
			int h;
printf("\033[2J");
printf("\n\nPROPING, SORTING STATISTICAL TABLE by SOURCE of INTERRUPTIONS;\n");
printf("%20s%32s\n\n","|Interrupt segment source ip|","|Number of interruptions|");
			for(h = 1; h <= lines ; h++){ // ignore line 0 is bad data, bad sampling no data NULL
				int y;
				//for(y = 9; y <= 12 ; y++){ 
					if((array_statistic[h][y] != NULL)&&(strcmp(array_statistic[h][12],";") != 0)){

						printf ("%35s %7s", array_statistic[h][9],array_statistic[h][12]);

						//printf("%d-%d =(%s) ",h,y,array_statistic[h][y]);
					}	
				//}
				if(strcmp(array_statistic[h][12],";") != 0){
				  printf("\n");
				}
			}
			printf("\n");
printf("%20s%32s\n\n","|Interrupt segment source ip|","|Number of interruptions|");
printf("PROPING, SORTING STATISTICAL TABLE by SOURCE of INTERRUPTIONS;\n\n");
		}
			if (strcmp(argv[1],arg_stat2)==0){
			reader_source_interrupt();
			}
		/********************************/





	/*******read array_statistic***********/
		void reader_stat(void)
		{
int h;
printf("\033[2J");
printf("\n\nPROPING, SORTING STATISTICAL TABLE by DATE;\n");
printf("|Hr:|:Min|:Sec| |Yr   |Mt     |Day   |Dn\t\t|IP.breakdown\t  |Host.Name   |IP.Ping.\n\n");
			for(h = 1; h < lines ; h++){ // ignore line 0 is bad data, bad sampling no data NULL
				int y;
				for(y = 1; y < 12 ; y++){ 
					if(array_statistic[h][y] != NULL){
						if(y == 1){
							printf("%sH:",array_statistic[h][y]);
						}else if(y == 2){
							printf("%sM:",array_statistic[h][y]);
						}else if(y == 3){
							printf("%sS",array_statistic[h][y]);
						}else{
						printf("%s   ",array_statistic[h][y]);
						}
						//printf("%d-%d =(%s) ",h,y,array_statistic[h][y]);
					}	
				}
				  printf("\n");

			}
			printf("\n");
printf("|Hr:|:Min|:Sec| |Yr   |Mt     |Day   |Dn\t\t|IP.breakdown\t  |Host.Name   |IP.Ping.\n\n");
printf("PROPING, SORTING STATISTICAL TABLE by DATE;\n\n");
		}
	  if (strcmp(argv[1],arg_stat)==0){
			reader_stat();
	  }
		/********************************/
return 0; // end of main
}

/*********************************END OF PAGE***************************************/


