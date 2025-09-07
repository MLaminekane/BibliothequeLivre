// Application de gestion d'une bibliothèque (version console pédagogique)
#include <iostream>
#include <limits>
#include <string>
#include "include/Livre.h"
#include "include/Etudiant.h"
#include "include/Bibliotheque.h"
#include "include/ConsoleFormat.h"

namespace
{
  constexpr std::streamsize FLUSH_SIZE = 10000; // Limite de purge d'entrée adaptée à nos lectures simples

  void viderEntree()
  {
    std::cin.clear();
    std::cin.ignore(FLUSH_SIZE, '\n');
  }

  void afficherMenuPrincipal()
  {
    using namespace ConsoleFmt;
    std::cout << CYAN << "\n========================================\n";
    std::cout << "           MENU PRINCIPAL\n";
    std::cout << "========================================" << RESET << '\n'
              << "1. Livres\n"
              << "2. Étudiants\n"
              << "3. Emprunter\n"
              << "4. Rendre\n"
              << "5. Rechercher un livre\n"
              << "6. Afficher livres empruntés (tous)\n"
              << "0. Quitter\n"
              << "Choix: ";
  }

  void menuLivres(Bibliotheque &bibliotheque)
  {
    while (true)
    {
      std::cout << "\n--- MENU LIVRES ---\n"
                << "1. Lister tous\n"
                << "2. Lister par catalogue\n"
                << "3. Ajouter un livre\n"
                << "4. Livres disponibles\n"
                << "0. Retour\n"
                << "Choix: ";

      int choixMenuLivres;
      if (!(std::cin >> choixMenuLivres))
      {
        viderEntree();
        continue; // Demander à nouveau
      }
      std::cin.ignore(FLUSH_SIZE, '\n');

      switch (choixMenuLivres)
      {
      case 0:
        return; // Retour au menu principal
      case 1:
        bibliotheque.afficherCatalogue();
        break;
      case 2:
      {
        std::string nomCatalogue;
        std::cout << "Catalogue (ex: CleanCode, Python, C++): ";
        std::getline(std::cin, nomCatalogue);
        bibliotheque.afficherLivresParCatalogue(nomCatalogue);
        break;
      }
      case 3:
      {
        std::string titre, auteur, isbn, nomCatalogue;
        int anneePublication;
        std::cout << "Titre: ";
        std::getline(std::cin, titre);
        std::cout << "Auteur: ";
        std::getline(std::cin, auteur);
        std::cout << "Année: ";
        if (!(std::cin >> anneePublication))
        {
          viderEntree();
          std::cout << "Année invalide. Ajout annulé.\n";
          break;
        }
        std::cin.ignore(FLUSH_SIZE, '\n');
        std::cout << "ISBN: ";
        std::getline(std::cin, isbn);
        std::cout << "Catalogue: ";
        std::getline(std::cin, nomCatalogue);
        bibliotheque.ajouterLivre(Livre(titre, auteur, anneePublication, isbn, nomCatalogue));
        break;
      }
      case 4:
        bibliotheque.afficherLivresDisponibles();
        break;
      default:
        std::cout << "Choix inconnu.\n";
        break;
      }
    }
  }

  void menuEtudiants(Bibliotheque &bibliotheque)
  {
    while (true)
    {
      std::cout << "\n--- MENU ÉTUDIANTS ---\n"
                << "1. Lister étudiants\n"
                << "2. Ajouter étudiant\n"
                << "0. Retour\n"
                << "Choix: ";

      int choixMenuEtudiants;
      if (!(std::cin >> choixMenuEtudiants))
      {
        viderEntree();
        continue;
      }
      std::cin.ignore(FLUSH_SIZE, '\n');

      switch (choixMenuEtudiants)
      {
      case 0:
        return;
      case 1:
        bibliotheque.afficherEtudiants();
        break;
      case 2:
      {
        std::string nom, prenom, codePermanent, adresse;
        std::cout << "Nom: ";
        std::getline(std::cin, nom);
        std::cout << "Prénom: ";
        std::getline(std::cin, prenom);
        std::cout << "Code permanent: ";
        std::getline(std::cin, codePermanent);
        std::cout << "Adresse: ";
        std::getline(std::cin, adresse);
        bibliotheque.ajouterEtudiant(Etudiant(nom, prenom, codePermanent, adresse));
        break;
      }
      default:
        std::cout << "Choix inconnu.\n";
        break;
      }
    }
  }

