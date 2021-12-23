#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcion1.h"

//Definimos todas las librerías desde la línea 1 hasta la 5


char fast_dns[50] = ""; //Variable global

void Funcion1() {
	
	FILE* flectura_txt_dns;
	FILE* fescritura_txt;
	FILE* fabrir_txt_ping;
	char read_ip[15] = "";
	char read_documento[100] = ""; //al encontrarse el txt en la misma carpeta que el proyecto no necesita la ruta, solo el nombre de archivo con su extensi�n
	char hacer_ping[100] = "";
	char resultado_ping[500] = "";

	printf("Ruta archivo:\n");
	scanf("%s", &read_documento);  //guardamos el resultado en la variable

	flectura_txt_dns = fopen(read_documento, "rt");

	//Funcion para indicar que no se ha encontrado el documento
	if (flectura_txt_dns == NULL) {
		printf("Documento no encontrado.\n");
		exit(-1);
	}

	//Funcion que muestra el contenido del txt
	printf("\n");
	printf("Archivo: %s", read_documento);
	printf("\n");
	
	while (fscanf(flectura_txt_dns, "%s", read_ip) != EOF) {

		printf("Direccion: %s \n", read_ip);		// Mostramos la IP a la que se va a hacer ping
	}
	fclose(flectura_txt_dns);

	flectura_txt_dns = fopen(read_documento, "rt");	//Abre el archivo de texto
	fescritura_txt = fopen("resultado.txt", "w");
	printf("\n");
	printf("Resultado del ping:\n");
	printf("\n");

	while (fscanf(flectura_txt_dns, "%s", read_ip) != EOF) {

		printf("Direccion: %s", read_ip);		// Mostramos la IP

		strcpy(hacer_ping, "ping -n 3 -w 500 ");	// Le a�adimos a la IP el comnado que nos hace falta para hacer el ping

		strcat(hacer_ping, read_ip);			// Guardamos el ping en el archivo txt
		strcat(hacer_ping, " > resultadoping.txt");

		system(hacer_ping);						// Hacemos ping


		fabrir_txt_ping = fopen("resultadoping.txt", "rt");	//abrimos el txt con el resultado del ping guardado
		if (fabrir_txt_ping == NULL) {						// Comprobaci�n de ruta
			printf("Error al abrir el archivo");
		}

		while (!feof(fabrir_txt_ping)) {
			fscanf(fabrir_txt_ping, "%s", resultado_ping);

			if (strncmp(resultado_ping, "(0%", 3) == 0) {			//Si contesta
				printf(" -> Contesta \n");
				fprintf(fescritura_txt, "%s\n", read_ip);
				break;
			}

			if (strncmp(resultado_ping, "agotado", 7) == 0) {		//Si se agota el tiempo de respuesta
				printf(" -> No contesta \n");
				break;
			}

			if (strncmp(resultado_ping, "inaccesible", 11) == 0) {	//Si no contesta
				printf(" -> No contesta \n");
				break;
			}
		}
		fclose(fabrir_txt_ping);
	}
	fclose(flectura_txt_dns);
	fclose(fescritura_txt);
}

