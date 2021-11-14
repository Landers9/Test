#ifndef ARBREAVL_H
#define ARBREAVL_H

#include <cassert>
#include "pile.h"

template <class T>
class ArbreAVL {
  public:
    ArbreAVL();
    ArbreAVL(const ArbreAVL&);
    ~ArbreAVL();

    // Annonce l'existance d'une classe Iterateur.
    class Iterateur;
    //class IterateurConst;//maj

    void inserer(const T&);
    bool contient(const T&) const;
    bool vide() const;
    void vider();
    void enlever(const T&); // non requis pour le TP2.
    int  hauteur() const;

    // Fonctions pour obtenir un itérateur (position dans l'arbre)
    Iterateur debut() const;
    Iterateur fin() const;
    Iterateur rechercher(const T&) const;
    Iterateur rechercherEgalOuSuivant(const T&) const;
    Iterateur rechercherEgalOuPrecedent(const T&) const;

    // Accès aux éléments de l'arbre via un intérateur.
    const T& operator[](const Iterateur&) const;
    T& operator[](const Iterateur&);

    // Copie d'un arbre AVL.
    ArbreAVL& operator = (const ArbreAVL&);

  private:
    struct Noeud {
      Noeud(const T&);
      T contenu;
      int equilibre;
      Noeud* gauche = nullptr;
      Noeud* droite = nullptr;
    };

    
    Noeud* racine;

    // Fonctions internes
    bool inserer(Noeud*&, const T&);
    bool contient(const T&, const Noeud*) const;
    bool enleverGauche(Noeud*&, const T&);
    bool enleverDroite(Noeud*&, const T&);

    void rotationGaucheDroite(Noeud*&);
    void rotationDroiteGauche(Noeud*&);
    void vider(Noeud*&);
    void copier(const Noeud*, Noeud*&) const;
    const T& max(Noeud*) const;
    bool enlever(Noeud*&, const T& e);

  public:
    // Sera présenté à la semaine #7
    class Iterateur {
      public:
        Iterateur(const ArbreAVL& a);
        Iterateur(const Iterateur& a);

        operator bool() const;
        bool operator!() const;
        bool operator==(const Iterateur&) const;
        bool operator!=(const Iterateur&) const;

        const T& operator*() const;

        Iterateur& operator++(); // Pré-incrément ++i
        Iterateur operator++(int); // Post-incrément i++
        Iterateur& operator = (const Iterateur&);
      private:
        const ArbreAVL& arbre_associe;
        Noeud* courant;
        Pile<Noeud*> chemin;

        friend class ArbreAVL;
    };
};


//-----------------------------------------------------------------------------

  template <class T>
ArbreAVL<T>::Noeud::Noeud(const T& c)
  : contenu(c), equilibre(0), gauche(nullptr), droite(nullptr) {
  }

  template <class T>
ArbreAVL<T>::ArbreAVL()
  : racine(nullptr) {
  }

  template <class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T>& autre)
  : racine(nullptr) {
    copier(autre.racine, racine);
  }

template <class T>
ArbreAVL<T>::~ArbreAVL() {
  vider(racine);
}

template <class T>
bool ArbreAVL<T>::contient(const T& element, const Noeud* noeud) const {
  if(noeud == nullptr)
    return false;
  if(element == noeud->contenu)
    return true;
  if(element < noeud->contenu)
    return contient(element, noeud->gauche);
  return contient(element, noeud->droite);
}

template <class T>
bool ArbreAVL<T>::contient(const T& element) const {
  return contient(element, racine);
}

template <class T>
void ArbreAVL<T>::inserer(const T& element) {
  inserer(racine, element);
}