  void fluxEmprunt(Bibliotheque &bibliotheque)
  {
    std::string codePermanent;
    std::cout << "Code étudiant: ";
    std::getline(std::cin, codePermanent);

    Etudiant *etudiant = bibliotheque.rechercherEtudiantParCode(codePermanent);
    if (etudiant == nullptr)
    {
      std::cout << "Étudiant introuvable. Ajoute-le d'abord (menu Étudiants).\n";
      bibliotheque.listerCodesEtudiants();
      return;
    }

    std::cout << "\nLivres disponibles (ID) :\n";
    bibliotheque.afficherLivresDisponibles();
    std::cout << "ID du livre (0 annuler): ";

    int livreIdSelectionne;
    if (!(std::cin >> livreIdSelectionne))
    {
      viderEntree();
      std::cout << "Entrée invalide\n";
      return;
    }
    std::cin.ignore(FLUSH_SIZE, '\n');
    if (livreIdSelectionne == 0)
      return;

    Livre *livre = bibliotheque.rechercherLivreParId(livreIdSelectionne);
    if (livre == nullptr)
    {
      std::cout << "ID inconnu.\n";
      return;
    }

    bool empruntReussi = etudiant->emprunterLivre(*livre);
    if (empruntReussi)
      std::cout << "Emprunt OK\n";
    else
      std::cout << "Impossible (limite ou indisponible)\n";
  }

  void fluxRetour(Bibliotheque &bibliotheque)
  {
    std::string codePermanent;
    std::cout << "Code étudiant: ";
    std::getline(std::cin, codePermanent);

    Etudiant *etudiant = bibliotheque.rechercherEtudiantParCode(codePermanent);
    if (etudiant == nullptr)
    {
      std::cout << "Étudiant introuvable.\n";
      bibliotheque.listerCodesEtudiants();
      return;
    }
    if (etudiant->getLivresEmpruntes().empty())
    {
      std::cout << "Aucun emprunt.\n";
      return;
    }

    while (true)
    {
      std::cout << "\nLivres empruntés (sélection par numéro) :\n";
      int indexAffichage = 1;
      for (Livre *livreEmprunte : etudiant->getLivresEmpruntes())
      {
        std::cout << indexAffichage++ << ") " << livreEmprunte->getTitre() << " (#" << livreEmprunte->getId() << ")\n";
      }
      std::cout << "0. Retour\nChoix: ";

      int choixSelection;
      if (!(std::cin >> choixSelection))
      {
        viderEntree();
        continue; // redemander
      }
      std::cin.ignore(FLUSH_SIZE, '\n');

      if (choixSelection == 0)
        return; // abandon

      if (choixSelection > 0 && choixSelection <= static_cast<int>(etudiant->getLivresEmpruntes().size()))
      {
        Livre *livreARendre = etudiant->getLivresEmpruntes()[choixSelection - 1];
        etudiant->rendreLivre(*livreARendre);
        std::cout << "Rendu OK\n";
        return; // fin du flux
      }
      std::cout << "Numéro invalide.\n";
    }
  }
} // namespace

int main()
{
  Bibliotheque bibliotheque;

  // Pré-chargement de quelques livres réalistes dans différents catalogues
  bibliotheque.ajouterLivre(Livre("Clean Code", "Robert C. Martin", 2008, "ISBN-CC", "CleanCode"));
  bibliotheque.ajouterLivre(Livre("Python Crash Course", "Eric Matthes", 2019, "ISBN-PCC", "Python"));
  bibliotheque.ajouterLivre(Livre("Effective C++", "Scott Meyers", 2005, "ISBN-ECpp", "C++"));

  while (true)
  {
    afficherMenuPrincipal();

    int choixMenuPrincipal;
    if (!(std::cin >> choixMenuPrincipal))
    {
      viderEntree();
      std::cout << "Entrée invalide.\n";
      continue;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // vider le reste de la ligne

    if (choixMenuPrincipal == 0)
      break;

    switch (choixMenuPrincipal)
    {
    case 1:
      menuLivres(bibliotheque);
      break;
    case 2:
      menuEtudiants(bibliotheque);
      break;
    case 3:
      fluxEmprunt(bibliotheque);
      break;
    case 4:
      fluxRetour(bibliotheque);
      break;
    case 5:
    {
      std::string titreRecherche;
      std::cout << "Titre: ";
      std::getline(std::cin, titreRecherche);
      Livre *livreTrouve = bibliotheque.rechercherLivreParTitre(titreRecherche);
      if (livreTrouve != nullptr)
        livreTrouve->afficherInfo();
      else
        std::cout << "Introuvable\n";
      break;
    }
    case 6:
      bibliotheque.afficherLivresEmpruntesTous();
      break;
    default:
      std::cout << "Choix inconnu.\n";
      break;
    }
  }

  std::cout << "Au revoir!\n";
  return 0;
}
