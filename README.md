# Bézier Cubique – Analyse & Visualisation
 
> ⚠️ **Projet annexe / laboratoire de tests** — code expérimental, pas de prétention à la propreté.
 
Exploration mathématique d'une courbe de Bézier cubique en C++, avec export CSV et visualisation Python (matplotlib).
 
---
 
## Ce que fait le projet
 
- **Calcul de longueur d'arc** par la méthode de Simpson (comparaison sur plusieurs résolutions : 5, 10, 50, 200, 1000, 10 000 points)
- **Analyse de courbure** en chaque point via produit scalaire et produit vectoriel des vecteurs directeurs successifs
- **Recherche du point le plus proche** d'un point Q aléatoire sur la courbe (approche par force brute sur 1 000 échantillons)
- **Export CSV** (`bezier.csv`, `ctrl.csv`) pour visualisation externe
- **Visualisation matplotlib** via `visualise.py`
 
---
 
## Stack
 
- **C++17** — calcul et export des données
- **Python 3 / matplotlib** — visualisation (`visualise.py`)
 
---
 
## Structure
 
```
.
├── main.cpp              # Calculs C++ (Bézier, Simpson, dot/cross, closest point)
├── visualise.py          # Tracé matplotlib depuis bezier.csv et ctrl.csv
├── bezier.csv            # Données de la courbe (généré à l'exécution)
├── ctrl.csv              # Points de contrôle (généré à l'exécution)
├── bezier.png            # Aperçu de la courbe
└── bezier_analysis.png   # Aperçu de l'analyse de courbure
```
 
---
 
## Compilation & exécution
 
```bash
g++ -std=c++17 -o main main.cpp -lm
./main
```
 
Puis pour visualiser :
 
```bash
python visualise.py
```
 
---
 
## Paramètres de la courbe
 
Définis directement dans `main.cpp` :
 
```cpp
Vec2 p0 = {   0.0,   0.0 };  // Départ
Vec2 p1 = {  20.0, 100.0 };  // Contrôleur 1
Vec2 p2 = {  80.0, 100.0 };  // Contrôleur 2
Vec2 p3 = { 100.0,   0.0 };  // Arrivée
```
 
Le point Q est généré aléatoirement dans `[0, 200] × [0, 200]` à chaque exécution.
 
---
 
## Exemple de sortie console
 
```
nbPoints = 5      →  132.84
nbPoints = 10     →  132.73
nbPoints = 50     →  132.71
nbPoints = 200    →  132.71
nbPoints = 1000   →  132.71
nbPoints = 10000  →  132.71
 
===================== Coordonnés Newton-Raphson =======================
Q : (x: 143, y: 87)
Coordonnés le plus proche : (x: 99.1, y: 74.3)
Distance : 44.2
=======================================================================
Longueur totale : 132.71
OK — bezier.csv et ctrl.csv generes
```
 
---
 
## Notes
 
- La méthode "Newton-Raphson" mentionnée en console est en réalité une recherche par force brute — l'implémentation réelle de NR est prévue comme amélioration future.
- Des logs de debug sont présents dans le code (commentés).
