#ifndef BIBLIOTHEQUE_H
#define BIBLIOTHEQUE_H
#include <vector>
#include <string>

class Livre;
class Etudiant;

class Bibliotheque
{
private:
  std::vector<Livre> livres;
  std::vector<Etudiant> etudiants;

public:
  void ajouterLivre(const Livre &livre);
  void ajouterEtudiant(const Etudiant &etu);
  Livre *rechercherLivreParTitre(const std::string &titre);
  Livre *rechercherLivreParId(int id);
  Etudiant *rechercherEtudiantParCode(const std::string &codePermanent);
  void listerCodesEtudiants() const;                                   // aide pour sélection
  void afficherCatalogue() const;                                      // tous les livres
  void afficherLivresParCatalogue(const std::string &catalogue) const; // filtré
  void afficherLivresEmpruntesTous() const;                            // tous les emprunts
  void afficherEtudiants() const;
  void afficherLivresDisponibles() const;
};

#endif // BIBLIOTHEQUE_H
