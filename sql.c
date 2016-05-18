static MYSQL *connection;

/**	creates connection to NSA-SQL Database
 * 	if it doesnt work the program will close because there is no need for it tu be running without the SQL connection.
 */
void createConnectionSQL(){
    connection = mysql_init(NULL);
    if (mysql_real_connect(connection, "localhost", "simon", "lammkott","nsa-uno-db", 0, NULL, 0) == NULL) {
    	fprintf(stderr,"fail connection\n\n %s [%d]\n",mysql_error(connection), mysql_errno(connection));         
        mysql_close(connection);
	exit(1);
    }
}
/**	sends data to NSA-SQL Database
 * 	if it doesnt work the program will close because there is no need for it to be running without the posibility to send data SQL.
 */
void sendTriggerToSQL(){
    if(mysql_query(connection, "INSERT INTO event(type) VALUES(3)")){
	fprintf(stderr,"fail connection\n\n %s [%d]\n",mysql_error(connection), mysql_errno(connection));
        mysql_close(connection);
        exit(0);
    }
}
/** fetches the last trigger type from database and returns it
 *	returns event type if successful or -1 if fail or NULL.
 */

int getLastTriggerFromSQL(){
    
    if(mysql_query(connection, "SELECT type FROM event ORDER BY id DESC LIMIT 1;")){
	fprintf(stderr,"fail connection\n\n %s [%d]\n",mysql_error(connection), mysql_errno(connection));
	mysql_close(connection);
	exit(0);
    }
    MYSQL_ROW row;
    MYSQL_RES *result = mysql_store_result(connection);
    
    if((row = mysql_fetch_row(result))){
	int  resultvalue = atoi(row[0]);
	mysql_free_result(result);
	return resultvalue;
	
    }
    mysql_free_result(result);
    return -1;
}

void sendArduinoDisconnectToSQL(){
    if(mysql_query(connection, "INSERT INTO event(type) VALUES(4)")){
	fprintf(stderr,"fail connection\n\n %s [%d]\n",mysql_error(connection), mysql_errno(connection));
        mysql_close(connection);
        exit(0);
    }
}

void triggerdLoop(){
    while(1){
	int value = getLastTriggerFromSQL();
	if(value!=3 && value!=-1){
	    return;
	}
	sleep(2);
    }
}
