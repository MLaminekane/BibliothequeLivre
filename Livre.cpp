#include "include/Livre.h"
#include "include/ConsoleFormat.h"
#include <iostream>
#include <iomanip>

int Livre::nextId = 1;

Livre::Livre(std::string titre, std::string auteur, int annee, std::string isbn, std::string catalogue)
    : titre(std::move(titre)), auteur(std::move(auteur)), annee(annee), isbn(std::move(isbn)), catalogue(std::move(catalogue))
{
  id = nextId++;
}

const std::string &Livre::getTitre() const { return titre; }
const std::string &Livre::getAuteur() const { return auteur; }
const std::string &Livre::getIsbn() const { return isbn; }
const std::string &Livre::getCatalogue() const { return catalogue; }
bool Livre::estDisponible() const { return disponible; }

bool Livre::emprunter()
{
  if (!disponible)
    return false;
  disponible = false;
  return true;
}

void Livre::rendre() { disponible = true; }

void Livre::afficherInfo() const
{
  using namespace ConsoleFmt;
  // Carte détaillée (utilisée pour la recherche d'un seul livre)
  const std::string statut = disponible ? (GREEN + std::string("Disponible") + RESET)
                                        : (RED + std::string("Emprunté") + RESET);
  // Largeur fixe simple pour aligner (peut être ajustée)
  constexpr int LABEL_W = 11; // largeur des libellés
  constexpr int BOX_W = 60;   // largeur intérieure approximative

  auto ligneSep = [&]()
  {
    std::cout << CYAN << std::string(BOX_W, '-') << RESET << '\n';
  };

  std::cout << CYAN << "+" << std::string(BOX_W - 2, '-') << "+" << RESET << '\n';
  std::cout << CYAN << "|" << RESET << BOLD << " Livre #" << id << RESET;
  std::cout << std::string(std::max(0, BOX_W - 2 - static_cast<int>(8 + std::to_string(id).size())), ' ') << CYAN << "|" << RESET << '\n';
  ligneSep();

  auto champ = [&](const std::string &label, const std::string &value)
  {
    std::cout << CYAN << "|" << RESET << std::left << std::setw(LABEL_W) << label << ": "
              << value;
    int used = LABEL_W + 2 + static_cast<int>(value.size());
    if (used < BOX_W - 2)
      std::cout << std::string(BOX_W - 2 - used, ' ');
    std::cout << CYAN << "|" << RESET << '\n';
  };

  champ("Titre", titre);
  champ("Auteur", auteur);
  champ("Année", std::to_string(annee));
  champ("ISBN", isbn);
  champ("Catalogue", catalogue);
  champ("Statut", statut);

  std::cout << CYAN << "+" << std::string(BOX_W - 2, '-') << "+" << RESET << '\n';
}
