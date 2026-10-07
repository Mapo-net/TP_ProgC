/*
 * SPDX-FileCopyrightText: 2021 John Samuel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client.h"

int envoie_operateur_numeros(int socketfd, char operateur, double nombre1,
                             double nombre2, int nombre_operandes)
{
  char data[1024];
  int longueur;

  if (nombre_operandes == 1)
  {
    longueur = snprintf(data, sizeof(data), "calcule : %c %.10g\n", operateur, nombre1);
  }
  else
  {
    longueur = snprintf(data, sizeof(data), "calcule : %c %.10g %.10g\n",
                        operateur, nombre1, nombre2);
  }

  if (longueur < 0 || (size_t)longueur >= sizeof(data))
  {
    fprintf(stderr, "Opération trop longue.\n");
    return -1;
  }

  if (write(socketfd, data, (size_t)longueur) < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  memset(data, 0, sizeof(data));
  int read_status = read(socketfd, data, sizeof(data) - 1);
  if (read_status <= 0)
  {
    if (read_status < 0)
    {
      perror("Erreur de lecture");
    }
    return -1;
  }

  data[read_status] = '\0';
  printf("Réponse du serveur: %s", data);
  return 0;
}

/**
 * Fonction pour envoyer et recevoir un message depuis un client connecté à la socket.
 *
 * @param socketfd Le descripteur de la socket utilisée pour la communication.
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int envoie_recois_message(int socketfd)
{
  char data[1024];
  char message[1024];
  char operateur;
  double nombre1;
  double nombre2;

  printf("Votre message (max 1000 caractères): ");
  if (fgets(message, sizeof(message), stdin) == NULL)
  {
    return -1;
  }

  if (strncmp(message, "calcule :", 9) == 0)
  {
    int nombre_valeurs = sscanf(message, "calcule : %c %lf %lf",
                                 &operateur, &nombre1, &nombre2);
    if (nombre_valeurs != 2 && nombre_valeurs != 3)
    {
      fprintf(stderr, "Format attendu : calcule : opérateur nombre [nombre]\n");
      return 0;
    }

    return envoie_operateur_numeros(socketfd, operateur, nombre1, nombre2,
                                    nombre_valeurs - 1);
  }

  int longueur = snprintf(data, sizeof(data), "message: %s", message);
  if (longueur < 0 || (size_t)longueur >= sizeof(data))
  {
    fprintf(stderr, "Message trop long.\n");
    return 0;
  }

  if (write(socketfd, data, (size_t)longueur) < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  memset(data, 0, sizeof(data));
  int read_status = read(socketfd, data, sizeof(data) - 1);
  if (read_status <= 0)
  {
    if (read_status < 0)
    {
      perror("Erreur de lecture");
    }
    return -1;
  }
  data[read_status] = '\0';

  printf("Message reçu: %s\n", data);
  return 0;
}

int main()
{
  int socketfd;

  struct sockaddr_in server_addr;

  /*
   * Creation d'une socket
   */
  socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd < 0)
  {
    perror("socket");
    exit(EXIT_FAILURE);
  }

  // détails du serveur (adresse et port)
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  // demande de connection au serveur
  int connect_status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (connect_status < 0)
  {
    perror("connection serveur");
    exit(EXIT_FAILURE);
  }

  while (envoie_recois_message(socketfd) == 0)
  {
  }

  close(socketfd);
}
