
#ifndef ARBREMAP_H
#define ARBREMAP_H

#include "arbreavl.h"

template <class K, class V>
class ArbreMap {
  struct Entree;

 public:
  class Iterateur {
   public:
    Iterateur(const ArbreMap& a) : iter(a.entrees.debut()) {}
    Iterateur(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {}

    operator bool() const;
    bool operator!() const;
    Iterateur& operator++();
    Iterateur operator++(int);
    Iterateur& operator = (const Iterateur& o);

    const K& cle() const;
    const V& valeur() const;
    V& valeur();

   private:
    typename ArbreAVL<Entree>::Iterateur iter;
  };

/*
//Maj
  class IterateurConst {
   public:
    IterateurConst(const ArbreMap& a) : iter(a.entrees.debut()) {}
    IterateurConst(typename ArbreAVL<Entree>::IterateurConst i) : iter(i) {}

    operator bool() const;
    bool operator!() const;
    IterateurConst& operator++();
    IterateurConst operator++(int);
    IterateurConst& operator = (const IterateurConst& o);

    const K& cle() const;
    const V& valeur() const;
    V& valeur();

   private:
    typename ArbreAVL<Entree>::IterateurConst iter;
  };
//majFin
*/
  bool contient(const K&) const;
  void enlever(const K&);
  void vider();
  bool vide() const;
  const V& operator[](const K&) const;
  V& operator[](const K&);

  Iterateur debut() const;
  Iterateur debut();//Math
  Iterateur fin() const;
  Iterateur rechercher(const K& cle) const;
  Iterateur rechercherEgalOuSuivant(const K& cle) const;
  Iterateur rechercherEgalOuPrecedent(const K& cle) const;

 private:
  struct Entree {
    K cle;
    V valeur;

    Entree(const K& c) : cle(c), valeur() {}

    bool operator < (const Entree& other) const {
      return cle < other.cle;
    }
    bool operator == (const Entree& other) const {
      return cle == other.cle;
    }
    bool operator != (const Entree& other) const {
      return ! operator==(other);
    }
  };

  ArbreAVL<Entree> entrees;
};

template <class K, class V>
void ArbreMap<K, V>::vider() {
  entrees.vider();
}

template <class K, class V>
bool ArbreMap<K, V>::vide() const {
  return entrees.vide();
}

template <class K, class V>
void ArbreMap<K, V>::enlever(const K& c) {
  entrees.enlever(Entree(c));
}

template <class K, class V>
bool ArbreMap<K, V>::contient(const K& c) const {
  return entrees.contient(Entree(c));
}

template <class K, class V>
const V& ArbreMap<K,V>::operator[] (const K& c) const {
typename ArbreAVL<Entree>::Iterateur iter=entrees.rechercher(c); 
return entrees[iter].valeur;
}

/*
template <class K, class V>
const V& ArbreMap<K, V>::operator[](const K& c) const {
  return entrees[entrees.rechercher(Entree(c))].valeur;
}
*/

template <class K, class V>
V& ArbreMap<K, V>::operator[](const K& c) {
  auto iter = entrees.rechercher(Entree(c));
  if(!iter) {
    entrees.inserer(Entree(c));
    iter = entrees.rechercher(Entree(c));
  }
  return entrees[iter].valeur;
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::debut() const {
  return Iterateur(entrees.debut());
}

//maj
template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::debut() {
  return Iterateur(entrees.debut());
}
//majFin

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::fin() const {
  return Iterateur(entrees.fin());
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercher(const K& cle) const {
  return Iterateur(entrees.rechercher(Entree(cle)));
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuSuivant(const K& cle) const {
  return Iterateur(entrees.rechercherEgalOuSuivant(Entree(cle)));
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur ArbreMap<K,V>::rechercherEgalOuPrecedent(const K& cle) const {
  return Iterateur(entrees.rechercherEgalOuPrecedent(Entree(cle)));
}

//----------------------- !!! ITERATEUR !!! -----------------------------

template <class K, class V>
ArbreMap<K, V>::Iterateur::operator bool() const {
  return iter;
}

template <class K, class V>
bool ArbreMap<K, V>::Iterateur::operator!() const {
  return !iter;
}

template <class K, class V>
typename ArbreMap<K, V>::Iterateur& ArbreMap<K, V>::Iterateur::operator++() {
  ++iter;
  return *this;
}

template <class K, class V>
typename ArbreMap<K, V>::Iterateur ArbreMap<K, V>::Iterateur::operator++(int) {
  auto it{*this};
  ++iter;
  return it;
}

template <class K, class V>
typename ArbreMap<K,V>::Iterateur& ArbreMap<K, V>::Iterateur::operator = (const Iterateur& o) {
  if(this == &o)
    return *this;
  iter = o.iter;
  return *this;
}

template <class K, class V>
const K& ArbreMap<K, V>::Iterateur::cle() const {
  return (*iter).cle;
}

template <class K, class V>
const V& ArbreMap<K, V>::Iterateur::valeur() const {
  return (*iter).valeur;
}

template <class K, class V>
V& ArbreMap<K, V>::Iterateur::valeur() {
  const V& e = (*iter).valeur;
  return const_cast<V&>(e);
}

#endif
