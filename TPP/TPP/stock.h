#ifndef STOCK_H
#define STOCK_H
#include <iostream>
#include"arbremap.h"
/*
class Ingredient
{
public: 
    Ingredient();
    Ingredient(std::string nom, int quantite);
    ~Ingredient();
    int quantite;
    std::string nom;

private:
 struct arbre{ 
    int quantité;
    std::string nom;
    std::string date;
    arbre * filsGauche;
    arbre * filsDroit;
  };

};
*/

class Ingredient 
{
private: 
  ArbreMap<std::string, int>conteneuringredients;//non --> quantité
  
public:
  void ajouter(std::string nom, int quantite);

  };


class Recette {
  // constructeur d'une recette? 
  public:
  /*
    std::string nomrecette;
    std::string dateexpiration;
    ArbreMap<std::string, std::string>conteneurrecettes; //nom --> Ingredients
private:
*/
    friend std::istream& operator >> (std::istream& is, Recette& recette);  
};


class Stock
{
public:
    Stock();
    void ajout(std::string nomingredient, std::string date, int nombre);
    void retrait(std::string nomingredient, int nombre);
    void affichage();
    std::string dateExpiration(const Recette& recette) const;
    bool realisable(const Recette& recette) const;
    bool utilisation(const Recette& recette);
    void afficher(const Recette& recette);

private: 
    /*ArbreMap<std::string, int>conteneuringredients;//nom--> quantité
    ArbreMap<std::string, std::string>conteneurrecettes; //nom --> Ingredients
    ArbreMap<ArbreMap<std::string, int>, ArbreMap<std::string, std::string>>conteneur;//Recette --> ingredientRecette
    ArbreMap<std::string, std::string>stokage; 
     ArbreMap<std::string, std::string>stokage; 
     ArbreAVL<std::string>Stokage; 
   */
};

#endif // STOCK_H


  