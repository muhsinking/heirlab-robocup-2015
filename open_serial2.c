#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <termios.h> /* POSIX terminal control definitions */


int main() {

	int fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY);

	configure_port(fd);

	if (fd != -1)
	{
		char psResponse[3] = {0};
		int bytes = read(fd, psResponse, 2);

		if (bytes == 2)
		{
			double n = atoi(psResponse) * 0.322265625;
			printf("n = %.1f\n", n);
		}
		else if (bytes == 0)
		{
			printf("EOF detected!\n");
		}
		else if (bytes == -1)
		{
			printf("Error: %s (%d)\n", strerror(errno), errno);
		}

		close(fd);
	}
	else
	{
		printf("Error: Cannot open USB device; Reason: %s (%d)\n",
			strerror(errno), errno);
		return -1;
	}

	return 0;
}


int configure_port(int fd) // configure the port
{
	struct termios port_settings; // structure to store the port settings in
	cfsetispeed(&port_settings, B57600); // set baud rates
	cfsetospeed(&port_settings, B57600);
	port_settings.c_cflag &= ~PARENB; // set no parity, stop bits, data bits
	port_settings.c_cflag &= ~CSTOPB;
	port_settings.c_cflag &= ~CSIZE;
	port_settings.c_cflag |= CS8;
	cfmakeraw(&port_settings);
	tcsetattr(fd, TCSANOW, &port_settings); // apply the settings to the port
	return(fd);
}