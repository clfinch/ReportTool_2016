#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
#include "DatabaseConnection.h"
using namespace std;

int main(){
	char* const configurationFile = ":\DirectorIT\LiveFeedReporting\LiveFeedReport.ini";
	string databaseName;
	string startShiftTime;
	string endShiftTime;
	int connectionStatus;
	char installLetter;
	// get install Path of DirectorIT
	installLetter = installedDrive();
	if(installLetter == 0){
		// TODO Add Logging
		return -1;
	}// end if
	
	// Read configuration File
	ifstream myFile;
	myFile.open(installLetter + configurationFile);
	if(myFile.is_open()){
		string configLine;
		while(getline(myFile,configLine))
		{
			if(configLine.find("DatabaseName")){
				databaseName = configLine.substr(configLine.find("DatabaseName"));
			}//end if
			else if(configLine.find("StartShift")){
				startShiftTime = configLine.substr(configLine.find("StartShift"));
			}// end elseif
			else if(configLine.find("EndShift")){
				endShiftTime = configLine.substr(configLine.find("EndShift"));
			}// end else if
		}// end while

		// Verify critical configs have been set
		if(databaseName.empty() || startShiftTime.empty() || endShiftTime.empty()){
			//TODO Add Error Logging
			return -1;
		}// end  if
	}//end if
	else{
		//TODO Add Error logging
		return -1;
	}// end else
	//TODO Add retries for connecting?
	pickDBConnection pDB;
	connectionStatus = pDB.sqlconn(databaseName);

	// check if connection successful
	if(connectionStatus == -1){
		// TODO add error logging
		return -1;
	}// end if

	startOfShiftCleanup(pDB);
}// end main

int startOfShiftCleanup(pickDBConnection aDB)
{
	string theSQLExec("TRUNCATE TABLE ReportTool.CurrentStandings");
	// First we need to clear the currentstandings
	aDB.sqlexec(theSQLExec,"delete");
	return 1;
}// end startOfShiftCleanup
// Helper Function to find the installed Drive
char installedDrive() {
	char* iPath;
	iPath = getenv("DITPATH");

	if(iPath!=NULL){
		return iPath[0];
	}// end if
	else{
		return 0;
	}// end else
}// end installedDrive