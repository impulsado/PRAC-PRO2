#ifndef CIUTAT_HH
#define CIUTAT_HH

#include "Producte.hh"
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
using namespace std;

class Ciutat {

private:
    string id;
    map<int, pair< pair<int,int> ,int>> inventari;
    // first.first -> oferta
    // first.second -> demanda
    // second -> necessitat
    double pes_total;
    double volum_total;


public:
    /* CONSTRUCTORS */
    Ciutat();
    // - [ ] Com es l'entrada de ciutats?

    /* CONSULTORS */
    bool teInventari() const;
    bool teProducte(int id) const;
    int consultarOferta(int id) const;
    int consultarDemanda(int id) const;
    int consultarDiferencia(int id) const;
    double consultarPesTotal() const;
    double consultarVolumTotal() const;
    vector<int> consultarProductes() const;

    /* MODIFICADORS */
    void afegirProdAlInventari(int id, int oferta, int demanda, double pes, double volum);
    void modificarProdDelInventari(int id, int oferta, int demanda, double pes, double volum);
    void modificarOfertaProd(int id, int oferta, double pes, double volum);
    void eliminarProdDelInventari(int id, double pes, double volum);

    /* ESCRIPTURA */
    void escriure() const;
};

#endif