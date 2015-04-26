/*
 * socket.h
 *
 *  Created on: 24/4/2015
 *      Author: utnso
 */

#ifndef SOCKET_H_
#define SOCKET_H_

//Estructura del paquete como t_paquete y se instancia una llamada Paquete
		//Type - Tamanio del Payload
		//Generico
typedef struct t_paquete {
			int8_t type;
			int16_t payloadlength;
		} Header;

		typedef struct{
			char* ip;
			int puerto;
		} t_equipo;


		//envia un mensaje se envia el puntero al string o char, o struct ej:
		//char recActual;
		//buffer= &recActual;
		//if (mandarMensaje(unSocket,1 , sizeof(recActual),buffer))
		//o char* caracter; mandarMensaje(unSocket,1 , sizeof(recActual),caracter)
		//Enviar String (mandar tamaño del string +1 para incluir el \0)
		//mandarMensaje(unSocketOrq,1,strlen(nivelActual)+1,nivelActual);
		int mandarMensaje(int unSocket, int8_t tipo, int tamanio, void *buffer);
		//Recibe un mensaje el cual ya sabes lo que te va a llegar, recomiendo usar las otras funciones en 2 partes
		//ej (Recomendable al recibir char o un string)
		//char* nivelDelPersonaje;
		//if(recibirMensaje(socketNuevaConexion, (void**) &nivelDelPersonaje)>=0) {
		int recibirMensaje(int unSocket, void** buffer) ;
		//recibe un header
		//ej
		//Header unHeader;
		//recibirHeader(unSocket,&unHeader)
		int recibirHeader(int unSocket, Header* header);
//		recibe Data enviado el header anteriormente recibido, esta y la funcion anterior son complementarias
		//ej
		//Recibir un string o char
		//char * rec;
		//rec=malloc(sizeof(char));
		//recibirData(socketNuevaConexion, headMen, (void**)rec);
//
		//recibir un in
		//int * aux;
		//aux=malloc(sizeof(int));
		//recibirData(socketNuevaConexion, headMen, (void**)aux);
		//Recibir un struct
		//Posicion lifeSucks;
		//recibirData(unSocket,unHeader,(void**)&lifeSucks);
		int recibirData(int unSocket, Header header, void** buffer);


		int sendAll(int s, char *buf, int *len) ;
int socket_get_conectado(t_equipo equipo);
int solicitarSocketAlSO();
struct sockaddr_in especificarSocketInfo(char* direccion, int puerto);
int socket_get_escucha(int puerto);

#endif /* SOCKET_H_ */
