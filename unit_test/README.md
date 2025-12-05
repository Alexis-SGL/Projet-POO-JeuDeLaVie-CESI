# Tests unitaires – Jeu de la vie (Catch2)

Ce projet utilise **Catch2** pour tester la logique du Jeu de la vie (partie métier, sans SFML).

Les tests sont définis dans `unit_test/test_sanity.cpp`.

---

## 1. Comment lancer les tests

Depuis la racine du projet :

```bash
make test
```

Cette commande :

- compile les fichiers de test dans `unit_test/`,
- génère l’exécutable `unit_test/tests`,
- exécute tous les tests Catch2.

On peut aussi lancer manuellement :

```bash
./unit_test/tests
```


Catch2 affiche alors le nombre de tests, d’assertions, et lesquels passent/échouent.

---

## 2. Ce qui est testé

Les tests utilisent deux fonctions utilitaires :

- `remplirGrilleAvecPattern(Grille&, const std::vector<std::pair<int,int>>& vivantes)`  
  Initialise une grille en mettant **toutes les cellules à mort**, puis en activant uniquement les cellules aux coordonnées données (pratique pour construire des motifs comme le blinker, le bloc, etc.).

- `cellulesVivantes(const Grille&)`  
  Parcourt la grille et renvoie un `std::vector<std::pair<int,int>>` contenant les coordonnées de toutes les cellules vivantes (pratique pour vérifier l’état après une ou plusieurs itérations).

Ensuite, plusieurs `TEST_CASE` vérifient des comportements précis :

### 2.1. Tests sur `Cellule`

- `Cellule - transitions de base`  
  Vérifie les règles locales :
  - cellule vivante + 0 voisins → meurt (sous-population),
  - cellule morte + 3 voisins → devient vivante (naissance),
  - cellule vivante + 2 voisins → reste vivante (survie).

### 2.2. Tests sur `Grille` (mode non torique)

- `Grille - blinker non torique`  
  Initialise un **blinker** (oscillateur de 3 cellules) au centre d’une grille 5×5 et vérifie que :
  - après 1 itération, le motif passe de vertical à horizontal,
  - après 2 itérations, il revient à son état initial (période 2).

- `Grille - voisins aux bords non toriques`  
  Place des cellules sur le bord d’une grille 3×3 non torique et vérifie que les voisins sont correctement pris en compte (dans ce cas, les cellules meurent faute de voisins suffisants).

- `Grille - bloc stable`  
  Place un **bloc 2×2** de cellules vivantes (motif stable) et vérifie que :
  - après plusieurs itérations, la configuration ne change pas,
  - la méthode `Grille::estStable()` devient `true`.

- `Grille - blinker apres N iterations`  
  Vérifie qu’un blinker revient à son état initial après un nombre d’itérations **arbitraire** `N` (ici `N = 4`).  
  Cela illustre la vérification de l’état de la grille après un nombre donné d’itérations, comme demandé dans le sujet.

- `Grille - extinction complete`  
  Place une seule cellule vivante isolée au centre d’une grille 3×3 et vérifie qu’après une itération, toutes les cellules sont mortes (extinction complète).

### 2.3. Test sur la grille torique (extension)

- `Grille - voisins toriques basique`  
  Utilise une grille 3×3 en mode **torique** (les bords “bouclent”) et vérifie que :
  - la mise à jour `updateGrille()` s’exécute sans erreur,
  - le nombre de cellules vivantes reste dans des bornes logiques.  
  Ce test sert surtout à s’assurer que l’option torique ne casse pas la logique de mise à jour.

---

## 3. Objectif pédagogique

Ces tests :

- valident l’implémentation des **règles du Jeu de la vie** au niveau d’une cellule,
- vérifient la **mise à jour globale de la grille** sur plusieurs itérations,
- couvrent plusieurs motifs classiques : oscillateur (*blinker*), motif stable (*bloc*), extinction,
- testent la gestion des **bords** (non torique et torique),
- montrent comment vérifier l’**état de la grille après N itérations**, comme demandé dans le sujet.

Ils servent également de base pour ajouter d’autres tests si la logique du jeu évolue (nouvelles règles, nouveaux types de cellules, etc.).
