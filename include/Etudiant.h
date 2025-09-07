#ifndef ETUDIANT_H
#define ETUDIANT_H
#include <string>
#include <vector>

class Livre;

class Etudiant
{
private:
    std::string nom;
    std::string prenom;
    std::string codePermanent;
    std::string adresse;
    int nbEmprunts{0};
    std::vector<Livre *> livresEmpruntes; // non propriétaire
    int limite{3};

public:
    Etudiant(std::string nom, std::string prenom, std::string codePermanent, std::string adresse);
    const std::string &getNom() const;
    const std::string &getPrenom() const;
    const std::string &getCodePermanent() const;
    const std::string &getAdresse() const;
    int getNbEmprunts() const;
    int limiteEmprunts() const;
    const std::vector<Livre *> &getLivresEmpruntes() const;
    void afficherInfo() const;
    // Renvoie true si emprunt réussi
    bool emprunterLivre(Livre &livre);
    void rendreLivre(Livre &livre);
};

#endif // ETUDIANT_H
