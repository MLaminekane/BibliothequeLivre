# 📚 Mini Bibliothèque C++ (version pédagogique simplifiée)

Application console pour gérer des livres et des étudiants avec emprunts/retours, affichages lisibles (tableaux alignés + couleurs ANSI).

## ✨ Fonctionnalités principales

- Ajout de livres (avec prévention doublon ISBN) + ID auto
- Listing : tous / disponibles / par catalogue
- Recherche par titre → affichage détaillé en carte
- Ajout d'étudiants (code permanent unique)
- Emprunt via sélection par ID (limite 3)
- Rendu via menu avec sélection numérotée
- Tableau global des livres empruntés
- Tableaux formatés : livres, étudiants, emprunts
- Couleurs centralisées (`ConsoleFormat.h`)

## 🧱 Structure des classes

| Classe         | Rôle                        | Remarques                             |
| -------------- | --------------------------- | ------------------------------------- |
| `Livre`        | Métadonnées + disponibilité | ID auto, pas d’historique cumulatif   |
| `Etudiant`     | Emprunts actifs (max 3)     | Pointeurs non possédants vers `Livre` |
| `Bibliotheque` | Stockage & opérations       | Vecteurs valeur (livres, étudiants)   |

Pas d’héritage, pas d’exceptions, pas de smart pointers : priorité à la lisibilité.

## 🖥️ Exemple d’affichage (extraits)

```
=== TOUS LES LIVRES ===
ID   Titre                          Auteur            Année  ISBN          Catalogue    Statut
-----------------------------------------------------------------------------------------------
1    Clean Code                     Robert C. Martin  2008   ISBN-CC       CleanCode    Disponible
2    Python Crash Course            Eric Matthes      2019   ISBN-PCC      Python       Disponible

=== ÉTUDIANTS ===
Code           Nom complet                Nb        Livres
--------------------------------------------------------------
doej1234       John Doe                   1/3       Clean Code
```

## 🔧 Compilation

```
cmake -S . -B build
cmake --build build
./build/BibliothequeLivre
```

## 🕹️ Utilisation rapide

1. Lancer le binaire
2. Menu 2 → Ajouter un étudiant
3. Menu 3 → Emprunter (choisir ID)
4. Menu 4 → Rendre (sélectionner numéro)
5. Menu 6 → Voir tous les emprunts

## 🧪 Règles métier

- Limite : 3 emprunts simultanés par étudiant
- Un livre = disponible OU emprunté
- ISBN unique / Code permanent unique
- Emprunt refusé si indisponible ou limite atteinte

## 🚀 Idées d’amélioration (facultatif)

- Persistance (fichiers)
- Recherche partielle insensible à la casse
- Mode sans couleurs (variable NO_COLOR)
- Statistiques (historique emprunts)

## 📁 Fichiers clés

| Fichier                  | Description                             |
| ------------------------ | --------------------------------------- |
| `main.cpp`               | Menus et flux utilisateur               |
| `Livre.*`                | Modèle livre + affichage détaillé       |
| `Etudiant.*`             | Gestion emprunts individuels            |
| `Bibliotheque.*`         | Opérations globales (recherche, listes) |
| `ConsoleFormat.h`        | Couleurs / utilitaires format           |
| `consignes_exercice.txt` | Consignes pédagogiques                  |

## ✅ Qualité visée

- Code clair, noms explicites
- Pas de magie ni abréviations cryptiques
- Fonctions courtes & cohérentes

---

Bon apprentissage 👌
