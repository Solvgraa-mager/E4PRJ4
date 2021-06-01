#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int main(int argc, char **argv)
{
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "phpmyadmin", "raspberry",
          "testdb", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO measurements (temp, waterLevel, salt) VALUES(24.2, 22.1 , 30.0)")) {
      finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO measurements (temp, waterLevel, salt) VALUES(24.3, 22.2 , 30.1)")) {
      finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO measurements (temp, waterLevel, salt) VALUES(24.4, 22.4 , 30.2)")) {
      finish_with_error(con);
  }

  if (mysql_query(con, "INSERT INTO measurements (temp, waterLevel, salt) VALUES(24.5, 22.5 , 30.3)")) {
      finish_with_error(con);
  }

  mysql_close(con);
  exit(0);
}