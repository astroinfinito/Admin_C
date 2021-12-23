#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Funcion3.h"

//Definimos todas las librerías desde la línea 1 hasta la 5


char fast_dns3[50] = ""; //Variable global

void Funcion3() {
	char adaptador_netsh[100] = "";
	char configuracion_lectura[100] = "";
	char nombre_adaptador[100];
	char netsh_lista[100] = "";//"Variable donde guardaremos el comando netsh show ip config ";
	char adapadores_lista[100] = "";
	char DNS_cambio[500] = "";

	FILE* flectura_txt_configuracion_red;

	printf("\n");
	printf("Nombre adaptador:\n"); //Probar de forma predeterminada con la interfaz Wi-Fi
	scanf("%s", nombre_adaptador);  
	printf("\n");

	printf("Presiona Intro para continuar.\n");

	leecad(nombre_adaptador, 100);

	strcpy(adaptador_netsh, "netsh interface ip show config ");

	strcat(adaptador_netsh, nombre_adaptador);
	strcat(adaptador_netsh, " > nombre_adaptadores.txt");

	system(adaptador_netsh);

	flectura_txt_configuracion_red = fopen("nombre_adaptadores.txt", "rt");


	//Esta funcion se ejecuta cuando no se ha encontrado el documento
	if (flectura_txt_configuracion_red == NULL) {
		printf("No se ha podido abrir el documento. %s\n", flectura_txt_configuracion_red);
	}

	else {

		while (!feof(flectura_txt_configuracion_red)) { //El while está diseñado para encontrar la IP del servidor DNS
			fscanf(flectura_txt_configuracion_red, "%s", configuracion_lectura);

			if (!strcmp(configuracion_lectura, "DNS", 3)) {
				printf("Adaptador -> %s\n", nombre_adaptador);
				fscanf(flectura_txt_configuracion_red, "%s", configuracion_lectura);
				fscanf(flectura_txt_configuracion_red, "%s", configuracion_lectura);
				fscanf(flectura_txt_configuracion_red, "%s", configuracion_lectura);
				fscanf(flectura_txt_configuracion_red, "%s", configuracion_lectura);
				fscanf(flectura_txt_configuracion_red, "%s", configuracion_lectura);
				fscanf(flectura_txt_configuracion_red, "%s", configuracion_lectura);

				printf("DNS -> %s\n", configuracion_lectura);
				printf("\n");
			}
		}
	}

	//Renovamos la DNS anterior. Comprobar privelegios de administador.
	strcpy(DNS_cambio, "netsh interface ipv4 set dnsservers ");
	strcat(DNS_cambio, nombre_adaptador);
	strcat(DNS_cambio, " dhcp");
	strcat(DNS_cambio, "\0");

	system(DNS_cambio);

	//Introducimos una IP DNS nueva
	strcpy(DNS_cambio, "netsh interface ipv4 add dns ");
	strcat(DNS_cambio, nombre_adaptador);
	strcat(DNS_cambio, " ");
	strcat(DNS_cambio, fast_dns3);
	strcat(DNS_cambio, " index=1 validate=no");
	strcat(DNS_cambio, "\0");

	printf("Adaptador ->  %s  \n", nombre_adaptador);
	printf("DNS nuevo, el mas rapido ->  %s \n", fast_dns3);
	printf("\n");
}


//Comprobaciones condicionales finales

int leecad(char* cad, int n) {
	int i, c;
	c = getchar();
	if (c == EOF) {
		cad[0] = '\0';
		return 0;
	}
	if (c == '\n') {
		i = 0;
	}
	else {
		cad[0] = c;
		i = 1;
	}
	for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		cad[i] = c;
		cad[i] = '\0';
	}
	if (c != '\n' && c != EOF) {
		while ((c = getchar()) != '\n' && c != EOF);
	}
	return 1;
}