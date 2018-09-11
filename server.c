/*
 * server.c
 * 
 * Copyright 2018 Alvarito050506 <donfrutosgomez@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	int stsocket, new_stsocket, stport, n;
	socklen_t clilen;
	char buffer[2048];
	struct sockaddr_in address, cli_addr;
	if (argc == 2 && strcmp(argv[1], "-h") == 0 || argc == 2 && strcmp(argv[1], "--help") == 0)
	{
		printf("Uso: %s [opciones]\nOpciones:\n\t-h, --help\tMuestra esta ayuda.\n\nEstado de salida:\n\t0 si todo fue bien.\n\t1 si el puerto necesario no está disponible.\n\t2 si no se pudo escribir o leer el socket.\n", argv[0]);
		return 0;
	}
	stsocket = socket(AF_INET, SOCK_STREAM, 0);
	bzero((char *) &address, sizeof(address));
	stport = 3890;
	addres.sin_family = AF_INET;
	addres.sin_addr.s_addr = htonl(INADDR_ANY);
	addres.sin_port = htons(stport);
	n = bind(stsocket, (struct sockaddr *) &address, sizeof(address)); 
	if (n < 0)
	{
		write(new_stsocket, "202 - El puerto necesario no está disponible.\n", 56);
		printf("202 - El puerto necesario no está disponible.\n");
		return 1;
	}
	while (1 != 0)
	{
		listen(stsocket, 5);
		clilen = sizeof(cli_addr);
		new_stsocket = accept(stsocket, (struct sockaddr *) &cli_addr, &clilen);
		printf("101 - Conectado %s:3890. (STTP/1.0)\n", inet_ntoa(cli_addr.sin_addr));
		bzero(buffer, 2048);
		n = read(new_stsocket, buffer, 2047);
		printf("Mensaje del cliente: %s", buffer);
		n = write(new_stsocket, "100 - Mensaje recibido.", 29);
		if (n < 0)
		{
			write(new_stsocket, "200 - No se pudo escribir o leer el socket.\n", 55);
			printf("200 - No se pudo escribir o leer el socket.\n");
			return 2;
		}
		printf("100 - Mensaje recibido.\n");
	}
	close(new_stsocket);
	close(stsocket);
	return 0; 
}
