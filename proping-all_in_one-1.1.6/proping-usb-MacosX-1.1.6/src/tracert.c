/*tracert.c*/   
   
#include <stdio.h>   
#include <stdlib.h>   
#include <errno.h>   
#include <string.h>   
#include <sys/un.h>   
#include <sys/time.h>
#include <time.h>
#include <sys/times.h>   
#include <sys/ioctl.h>
#include <unistd.h>   
#include <netinet/in.h>   
#include <netdb.h>
//#include "socket.h"  

unsigned long fromlen;    
char *trace_ip4;   
   
//   
// Defines for ICMP message types   
//   
#define ICMP_ECHOREPLY      0   
#define ICMP_DESTUNREACH    3   
#define ICMP_SRCQUENCH      4   
#define ICMP_REDIRECT       5   
#define ICMP_ECHO           8   
#define ICMP_TIMEOUT       11   
#define ICMP_PARMERR       12   
   
#define MAX_HOPS           15   
   
#define ICMP_MIN 8    // Minimum 8 byte icmp packet (just header)   
   
//   
// IP Header   
//   
typedef struct iphdr    
{   
    unsigned int   h_len:4;        // Length of the header   
    unsigned int   version:4;      // Version of IP   
    unsigned char  tos;            // Type of service   
    unsigned short total_len;      // Total length of the packet   
    unsigned short ident;          // Unique identifier   
    unsigned short frag_and_flags; // Flags   
    unsigned char  ttl;            // Time to live   
    unsigned char  proto;          // Protocol (TCP, UDP etc)   
    unsigned short checksum;       // IP checksum   
    unsigned int   sourceIP;       // Source IP   
    unsigned int   destIP;         // Destination IP   
} IpHeader;   
   
//   
// ICMP header   
//   
typedef struct _ihdr    
{   
    char   i_type;               // ICMP message type   
    char   i_code;               // Sub code   
    unsigned short i_cksum;                 
    unsigned short i_id;                 // Unique id   
    unsigned short i_seq;                // Sequence number   
    // This is not the std header, but we reserve space for time   
    unsigned long timestamp;   
} IcmpHeader;   
   
#define DEF_PACKET_SIZE         32   
#define MAX_PACKET            1024   
   
//   
// Function: usage_tracert   
//   
void usage_tracert(char *progname)   
{   
    printf("usage_tracert: %s host-name [max-hops]\n", progname);  
	 exit(-1);
}   
   
//   
// Function: set_ttl   
//   
int set_ttl(int s, int nTimeToLive)   
{   
    int     nRet;   
       
    nRet = setsockopt(s, IPPROTO_IP, IP_TTL, (int *)&nTimeToLive, sizeof(int));   
    if (nRet < 0)   
    {   
        perror("setsockopt in set_ttl:");   
        return 0;   
    }   
    return 1;   
}   
   
//   
// Function: decode_resp   
//   
int decode_resp(char *buf, int bytes, struct sockaddr_in *from, int ttl)   
{   
    IpHeader       *iphdr = NULL;   
    IcmpHeader     *icmphdr = NULL;   
    unsigned short  iphdrlen;   
    struct hostent *lpHostent = NULL;   
    struct in_addr  inaddr = from->sin_addr;   
   
    iphdr = (IpHeader *)buf;   
    // Number of 32-bit words * 4 = bytes   
    iphdrlen = iphdr->h_len * 4;    
	
/****************************JF**************/   
    if (bytes < iphdrlen + ICMP_MIN)    
       /* printf("Too few bytes from %s\n",    
            inet_ntoa(from->sin_addr));   */
			
	trace_ip4 = inet_ntoa(from->sin_addr);
	
/********************************************/   
    icmphdr = (IcmpHeader*)(buf + iphdrlen);   
   
   /* switch (icmphdr->i_type)   
    {   
        case ICMP_ECHOREPLY:     // Response from destination   
            lpHostent = gethostbyaddr((const char *)&from->sin_addr, 4, AF_INET);   
            if (lpHostent != NULL)   
                printf("gethostbyaddr success\n");   
            return 1;   
            break;   
        case ICMP_TIMEOUT:      // Response from router along the way   
            printf("%2d  %s\n", ttl, inet_ntoa(inaddr));   
            return 0;   
            break;   
        case ICMP_DESTUNREACH:  // Can't reach the destination at all   
            printf("%2d  %s  reports: Host is unreachable\n", ttl,    
                inet_ntoa(inaddr));   
            return 1;   
            break;   
        default:   
            printf("non-echo type %d recvd\n", icmphdr->i_type);   
            return 1;   
            break;   
    }   */
    return 0;   
}   
   
//   
// Function: checksum   
//   
unsigned short checksum(unsigned short *buffer, int size)    
{   
    unsigned long cksum=0;   
   
    while(size > 1)    
    {   
        cksum += *buffer++;   
        size -= sizeof(unsigned short);   
    }   
    if(size )   
        cksum += *(unsigned char*)buffer;   
    cksum = (cksum >> 16) + (cksum & 0xffff);   
    cksum += (cksum >> 16);   
   
    return (unsigned short)(~cksum);   
}   
   
//   
// Function: fill_icmp_data   
//   
void fill_icmp_data(char * icmp_data, int datasize)   
{   
    IcmpHeader *icmp_hdr;   
    char       *datapart;   
   
    icmp_hdr = (IcmpHeader*)icmp_data;   
   
    icmp_hdr->i_type = ICMP_ECHO;   
    icmp_hdr->i_code = 0;   
    icmp_hdr->i_id   = (unsigned short)getpid();   
    icmp_hdr->i_cksum = 0;   
    icmp_hdr->i_seq = 0;   
     
    datapart = icmp_data + sizeof(IcmpHeader);   
    memset(datapart,'E', datasize - sizeof(IcmpHeader));   
}   
   
