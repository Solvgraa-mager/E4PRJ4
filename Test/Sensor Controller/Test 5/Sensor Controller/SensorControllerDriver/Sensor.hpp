#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <cstring>
#include <sys/file.h>


using namespace std; 

struct sensorConversionTable{
    long double offset_;
    long double factor_;
};

class Sensor
{
public:
    Sensor(int sensorNumber, string configPath);
    double sensorRead();
    uint16_t readRaw();
    void setOffset(long double offset);
    void setFactor(long double factor);
    ~Sensor();
private:
    int setConfig();
    int setupUART();
    int sendRequest(int fd);
    int receiveAnswer(int fd, uint16_t &value);
    int sensorNumber_;
    sensorConversionTable SCT_;

    string configPath_; 
    time_t configEditTime_;
};