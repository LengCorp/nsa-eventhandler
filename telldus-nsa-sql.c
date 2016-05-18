#include <Telldus-core.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <my_global.h>
#include <mysql.h>

int receiveTelldusData(){

}

static MYSQL *connection;

MYSQL createConnectionSQL(){
        connection = mysql_init(NULL);
  	if (mysql_real_connect(connection, "localhost", "root", "root_pswd", NULL, 0, NULL, 0) == NULL) {
      writeError(mysql_error(connection));
      mysql_close(connection);
      exit(1);
  	}  
  return connection;
}
void sendDataToSQL(){
  if(mysql_query(connection, "INSERT INTO event(type) VALUES(3)")){
      writeError(mysql_error(connection));
      mysql_close(connection);
    }
}

int isTriggered(){

    if(mysql_query(connection, "INSERT INTO event(type) VALUES(3)")){
	writeError(mysql_error(connection));
	mysql_close(connection);
	return 0;
    } else { 
	mysql_store_result(con);
	    
	    }
}

void writeError(char *text){
	FILE *errorlog = fopen( "/var/log/NSA/error.txt", "w+");
	fprintf(errorlog, "%s\n", text);
	fclose(fp);
}


int main(int argc, char const *argv[])
{
	MYSQL *connection = createConnectionSQL();
	sendDataToSQL(connection);
 	mysql_close(connection);
	return 0;
}
