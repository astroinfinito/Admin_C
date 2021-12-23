#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcion2.h"

//Definimos todas las librerías desde la línea 1 hasta la 5

char fast_dns2[50] = ""; //Variable global que usamos en las 3 funciones

void Funcion2() {

	FILE* flectura_txt_dns;
	FILE* fescritura_txt;
	FILE* fabrir_txt_ping;

	char read_ip[15] = "";
	char make_ping[100] = "";
	char read_ping[500] = "";
	char resultado_ping[500] = "";
	int media_ms_ping_dns = 0;
	int media_respuesta_dns_mas_rapid = 500;


	flectura_txt_dns = fopen("reescribir.txt", "rt");  //Apertura del txt para ver las respuestas del ping

	while (fscanf(flectura_txt_dns, "%s", read_ip) != EOF) {
		strcpy(make_ping, "ping ");
		strcpy(read_ping, make_ping);
		strcat(read_ping, read_ip);
		strcat(read_ping, "> resultadoping2.txt");

		system(read_ping);

		fabrir_txt_ping = fopen("resultadoping2.txt", "rt"); //Abre el txt para escribir las respuestas del ping

		while (fscanf(fabrir_txt_ping, "%s", resultado_ping) != EOF) {

			if (!strcmp(resultado_ping, "Media", 5)) {
				fscanf(fabrir_txt_ping, "%s", resultado_ping);
				fscanf(fabrir_txt_ping, "%s", resultado_ping);

				media_ms_ping_dns = atoi(strtok(resultado_ping, "ms"));
				printf("\n");
				printf("La velocidad media de respuesta de la DNS %s es:  %d\n", read_ip, media_ms_ping_dns);

				if (media_ms_ping_dns < media_respuesta_dns_mas_rapid) { //Dice el DNS más rápido
					media_respuesta_dns_mas_rapid = media_ms_ping_dns;
					strcpy(fast_dns2, read_ip);
				}
			}
		}

		fclose(fabrir_txt_ping);
		fscanf(flectura_txt_dns, "%s", read_ip); 
		fclose(flectura_txt_dns); //Cerramos el fichero seleccionado

		printf("\n");
		printf("El servidor mas rapido es %s, con %d ms\n", fast_dns2, media_respuesta_dns_mas_rapid);
		printf("\n");

		break;
	}
}


