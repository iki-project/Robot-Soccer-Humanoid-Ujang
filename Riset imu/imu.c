#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>


char *portname = "/dev/ttyUSB0";


int main(int argc, char *argv[])
{
  int fd,stop = 0;

/* Open the file descriptor in non-blocking mode */
fd = open(portname, O_RDWR | O_NOCTTY);

/* Set up the control structure */
struct termios toptions;

/* Get currently set options for the tty */
tcgetattr(fd, &toptions);

/* Set custom options */

/* 9600 baud */
cfsetispeed(&toptions, B115200);
cfsetospeed(&toptions, B115200);
/* 8 bits, no parity, no stop bits */
toptions.c_cflag &= ~PARENB;
toptions.c_cflag &= ~CSTOPB;
toptions.c_cflag &= ~CSIZE;
toptions.c_cflag |= CS8;
/* no hardware flow control */
toptions.c_cflag &= ~CRTSCTS;
/* enable receiver, ignore status lines */
toptions.c_cflag |= CREAD | CLOCAL;
/* disable input/output flow control, disable restart chars */
toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
/* disable canonical input, disable echo,
   disable visually erase chars,
   disable terminal-generated signals */
toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
/* disable output processing */
toptions.c_oflag &= ~OPOST;

/* wait for 1 character to come in before read returns */
/* WARNING! THIS CAUSES THE read() TO BLOCK UNTIL ALL */
/* CHARACTERS HAVE COME IN! */
toptions.c_cc[VMIN] = 1;
/* no minimum time to wait before read returns */
toptions.c_cc[VTIME] = 0;

/* commit the options */
tcsetattr(fd, TCSANOW, &toptions);

/* Wait for the Arduino to reset */
usleep(1000000);
/* Flush anything already in the serial buffer */
tcflush(fd, TCIFLUSH);

while(stop == 0){

  /* read up to 128 bytes from the fd */
  char  buf [256];
  int n = read(fd, &buf, 256);
  //int a = atoi(buf);
  usleep(1000);
  /* print how many bytes read */
  //printf("%i bytes got read...\n", n);
  /* print what's in the buffer */
  printf("Data Serial imu : %s", buf);
 }
 return 0;
}
