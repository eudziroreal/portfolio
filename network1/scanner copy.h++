// Begining of the program
// Include Files
#include <stdio.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <cstdlib>
#include <string>
#include <fcntl.h>

class scanner {
private:
  // Declare variables
  struct addrinfo *result, *rp, hints;
  struct pollfd PollFileDesc[1];
  int SocketFileDecs, ConnectToHost, bytes;
  char iBuffer[BUFSIZ+1];
  char IPbuffer[100];
  char *ip;

  int i, res, flags, ret;
  int RangeFrom, RangeTo, argumentcount;

public:
  scanner
  (int argc, char *argv1, char *argv2, char *argv3) {
    argumentcount = argc;
    ip            = argv1;
    RangeFrom     = atoi(argv2);
    RangeTo       = atoi(argv3);
  }


  void BeginScan() {

    printf("Scanning...\n");
    if ( argumentcount == 4 )
    {
      for(i = RangeFrom; i <= RangeTo; i++) {

          memset(&hints, 0, sizeof(hints));
          hints.ai_family = AF_UNSPEC;
          hints.ai_socktype = SOCK_STREAM;
          hints.ai_flags = 0;
          hints.ai_protocol = 0;

          sprintf (IPbuffer, "%s", ip);
          sprintf (iBuffer, "%d", i);
          ConnectToHost = getaddrinfo(IPbuffer, iBuffer , &hints, &result);
          if (ConnectToHost != 0) {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(ConnectToHost));
          }

          if ((SocketFileDecs = socket(result->ai_family, result->ai_socktype, result->ai_protocol )) < 0)
            perror(" socket()");

          PollFileDesc[0].fd = SocketFileDecs;
          PollFileDesc[0].events = POLLIN;

          flags = fcntl(SocketFileDecs, F_GETFL, 0);
          fcntl(SocketFileDecs, F_SETFL, flags | O_NONBLOCK);

          // start scanning for open ports
          res = connect(SocketFileDecs, result->ai_addr, result->ai_addrlen);

          ret = poll (PollFileDesc, 1, 1000);
          if (ret == -1)
            printf("error in poll\n");
          else if (ret == 0) {
            freeaddrinfo(result);
            close(SocketFileDecs);
          } else {
              if( PollFileDesc[0].revents & POLLIN ) {
                PollFileDesc[0].revents = 0;
                printf("%d port is open\n\n", i);
                freeaddrinfo(result);
                close(SocketFileDecs);
              }
          }
      }

      printf("Completed!\n");


   } else {
   printf("error, type: \"IP\" \"RangeFrom\" \"RangeTo\"\n");}

  }

};
