#include <stdio.h>
#include <stdlib.h>

// Strutures

struct intervalle{
	int borne_inf;
	int borne_sup;
};
typedef struct intervalle T_inter;

struct noeud{
    int ID_entreprise;
	T_inter intervalle;
    struct noeud *gauche;
    struct noeud *droite;
};
typedef struct noeud T_noeud ;

typedef T_noeud *T_arbre;

// Créer arbre (fonction supplémentaire)
T_arbre* creer_arbre(){
    T_arbre *res = malloc(sizeof(T_arbre));
    (*res)=NULL;
    return res;
}

// (1) Créer noeud
T_noeud *creer_noeud(int ID_entreprise, T_inter intervalle){
    T_noeud *elem = malloc(sizeof(T_noeud));
    elem->ID_entreprise = ID_entreprise;
	elem->intervalle.borne_inf = intervalle.borne_inf;
	elem->intervalle.borne_sup = intervalle.borne_sup;
    elem->gauche = NULL;
    elem->droite = NULL;
	return elem;
}

// Créer intervalle (fonction supplémentaire)
T_inter creer_intervalle(int borne_inf, int borne_sup){
    T_inter *res = malloc(sizeof(T_inter));
    res->borne_inf = borne_inf;
    res->borne_sup = borne_sup;
    return (*res);
}

// Vérifier la validité de l'id_entreprise et de l'intervalle (fonction supplémentaire)
int verifier_id_et_inter(int borne_inf, int borne_sup, int id_entreprise){

    // Affichage au format MMJJ
    int jour_min = borne_inf%100;
    int mois_min = ( borne_inf - jour_min )/100;
    int jour_max = borne_sup%100;
    int mois_max = ( borne_sup - jour_max )/100;

    // Vérifications
    if(borne_inf>borne_sup){
        printf("La date de debut doit etre inferieure a la date de fin. \n");
        return 0;
    }
    else if(borne_inf==borne_sup){
        printf("La date de debut ne peut etre egale a la date de fin. \n");
        return 0;
    }
    else if(borne_inf==231 || borne_inf==230 || borne_inf==431 ||
            borne_inf==631 || borne_inf==931 || borne_inf==1131){
        printf("Le mois ou debute la reservation n'a pas autant de jours ! \n");
        return 0;
    }
    else if(borne_sup==231 || borne_sup==230 || borne_sup==431 ||
            borne_sup==631 || borne_sup==931 || borne_sup==1131){
        printf("Le mois ou se termine la reservation n'a pas autant de jours ! \n");
        return 0;
    }
    else if(0<jour_min && jour_min<=31 && 0<mois_min && mois_min<=12 &&
            0<jour_max && jour_max<=31 && 0<mois_max && mois_max<=12 &&
            0<=id_entreprise){
        return 1;
    }
    else{
            printf("Erreur de saisie de la date ou de l'id de l'entreprise. \n");
        return 0;
    }
}

// (2) Ajouter un noeud
void ajouter_noeud(T_arbre* abr, T_noeud* noeud){

    // Arbre vide
    if(*abr==NULL){
        (*abr) = noeud;
        printf("Reservation [%d,%d] ajoutee pour l'entreprise %d. \n",
               noeud->intervalle.borne_inf,noeud->intervalle.borne_sup,noeud->ID_entreprise);
    }

    // Arbre non vide
    else{
        T_noeud *racine;
        racine = (*abr);
        if(racine->intervalle.borne_sup < noeud->intervalle.borne_inf){
            ajouter_noeud(&(racine->droite), noeud);
        }
        else if(racine->intervalle.borne_inf > noeud->intervalle.borne_sup){
            ajouter_noeud(&(racine->gauche), noeud);
        }
        else{
            printf("La salle est deja reservee sur cette periode. \n");
        }
    }
}

