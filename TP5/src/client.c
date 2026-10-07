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
                             double nombre2, int nombre_operandes,
                             double *resultat)
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
  if (resultat != NULL && sscanf(data, "calcule : %lf", resultat) != 1)
  {
    fprintf(stderr, "Réponse de calcul invalide : %s", data);
    return -1;
  }
  if (resultat == NULL)
  {
    printf("Réponse du serveur: %s", data);
  }
  return 0;
}

static int envoyer_requete(int socketfd, const char *requete)
{
  char reponse[1024];
  size_t longueur = strlen(requete);
  int recevoir_repertoire = strncmp(requete, "repertoire :", 12) == 0;

  if (write(socketfd, requete, longueur) < 0)
  {
    perror("Erreur d'écriture");
    return -1;
  }

  while (1)
  {
    int taille_reponse = read(socketfd, reponse, sizeof(reponse));
    if (taille_reponse <= 0)
    {
      if (taille_reponse < 0)
      {
        perror("Erreur de lecture");
      }
      return -1;
    }

    if (recevoir_repertoire)
    {
      char *fin = memchr(reponse, '\0', (size_t)taille_reponse);
      size_t longueur_affichee = fin == NULL ? (size_t)taille_reponse :
                                 (size_t)(fin - reponse);
      fwrite(reponse, 1, longueur_affichee, stdout);
      fflush(stdout);
      if (fin != NULL)
      {
        return 0;
      }
    }
    else
    {
      fwrite(reponse, 1, (size_t)taille_reponse, stdout);
      return 0;
    }
  }
}

static int lire_note(const char *dossier, int numero_etudiant,
                     int numero_note, double *note)
{
  char chemin[1024];
  FILE *fichier;
  int longueur = snprintf(chemin, sizeof(chemin), "%s/%d/note%d.txt",
                          dossier, numero_etudiant, numero_note);

  if (longueur < 0 || (size_t)longueur >= sizeof(chemin))
  {
    fprintf(stderr, "Chemin de fichier trop long.\n");
    return -1;
  }

  fichier = fopen(chemin, "r");
  if (fichier == NULL)
  {
    perror(chemin);
    return -1;
  }

  if (fscanf(fichier, "%lf", note) != 1)
  {
    fprintf(stderr, "La note dans %s n'est pas un nombre valide.\n", chemin);
    fclose(fichier);
    return -1;
  }

  fclose(fichier);
  return 0;
}

static int demander_calcul(int socketfd, char operateur, double nombre1,
                           double nombre2, double *resultat)
{
  return envoie_operateur_numeros(socketfd, operateur, nombre1, nombre2,
                                  2, resultat);
}

static int extraire_numero_note(const char *texte, int *numero_note)
{
  char reste;

  return sscanf(texte, "note%d%c", numero_note, &reste) == 1 &&
         *numero_note >= 1 && *numero_note <= 5;
}

static int ajouter(double *somme, int *initialisee, double valeur, int socketfd)
{
  double resultat;

  if (!*initialisee)
  {
    *somme = valeur;
    *initialisee = 1;
    return 0;
  }

  if (demander_calcul(socketfd, '+', *somme, valeur, &resultat) != 0)
  {
    return -1;
  }
  *somme = resultat;
  return 0;
}

static int traiter_commande_note(int socketfd, const char *commande)
{
  char premier[32];
  char deuxieme[32];
  char troisieme[32];
  char surplus[2];
  int nombre_mots = sscanf(commande, "note : %31s %31s %31s %1s",
                           premier, deuxieme, troisieme, surplus);

  if (nombre_mots == 1)
  {
    int numero_note;
    if (!extraire_numero_note(premier, &numero_note))
    {
      fprintf(stderr, "Commande attendue : note : note1 (note1 à note5).\n");
      return 0;
    }

    for (int etudiant = 1; etudiant <= 5; etudiant++)
    {
      double note;
      if (lire_note("../etudiant", etudiant, numero_note, &note) != 0)
      {
        return 0;
      }
      printf("Étudiant %d, note%d : %.10g\n", etudiant, numero_note, note);
    }
    return 0;
  }

  if (nombre_mots != 3)
  {
    fprintf(stderr, "Commande note invalide.\n");
    return 0;
  }

  if (strcmp(premier, "+") == 0 && strcmp(deuxieme, "somme") == 0)
  {
    int numero_note;
    int somme_initialisee = 0;
    double somme = 0;

    if (!extraire_numero_note(troisieme, &numero_note))
    {
      fprintf(stderr, "Format attendu : note : + somme note1 (note1 à note5).\n");
      return 0;
    }

    for (int etudiant = 1; etudiant <= 5; etudiant++)
    {
      double note;
      if (lire_note("../etudiant", etudiant, numero_note, &note) != 0 ||
          ajouter(&somme, &somme_initialisee, note, socketfd) != 0)
      {
        return -1;
      }
    }
    printf("Somme de note%d pour les 5 étudiants : %.10g\n", numero_note, somme);
    return 0;
  }

  if (strcmp(premier, "+") == 0)
  {
    int numero_note1;
    int numero_note2;

    if (!extraire_numero_note(deuxieme, &numero_note1) ||
        !extraire_numero_note(troisieme, &numero_note2))
    {
      fprintf(stderr, "Format attendu : note : + note1 note2.\n");
      return 0;
    }

    for (int etudiant = 1; etudiant <= 5; etudiant++)
    {
      double note1;
      double note2;
      double somme;

      if (lire_note("../etudiant", etudiant, numero_note1, &note1) != 0 ||
          lire_note("../etudiant", etudiant, numero_note2, &note2) != 0 ||
          demander_calcul(socketfd, '+', note1, note2, &somme) != 0)
      {
        return -1;
      }
      printf("Étudiant %d : note%d + note%d = %.10g\n",
             etudiant, numero_note1, numero_note2, somme);
    }
    return 0;
  }

  if (strcmp(premier, "/") == 0 && strcmp(deuxieme, "somme") == 0 &&
      strcmp(troisieme, "5") == 0)
  {
    int total_initialise = 0;
    double total = 0;

    for (int etudiant = 1; etudiant <= 5; etudiant++)
    {
      int somme_etudiant_initialisee = 0;
      double somme_etudiant = 0;

      for (int numero_note = 1; numero_note <= 5; numero_note++)
      {
        double note;
        if (lire_note("../etudiant", etudiant, numero_note, &note) != 0 ||
            ajouter(&somme_etudiant, &somme_etudiant_initialisee, note, socketfd) != 0)
        {
          return -1;
        }
      }
      if (ajouter(&total, &total_initialise, somme_etudiant, socketfd) != 0)
      {
        return -1;
      }
    }

    double moyenne;
    if (demander_calcul(socketfd, '/', total, 5, &moyenne) != 0)
    {
      return -1;
    }
    printf("Moyenne des totaux des 5 étudiants : %.10g\n", moyenne);
    return 0;
  }

  fprintf(stderr, "Commande note non prise en charge.\n");
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
                                    nombre_valeurs - 1, NULL);
  }

  if (strncmp(message, "repertoire :", 12) == 0)
  {
    return envoyer_requete(socketfd, message);
  }

  if (strncmp(message, "note :", 6) == 0)
  {
    return traiter_commande_note(socketfd, message);
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
  return EXIT_SUCCESS;
}