template <class T>
bool ArbreAVL<T>::inserer(Noeud*& noeud, const T& element) {
  if(noeud == nullptr) {
    noeud = new Noeud(element);
    return true;
  }
  if(element < noeud->contenu) { // Insertion à gauche
    if(inserer(noeud->gauche, element)) {
      ++(noeud->equilibre);
      if(noeud->equilibre == 0)
        return false;
      if(noeud->equilibre == 1)
        return true;
      assert(noeud->equilibre == 2);
      if(noeud->gauche->equilibre == -1)
        rotationDroiteGauche(noeud->gauche);
      rotationGaucheDroite(noeud);
    }
    return false;
  } else if(noeud->contenu < element) { // Insertion à droite
    if(inserer(noeud->droite, element)) {
      --(noeud->equilibre);
      if(noeud->equilibre == 0)
        return false;
      if(noeud->equilibre == -1)
        return true;
      assert(noeud->equilibre == -2);
      if(noeud->droite->equilibre == 1)
        rotationGaucheDroite(noeud->droite);
      rotationDroiteGauche(noeud);
    }
    return false;
  }

  // element == noeud->contenu
  noeud->contenu = element;  // Mise à jour
  return false;
}

template <class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud*& racinesousarbre) {
  Noeud* temp = racinesousarbre->gauche;
  int  ea = temp->equilibre;
  int  eb = racinesousarbre->equilibre;
  int  neb = -(ea > 0 ? ea : 0) - 1 + eb;
  int  nea = ea + (neb < 0 ? neb : 0) - 1;

  temp->equilibre = nea;
  racinesousarbre->equilibre = neb;
  racinesousarbre->gauche = temp->droite;
  temp->droite = racinesousarbre;
  racinesousarbre = temp;
}

template <class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud*& racinesousarbre) {
  Noeud* temp = racinesousarbre->droite;
  int  ea = racinesousarbre->equilibre;
  int  eb = temp->equilibre;
  int  eap = 1 + ea - (0 < eb ? 0 : eb);
  int  ebp = 1 + eb + (0 > eap ? 0 : eap);

  racinesousarbre->equilibre = eap;
  temp->equilibre = ebp;
  racinesousarbre->droite = temp->gauche;
  temp->gauche = racinesousarbre;
  racinesousarbre = temp;
}

template <class T>
bool ArbreAVL<T>::vide() const {
  return racine == nullptr;
}

template <class T>
void ArbreAVL<T>::vider() {
  vider(racine);
}

template <class T>
void ArbreAVL<T>::vider(Noeud*& noeud) {
  if(noeud != nullptr) {
    vider(noeud->gauche);
    vider(noeud->droite);
    delete noeud;
    noeud = nullptr;
  }
}

template <class T>
void ArbreAVL<T>::copier(const Noeud* source, Noeud*& noeud) const {
  if(source != nullptr) {
    noeud = new Noeud(source->contenu);
    noeud->equilibre = source->equilibre;
    copier(source->gauche, noeud->gauche);
    copier(source->droite, noeud->droite);
  }
}

template <class T>
int  ArbreAVL<T>::hauteur() const {
  Noeud* temp = racine;
  int h = 0;
  while(temp != nullptr) {
    ++h;
    temp = temp->equilibre > 0 ? temp->gauche : temp->droite;
  }
  return h;
}

template <class T>
const T& ArbreAVL<T>::max(Noeud* n) const {
  while(n->droite != nullptr)
    n = n->droite;
  return n->contenu;
}

// L'enlèvement est optionnel 
// TODO
/* template <class T> */
/* void ArbreAVL<T>::enlever(const T& e) { */
/*   std::cout << "Suppression : " << e << std::endl; */

/*   // Trouver le noeud à enlever */
/*   Pile<Noeud*> pile; */
/*   Noeud* courant = racine; */
/*   Noeud* avantCourant = nullptr; */
/*   while(courant != nullptr && courant->contenu != e) { */
/*     pile.empiler(courant); */
/*     avantCourant = courant; */
/*     courant = (e < courant->contenu) ? courant->gauche : courant->droite; */
/*   } */
/*   assert(courant != nullptr); */

