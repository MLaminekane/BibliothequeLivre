#ifndef LIVRE_H
#define LIVRE_H
#include <string>

class Livre
{
private:
  std::string titre;
  std::string auteur;
  int annee{};
  std::string isbn;
  std::string catalogue;
  bool disponible{true};
  int id{0};
  static int nextId;

public:
  Livre() = default;
  Livre(std::string titre, std::string auteur, int annee, std::string isbn, std::string catalogue);

  const std::string &getTitre() const;
  const std::string &getAuteur() const;
  const std::string &getIsbn() const;
  const std::string &getCatalogue() const; // nouveau nom
  int getAnnee() const { return annee; }
  int getId() const { return id; }
  bool estDisponible() const;

  // Renvoie true si l'emprunt est possible, false sinon
  bool emprunter();
  void rendre();
  void afficherInfo() const;
};

#endif // LIVRE_H
