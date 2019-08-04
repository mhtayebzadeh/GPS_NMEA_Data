/*
https://github.com/xanthium-enterprises/Serial-Port-Programming-on-Linux

developed by mhtayebzadeh@yahoo.com
https://github.com/mhtayebzadeh
*/
#ifndef SerialPort_h
#define SerialPort_h

#include <stdio.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */ 
#include <errno.h>   /* ERROR Number Definitions           */

#include <iostream>
#include <string>
#include <cstring>


// using namespace std;
class SerialPort
{
private:
    int fd;/*File Descriptor*/

public:
    SerialPort(const char* portName , int baud);
    ~SerialPort();

    char readChar();
    char* readString(int maxBuffer);
    char* readString();
    int writeChar(char c);
    int writeString(char* str);
    int writeString(std::string str);

    //TODO: 
    // std::string readLines(int n);
};

SerialPort::SerialPort(const char* portName , int baud)
{
    this->fd = open(portName,O_RDWR | O_NOCTTY);
    if(fd == -1) printf("\n  Error! in Opening port %s ",portName);
    else printf("\n  %s Opened Successfully " ,portName);

    struct termios SerialPortSettings;	/* Create the structure  */

    tcgetattr(fd, &SerialPortSettings);	/* Get the current attributes of the Serial port */
    
    /* set baudrate_num */
    
    unsigned int baudrate_num ;
    if  (baud == 0)
        baudrate_num = 0000000 ;		/* hang up */
    else if  (baud == 50)	
        baudrate_num = 0000001 ;
    else if  (baud == 75)
        baudrate_num = 0000002 ;
    else if  (baud == 110)	
        baudrate_num = 0000003 ;
    else if  (baud == 134)	
        baudrate_num = 0000004;
    else if  (baud == 150)	
        baudrate_num = 0000005;
    else if  (baud == 200)	
        baudrate_num = 0000006;
    else if  (baud == 300)	
        baudrate_num = 0000007;
    else if  (baud == 600)	
        baudrate_num = 0000010;
    else if  (baud == 1200)	
        baudrate_num = 0000011;
    else if  (baud == 1800)	
        baudrate_num = 0000012;
    else if  (baud == 2400)	
        baudrate_num = 0000013;
    else if  (baud == 4800)	
        baudrate_num = 0000014;
    else if  (baud == 9600)	
        baudrate_num = 0000015;
    else if  (baud == 19200)	
        baudrate_num = 0000016;
    else if  (baud == 38400)	
        baudrate_num = 0000017;
    else if  (baud == 57600)   
        baudrate_num = 0010001;
    else if  (baud == 115200)  
        baudrate_num = 0010002;
    else if  (baud == 230400)  
        baudrate_num = 0010003;
    else if  (baud == 460800)  
        baudrate_num = 0010004;
    else if  (baud == 500000)  
        baudrate_num = 0010005;
    else if  (baud == 576000)  
        baudrate_num = 0010006;
    else if  (baud == 921600)  
        baudrate_num = 0010007;
    else if  (baud == 1000000) 
        baudrate_num = 0010010;
    else if  (baud == 1152000) 
        baudrate_num = 0010011;
    else if  (baud == 1500000) 
        baudrate_num = 0010012;
    else if  (baud == 2000000) 
        baudrate_num = 0010013;
    else if  (baud == 2500000) 
        baudrate_num = 0010014;
    else if  (baud == 3000000) 
        baudrate_num = 0010015;
    else if  (baud == 3500000) 
        baudrate_num = 0010016;
    else if  (baud == 4000000) 
        baudrate_num = 0010017;
    else
    {
        std::cout << "Error! baudrate not supported" << std::endl;
    }
    
    //////////////
    /* Se(tting the Baud rate */
    cfsetispeed(&SerialPortSettings,baudrate_num); /* Set Read  Speed as baudrate_num */
    cfsetospeed(&SerialPortSettings,baudrate_num); /* Set Write Speed as baudrate_num */

        /* 8N1 Mode */
    SerialPortSettings.c_cflag &= ~PARENB;   /* Disables the Parity Enable bit(PARENB),So No Parity   */
    SerialPortSettings.c_cflag &= ~CSTOPB;   /* CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit */
    SerialPortSettings.c_cflag &= ~CSIZE;	 /* Clears the mask for setting the data size             */
    SerialPortSettings.c_cflag |=  CS8;      /* Set the data bits = 8                                 */
    
    SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
    SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 
    
    
    SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
    SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

    SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/
    
    /* Setting Time outs */
    SerialPortSettings.c_cc[VMIN] = 10; /* Read at least 10 characters */
    SerialPortSettings.c_cc[VTIME] = 0; /* Wait indefinetly   */

    if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
        printf("\n  ERROR ! in Setting attributes");
    else
        printf("\n  BaudRate = %d \n  StopBits = 1 \n  Parity   = none",baud);
        
        /*------------------------------- Read data from serial port -----------------------------*/

    tcflush(fd, TCIFLUSH);   /* Discards old data in the rx buffer            */
}
SerialPort::~SerialPort()
{
    close(this->fd);
}

/* return char */
char SerialPort::readChar()
{
    char c;
    int byte_read = read(this->fd,&c,1);
    if (byte_read > 0)
        return c;
    else
        return -1;
}

/* return char* string with maxBufferSize = 200  */
char* SerialPort::readString()
{
    return this->readString(200);
}

/* return char* string with maxBufferSize  */
char* SerialPort::readString(int maxBufferSize)
{
    int index = 0;
    char* buf = new char[maxBufferSize];
    char c = ' ';
    
    while(c != '\n' and index < maxBufferSize-2)
    {
        c = this->readChar();
        // cout << c << endl;
        buf[index] = c;
        index++;
    }
    // cout << buf << endl;
    return buf;
}
int SerialPort::writeChar(char c)
{
    char cc[1];
    cc[0] = c;
    int  bytes_written  = 0;  
	bytes_written = write(fd,cc,sizeof(cc));
    return bytes_written;
}
int SerialPort::writeString(char* str)
{
    int  bytes_written  = 0;  
	bytes_written = write(fd,str,sizeof(str));
    bytes_written += write(fd,"\n",sizeof("\n"));
    return bytes_written;
}
int SerialPort::writeString(std::string str)
{
	char cstr[str.size() + 1];
	strcpy(cstr, str.c_str());
    int  bytes_written  = 0;  
	bytes_written = write(fd,cstr,sizeof(cstr));
    bytes_written += write(fd,"\n",sizeof("\n"));    
    return bytes_written;
}
#endif
