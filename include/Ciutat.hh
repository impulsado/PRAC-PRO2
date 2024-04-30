#ifndef CIUTAT_HH
#define CIUTAT_HH

#include "PRO2Excepcio.hh"
#include "Producte.hh"
#include <iostream>
#include <string>
#include <map>

class Ciutat {

private:
    string id;
    map<int, pair<int,int>> inventari;
    // first = oferta
    // second = demanda
    double pes_total;
    double volum_total;

    bool teInventari() const;

public:
    /* CONSTRUCTORS */
    Ciutat();
    // - [ ] Com es l'entrada de ciutats?

    /* CONSULTORS */
    string consultarId() const;
    bool teProducte(int id) const;
    int consultarOferta(int id) const;
    int consultarDemanda(int id) const;

    /* MODIFICADORS */
    void afegirProdAlInventari(int id, double pes, double volum);
    void modificarProdDelInventari(int id, double pes, double volum);
    void eliminarProdDelInventari(int id, double pes, double volum);

    /* ESCRIPTURA */
    void escriure() const;
};

#endif