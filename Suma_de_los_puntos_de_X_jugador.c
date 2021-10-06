
//programa en C para consultar los datos de la base de datos
//Suma de los puntos de jugador introducido
//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexiￃﾳn: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	//inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "BBDDv1",0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexiￃﾳn: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
		
		// construimos la consulta SQL
	    printf("Dame el nombre \n");
	    char nombre [20];
		scanf ("%s", nombre);
		char consulta [200];
		sprintf(consulta,"SELECT sum(participacion.puntos) FROM (participacion, jugador) WHERE jugador.nombre = '%s' AND jugador.id = participacion.idJ", nombre);
		//strcpy(consulta,"SELECT * FROM participacion");
		err=mysql_query (conn, consulta); 
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta 
		resultado = mysql_store_result (conn); 
		row = mysql_fetch_row (resultado);
		if (row == NULL){
			printf("No ha jugado");
		}
		else{
			printf("Resultado: %s", row[0]);
		}
		// cerrar la conexion con el servidor MYSQL 
		mysql_close (conn);
		exit(0);
}