/*   // Enlever le noeud */
/*   Noeud* temp = courant; */
/*   if(courant->gauche != nullptr && courant->droite != nullptr) { */
/*     pile.empiler(courant); */
/*     courant = courant->gauche; */
/*     while(courant->droite != nullptr) { */
/*       pile.empiler(courant); */
/*       courant = courant->droite; */
/*     } */
/*     temp->contenu = courant->contenu; // On doit supprimer courant */
/*     temp = courant; */
/*   } else { */
/*     if(courant->gauche == nullptr) { */
/*       avantCourant == nullptr ? */
/*         racine = courant->droite : */
/*         (avantCourant->contenu < courant->contenu ? */
/*          avantCourant->droite = courant->droite : */
/*          avantCourant->gauche = courant->droite); */
/*     } */
/*     if(courant->droite == nullptr) { */
/*       avantCourant == nullptr ? */
/*         racine = courant->gauche : */
/*         (avantCourant->contenu < courant->contenu ? */
/*          avantCourant->droite = courant->gauche : */
/*          avantCourant->gauche = courant->gauche); */
/*     } */
/*   } */
/*   delete temp; */

/*   // Mise-à-jour des équilibres */
/*   T sousElem = e; */
/*   while(!pile.vide()) { */
/*     courant = pile.depiler(); */
/*     Noeud*& n = courant == racine ? racine : courant; */
/*     if(sousElem > n->contenu) { // À droite */
/*       ++(n->equilibre); */
/*       if(n->equilibre == 1) */
/*         break; */
/*       if(n->equilibre == 2) { */
/*         bool retour = n->gauche->equilibre != 0; */
/*         if(n->gauche->equilibre == -1) */
/*           rotationDroiteGauche(n->gauche); */
/*         rotationGaucheDroite(n); */
/*         if(!retour) */
/*           break; */
/*       } */
/*     } else { // À gauche */
/*       --(n->equilibre); */
/*       if(n->equilibre == -1) */
/*         break; */
/*       if(n->equilibre == -2) { */
/*         bool retour = n->droite->equilibre != 0; */
/*         if(n->droite->equilibre == 1) */
/*           rotationGaucheDroite(n->droite); */
/*         rotationDroiteGauche(n); */
/*         if(!retour) */
/*           break; */
/*       } */
/*     } */
/*   } */
/* } */

template <class T>
void ArbreAVL<T>::enlever(const T& element) {
  enlever(racine, element);
}

template <class T>
bool ArbreAVL<T>::enlever(Noeud*& noeud, const T& element) {
  if(element < noeud->contenu)
    return enleverGauche(noeud, element);
  else if(element > noeud->contenu)
    return enleverDroite(noeud, element);
  else if(element == noeud->contenu) {
    Noeud* temp = noeud;
    if(noeud->gauche == nullptr) {
      noeud = noeud->droite;
      delete temp;
      return true;
    }
    if(noeud->droite == nullptr) {
      noeud = noeud->gauche;
      delete temp;
      return true;
    }

    // noeud->gauche != nullptr && noeud->droite != nullptr
    noeud->contenu = max(noeud->gauche);
    return enleverGauche(noeud, noeud->contenu);
  }
  return false;
}

template <class T>
bool ArbreAVL<T>::enleverGauche(Noeud*& n, const T& e) {
  bool retour = false;
  if(enlever(n->gauche, e)) {
    n->equilibre--;
    if(n->equilibre == -1)
      return false;
    if(n->equilibre == 0)
      return true;
    assert(n->equilibre == -2);
    retour = n->droite->equilibre != 0;
    if(n->droite->equilibre == 1)
      rotationGaucheDroite(n->droite);
    rotationDroiteGauche(n);
  }
  return retour;
}

