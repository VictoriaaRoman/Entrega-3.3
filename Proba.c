//programa en C para consultar los datos de la base de datos
//Suma de las partidas ganadas de Victoria
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
	MYSQL_ROW rowS;
	MYSQL_ROW rowI;
	char consulta [80];
	int idJI=4;
	int idPI[100];
	int idPS[100];
	char nombre[60];
	strcpy (nombre,"Victoria");
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
		sprintf (consulta,"SELECT sum (partidas.ganador) FROM (partidas, participacion, jugador) WHERE jugador.nombre = '%s' AND jugador.id = participacion.idJ AND participacion.idP = partidas.id",nombre);
		// hacemos la consulta 
		err=mysql_query (conn, consulta); 
		if (err!=0) {
			printf ("Error al consultar datos de la base %u %s\n",
					mysql_errno(conn), mysql_error(conn));
			exit (1);
		}
		//recogemos el resultado de la consulta 
		resultado = mysql_store_result (conn); 
		rowS = mysql_fetch_row (resultado);
		int x=0;
		int y=0;
		if (rowS == NULL)
			printf ("No se han obtenido datos en la consulta\n");
		else{
			while (rowS !=NULL) {
			// El resultado debe ser una matriz con 3 filas
			// y una columna que contiene el id de partida
				idPS[x]=atoi(rowS[0]);
				x++;
				rowS = mysql_fetch_row (resultado);
			}
			y=x;
		}
		sprintf("La suma de las partidas ganadas de %s son %d", nombre,idPS[0]);
		// cerrar la conexion con el servidor MYSQL 
		mysql_close (conn);
		exit(0);
}
