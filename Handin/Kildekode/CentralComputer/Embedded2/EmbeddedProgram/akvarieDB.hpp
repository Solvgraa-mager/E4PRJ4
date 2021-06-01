//////////////////////////////////////
// Developed by Christian and David //
// Digitalizing is assuming reality //
//////////////////////////////////////
#pragma once
#include <string>
#include <iostream>
#include <mysql.h>

using namespace std;

class akvarieDB{
public:
    akvarieDB();
    bool getFlag(string);
    float getSetpoint(string);
    void SaveData(string Message);
    ~akvarieDB();


private:
    bool MySqlGetFlag(string);
    float MySqlgetSetpoint(string);
    MYSQL* MysqlInit();
    void finish_with_error(MYSQL*);
    
    bool SaltFlag;
    bool LightFlag;
    bool TempFlag;

    float temperature;
    float salt;
    float waterLevel;
    bool light;
    //Acctual DB parameters!
    const string DOMAIN = "localhost";
    const string USERNAME = "phpmyadmin";
    const string PASSWORD = "raspberry";
    const string DBNAME = "akvarieDB"; 

};