// (3) Rechercher un noeud (une réservation)
T_noeud* recherche(T_arbre abr, T_inter intervalle,int ID_entreprise){
        if(ID_entreprise==abr->ID_entreprise
           && intervalle.borne_inf==abr->intervalle.borne_inf
           && intervalle.borne_sup==abr->intervalle.borne_sup ){
            return abr;
        }
        else if(intervalle.borne_inf > abr->intervalle.borne_sup){
			return recherche(abr->droite,intervalle,ID_entreprise);
        }
        else if(intervalle.borne_sup < abr->intervalle.borne_inf){
			return recherche(abr->gauche,intervalle,ID_entreprise);
        }
        else{
            return NULL;
        }
}

// Rechercher le pere d'un noeud (fonction supplémentaire)
T_noeud* recherche_pere(T_arbre abr, T_noeud *noeud){
        if(abr==noeud){
            return NULL;
        }
        else if(abr->droite==noeud || abr->gauche==noeud){
            return abr;
        }
        else if(noeud->intervalle.borne_inf > abr->intervalle.borne_sup){
			recherche_pere(abr->droite,noeud);
        }
        else if(noeud->intervalle.borne_sup < abr->intervalle.borne_inf){
			recherche_pere(abr->gauche,noeud);
        }
}

// (4) Supprimer une reservation
void supp_noeud(T_arbre *abr, T_inter intervalle, int ID_entreprise){
    T_noeud *pnt = recherche(*abr, intervalle, ID_entreprise);
    if (pnt==NULL){
        printf("Cette reservation n'existe pas. \n");
    }
    else if(pnt==(*abr)){ // pnt est la racine
            if(pnt->droite==NULL && pnt->gauche==NULL){ // pnt n'a pas de fils
                (*abr)=NULL;
                free(pnt);
            }
            else if(pnt->gauche==NULL){ // pnt a seulement un fils droit
                (*abr)=pnt->droite;
                free(pnt);
            }
            else if(pnt->droite==NULL){ // pnt a seulement un fils gauche
                (*abr)=pnt->gauche;
                free(pnt);
            }
            else{ // pnt a deux fils
                // On cherche son successeur
                T_noeud *succ = pnt->droite;
                while(succ->gauche!=NULL){
                    succ=succ->gauche;
                }
                // On cherche l'ancien père du successeur afin de lui retirer son fils
                T_noeud *pere_succ = recherche_pere(*abr,succ);
                if(succ==pere_succ->droite)pere_succ->droite=NULL;
                if(succ==pere_succ->gauche)pere_succ->gauche=NULL;

                // Puis on le remplace par son successeur
                (*abr)=succ;
                succ->gauche=pnt->gauche;
                if(succ!=pnt->droite){succ->droite=pnt->droite;}
                free(pnt);
            }
    }
    else{
            // recherche du pere
            T_noeud *pere = recherche_pere(*abr,pnt);

            // pnt est le fils droit
            if(pnt==pere->droite){
                    if(pnt->droite==NULL && pnt->gauche==NULL){ // pnt n'a pas de fils
                        pere->droite=NULL;
                        free(pnt);
                    }
                    else if(pnt->gauche==NULL){ // pnt a seulement un fils droit
                        pere->droite=pnt->droite;
                        free(pnt);
                    }
                    else if(pnt->droite==NULL){ // pnt a seulement un fils gauche
                        pere->droite=pnt->gauche;
                        free(pnt);
                    }
                    else{ // pnt a deux fils
                        // On cherche son successeur
                        T_noeud *succ = pnt->droite;
                        while(succ->gauche!=NULL){
                            succ=succ->gauche;
                        }
                        // On cherche l'ancien père du successeur afin de lui retirer son fils
                        T_noeud *pere_succ = recherche_pere(*abr,succ);
                        if(succ==pere_succ->droite)pere_succ->droite=NULL;
                        if(succ==pere_succ->gauche)pere_succ->gauche=NULL;
                        // Puis on le remplace par son successeur
                        pere->droite=succ;
                        succ->gauche=pnt->gauche;
                        if(succ!=pnt->droite){succ->droite=pnt->droite;}
                        free(pnt);
                    }
            }

            // pnt est le fils gauche
            else{
                    if(pnt->droite==NULL && pnt->gauche==NULL){ // pnt n'a pas de fils
                        pere->gauche=NULL;
                        free(pnt);
                    }
                    else if(pnt->gauche==NULL){ // pnt a seulement un fils droit
                        pere->gauche=pnt->droite;
                        free(pnt);
                    }
                    else if(pnt->droite==NULL){ // pnt a seulement un fils gauche
                        pere->gauche=pnt->gauche;
                        free(pnt);
                    }
                    else{ // pnt a deux fils
                        // On cherche son successeur
                        T_noeud *succ = pnt->droite;
                        while(succ->gauche!=NULL){
                            succ=succ->gauche;
                        }
                        // On cherche l'ancien père du successeur afin de lui retirer son fils
                        T_noeud *pere_succ = recherche_pere(*abr,succ);
                        if(succ==pere_succ->droite)pere_succ->droite=NULL;
                        if(succ==pere_succ->gauche)pere_succ->gauche=NULL;
                        // Puis on le remplace par son successeur
                        pere->gauche=succ;
                        succ->gauche=pnt->gauche;
                        if(succ!=pnt->droite){succ->droite=pnt->droite;}
                        free(pnt);
                    }
            }
    }
    printf("Reservation supprimee avec succes. \n");
}

