//////////////////////////////////////
// Developed by Christian and David //
// Digitalizing is assuming reality //
//////////////////////////////////////
#include "akvarieDB.hpp"

//Constructor for akvarieDB database - MariaDB database very similar to Mysql - same developers
akvarieDB::akvarieDB()
{
    
}

//Function to assist getFlag 
//Inspiration from https://zetcode.com/db/mysqlc/
bool akvarieDB::MySqlGetFlag(string RequestFlag){
        //string to receive message from Mysql
        string ret;
        MYSQL* con = MysqlInit();
        //Query to send request
        if(mysql_query(con, RequestFlag.c_str())){finish_with_error(con);};

        //Store result collects results + fetch row on the single row
        MYSQL_RES *result = mysql_store_result(con);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))){ret = row[0];}

        //Free ressources
        mysql_free_result(result);
        mysql_close(con);

        //Return bool for main as flag - true/false!
        if(ret == "1"){return true;}
        else{return false;}
}

//GetFlag method which writes which flag to request from DB. Database handled in MySqlGetFlag()
bool akvarieDB::getFlag(string Flag)
{
    string flag;
    string init = "SELECT ";
    string end = " FROM activeprocesses";
    
    //Collect wished flag from main
    if(Flag == "TempFlag") {flag = "Temp";}
    else if(Flag == "LightFlag"){flag = "Light";}
    else if(Flag == "SaltFlag"){flag = "Salt";}

    //Create Mysql string and perform mysql transfer - returns the boolean for main so..
    string request = init + flag + end;
    return MySqlGetFlag(request);
}

//MySqlSetpoint for getting setpoint from DB.
float akvarieDB::MySqlgetSetpoint(string RequestSetPoint)
{
     //string to receive message from Mysql
        string ret;
        MYSQL* con = MysqlInit();
        //Query to send request
        if(mysql_query(con, RequestSetPoint.c_str())){finish_with_error(con);};

        //Store result collects results + fetch row on the single row
        MYSQL_RES *result = mysql_store_result(con);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))){ret = row[0];}

        //Free ressources
        mysql_free_result(result);
        mysql_close(con);

        //Return bool for main as flag - true/false!
        return std::stof(ret);
}

//Method for getting setpoint with DBhandle by MySqlgetSetpoint
float akvarieDB::getSetpoint(string setPoint)
{
    string set;
    string init = "SELECT ";
    string end = " FROM setpoints";

    if(setPoint == "Temp") {set = "Temp";}
    else if(setPoint == "Light") {set = "Light";}
    else if(setPoint == "Salt") {set = "Salt";}
    else if(setPoint == "WaterLevel") {set = "Waterlevel";}
    
    string request = init + set + end;
    
    //Returns setPoint as float
    return MySqlgetSetpoint(request);
}

//Initmethod for intiating connection to DB
MYSQL* akvarieDB::MysqlInit(){
  MYSQL *con = mysql_init(NULL);
  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }
  if (mysql_real_connect(con, DOMAIN.c_str(), USERNAME.c_str(), PASSWORD.c_str(),
          DBNAME.c_str(), 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
      //Reconnect implementation and wait conditions.. To be continued 2.0 - it works without, since network is stable.
  }
  return con;
}

//Assist-function
void akvarieDB::finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

//SaveData method for putting data on DB
void akvarieDB::SaveData(string Message){
    MYSQL* con = MysqlInit();
     if (mysql_query(con, Message.c_str())){
      finish_with_error(con);
    }
    mysql_close(con);
}

//Destructor for akvarieDB   
akvarieDB::~akvarieDB()
{

}