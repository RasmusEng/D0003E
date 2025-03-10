#include "init.h"

int init(){
    int serial_port = open("/dev/tty.usbserial-FT6SD5S9", O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (serial_port == -1) {
        perror("Error opening serial port");
        return 1;
    }

    struct termios tty;
    if (tcgetattr(serial_port, &tty) != 0) {
        perror("Error getting terminal attributes");
        close(serial_port);
        return 1;
    }

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit characters
    tty.c_cflag &= ~PARENB; // No parity
    tty.c_cflag &= ~CSTOPB; // 1 stop bit
    tty.c_cflag |= CREAD | CLOCAL; // Enable receiver, ignore modem control lines

    tcsetattr(serial_port, TCSANOW, &tty);

    return serial_port;
}