
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
    if (err < 0){
        cout << "setConfig: stat returned " << err << endl;
        cout << "setConfig: errno :" << errno << endl;  
    }

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
        //cout << "Sensor " << sensorNumber_ << ": Offset = " << SCT_.offset_ << " Factor = " << SCT_.factor_ << endl; 
    }

    return (err < 0 ? 0 : 1); 
}

int Sensor::setupUART(){
    int err = 0; 
    filedescriptor_ = -1;
    struct termios options;
    
    filedescriptor_ = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
    cout << "Filedescriptor (setupUART): " << filedescriptor_ << endl; 
    if (filedescriptor_ < 0)
	{
		printf("Error - Unable to open UART.\n");
        return err; 
	}
    tcgetattr(filedescriptor_, &options);
    options.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    options.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication
    options.c_cflag &= ~CSIZE; // Clear all the size bits
    options.c_cflag |= CS8;
    options.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control
    options.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)
    options.c_lflag &= ~ICANON; //Cannonical mode disable
    options.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    options.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    options.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL); // Disable any special handling of received bytes
    options.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    options.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    options.c_cc[VTIME] = 100;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
    options.c_cc[VMIN] = 0;

    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);

	//tcflush(filedescriptor_, TCIFLUSH);
	err = tcsetattr(filedescriptor_, TCSANOW, &options);

    return err;  
}

uint16_t Sensor::readRaw(){
    int attempt = 0, err = 0, rv = 0; 
    unsigned char request = 0, kontrol = 0, checksum = 0xFF;
    char reply[1000];
    int rx_length = 0; 

    setConfig();

    request = (1 << (sensorNumber_-1));
    
    do{
        if (attempt == 0)
            usleep(200000);
        
        attempt++; 
        cout << "Filedescriptor (readRaw): " <<filedescriptor_ << endl; 
        err = write(filedescriptor_, &request, 1);
        //printf("%i bytes request written to UART\n", err);
        if (err < 0)
        {
           printf("Write error! Errno: %i\n", errno); 
           perror("Write error: ");
        }
        usleep(15000); //According to protocol
        
        memset(&reply, '\0', sizeof(reply));

		rx_length = read(filedescriptor_, &reply, sizeof(reply));

        cout << "rx_length = " << rx_length << endl; 
		if (rx_length < 0)
		{
			printf("Nothing to read from UART\n",rx_length);
            printf("Errno: %i\n", errno); 
		}
		else if (rx_length == 0)
		{
			printf("Ny bytes read in UART\n");
		}
		else
		{
			//printf("Attempt: %i\n", attempt);
            for(int i = 0; i<rx_length;i++)
            {
                printf("%#X ",reply[i]);
            }
            printf("\n");
		}
	
    }while( (attempt < 3) && (rx_length < 0));

    return 1; 
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
    close(filedescriptor_);
}