template <class T>
bool ArbreAVL<T>::enleverDroite(Noeud*& n, const T& e) {
  bool retour = false;
  if(enlever(n->droite, e)) {
    n->equilibre++;
    if(n->equilibre == 1)
      return false;
    if(n->equilibre == 0)
      return true;
    assert(n->equilibre == 2);
    retour = n->gauche->equilibre != 0;
    if(n->gauche->equilibre == -1)
      rotationDroiteGauche(n->gauche);
    rotationGaucheDroite(n);
  }
  return retour;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const {
  Iterateur iter(*this);
  iter.courant = this->racine;
  while(iter && iter.courant->gauche != nullptr) {
    iter.chemin.empiler(iter.courant);
    iter.courant = iter.courant->gauche;
  }
  return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const {
  return Iterateur(*this);
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T& e) const {
  Iterateur iter = rechercherEgalOuSuivant(e);
  if(!iter) {
    iter.chemin.vider();
    iter.courant = nullptr;
  }
  return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant( const T& e) const {
  Iterateur iter(*this);
  iter.courant = this->racine;
  while(iter && iter.courant->contenu != e) {
    if(e < iter.courant->contenu) {
      iter.chemin.empiler(iter.courant);
      iter.courant = iter.courant->gauche;
    } else
      iter.courant = iter.courant->droite;
  }

  if(!iter && !iter.chemin.vide())
    iter.courant = iter.chemin.depiler();
  return iter;
}

template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent( const T& e) const {
  Iterateur iter(*this);
  iter.courant = this->racine;
  Noeud* temp = nullptr;
  while(iter && iter.courant->contenu != e) {
    if(e < iter.courant->contenu) {
      iter.chemin.empiler(iter.courant);
      iter.courant = iter.courant->gauche;
    } else {
      temp = iter.courant;
      iter.courant = iter.courant->droite;
    }
  }

  if(!iter) {
    if(temp != nullptr)
      iter = rechercher(temp->contenu);
    else
      iter.chemin.vider();
  }

  return iter;
}

template <class T>
const T& ArbreAVL<T>::operator[](const Iterateur& iterateur) const {
  assert(&iterateur.arbre_associe == this);
  assert(iterateur.courant);
  return iterateur.courant->contenu;
}

template <class T>
T& ArbreAVL<T>::operator[](const Iterateur& iterateur) {
  assert(&iterateur.arbre_associe == this);
  assert(iterateur.courant);
  return iterateur.courant->contenu;
}

template <class T>
ArbreAVL<T>& ArbreAVL<T>::operator=(const ArbreAVL& autre) {
  if(this == &autre)
    return *this;
  vider();
  copier(autre.racine, racine);
  return *this;
}

//----------------------- !!! ITERATEUR !!! -----------------------------

  template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL& a) : arbre_associe(a), courant(nullptr) {}

  template <class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur& a)
  : arbre_associe(a.arbre_associe), courant(a.courant), chemin(a.chemin) {}

// Pré-incrément
template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator++() {
  if(!*this)
    return *this;

  courant = courant->droite;
  while(*this) {
    chemin.empiler(courant);
    courant = courant->gauche;
  }
  if(!chemin.vide())
    courant = chemin.depiler();

  return *this;
}

// Post-incrément
template <class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int) {
  Iterateur copie(*this);
  operator++();
  return copie;
}

template <class T>
ArbreAVL<T>::Iterateur::operator bool() const {
  return courant != nullptr;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!() const {
  return courant == nullptr;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur& o) const {
  assert(&arbre_associe == &o.arbre_associe);
  return courant == o.courant;
}

template <class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur& o) const {
  assert(&arbre_associe == &o.arbre_associe);
  return courant != o.courant;
}

template <class T>
const T& ArbreAVL<T>::Iterateur::operator *() const {
  assert(courant != nullptr);
  return courant->contenu;
}

template <class T>
typename ArbreAVL<T>::Iterateur& ArbreAVL<T>::Iterateur::operator = (const Iterateur& autre) {
  assert(&arbre_associe == &autre.arbre_associe);
  courant = autre.courant;
  chemin = autre.chemin;
  return *this;
}

#endif
