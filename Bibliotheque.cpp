#include "include/Bibliotheque.h"
#include "include/Livre.h"
#include "include/Etudiant.h"
#include "include/ConsoleFormat.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>

namespace
{
  using ConsoleFmt::BOLD;
  using ConsoleFmt::CYAN;
  using ConsoleFmt::GREEN;
  using ConsoleFmt::RED;
  using ConsoleFmt::RESET;
  using ConsoleFmt::trunc;

  constexpr int W_ID = 4;
  constexpr int W_TITRE = 30;
  constexpr int W_AUTEUR = 18;
  constexpr int W_ANNEE = 6;
  constexpr int W_ISBN = 13;
  constexpr int W_CATALOGUE = 12;
  constexpr int W_STATUT = 11;

  std::string statutLivre(const Livre &livre)
  {
    return livre.estDisponible() ? (GREEN + std::string("Disponible") + RESET)
                                 : (RED + std::string("Emprunté") + RESET);
  }

  void enteteLivres()
  {
    std::cout << BOLD
              << std::left << std::setw(W_ID) << "ID" << " "
              << std::setw(W_TITRE) << "Titre" << " "
              << std::setw(W_AUTEUR) << "Auteur" << " "
              << std::setw(W_ANNEE) << "Année" << " "
              << std::setw(W_ISBN) << "ISBN" << " "
              << std::setw(W_CATALOGUE) << "Catalogue" << " "
              << std::setw(W_STATUT) << "Statut"
              << RESET << '\n';
    std::cout << std::string(W_ID + W_TITRE + W_AUTEUR + W_ANNEE + W_ISBN + W_CATALOGUE + W_STATUT + 7, '-') << '\n';
  }

  void ligneLivre(const Livre &l)
  {
    std::cout << std::left << std::setw(W_ID) << l.getId() << " "
              << std::setw(W_TITRE) << trunc(l.getTitre(), W_TITRE) << " "
              << std::setw(W_AUTEUR) << trunc(l.getAuteur(), W_AUTEUR) << " "
              << std::setw(W_ANNEE) << l.getAnnee() << " "
              << std::setw(W_ISBN) << trunc(l.getIsbn(), W_ISBN) << " "
              << std::setw(W_CATALOGUE) << trunc(l.getCatalogue(), W_CATALOGUE) << " "
              << std::setw(W_STATUT) << statutLivre(l)
              << '\n';
  }

  // Largeurs pour tableau étudiants
  constexpr int W_CODE = 14;
  constexpr int W_NOM_COMPLET = 26;
  constexpr int W_EMPRUNTS = 9; // ex "2/3"
  constexpr int W_LIVRES_LISTE = 40;

  void enteteEtudiants()
  {
    std::cout << BOLD
              << std::left << std::setw(W_CODE) << "Code" << " "
              << std::setw(W_NOM_COMPLET) << "Nom complet" << " "
              << std::setw(W_EMPRUNTS) << "Nb" << " "
              << std::setw(W_LIVRES_LISTE) << "Livres" << RESET << '\n';
    std::cout << std::string(W_CODE + W_NOM_COMPLET + W_EMPRUNTS + W_LIVRES_LISTE + 4, '-') << '\n';
  }

  std::string concatLivres(const Etudiant &e)
  {
    std::string liste;
    const auto &vec = e.getLivresEmpruntes();
    for (size_t i = 0; i < vec.size(); ++i)
    {
      liste += vec[i]->getTitre();
      if (i + 1 < vec.size())
        liste += ", ";
    }
    return liste;
  }

  void ligneEtudiant(const Etudiant &e)
  {
    std::string livresConcat = concatLivres(e);
    std::string nb = std::to_string(e.getNbEmprunts()) + "/" + std::to_string(e.limiteEmprunts());
    std::cout << std::left
              << std::setw(W_CODE) << e.getCodePermanent() << " "
              << std::setw(W_NOM_COMPLET) << trunc(e.getPrenom() + " " + e.getNom(), W_NOM_COMPLET) << " "
              << std::setw(W_EMPRUNTS) << nb << " "
              << std::setw(W_LIVRES_LISTE) << trunc(livresConcat, W_LIVRES_LISTE)
              << '\n';
  }
}

