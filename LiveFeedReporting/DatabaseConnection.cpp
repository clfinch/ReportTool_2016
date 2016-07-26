#include"DatabaseConnection.h"

pickDBConnection::pickDBConnection(){
	_mbscpy_s(dataSource,SQL_MAX_DSN_LENGTH, (const unsigned char *)"PickDirector");
}

int pickDBConnection::sqlconn(string aDBName){
	SQLAllocEnv(&henv);
	SQLAllocConnect(henv,&hdbc);
	rc = SQLConnect(hdbc,(unsigned char*)aDBName,SQL_NTS,0,0,0,0);

	// Deallocate Handles, Display error message, and exit
	if(!MYSQLSUCCESS(rc)) {
		//SQLFreeConnect(henv);
		SQLFreeEnv(henv);
		SQLFreeConnect(hdbc);
		if(hstmt)
			error_out();
		return -1;
	}// end if

	//rc = SQLAllocStmt(hdbc,&hstmt);
	return rc;
}// end sqlconn

// Execute sql command
int pickDBConnection::sqlexec(string aSQL, string aAction){
	rc = SQLAllocStmt(hdbc,&hstmt);
	rc = SQLExecDirect(hstmt,(unsigned char*)aSQL,SQL_NTS);
	if(!MYSQLSUCCESS(rc)){
		error_out();
		//Deallocate Handles and disconnect
		SQLFreeStmt(hstmt,SQL_DROP);
		SQLDisconnect(hdbc);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
		return -1;
	}// end if

	if(aAction.compare("update") == 0)
	{
		for( rc = SQLFetch(hstmt); rc == SQL_SUCCESS ; rc=SQLFetch(hstmt)){
			// TODO Add colum gets for each row. Not sure exact arch atm
			SQLGetData(hstmt,1,SQL_C_CHAR,szData,sizeof(szData),&cbData);
		}// end for
	}
	else if(aAction.compare("delete") == 0)
	{
		//todo start delete logic
	}
	return rc;
}// end sqlexec

// Free teh handles
void pickDBConnection::sqldisconn(){
	SQLFreeStmt(hstmt,SQL_DROP);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);
}// end sqldiscon

void pickDBConnection::error_out(){
	unsigned char szSQLSTATE[10];
	SDWORD nErr;
	unsigned char msg[SQL_MAX_MESSAGE_LENGTH+1];
	SWORD cbmsg;

}// end error out

