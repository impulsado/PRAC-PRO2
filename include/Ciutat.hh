#ifndef CIUTAT_HH
#define CIUTAT_HH

#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <vector>
using namespace std;

class Ciutat {

private:
    string id;
    std::map<int, pair< pair<int,int> ,int>> inventari;
    // first -> id producte
    // second.first.first -> oferta
    // second.first.second -> demanda
    // second.second -> necessitat
    int pes_total;
    int volum_total;


public:
    /* CONSTRUCTORS */
    Ciutat();
    Ciutat(string id_city);

    /* CONSULTORS */
    bool teInventari() const;
    bool teProducte(int id_prod) const;
    int consultarOferta(int id_prod) const;
    int consultarDemanda(int id_prod) const;
    int consultarDiferencia(int id_prod) const;
    int consultarPesTotal() const;
    int consultarVolumTotal() const;
    vector<int> consultarProductes() const;

    /* MODIFICADORS */
    void afegirProdAlInventari(int id_prod, int oferta, int demanda, int pes, int volum);
    void modificarProdDelInventari(int id_prod, int oferta, int demanda, int pes, int volum);
    void modificarOfertaProd(int id_prod, int oferta, int pes, int volum);
    void modificarDemandaProd(int id_prod, int quantitat, int pes, int volum);
    void eliminarProdDelInventari(int id_prod, int pes, int volum);

    /* ESCRIPTURA */
    void escriure() const;
};

#endif