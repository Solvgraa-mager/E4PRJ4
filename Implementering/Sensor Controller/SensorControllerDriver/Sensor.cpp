
#include "Sensor.hpp"
#include "Exception.hpp"



Sensor::Sensor(int sensorNumber, string configPath) :
    configPath_(configPath), sensorNumber_(sensorNumber), configEditTime_(0)
{
    int err = 0; 
    //Get offset and factor
    err = setConfig(); 
    if(!err)
        throw Exception("Config not accessible (try using sudo)");
    
    //Setup UART
    err = setupUART();
    if(err < 0)
        throw Exception("UART unavaliable");
}

int Sensor::setConfig()
{
    struct stat attr;
    int err = 0; 

    ifstream file(configPath_);
    string configLine;

    err = stat(configPath_.c_str(), &attr);

    if (configEditTime_ != attr.st_mtim.tv_sec)
    {
        configEditTime_ = attr.st_mtim.tv_sec;

        while(getline(file,configLine))
        {
            stringstream linestream(configLine);
            string sensorNumber, offset, factor; 
            int sensorNumberInt;

            getline(linestream,sensorNumber,';');
            getline(linestream,offset,';');
            getline(linestream,factor,';');
            
            sensorNumberInt = stoi(sensorNumber);

            if(sensorNumberInt == sensorNumber_)
            {
                setOffset(stold(offset));
                setFactor(stold(factor));
            }
        }
        cout << "Sensor " << sensorNumber_ << ": Offset = " << SCT_.offset_ << " Factor = " << SCT_.factor_ << endl; 
    }

    return (err < 0 ? 0 : 1); 
}

int Sensor::setupUART(){
    
    struct termios options;
    int err = 0; 

    filedescriptor_ = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
    cout << "Open UART driver. File descriptor: " << filedescriptor_ << endl; 
    
    if (filedescriptor_ == -1)
    {
        perror("open_port: Unable to open /dev/ttyf1 - ");
        return -1; 
    }
    
    err = fcntl(filedescriptor_, F_SETFL, FNDELAY); //Set delay
    cout << "UART: set delay returned " << err << endl; 

    err = tcgetattr(filedescriptor_, &options); //Get options 
    cout << "UART: get options returned " << err << endl; 
    
    err = cfsetispeed(&options, B9600); //Set input BAUD
    err = cfsetospeed(&options, B9600); //Set output BAUD
    cout << "UART: set baud returned " << err << endl; 
   
    options.c_cflag |= (CLOCAL | CREAD); //Set CLOCAL = no modem, CREAD = possible to read
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); //Raw input
    
    options.c_cflag &= ~CSIZE; //Mask to set data bit
    options.c_cflag |= CS8;    //8 data bit

    options.c_lflag &= ~ICANON; // Set non-canonical mode
    
    err = tcsetattr(filedescriptor_, TCSANOW, &options); //Set changes

    //Timeout 

    cout << "UART: set options returned " << err << endl; 

    return err;
}

uint16_t Sensor::readRaw(){
    int attempt = 0, err = 0, rv = 0; 
    unsigned char request = 0, kontrol = 0, checksum = 0xFF;
    uint32_t reply = 0; 
    struct termios options;
    fd_set set; 
    struct timeval timeout; 

    setConfig();

    do{
        if (attempt == 0)
            usleep(20000);
        
        attempt++; 

        write(filedescriptor_,&request,1);

        err = tcgetattr(filedescriptor_, &options); //Get options
        if (err < 0)
            cout << "READ: Get attr returned " << err << endl;
        err = tcsetattr(filedescriptor_, TCSAFLUSH, &options); //Flush buffer
        if (err < 0)
            cout << "READ: Set attr (buffer flush) returned " << err << endl;
        
        //Read with timeout
        FD_ZERO(&set);
        FD_SET(filedescriptor_, &set);
        timeout.tv_sec = 0;
        timeout.tv_usec = 50000;
        rv = select(filedescriptor_ + 1, &set, NULL, NULL, &timeout);
        if (err < 0)
            cout << "UART: read returned with error: " << err << endl; 
        else if(rv == 0)
            cout << "UART: read returned with timeout" << endl; 
        else
            read(filedescriptor_,&reply,4);
    }while( attempt <= 3 &&
            (((kontrol + request) & 0xFF) != checksum) && 
            reply == 0);

    if ((((kontrol + request) & 0xFF) != checksum) && reply != 0)
        return reply;
    else
        return 0;
}

double Sensor::sensorRead(){
    uint16_t data = readRaw();
    return ((data * SCT_.factor_)+data + SCT_.offset_);
}

void Sensor::setOffset(long double offset){
    if(!isnanl(offset))
    {

        SCT_.offset_ = offset;
    }
    return; 
}

void Sensor::setFactor(long double factor){
        if(!isnanl(factor))
    {

        SCT_.factor_ = factor;
    }
    return; 
}

Sensor::~Sensor()
{
}