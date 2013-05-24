 #include <sys/select.h>
 #include <sys/time.h>
 #include <sys/types.h>
 #include <unistd.h>


 int sockfd = socket(AF_INET, SOCK_STREAM, 0);

 struct sockaddr serv_addr;
 struct timeval tm;
 fd_set  set;
 unsigned long ul = 1;

 ioctl(sockfd, FIONBIO, &ul);

 if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
     tm.tv_set = TIME_OUT_TIME;
     tm.tv_uset = 0;
     FD_ZERO(&set);
     FD_SET(sockfd, &set);
     if (select(sockfd+1, NULL, &set, NULL, &tm) > 0){
         getsockopt(sockfd, SO_SOCKET||SO_ERROR, &error);
         if (error == 0)
                 ret = true;
         else
                 ret = false;
     }else
             ret = false;

 }else
     ret = true;

 ul = 0;
 ioctl(sockfd, FIONBIO, &ul);
