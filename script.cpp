// 
// Producto 2 P4-Comandos personalizados para el sistema operativo 
// Alumno: Rafael Alberto Zarzo Torres
//

//Cargamos las librerías básicas del programa

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Funcion1.h"
#include "Funcion2.h"
#include "Funcion3.h"


void Funcion1() { //Esta es la función que nos permitirá saber que maquinas responden a un ping en la red
	system("cls");
	printf("Has seleccionado un 1\n");
	printf("\n");
	printf("1) Mostrar las maquinas que respoden a un ping de la red\n");
	printf("\n");
	
	//Declaración de variables

	FILE* ip;
	char txt[100];
	char respuesta[100];
	char auxiliar1[100];

	printf("\n");
	printf("Introduzca la ruta del archivo: ");
	scanf("%s", txt);
	rewind(stdin);

	ip = fopen(txt, "r");

	if (ip == NULL) {
		printf("Error al abrir el archivo. Revise la ruta.");
		exit;
	}else {
		printf("\n Archivo abierto, su contenido es: \n\n");
		while (!feof(ip)) {
			printf("%c", getc(ip));
		}
		fclose(ip);
	}

	FILE* ip1;
	char auxiliar2[100];
	char ip2[100];
	char respuesta2[100];

	printf("\n");
	ip = fopen(txt, "r");

	while (!feof(ip)) {
		fgets(auxiliar1, 100, ip);
		printf("Analizando ip %s", auxiliar1);
		strcpy(respuesta, "> C:/IP/IP.txt ping ");
		strcat(respuesta, auxiliar1);
		system(respuesta);
		printf("\n");

		//strstr busca un string peque�o en un string mas grande

		bool encontrado = false;
		ip1 = fopen("C:/IP/ip.txt", "r");
		fgets(auxiliar2, 100, ip1);
		while (!feof(ip1) && !encontrado) {
			encontrado = (strstr(auxiliar2, "milisegundos") != NULL);
			if (!encontrado)fgets(auxiliar2, 100, ip1);
		}
		if (encontrado)printf("El ping %s es correcto\n", auxiliar1);
		else printf("El ping %s no es correcto\n", auxiliar1);

	}
	fclose(ip);

}

void Funcion2() { //Muestra la configuración de red de la máquina local //Comando a utilizar: netsh interface ipv4 show config name=Wi-Fi

	char adap[100]; //Nombre de la variable en la cual guardamos el adaptador de red
	char comando[100];

	system("cls");
	printf("Has seleccionado un 2\n");
	printf("\n");
	printf("2) Mostrar la configuracion de red de la maquina local \n");
	printf("\n");
	printf("Introduzca el nombre del adaptador: ");
	scanf("%s", adap);
	sprintf(comando, "netsh interface ipv4 show config name=%s", adap); //En caso de duda, probar con la interfaz Wi-Fi
	system(comando);
	
}

void Funcion3() { //Esta función lanzará pings y nos permitirá ver que IP responde antes
	
	system("cls");
	printf("Has selecionado un 3\n");
	printf("\n");
	printf("3) Lanzar pings a dos DNS y mostrar cuál de ellos responde antes\n");
	printf("\n");

	//Declaración de ficheros del programa

	FILE* DNS1;
	FILE* DNS2;

	//Declaración de variables

	char grabado1[50];
	char grabado2[50];
	char IP1[50];
	char IP2[50];
	char serial[100];
	char var1[100];
	bool encontrado;
	
	//Solicitamos las IP's al usuario

	printf("Introduzca la primera IP: "); //Guardamos las IP's en una variable
	rewind(stdin);
	scanf("%s", &grabado1);

	printf("Introduzca la segunda IP: "); //Guardamos las IP's en una variable
	rewind(stdin);
	scanf("%s", &grabado2);

	//Lanzamiento de ping del servidor DNS. Redireccionamiento

	strcpy(IP1, "> C:/IP/DNS1.txt ping "); //Leemos el contenido del archivo DNS1.txt. Está guardado en la unidad C:
	strcat(IP1, grabado1);
	printf("\n--Analizando IP 1: %s\n", grabado1);
	system(IP1);
	encontrado = false;
	DNS1 = fopen("C:/IP/DNS1.txt", "r"); //Abrimos el archivo con permisos de lectura
	fgets(serial, 100, DNS1);

	while (!feof(DNS1) && !encontrado) {
		encontrado = (strstr(serial, "milisegundos") != NULL);
		if (!encontrado) fgets(serial, 100, DNS1);
	}
	if (encontrado) {
		printf("El ping es %s es CORRECTO", &grabado1);
	}else {
		printf("El ping es %s es INCORRECTO", &grabado1);
	}
	strcpy(IP2, "> C:/IP/DNS2.txt "); //Leemos el contenido del archivo DNS2.txt. Está guardado en la unidad C:
	strcat(IP2, "ping ");
	strcat(IP2, grabado2);
	printf("\n--Analizando IP 2: %s", grabado2);
	system(IP2);

	encontrado = false;
	DNS2 = fopen("C:/IP/DNS2.txt", "r");
	fgets(var1, 100, DNS2);

	while (!feof(DNS2) && !encontrado) {
		encontrado = (strstr(var1, "milisegundos") != NULL);
		if (!encontrado) fgets(var1, 100, DNS2);

	}
	if (encontrado) { //Sentencia condicional de las IPS
		printf("\nEl Ping %s es CORRECTO\n", grabado2);
	}
	else {
		printf("\nEl Ping %s es INCORRECTO\n", grabado2);
	}

	//Registramos la velocidad y la mostramos en pantalla
	rewind(DNS1);
	for (int i = 0; i < 11; i++) fgets(serial, 100, DNS1);
	for (int i = 0; i < 10; i++) fscanf(DNS1, "%s", serial);
	printf("\n\n Velocidad media DNS 1 es: %s ", serial);

	rewind(DNS2);
	for (int i = 0; i < 11; i++) fgets(serial, 100, DNS1);
	for (int i = 0; i < 10; i++) fscanf(DNS2, "%s", serial);
	printf("\n\n Velocidad media DNS 2 es: %s ", serial);

	serial[2] = '\0';
	int pl1 = atoi(serial);
	printf("\n");

	var1[2] = '\0';
	int pl2 = atoi(var1);
	printf("\n");

	//imprimimos por pantalla la DNS mas rapida 

	if (pl1 > pl2)
		printf("\n\n El DNS mas rapido es : %s", grabado2);
	else printf("\n\n El DNS mas rapido es: %s", grabado1);

	fclose(DNS1);
	fclose(DNS2);

}


int main() {

	int menu;
	char arr[10];
	printf("Elija una opcion: \n\n");
	printf("1) Mostrar las maquinas que respoden a un ping de la red\n");
	printf("2) Mostrar la configuracion de red de la maquina local \n");
	printf("3) Lanzar pings a dos DNS y mostrar cual de ellos responde antes\n");
	scanf("%i", &menu);

	switch (menu) { //Menú principal para llamar a las diferentes opciones del programa
	case 1: Funcion1();
		break;
	case 2:Funcion2();
		break;
	case 3:Funcion3();
		break;
	}

	if (menu<0 || menu>3) {
		printf("Opcion incorrecta");
		exit;  //En el caso de que el usuario introduzca un número inferor a 1 o superior a 3, se termina la ejecucción del programa
	}else if(menu==0) {
		exit; //En el caso de que el usuario introduzca el número 0, se termina la ejecución del programa
	}
	return 0;
} 
	
