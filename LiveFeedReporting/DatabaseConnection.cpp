#include"DatabaseConnection.h"

pickDBConnection::pickDBConnection(){
	_mbscpy_s(dataSource,SQL_MAX_DSN_LENGTH, (const unsigned char *)"PickDirector");
}

int pickDBConnection::sqlconn(){
	SQLAllocEnv(&henv);
	SQLAllocConnect(henv,&hdbc);
	rc = SQLConnect(hdbc,dataSource,SQL_NTS,NULL,0,NULL,0);

	// Deallocate Handles, Display error message, and exit
	if(!MYSQLSUCCESS(rc)) {
		SQLFreeConnect(henv);
		SQLFreeEnv(henv);
		SQLFreeConnect(hdbc);
		if(hstmt)
			error_out();
		return -1;
	}// end if

	rc = SQLAllocStmt(hdbc,&hstmt);
	return 1;
}// end sqlconn

// Execute sql command
int pickDBConnection::sqlexec(unsigned char* cmdstr){
	rc = SQLExecDirect(hstmt,cmdstr,SQL_NTS);
	if(!MYSQLSUCCESS(rc)){
		error_out();
		//Deallocate Handles and disconnect
		SQLFreeStmt(hstmt,SQL_DROP);
		SQLDisconnect(hdbc);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
		return -1;
	}// end if
	else{
		for( rc = SQLFetch(hstmt); rc == SQL_SUCCESS ; rc=SQLFetch(hstmt)){
			SQLGetData(hstmt,1,SQL_C_CHAR,szData,sizeof(szData),&cbData);
		}// end for
	}// end else
	return 1;
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

	while(SQLError(0,0,hstmt,szSQLSTATE,&nErr,msg,sizeof(msg), &cbmsg) == SQL_SUCCESS){
		// TODO Add Error Logging
	}// END while
}// end error out

