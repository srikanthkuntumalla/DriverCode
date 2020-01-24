
    	#include <stdio.h>
    	#include <fcntl.h>   
    	#include <termios.h>
    	#include <unistd.h>   
    	#include <errno.h>   :
	
	void main(void)
    	{
        	int fd;/*File Descriptor*/
		char write_buffer[] = "A";	
		int  bytes_written  = 0;  
		char read_buffer[32];  
		int  bytes_read = 0;    
 		int i = 0;



		printf("+----------- Serial Port Read -------------+\n");

             	fd = open("/dev/ttyS0",O_RDWR | O_NOCTTY);					                                        
									
        	if(fd == -1)				
            	   printf("Error! in Opening ttyS0 \n");
        	else
            	   printf("ttyUSB0 Opened Successfully \n");

	
		/*---------- Setting the Attributes of the serial port using termios structure --------- */
		
		struct termios SerialPortSettings;	

		tcgetattr(fd, &SerialPortSettings);	

		/* Setting the Baud rate */
		cfsetispeed(&SerialPortSettings,B115200);
		cfsetospeed(&SerialPortSettings,B115200);

		/* 8N1 Mode */
		SerialPortSettings.c_cflag &= ~PARENB;   
		SerialPortSettings.c_cflag &= ~CSTOPB;   
		SerialPortSettings.c_cflag &= ~CSIZE;	 
		SerialPortSettings.c_cflag |=  CS8;      
		
		SerialPortSettings.c_cflag &= ~CRTSCTS;       /* No Hardware flow Control                         */
		SerialPortSettings.c_cflag |= CREAD | CLOCAL; /* Enable receiver,Ignore Modem Control lines       */ 
		
		SerialPortSettings.c_iflag &= ~(IXON | IXOFF | IXANY);          /* Disable XON/XOFF flow control both i/p and o/p */
		SerialPortSettings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /* Non Cannonical mode                            */

		SerialPortSettings.c_oflag &= ~OPOST;/*No Output Processing*/
		
		/* Setting Time outs */
		SerialPortSettings.c_cc[VMIN] = 10; /* Read at least 10 characters */
		SerialPortSettings.c_cc[VTIME] = 0; /* Wait indefinetly   */

		if((tcsetattr(fd,TCSANOW,&SerialPortSettings)) != 0) /* Set the attributes to the termios structure*/
		    printf("ERROR ! in Setting attributes\n");
		else
                    printf("BaudRate = 115200 \n  StopBits = 1 \n  Parity   = none");
			
	       
                /*------------------------------- Write data to serial port -----------------------------*/
	
		bytes_written = write(fd,write_buffer,sizeof(write_buffer));

		printf(" %s written to ttyS0\n",write_buffer);
		printf(" %d Bytes written to ttyS0\n", bytes_written);

		close(fd);/* Close the Serial port */



    	}
