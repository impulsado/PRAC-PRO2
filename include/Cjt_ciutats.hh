#ifndef CONJ_CITY_HH
#define CONJ_CITY_HH

#include "Ciutat.hh"
#include "Cjt_productes.hh"
#include <map>

class Cjt_ciutats {

private:
    map<string, Ciutat> cmap;
    int determinarDiferencia(int i, int j) const;

public:
    /* CONSTRUCTORS */
    Cjt_ciutats();

    /* MODIFICADORS */
    void modificarCiutat(string id_city, const Ciutat& city);
    void afegirProdACiutat(string id_city, int id_prod, int oferta, int demanda, double pes, double volum);
    void comerciar(string id_city1, string id_city2, const Cjt_productes& productes);

    /* CONSULTORS */
    bool existeixCiutat(string id_city) const;
    Ciutat consultarCiutat(string id_city) const;
};

#endif