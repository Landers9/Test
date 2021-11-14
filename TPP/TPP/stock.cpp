#include "stock.h"
#include "arbremap.h"//maj
#include <iostream>//maj
//using namespace std;//maj


std::istream& operator >> (std::istream& is, Recette& recette){

    std::string chaine;
    int quantite;


    for(;;) {
        is >> chaine;
        if(chaine == ";")
            break;
        is >> quantite;

        //TODO
     


    }


    return is;
}

    Stock:: Stock(){};

    void Stock :: ajout(std::string nomingredient, std::string date, int nombre){
        
        //stokage[nomingredient] = nombre;
    }

    void Stock :: retrait(std::string nomingredient, int nombre){

           // conteneurIngredients.enlever(nomingredient);
    }

    void Stock :: affichage(){


    }      
    

    std::string Stock :: dateExpiration(const Recette& recette) const{

        //return recette.dateexpiration;
        return " ";
      }

    bool Stock :: realisable(const Recette& recette) const{

           std::cout<<" Réalisable_Mathieu"<<std::endl;
          
        return true;
    }

    bool Stock :: utilisation(const Recette& recette){

            std::cout<<" Utilisation_Mathieu"<<std::endl;

      return true;
    }

        //maj
        /*
        void Ingredient::ajouter(std::string nom, int quantite) 
        {
            contenurIngredient[nom] = quantite;
        
        }

        ArbreMap<std::string, std::string> conteneur;
        
        for(ArbreMap<std::string, std::string> :: Iterateur iter = conteneur.debut();iter;++iter)
            std::cout<<iter.cle()<<" : "<<iter.valeur()<<std::endl;
            //std::cout<<" Affichage_Mathieu"<<std::endl;



void modifier(const ArbreMap <std::string,  std::string>& dictionnaire){ 
    //ArbreMap <std::string,  std::string> :: Iterateur iter = dictionnaire.debut();
        for(ArbreMap <std::string,  std::string> :: Iterateur iter = dictionnaire.debut();iter;++iter){ 
            std::cout<<iter.cle()<<":"<<iter.valeur()<<std::endl;
            iter.valeur() = "Patate";
        }
}

std::istream& operator >> (std::istream& is, Recette& recette){

    std::string chaine;
    int quantite;


    for(;;) {
        is >> chaine;
        if(chaine == ";")
            break;
        is >> quantite;

        // TODO
        if(quantite < 1){ 
            std::cout<<"Nombre d'ingrédient incorrect doit être positif"<<std::endl;
        //FIN TODO 
        }else{

        ArbreMap<std::string, std::string> cp;
        while(cin)
        }
        std::string mot;
        std::cin>>mot>>ws;
        cp[mot]++;
        }

            Pile<string> cours;
            cours.inserer("bonMager");
            cours.inserer("Bonne bouffe");

        ArbreMap<std::string, std::string>conteneurrecettes;
        for(ArbreMap<std::string, std::string>::Iterateur iter = conteneurrecettes.debut(); iter;++iter)
        std::cout<<conteneurrecettes[iter]<<" : "<<

        }
        

       ArbreMap<std::string, int> cp;

for(int i = 0; i<8; i++){
    std::string mot;
    std::cin>>mot>>ws;
    cp[mot]++;
}

    for(ArbreMap<std::string, int> :: Iterateur iter = cp.debut(); iter;++iter)
    std::cout<<iter.cle()<<":"<<iter.valeur()<<std::endl;

    }


    return is;
}*/