// (5) Modifier une réservation
void modif_noeud(T_arbre abr,T_inter intervalle, int ID_entreprise, T_inter Nouvelintervalle){
    T_noeud *pnt = recherche(abr, intervalle, ID_entreprise);
    if (pnt==NULL){
        printf("Cette reservation n'existe pas. \n");
    }
    else{
        T_noeud *nd;
        supp_noeud(&abr,intervalle,ID_entreprise);
        nd=creer_noeud(ID_entreprise,Nouvelintervalle);
        ajouter_noeud(&abr,nd);
    }
}

// Afficher une réservation (fonction supplémentaire)
void afficher_resa(T_noeud *noeud){
    if (noeud!=NULL){
        int jour_min = (noeud->intervalle.borne_inf)%100;
        int mois_min = ( noeud->intervalle.borne_inf - jour_min )/100;
        int jour_max = (noeud->intervalle.borne_sup)%100;
        int mois_max = ( noeud->intervalle.borne_sup - jour_max )/100;
        printf("_______________________________________________\n");
        printf("Entreprise : %d \n", noeud->ID_entreprise);
        printf("Reservation du %d/%d au %d/%d \n",jour_min, mois_min, jour_max, mois_max);
    }
}

// (6) Afficher toutes les réservations de l'arbre par ordre croissant (parcours infixe)
void affiche_abr(T_arbre abr){
    if(abr!=NULL){
        T_noeud *racine = abr;
        affiche_abr(racine->gauche);
        afficher_resa(racine);
        affiche_abr(racine->droite);
    }
}

// (7) Afficher les réservation d'une entreprise
void affiche_entr(T_arbre abr,int ID_entreprise){
        if(abr!=NULL && ID_entreprise==abr->ID_entreprise) afficher_resa(abr);
        if(abr->droite!=NULL)affiche_entr(abr->droite,ID_entreprise);
        if(abr->gauche!=NULL)affiche_entr(abr->gauche,ID_entreprise);
}

// (8) Détruire tous les noeuds d'un arbre binaire
void detruire_arbre(T_arbre *abr){
    if(abr!=NULL){
        if(&((*abr)->droite)!=NULL){
                detruire_arbre(&((*abr)->droite));
        }
        if(&((*abr)->gauche)!=NULL){
                detruire_arbre(&((*abr)->gauche));
        }
        free(abr);
    }
}
