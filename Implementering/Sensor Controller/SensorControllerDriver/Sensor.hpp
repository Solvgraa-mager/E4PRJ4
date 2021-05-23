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
    int sensorNumber_;
    sensorConversionTable SCT_;
    int filedescriptor_; 
    string configPath_; 
    time_t configEditTime_;
};