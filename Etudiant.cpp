// Implémentation de la classe Etudiant
#include "include/Etudiant.h"
#include "include/Livre.h"
#include "include/ConsoleFormat.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

Etudiant::Etudiant(std::string nom, std::string prenom, std::string codePermanent, std::string adresse)
    : nom(std::move(nom)), prenom(std::move(prenom)), codePermanent(std::move(codePermanent)), adresse(std::move(adresse)) {}

const std::string &Etudiant::getNom() const { return nom; }
const std::string &Etudiant::getPrenom() const { return prenom; }
const std::string &Etudiant::getCodePermanent() const { return codePermanent; }
const std::string &Etudiant::getAdresse() const { return adresse; }
int Etudiant::getNbEmprunts() const { return nbEmprunts; }
int Etudiant::limiteEmprunts() const { return limite; }
const std::vector<Livre *> &Etudiant::getLivresEmpruntes() const { return livresEmpruntes; }

void Etudiant::afficherInfo() const
{
    using namespace ConsoleFmt;
    std::cout << BOLD << codePermanent << RESET << " | "
              << prenom << " " << nom
              << " | Emprunts: " << nbEmprunts << "/" << limiteEmprunts();
    if (!livresEmpruntes.empty())
    {
        std::cout << " | Livres: ";
        for (size_t i = 0; i < livresEmpruntes.size(); ++i)
        {
            std::cout << livresEmpruntes[i]->getTitre();
            if (i + 1 < livresEmpruntes.size())
                std::cout << ", ";
        }
    }
    std::cout << '\n';
}

bool Etudiant::emprunterLivre(Livre &livre)
{
    if (!livre.estDisponible())
        return false;
    if (nbEmprunts >= limiteEmprunts())
        return false;
    if (!livre.emprunter())
        return false;
    nbEmprunts++;
    livresEmpruntes.push_back(&livre);
    return true;
}

void Etudiant::rendreLivre(Livre &livre)
{
    livre.rendre();
    if (nbEmprunts > 0)
        nbEmprunts--;
    auto it = std::find(livresEmpruntes.begin(), livresEmpruntes.end(), &livre);
    if (it != livresEmpruntes.end())
        livresEmpruntes.erase(it);
}
