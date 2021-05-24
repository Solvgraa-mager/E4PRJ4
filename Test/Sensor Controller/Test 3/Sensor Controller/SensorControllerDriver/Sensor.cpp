
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
        cout << "setConfig: stat returned " << err << " with errno: " << errno << endl;
        return 0; 
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
                break;
            }
        }
        cout << "Sensor " << sensorNumber_ << ": Offset = " << SCT_.offset_ << " Factor = " << SCT_.factor_ << endl; 
    }

    return (err < 0 ? 0 : 1); 
}

int Sensor::setupUART(){
    int err = 0; 
    int filedescriptor = -1;
    struct termios options;
    
    filedescriptor = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (filedescriptor < 0)
	{
		cout << "Error - Unable to open UART." << endl; 
        return err;
	}
    tcgetattr(filedescriptor, &options); //Get attributes
    /**** UART Options ****/
    options.c_cflag &= ~PARENB; // Clear parity bit, disabling parity
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

	//tcflush(filedescriptor, TCIFLUSH); //Flush UART receive buffer
	err = tcsetattr(filedescriptor, TCSANOW, &options); //Set attributes
    
    close(filedescriptor);

    return err;  
}

uint16_t Sensor::readRaw(){
    /**** Allocations ****/
    int attempt = 0, err = 0, filedescriptor, readErr; 
    
    uint16_t value = 0; 
    
    setConfig(); //Check if new calibration data

    do{
        if (attempt == 0)
            usleep(20000); //Protocol flow control
        
        attempt++; //Increment attempt-count

        filedescriptor = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);

        sendRequest(filedescriptor); //Send request encoded
        
        usleep(10000); //Wait for reply according to protocol

        readErr = receiveAnswer(filedescriptor,value); //Read and parse reply
        
    }while((attempt < 3) && !readErr);

    close(filedescriptor);

    return value; 
}

int Sensor::receiveAnswer(int fd, uint16_t &value){
    int rx_length = 0;
    char reply[256] = {0};
    unsigned char kontrol = 0, checksum = 0xFF;

    rx_length = read(fd, &reply, sizeof(reply)); //Get reply

		if (rx_length < 0) //Error handling
		{
            printf("UART: Errno: %i\n", errno); 
            return false; //UART Error 
		}
		else if (rx_length == 0) //No bytes in UART
		{
			printf("No bytes read in UART\n");
            return false; 
		}
        else if(rx_length == 4) //Answer according to protocol
        {
            /*** Parse answer ***/
            value = ((reply[0]<<8) + reply[1]);
            kontrol = reply[2];
            checksum = reply[3];

            if(kontrol != 0xFF)
            {
                cout << "Invalid read!" << endl;
                return false;
            }
            if(checksum != ((value+sensorNumber_) & 0xFF))
            {
                cout << "Checksum not correct" << endl; 
                return false; 
            }
            return true; 
        }
		else
		{
			cout << "Unparsable msg" << endl; 
            return false; 
		}
}

int Sensor::sendRequest(int fd){
    unsigned char requestEncoded; 
    int err; 
    
    requestEncoded = (1 << (sensorNumber_)); //Request one-hot encoding
    
    tcflush(fd,TCIOFLUSH); //Flush UART receive buffer
    
    err = write(fd, &requestEncoded, 1); //Write request
        if (err < 0)
        {
           printf("Write error! Errno: %i\n", errno); 
           perror("Write error: ");
        }
    return err; 
}

double Sensor::sensorRead(){
    uint16_t data = readRaw();
    double reading = ((double)data*(double)SCT_.factor_)+(double)SCT_.offset_;
    return reading;
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