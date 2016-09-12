#ifndef DatabaseConnection.h
#define DatabaseConnection.h
#include<stdio.h>
#include<windows.h>
#include<sql.h>
#include<sqlext.h>
#include<mbstring.h>
#include<string>

#define MYSQLSUCCESS(rc) ((rc == SQL_SUCCESS)|| (rc == SQL_SUCCESS_WITH_INFO) )
using namespace std;
class pickDBConnection {
	RETCODE rc; //ODBC return code
	HENV henv; //Enviornment
	HDBC hdbc; // ConnectionHandle
	HSTMT hstmt; // statement handle
	SDWORD cbData; // output length
	unsigned char dataSource[SQL_MAX_DSN_LENGTH];
	unsigned char szData[5000]; // Returned DataStruct
	//SQLRETURN rc;
public:
	pickDBConnection();//constructior
	int sqlconn(string aDBName);
	int sqlexec(string aSQL, string aAction);
	void sqldisconn();
	void error_out();
};// end class pickDBConnection

#endif