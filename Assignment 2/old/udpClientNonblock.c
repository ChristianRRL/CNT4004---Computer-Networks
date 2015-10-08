//============================================ file = udpClientNonblock.c =====
//=  A message "client" program to demonstrate sockets programming            =
//=   - This is udpClient.c modified to use non-blocking sockets              =
//=============================================================================
//=  Notes:                                                                   =
//=    1) This program conditionally compiles for Winsock and BSD sockets.    =
//=       Set the initial #define to WIN or BSD as appropriate.               =
//=    2) This program needs udpServer to be running on another host.         =
//=       Program udpServer must be started first.                            =
//=    3) This program assumes that the IP address of the host running        =
//=       udpServer is defined in "#define IP_ADDR"                           =
//=    4) To test this program (i.e., to demonstrate that the recvfrom() is   =
//=       not blocking) add a delay to udpServer.c between its receive of a   =
//=       message and send of a message.                                      =
//=---------------------------------------------------------------------------=
//=  Example execution: (udpServer and udpClientNonblock on host 127.0.0.1)   =
//=    ....................................................................   =
//=    ....................................................................   =
//=    ...Received from server: This is a reply message from SERVER to CLIENT =
//=---------------------------------------------------------------------------=
//=  Build: bcc32 ucpClientNonblock.c or cl udpClientNonblock.c wsock32.lib   =
//=         for Winsock, gcc udpClientNonblock.c -lsocket -lnsl for BSD               =
//=---------------------------------------------------------------------------=
//=  Execute: udpClientNonblock                                               =
//=---------------------------------------------------------------------------=
//=  Author: Ken Christensen                                                  =
//=          University of South Florida                                      =
//=          WWW: http://www.csee.usf.edu/~christen                           =
//=          Email: christen@csee.usf.edu                                     =
//=---------------------------------------------------------------------------=
//=  History:  KJC (10/24/10) - Genesis (from udpClient.c)                    =
//=            BT  (09/21/14) - Made it to work for BSD                       =
//=============================================================================
#define BSD                 // WIN for Winsock and BSD for BSD sockets

//----- Include files ---------------------------------------------------------
#include <stdio.h>          // Needed for printf()
#include <string.h>         // Needed for memcpy() and strcpy()
#ifdef WIN
  #include <windows.h>      // Needed for all Winsock stuff
#endif
#ifdef BSD
  #include <stdlib.h>
  #include <unistd.h>
  #include <sys/types.h>    // Needed for sockets stuff
  #include <netinet/in.h>   // Needed for sockets stuff
  #include <sys/socket.h>   // Needed for sockets stuff
  #include <arpa/inet.h>    // Needed for sockets stuff
  #include <fcntl.h>        // Needed for sockets stuff
  #include <netdb.h>        // Needed for sockets stuff
#endif

//----- Defines ---------------------------------------------------------------
#define  PORT_NUM           1050  // Port number used
#define  IP_ADDR      "127.0.0.1" // IP address of server1 (*** HARDWIRED ***)

//===== Main program ==========================================================
#ifdef WIN
void main(void)
#endif
#ifdef BSD
int main(void)
#endif
{
#ifdef WIN
  WORD wVersionRequested = MAKEWORD(1,1);       // Stuff for WSA functions
  WSADATA wsaData;                              // Stuff for WSA functions
#endif
  int                  client_s;        // Client socket descriptor
  unsigned long int    noBlock;         // Non-blocking flag
  struct sockaddr_in   server_addr;     // Server Internet address
  int                  addr_len;        // Internet address length
  char                 out_buf[4096];   // Output buffer for data
  char                 in_buf[4096];    // Input buffer for data
  int                  retcode;         // Return code

#ifdef WIN
  // This stuff initializes winsock
  WSAStartup(wVersionRequested, &wsaData);
#endif

  // Create a socket
  client_s = socket(AF_INET, SOCK_DGRAM, 0);
  if (client_s < 0)
  {
    printf("*** ERROR - socket() failed \n");
    exit(-1);
  }

#ifdef WIN
  // Make client_s non-blocking
  noBlock = 1;
  ioctlsocket(client_s, FIONBIO, &noBlock);
#endif
#ifdef BSD
  int flags = fcntl(client_s, F_GETFL, 0);
  fcntl(client_s, F_SETFL, flags | O_NONBLOCK);
#endif

  // Fill-in server socket's address information
  server_addr.sin_family = AF_INET;                 // Address family to use
  server_addr.sin_port = htons(PORT_NUM);           // Port num to use
  server_addr.sin_addr.s_addr = inet_addr(IP_ADDR); // IP address to use

  // // Assign a message to buffer out_buf
  // strcpy(out_buf, "Test message from CLIENT to SERVER");

    // Assign a message to buffer out_buff
    printf("Enter 140 character tweet: ");
    char temp[140];
    fgets(temp, sizeof(temp), stdin);   //use fgets to retreive entire input string
    
    strcpy(out_buf, temp);
    
    retcode = sendto(client_s, out_buf, (strlen(out_buf) + 1), 0,
                     (struct sockaddr *)&server_addr, sizeof(server_addr));

  // Now send the message to server.
  retcode = sendto(client_s, out_buf, (strlen(out_buf) + 1), 0,
  (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (retcode < 0)
  {
    printf("*** ERROR - sendto() failed \n");
    exit(-1);
  }

  // Wait to receive a message (need to spin loop on the receive)
  //  - Output a "." for each spin that sleeps for 1 second
  addr_len = sizeof(server_addr);
  retcode = 0;
    printf("in_buf = %s", in_buf);
  while (retcode <= 0)
  {
    //check if the server is up now
    

#ifdef WIN
    Sleep(1000);  // Windows Sleep for 1000 ms (1 second)
    printf(".");
#endif
#ifdef BSD
    sleep(1);     // Unix sleep for 1 second
    printf(".");
    fflush(stdout);
#endif
    retcode = recvfrom(client_s, in_buf, sizeof(in_buf), 0,
      (struct sockaddr *)&server_addr, &addr_len);
//      printf("retcode = %d", retcode);
//      printf("  --  client_s = %d", client_s);
//      printf("  --  in_buf = %s", in_buf);
//      printf("  -- out_buf = %s\n", out_buf);
  }

  // Output the received message
  printf("\n");
  printf("Received from server: %s \n", in_buf);

   // Close all open sockets
#ifdef WIN
  retcode = closesocket(client_s);
  if (retcode < 0)
  {
    printf("*** ERROR - closesocket() failed \n");
    exit(-1);
  }
#endif
#ifdef BSD
  retcode = close(client_s);
  if (retcode < 0)
  {
    printf("*** ERROR - close() failed \n");
    exit(-1);
  }
#endif

#ifdef WIN
  // This stuff cleans-up winsock
  WSACleanup();
#endif
}