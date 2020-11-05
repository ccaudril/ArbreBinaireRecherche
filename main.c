#include "TP4.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int fin = 0;
    int choix,check;
    int id_entreprise,borne_inf,borne_sup,nouvelle_borne_inf,nouvelle_borne_sup;
    T_arbre *mon_arbre;
    mon_arbre=NULL;
    T_noeud *noeud;

    while (fin == 0){

        // Affichage du menu
        printf("        _________________________________________________________________\n");
        printf("       |                             MENU                                |\n");
        printf("       |  1. Creer un ABR                                                |\n");
        printf("       |  2. Afficher toutes les reservations                            |\n");
        printf("       |  3. Ajouter une reservation                                     |\n");
        printf("       |  4. Modifier une reservation                                    |\n");
        printf("       |  5. Supprimer une reservation                                   |\n");
        printf("       |  6. Afficher les reservation d'une entreprise                   |\n");
        printf("       |  7. Supprimer l'arbre                                           |\n");
        printf("       |  8. Quitter                                                     |\n");
        printf("       |_________________________________________________________________|\n");

        scanf("%d", &choix);

        switch(choix){

            case 1 : // Creer un ABR
                mon_arbre=creer_arbre();
                printf("Nouvel arbre cree ! \n");
                break ;

            case 2 : // Afficher toutes les reservations
                if(mon_arbre!=NULL){
                    if(*mon_arbre!=NULL){
                        affiche_abr(*mon_arbre);
                    }
                    else{
                        printf("Arbre vide. \n");
                    }
                }
                else{
                    printf("Merci de commencer par creer un arbre. \n");
                }
                break ;

            case 3 : // Ajouter une reservation
                if(mon_arbre!=NULL){
                    printf("Quel est l'identifiant de l'entreprise ? \n");
                    scanf("%d", &id_entreprise);
                    printf("Quelle est la date de debut de reservation ? (format MMJJ) \n");
                    scanf("%d", &borne_inf);
                    printf("Quelle est la date de fin de reservation ? (format MMJJ) \n");
                    scanf("%d", &borne_sup);
                    check=verifier_id_et_inter(borne_inf,borne_sup,id_entreprise);
                    if(check==1){
                        noeud = creer_noeud(id_entreprise, creer_intervalle(borne_inf, borne_sup));
                        ajouter_noeud(mon_arbre,noeud);
                    }
                }
                else{
                    printf("Merci de commencer par creer un arbre. \n");
                }
                break ;

            case 4 : // Modifier une reservation
                if(mon_arbre!=NULL){
                    printf("Quel est l'identifiant de l'entreprise ? \n");
                    scanf("%d", &id_entreprise);
                    printf("Quelle est la date de debut de reservation ? (format MMJJ) \n");
                    scanf("%d", &borne_inf);
                    printf("Quelle est la date de fin de reservation ? (format MMJJ) \n");
                    check=verifier_id_et_inter(borne_inf,borne_sup,id_entreprise);

                    if(check==1){
                        scanf("%d", &borne_sup);
                        printf("Quelle est la nouvelle date de debut de reservation ? (format MMJJ) \n");
                        scanf("%d", &nouvelle_borne_inf);
                        printf("Quelle est la nouvelle date de fin de reservation ? (format MMJJ) \n");
                        scanf("%d", &nouvelle_borne_sup);
                        check=verifier_id_et_inter(nouvelle_borne_inf,nouvelle_borne_sup,id_entreprise);

                        if(check==1){
                            modif_noeud(*mon_arbre,creer_intervalle(borne_inf, borne_sup),
                                id_entreprise,creer_intervalle(nouvelle_borne_inf,nouvelle_borne_sup));
                        }
                    }
                }
                else{
                    printf("Merci de commencer par creer un arbre. \n");
                }
                break ;

            case 5 : // Supprimer une reservation
                if(mon_arbre!=NULL){
                    printf("Quel est l'identifiant de l'entreprise ? \n");
                    scanf("%d", &id_entreprise);
                    printf("Quelle est la date de debut de reservation ? (format MMJJ) \n");
                    scanf("%d", &borne_inf);
                    printf("Quelle est la date de fin de reservation ? (format MMJJ) \n");
                    scanf("%d", &borne_sup);

                    check=verifier_id_et_inter(borne_inf,borne_sup,id_entreprise);
                    if(check==1){
                        supp_noeud(mon_arbre,creer_intervalle(borne_inf, borne_sup),id_entreprise);
                    }
                }
                else{
                    printf("Merci de commencer par creer un arbre. \n");
                }
                break ;

            case 6 : // Afficher les reservations d'une entreprise

                if(mon_arbre!=NULL){
                    printf("Quel est l'identifiant de l'entreprise ? \n");
                    scanf("%d", &id_entreprise);
                    affiche_entr(*mon_arbre,id_entreprise);
                }
                else{
                    printf("Merci de commencer par creer un arbre. \n");
                }
                break ;

            case 7 : // Supprimer l'arbre
                if(mon_arbre!=NULL){
                    detruire_arbre(mon_arbre);
                    printf("Arbre detruit ! \n");
                }
                else{
                    printf("Merci de commencer par creer un arbre. \n");
                }
                break ;

            case 8: // Quitter
                printf("Fin du programme ! \n");
                fin = 1;
                break ;

            default : printf ("Merci de saisir un chiffre entre 1 et 8.");
                break;
        }
    }
    return 0;
}

