//
// Created by xixiliadorabarry on 1/24/19.
//

#include <uart/uart.h>
#include <energy/param_struct_define.h>
#include <log.h>

using std::cout;
using std::cerr;
using std::clog;
using std::dec;
using std::endl;
using std::hex;

GMAngle_t aim;


Uart::Uart(){
    fd = open("/dev/ttyUSB0", O_RDWR);
    if(fd < 0)
    {
        cerr<<"open port error"<<endl;
        return;
    }

    if(set_opt(fd, 115200, 8, 'N', 1) < 0 )
    {
        cerr<<"set opt error"<<endl;
        return;
    }
    cout<<"uart port success"<<endl;

    buff[0] = 's';
    buff[1] = '+';
    buff[2] = (0 >> 8) & 0xFF;
    buff[3] = 0 & 0xFF;
    buff[4] = '+';
    buff[5] = (0 >> 8) & 0xFF;
    buff[6] = (0 & 0xFF);
    buff[7] = 'e';

    fps = 0;
    cur_time = time(nullptr);

}

int Uart::set_opt(int fd, int nSpeed, int nBits, char nEvent, int nStop) {
    termios newtio{}, oldtio{};
    if (tcgetattr(fd, &oldtio) != 0) {
        perror("SetupSerial 1");
        return -1;
    }
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch (nBits) {
        case 7:
            newtio.c_cflag |= CS7;break;
        case 8:
            newtio.c_cflag |= CS8;break;
        default:break;
    }

    switch (nEvent) {
        case 'O':  //奇校验
            newtio.c_cflag |= PARENB;
            newtio.c_cflag |= PARODD;
            newtio.c_iflag |= (INPCK | ISTRIP);
            break;
        case 'E':  //偶校验
            newtio.c_iflag |= (INPCK | ISTRIP);
            newtio.c_cflag |= PARENB;
            newtio.c_cflag &= ~PARODD;
            break;
        case 'N':  //无校验
            newtio.c_cflag &= ~PARENB;
            break;
        default:break;
    }

    switch (nSpeed) {
        case 2400:
            cfsetispeed(&newtio, B2400);
            cfsetospeed(&newtio, B2400);
            break;
        case 4800:
            cfsetispeed(&newtio, B4800);
            cfsetospeed(&newtio, B4800);
            break;
        case 9600:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
        case 115200:
            cfsetispeed(&newtio, B115200);
            cfsetospeed(&newtio, B115200);
            break;
        default:
            cfsetispeed(&newtio, B9600);
            cfsetospeed(&newtio, B9600);
            break;
    }

    if (nStop == 1) {
        newtio.c_cflag &= ~CSTOPB;
    } else if (nStop == 2) {
        newtio.c_cflag |= CSTOPB;
    }

    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 0;
    tcflush(fd, TCIFLUSH);
    if ((tcsetattr(fd, TCSANOW, &newtio)) != 0) {
        perror("com set error");
        return -1;
    }
    printf("set done!\n");

    return 0;
}

void Uart::sendTarget(float x, float y, float z) {
    static short x_tmp, y_tmp, z_tmp;

    time_t t = time(nullptr);
    if(cur_time != t)
    {
        cur_time = t;
        cout<<"fps:"<<fps<<", ("<<x<<","<<y<<","<<z<<")"<<endl;
        fps = 0;
    }
    fps += 1;

    x_tmp= static_cast<short>(x * (32768 - 1) / 100);
    y_tmp= static_cast<short>(y * (32768 - 1) / 100);
    z_tmp= static_cast<short>(z * (32768 - 1) / 1000);

    buff[0] = 's';
    buff[1] = static_cast<char>((x_tmp >> 8) & 0xFF);
    buff[2] = static_cast<char>((x_tmp >> 0) & 0xFF);
    buff[3] = static_cast<char>((y_tmp >> 8) & 0xFF);
    buff[4] = static_cast<char>((y_tmp >> 0) & 0xFF);
    buff[5] = static_cast<char>((z_tmp >> 8) & 0xFF);
    buff[6] = static_cast<char>((z_tmp >> 0) & 0xFF);
    buff[7] = 'e';

    write(fd, buff, 8);

}

uint8_t Uart::receive() {
    uint8_t data;
    while(read(fd, &data, 1) < 1);
    return data;
}
