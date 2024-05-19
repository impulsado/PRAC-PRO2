#ifndef CONJ_CITY_HH
#define CONJ_CITY_HH

#include "Cjt_productes.hh"
#include "Ciutat.hh"
#include <map>

class Cjt_ciutats {

private:
    std::map<string, Ciutat> cmap;
    int determinarDiferencia(int i, int j) const;

public:
    /* CONSTRUCTORS */
    Cjt_ciutats();

    /* MODIFICADORS */
    void afegirCiutat(string id_city, const Ciutat& city);
    void modificarCiutat(string id_city, const Ciutat& city);
    void afegirProdACiutat(string id_city, int id_prod, int oferta, int demanda, int pes, int volum);
    void comerciar(Cjt_ciutats& ciutats, string id_city1, string id_city2, const Cjt_productes& productes);
    void eliminarCiutats();
    void eliminarTotsProdDeCiutat(string id_city);

    /* CONSULTORS */
    bool existeixCiutat(string id_city) const;
    Ciutat consultarCiutat(string id_city) const;
};

#endif