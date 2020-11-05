#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

// Structures et types

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


// Fonctions

T_arbre *creer_arbre();
T_inter creer_intervalle(int borne_inf, int borne_sup);
T_noeud *creer_noeud(int ID_entreprise,T_inter intervalle);

int verifier_id_et_inter(int borne_inf, int borne_sup, int id_entreprise);

void ajouter_noeud (T_arbre* abr, T_noeud* noeud);

T_noeud *recherche(T_arbre abr, T_inter intervalle,int ID_entreprise);
T_noeud* recherche_pere(T_arbre abr, T_noeud *noeud);

void supp_noeud(T_arbre *abr, T_inter intervalle, int ID_entreprise);
void modif_noeud(T_arbre abr,T_inter intervalle, int ID_entreprise, T_inter Nouvelintervalle);

void afficher_resa(T_noeud *noeud);
void affiche_abr(T_arbre abr);
void affiche_entr(T_arbre abr,int ID_entreprise);

void detruire_arbre(T_arbre *abr);


#endif // TP4_H_INCLUDED
