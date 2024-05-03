#ifndef CIUTAT_HH
#define CIUTAT_HH

#include "PRO2Excepcio.hh"
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