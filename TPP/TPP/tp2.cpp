#include <iostream>//maj
#include <fstream>//maj
#include "stock.h"
#include "arbreavl.h"//maj


int main(int argc, const char** argv) {
    std::istream* entree;
    std::ifstream* entree_fichier = NULL;

    if(argc>1){
         entree = entree_fichier = new std::ifstream(argv[1]);
         if(entree->fail())
             std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
    } else {
         entree = &std::cin;
    }
    
    //TODO DEBUT
    /*
    ArbreAVL <Stock> arbre; //class avl
    Ingredient ingredient;//struc de données
    Recette recette; //struc de données
    // TODO : ajouter les structures a utiliser
*/
    Stock stock;

    while(*entree){
        std::string commande;
        *entree >> commande;
        if(!(*entree)) break;
        if(commande=="recette"){
            std::string nomrecette;
            *entree >> nomrecette;

            // TODO
            // Appeler la fonction qui ajoute ou met à jour les recettes
            //TODO FIN

        } else if(commande=="ajout") {
            std::string nomingredient;
            *entree >> nomingredient;
            int nombre = 0;
            *entree >> nombre;
            if( nombre <= 0) {
                std::cerr << "Erreur sur le nombre d'ingredient." << std::endl;
                return -1;
            }
            std::string date;
            *entree >> date;

            stock.ajout(nomingredient, date, nombre);

        } else if(commande=="retrait") {

            std::string nomingredient;
            *entree >> nomingredient;
            std::cerr << "retrait " << nomingredient << std::endl;
            int nombre = 0;
            *entree >> nombre;
            if( nombre <= 0) {
                std::cerr << "Erreur sur le nombre d'ingredient." << std::endl;
                return -1;
            }

            stock.retrait(nomingredient, nombre);

        } else if(commande=="recommendation") {
            
            // TODO

            //TODO FIN
        } else if(commande=="utilisation") {
            std::string nomrecette;
            *entree >> nomrecette;

            // TODO

            //TODO FIN

        } else if(commande=="affichage") {
            stock.affichage();
        } else {
            std::cerr << "commande \"" << commande << " non reconnue !" << std::endl; 
        }
    }
    delete entree_fichier;

ArbreMap<std::string, int> cp;

while(std::cin){
    std::string mot;
    std::cin>>mot;
    cp[mot]++;
}

    for(ArbreMap<std::string, int> :: Iterateur iter = cp.debut(); iter;++iter)
    std::cout<<iter.cle()<<":"<<iter.valeur()<<std::endl;


    return 0;
}
