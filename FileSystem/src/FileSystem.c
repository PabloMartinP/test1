#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <commons/config.h>
#include <commons/log.h>
#include <commons/string.h>
#include <socket.h>

#define CONFIG_PUERTO_LISTEN "PUERTO_LISTEN"
#define CONFIG_LISTA_NODOS "LISTA_NODOS"

#define FILE_CONFIG "/home/utnso/workspace/FileSystem/config.txt"
#define FILE_LOG "/home/utnso/workspace/FileSystem/log.txt"

#define COMAND_MAX_SIZE 256

t_log* log = NULL;
t_config* config = NULL;

typedef enum {
	NODO_AGREGAR, NODO_ELIMINAR, NADA
} e_comando;

void atender_nodo(int socket) {
	printf("nodo conectado!\n");
}

e_comando getComando(char* input_user) {

	char* comando;

	comando = string_split(input_user, " ")[0];

	if (string_equals_ignore_case(comando, "agregarnodo\n"))
		return NODO_AGREGAR;

	return NADA;
}

void consola() {
	char comando[COMAND_MAX_SIZE]; //max chars de comando
	printf("inicio consola\nEsperando comandos ...\n");
	while (true) {
		//scanf("%s", comando );
		fgets(comando, COMAND_MAX_SIZE, stdin);

		switch (getComando(comando)) {
		case NODO_AGREGAR:
			printf("agregar nodo\n");

			break;
		case NODO_ELIMINAR:
			printf("eliminar nodo\n");
			break;
		default:
			printf("error comando\n");
			break;
		}

	}

	//agrega nodo nuevo
	int socketEscucha, socketNuevaConexion;
	int p;
	p = config_get_int_value(config, CONFIG_PUERTO_LISTEN);
	socketEscucha = socket_get_escucha(p);

	if (listen(socketEscucha, 10) != 0) {
		perror("Error al poner a escuchar socket");
		//return EXIT_FAILURE;
	}
/*
	//Este ciclo while sirve para que el servidor pueda volver a aceptar conexiones entrantes cuando se termine la conexión
	//con el cliente que está atendiendo.
	while (1) {

		printf("Escuchando conexiones entrantes.\n");

		// Aceptar una nueva conexion entrante. Se genera un nuevo socket con la nueva conexion.
		// La función accept es bloqueante, no sigue la ejecución hasta que se reciba algo
		if ((socketNuevaConexion = accept(socketEscucha, NULL, 0)) < 0) {

			perror("Error al aceptar conexion entrante");
			//return EXIT_FAILURE;

		}

		//Creación del thread que atiende al cliente. Se crean tantos threads como nuevas conexiones haya
		pthread_t thr1;

		//Se crea el thread y le indicamos que use la función antederCliente con el socket de la nueva conexión
		//como parámetro
		pthread_create(&thr1, NULL, atender_nodo, socketNuevaConexion);

		//Si sólo se quiere que el servidor atienda una sóla conexión, descomentar
		//lo que viene a continuación:
		pthread_join(thr1, NULL);
		pthread_detach(thr1);
	}
	close(socketEscucha);
*/
	printf("fin consola");
}

int main(void) {

	log = log_create(FILE_LOG, "FileSystem", false, LOG_LEVEL_INFO);
	config = config_create(FILE_CONFIG);

	//agrego un nuevo nodo
	pthread_t th_consola;
	if (pthread_create(&th_consola, NULL, (void*) consola, NULL) != 0) {
		perror("pthread_create");
		exit(1);
	}

	while (true)
		;

	config_destroy(config);
	log_destroy(log);
	return 0;
}
