<img src="https://alexis-sgl.fr/wp-content/uploads/2026/01/logo_CESI_projet_etudiant_NB.png" alt="Logo 3W" width="100" align="right" />
<br><br>


# 🦠 Projet POO : Le Jeu de la Vie (Game of Life)

![C++](https://img.shields.io/badge/C++-17-blue.svg) ![SFML](https://img.shields.io/badge/SFML-2.5-green.svg)

## 📌 Contexte

Ce projet s’inscrit dans le cadre du module de Programmation Orientée Objet (POO) de l’école d’ingénieurs CESI. Il consiste en la conception et le développement d’une simulation de l’automate cellulaire "Jeu de la Vie" de John Conway. L’application repose sur une architecture logicielle modulaire, intégrant la bibliothèque SFML pour l’affichage et respectant les principes SOLID ainsi que les Design Patterns.

---

## 🧬 Le Principe du Jeu

Le Jeu de la Vie se déroule sur une grille où chaque case est une **cellule** pouvant être **vivante** ou **morte**. L'évolution du monde est autonome et dépend de règles simples appliquées à chaque tour :

1.  **Une cellule survit** si elle a **2 ou 3** voisins vivants.
2.  **Une cellule naît** si elle a exactement **3** voisins vivants.
3.  **Sinon, elle meurt** (isolement ou surpopulation).

---

## 🚀 Architecture et Fonctionnalités

Ce projet se distingue par une **conception logicielle modulaire** respectant les principes SOLID :

* **Architecture en Couches :** Séparation stricte entre le **Moteur** (namespace `Principale`), la **Logique** (namespaces `Pattern...`) et la **Vue** (namespace `AffichageInterface`).
* **Application des Design Patterns :**
    * **Pattern État :** Gestion polymorphique des cellules (`EtatVivant` / `EtatMort`) pour éviter les structures conditionnelles complexes.
    * **Pattern Reglès :** Encapsulation de l'algorithme d'évolution (`RegleCelluleStandard`), permettant une extensibilité future des règles.
* **Double Interface Utilisateur :**
    * 🖥️ **Mode Console :** Exécution rapide avec génération de logs et sauvegarde automatique de chaque itération.
    * 🎨 **Mode Graphique :** Rendu visuel temps réel et gestion événementielle via la bibliothèque **SFML**.
* **Fonctionnalités Avancées :**
    * **Topologie Torique :** Gestion d'un univers "infini" (connexion des bords opposés) via arithmétique modulaire.
    * **Persistance des Données :** Parsing de fichiers d'entrée et sérialisation des états de sortie.
    * **Algorithme de Stabilité :** Détection automatique de l'arrêt du jeu si la grille se fige (état stable).

---

## 🌍 Extension : Gestion d'une Grille Torique

Dans le cadre des fonctionnalités bonus, nous avons implémenté la **topologie torique**.

### Principe
Cette extension permet de connecter les extrémités de la grille entre elles, supprimant ainsi les effets de bord. L'univers de simulation devient théoriquement **infini et continu** :
* Les cellules de la **colonne 0** sont voisines de celles de la **dernière colonne** ($N-1$).
* Les cellules de la **ligne 0** sont voisines de celles de la **dernière ligne**.

Cela crée une géométrie similaire à celle d'un **Donut** (Tore) ou à l'effet "Pac-Man" : un objet sortant par la droite réapparaît instantanément à gauche.

### Implémentation Technique
Pour réaliser cela sans alourdir le code avec de multiples conditions (`if`), nous avons utilisé l'**arithmétique modulaire** dans la classe `Grille`.

La formule de calcul des voisins utilise l'opérateur modulo (`%`) :
> `coordonnée_réelle = (coordonnée_calculée + taille_max) % taille_max`

Cette approche mathématique garantit que toute coordonnée hors limites est automatiquement ramenée à une position valide dans la grille opposée.

---

## 🛠️ Prérequis

* **Compilateur C++** (ex: `g++`)
* **Make**
* **SFML 2.5**


### Installation SFML

#### Linux (Debian/Ubuntu)

```bash
sudo apt-get update
sudo apt-get install libsfml-dev
```

---

## 📦 Installation et Compilation

### 1. Cloner le dépôt

```bash
git clone https://github.com/VOTRE-NOM/Projet-POO-JeuDeLaVie.git
cd Projet-POO-JeuDeLaVie
```

### 2. Compiler

```bash
make
```

### 3. Lancer les tests (optionnel)

```bash
make clean
```

### 4. Nettoyer (optionnel)

```bash
make clean
```

---

## 🎮 Utilisation

### 1. Préparer un fichier d'entrée

Dans le dossier `Data/`, créer un fichier comme `input.txt`.

#### Format :

```
HAUTEUR LARGEUR
matrice de 0 et 1...
```

#### Exemple :

```
10 10
0 0 0 0 0 0 0 0 0 0
0 0 1 0 0 0 0 0 1 0
0 0 0 1 0 0 0 0 1 0
0 1 1 1 0 0 0 0 1 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 1 1 0 0 0
0 0 0 0 0 1 1 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
```

### 2. Lancer le programme

```bash
./main Data/input.txt
```

### 3. Répondre aux questions

- Nombre d'itérations
- Mode torique (o/n)
- Mode d'affichage :
  - 1 : Console
  - 2 : Graphique (SFML)

---

## 📂 Structure du Projet

```
Projet-POO/
├── main.cpp                     # Point d'entrée
├── Makefile
├── Data/                        # Fichiers d'entrée et sortie
│
├── Principale/                  # Principale
│   ├── JeuDeLaVie.cpp/.h
│   ├── Grille.cpp/.h
│   ├── Cellule.cpp/.h
│   └── Fichier.cpp/.h
│
├── Etats/                       # PatternEtat
│   ├── EtatCellule.h
│   ├── EtatVivant.cpp/.h
│   └── EtatMort.cpp/.h
│
├── Regles/                      # PatternRegles
│   ├── RegleCellule.h
│   └── RegleCelluleStandard.cpp/.h
│
└── Affichage/                   # AffichageInterface
    ├── Interface.h
    ├── Console.cpp/.h
    └── FenetreGraphique.cpp/.h
```

---

## 👥 Auteurs

- SIEGEL Alexis
- CESAR Jonathan

---

Projet réalisé dans le cadre du module Programmation Orientée Objet (POO) de l'école d'ingénieurs CESI.