/*long GetTickCount()   
{   
    struct tms tm;   
    return times(tm);   
}  */

unsigned long GetTickCount()
{
struct timeval tv;
if( gettimeofday(&tv, NULL) != 0 )

return 0;
return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}


 
//   
// Function: main   
//

int argc;
char *argv[1];
char *option_argument;    
	
task_c(/*int argc, char **argv*/)   
{   

argc = 2;
argv[1] = option_argument;

    int       sockRaw;   
    struct hostent     *hp = NULL;   
    struct sockaddr_in   dest,   
                 from;   
    int          ret,   
                 datasize,   
                 fromlen = sizeof(from),   
                 done = 0,   
                 maxhops,   
                 ttl = 1;   
    char        *icmp_data,   
                *recvbuf;   
    int         bOpt;   
    unsigned short      seq_no = 0;   
    struct timeval timeout;   
       
    if (argc < 2)    
        usage_tracert(argv[0]);   
    if (argc == 3)   
        maxhops = atoi(argv[2]);   
    else   
        maxhops = MAX_HOPS;   
    sockRaw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);   
    if (sockRaw < 0)    
    {   
        perror("socket");   
		 return(-1);
        // exit(-1); /JF  
    }   
    //   
    // Set the receive and send timeout values to a second   
    //   
    timeout.tv_sec = 1;   
    timeout.tv_usec = 0;   
    ret = setsockopt(sockRaw, SOL_SOCKET, SO_RCVTIMEO,    
            &timeout, sizeof(struct timeval));   
    if (ret == -1)   
    {   
        perror("setsockopt in main receive:");   
        return -1;   
    }   
    timeout.tv_sec = 1;   
    timeout.tv_usec = 0;   
    ret = setsockopt(sockRaw, SOL_SOCKET, SO_SNDTIMEO,    
        &timeout, sizeof(struct timeval));   
    if (ret == -1)   
    {   
        perror("setsockopt in send:");   
        return -1;   
    }   
    memset(&dest, 0, sizeof(struct sockaddr_in));   
    dest.sin_family = AF_INET;   
    if ((dest.sin_addr.s_addr = inet_addr(argv[1])) == INADDR_NONE)   
    {   
       
       
        hp = gethostbyname(argv[1]);   
        if (hp)   
            memcpy(&dest.sin_addr, hp->h_addr, hp->h_length);   
        else   
        {   
            printf("Unable to resolve %s\n",argv[1]);   
			return(-1);//JF
			//exit(-1);   
        }   
    }   
    //   
    // Set the data size to the default packet size.   
    // We don't care about the data since this is just traceroute/ping   
    //   
    datasize = DEF_PACKET_SIZE;   
           
    datasize += sizeof(IcmpHeader);     
    //   
    // Allocate the sending and receiving buffers for ICMP packets   
    //   
    icmp_data = malloc(MAX_PACKET*sizeof(char));   
    recvbuf = malloc(MAX_PACKET*sizeof(char));     
   
    if ((!icmp_data) || (!recvbuf))   
    {   
        perror("malloc:");   
        return -1;   
    }   
    //     
    // Here we are creating and filling in an ICMP header that is the    
    // core of trace route.   
    //   
    memset(icmp_data, 0, MAX_PACKET);   
    fill_icmp_data(icmp_data, datasize);   
   
    printf("\nTracing route to %s over a maximum of %d hops:\n\n",    
        argv[1], maxhops);   
   
    for(ttl = 1; ((ttl < maxhops) && (!done)); ttl++)   
    {   
        int bwrote;   
   
        // Set the time to live option on the socket   
        //   
        set_ttl(sockRaw, ttl);   
   
        //   
        // Fill in some more data in the ICMP header   
        //   
        ((IcmpHeader*)icmp_data)->i_cksum = 0;   
        ((IcmpHeader*)icmp_data)->timestamp = GetTickCount();   
   
        ((IcmpHeader*)icmp_data)->i_seq = seq_no++;   
        ((IcmpHeader*)icmp_data)->i_cksum = checksum((unsigned short*)icmp_data,    
            datasize);   
        //   
        // Send the ICMP packet to the destination   
        //   
        bwrote = sendto(sockRaw, icmp_data, datasize, 0,    
                    (struct sockaddr *)&dest, sizeof(dest));   
        if (bwrote < 0)   
        {   
            perror("sendto:");   
            return -1;   
        }   
        // Read a packet back from the destination or a router along    
        // the way.   
        //   
		int flags = 0;
       ret = recvfrom(sockRaw, recvbuf, MAX_PACKET,
	    flags, (struct sockaddr*)&from, &fromlen);   
			
		/*ret =  recvfrom(int s, void *buf, size_t len, int flags,
			 struct sockaddr *from, socklen_t *fromlen);*/
        
		/*if (ret < 0)   
        {   
            perror("recvfrom:");   
            return -1;   
        }   */
        //   
        // Decode the response to see if the ICMP response is from a    
        // router along the way or whether it has reached the destination.   
        //   
        done = decode_resp(recvbuf, ret, &from, ttl);   
        sleep(1);   
    }   
    free(recvbuf);   
    free(icmp_data);   
    return 0;   
}   