#include "Cellule.h"
#include "../Etats/EtatVivant.h"
#include "../Etats/EtatMort.h"
#include "../Regles/RegleCelluleStandard.h"

namespace Principale {

// ============================================== 
//Constructeur 
// ==============================================

    Cellule::Cellule(PatternEtat::EtatCellule* etatInitial)
    : etatActuel(etatInitial), //initialise l'état de la cellule avec l'éatat donnée
      etatSuivant(nullptr), //pour l'instant on n'a pas calculer l'état suivant donc on met rien
      regle(new PatternRegles::RegleCelluleStandard()) {} //on associe les reglès qui vont avec la cellule en question (ici toutes nos cellules sont en mode standard)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ============================================== 
// Destructeur 
// ==============================================

    Cellule::~Cellule() {
        delete etatActuel;
        delete etatSuivant;
        delete regle;
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ============================================== 
// Méthodes : setEtatActuel() 
// ==============================================

    void Cellule::setEtatActuel(PatternEtat::EtatCellule* nouvelEtat) {
        if (etatActuel != nouvelEtat) { //si le nouvel état est différent de l'actuel
            delete etatActuel; //Alors on supprime l'état pour libérer le mémoire
            etatActuel = nouvelEtat; //et on donne à l'état actuel le nouvel état
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : getEtatActuel() 
// ==============================================

    bool Cellule::getEtatActuel() const {
        return etatActuel && etatActuel->estVivant(); //retroune l'état selon une vérificaction pour savoir si la cellule est vivante
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : calculerEtatSuivant() 
// ==============================================

    void Cellule::calculerEtatSuivant(int nbVoisins) {
        bool vivantActuel=getEtatActuel(); //booléen pour savoir si la cellule est vivante
        bool vivantSuivant = regle->calculerEtatSuivant(vivantActuel, nbVoisins); //ensuite on regarde si elle sera encore vivante à l'état suivant

        if (etatSuivant) delete etatSuivant; //si un état suivant existe, on le supprime
        if (vivantSuivant) { //si la cellule va rester vivante
            etatSuivant = new PatternEtat::EtatVivant(); //alors on va lui donnée l'état Vivant comme etat suivant
        } else {
            etatSuivant = new PatternEtat::EtatMort(); //sinon la cellule aura comme état morte à l'état suivant
        }
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : changerEtat() 
// ==============================================

    bool Cellule::changerEtat() {
        bool aChange=false; //booléen pour savoir si l'état doit être changer
        if (etatSuivant!=nullptr) { //si l'état suivant est non vide
            if (etatActuel->estVivant() != etatSuivant->estVivant()) { //et que l'état suivant est différent de l'état actuel
                aChange=true; //on passe la variable a true, qui nous permettra de savoir qu'il y a eu un changement dans la grille et qu'elle n'est pas stable
            }
            delete etatActuel; //on supprime l'état actuel
            etatActuel=etatSuivant; //et puis on lui associé l'état suivant à notre état acutel
            etatSuivant=nullptr; //et pour finir on supprime l'état suivant
        }
        return aChange; //on retourne notre booléen pour dire si la grille est stable ou non
    }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ==============================================
// Méthodes : recupererAffichage() 
// ==============================================

    int Cellule::recupererAffichage() const {
        return etatActuel ? etatActuel->affichageCellule() : 0; //demande le symbole pour récupere le symbole selon l'état de la cellule
    }
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}
