/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
  In order to run sudo apt-get install  libmysqlcppconn-dev
  Compile with: sudo g++ -Wall -I/usr/include/cppconn -o sqlTester sqlTester.cc -L/usr/lib -lmysqlcppconn

*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main(void){
  cout << endl;
  cout << "Running 'SELECT 'Hello World!' » AS _message'..." << endl;
  try {
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("puccini.cs.lth.se", "db75", "pegan1902");

    //Connect to the mySQL database
    con->setSchema("db75");
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM cookie");

    cout << "MySQL replies: \n";
    while (res->next()) {
      /* Access column data by alias or column name */
      cout << res->getString("cookieName") << endl;
      //cout << "\t... MySQL says it again: ";
      /* Access column fata by numeric offset, 1 is the first column */
      //cout << res->getString(1) << endl;
    }
    delete res;
    delete stmt;
    delete con;
  } catch (sql::SQLException &e) {
    cout << "# ERR: SQLException in " << "__FILE__";
    cout << "(" << "__FUNCTION__" << ") on line "
       << "__LINE__" << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  }

  cout << endl;
  return EXIT_SUCCESS;
}
