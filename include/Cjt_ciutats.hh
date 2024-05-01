#ifndef CONJ_CITY_HH
#define CONJ_CITY_HH

#include "Ciutat.hh"
#include <map>

class Cjt_ciutats {

private:
    map<string, Ciutat> cmap;

public:
    /* CONSTRUCTORS */
    Cjt_ciutats();

    /* MODIFICADORS */
    void modificarCiutat(string id_city, const Ciutat& city);
    void afegirProdACiutat(string id_city, int id_prod, int oferta, int demanda, double pes, double volum);

    /* CONSULTORS */
    bool existeixCiutat(string id_city);
};

#endif