void Bibliotheque::ajouterLivre(const Livre &livre)
{
  // Empêcher doublon ISBN
  for (const auto &l : livres)
    if (l.getIsbn() == livre.getIsbn())
    {
      std::cout << "ISBN déjà présent, ignoré.\n";
      return;
    }
  livres.push_back(livre);
  std::cout << "Livre ajouté.\n";
}
void Bibliotheque::ajouterEtudiant(const Etudiant &etu)
{
  for (const auto &e : etudiants)
    if (e.getCodePermanent() == etu.getCodePermanent())
    {
      std::cout << "Code permanent déjà existant, ignoré.\n";
      return;
    }
  etudiants.push_back(etu);
  std::cout << "Étudiant ajouté.\n";
}

Livre *Bibliotheque::rechercherLivreParTitre(const std::string &titre)
{
  for (auto &l : livres)
    if (l.getTitre() == titre)
      return &l;
  return nullptr;
}

Livre *Bibliotheque::rechercherLivreParId(int id)
{
  for (auto &l : livres)
    if (l.getId() == id)
      return &l;
  return nullptr;
}

Etudiant *Bibliotheque::rechercherEtudiantParCode(const std::string &codePermanent)
{
  for (auto &e : etudiants)
    if (e.getCodePermanent() == codePermanent)
      return &e;
  return nullptr;
}

void Bibliotheque::afficherCatalogue() const
{
  std::cout << CYAN << "\n=== TOUS LES LIVRES ===" << RESET << '\n';
  if (livres.empty())
  {
    std::cout << "(Aucun livre)\n";
    return;
  }
  enteteLivres();
  for (const auto &l : livres)
    ligneLivre(l);
}

void Bibliotheque::afficherLivresParCatalogue(const std::string &catalogue) const
{
  std::cout << CYAN << "\n=== CATALOGUE: " << catalogue << " ===" << RESET << '\n';
  bool trouve = false;
  for (const auto &l : livres)
    if (l.getCatalogue() == catalogue)
    {
      if (!trouve)
      {
        enteteLivres();
        trouve = true;
      }
      ligneLivre(l);
    }
  if (!trouve)
    std::cout << "(Aucun livre dans ce catalogue)\n";
}

void Bibliotheque::afficherLivresEmpruntesTous() const
{
  std::cout << CYAN << "\n=== LIVRES EMPRUNTÉS (TOUS ÉTUDIANTS) ===" << RESET << '\n';
  bool aucun = true;
  std::cout << std::left << BOLD << std::setw(14) << "Code étudiant" << std::setw(6) << "ID" << std::setw(35) << "Titre" << std::setw(15) << "Catalogue" << RESET << '\n';
  std::cout << std::string(14 + 6 + 35 + 15, '-') << '\n';
  for (const auto &etudiant : etudiants)
  {
    for (Livre *livre : etudiant.getLivresEmpruntes())
    {
      aucun = false;
      std::cout << std::left << std::setw(14) << etudiant.getCodePermanent()
                << std::setw(6) << livre->getId()
                << std::setw(35) << trunc(livre->getTitre(), 35)
                << std::setw(15) << trunc(livre->getCatalogue(), 15)
                << '\n';
    }
  }
  if (aucun)
    std::cout << "(Aucun emprunt)\n";
}

void Bibliotheque::afficherEtudiants() const
{
  std::cout << CYAN << "\n=== ÉTUDIANTS ===" << RESET << '\n';
  if (etudiants.empty())
  {
    std::cout << "(Aucun étudiant)\n";
    return;
  }
  enteteEtudiants();
  for (const auto &e : etudiants)
    ligneEtudiant(e);
}

void Bibliotheque::afficherLivresDisponibles() const
{
  std::cout << CYAN << "\n=== LIVRES DISPONIBLES ===" << RESET << '\n';
  bool any = false;
  for (const auto &l : livres)
    if (l.estDisponible())
    {
      if (!any)
      {
        enteteLivres();
        any = true;
      }
      ligneLivre(l);
    }
  if (!any)
    std::cout << "(Aucun livre disponible)\n";
}

void Bibliotheque::listerCodesEtudiants() const
{
  std::cout << "Codes étudiants: ";
  for (const auto &e : etudiants)
    std::cout << e.getCodePermanent() << ' ';
  std::cout << "\n";
}

// stats supprimé
