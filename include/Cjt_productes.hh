#ifndef CONJ_PROD_HH
#define CONJ_PROD_HH

#include "Producte.hh"
#include <vector>

class Cjt_productes {

private:
    int quant_prod;
    vector<Producte> vprod;

public:
    /* CONSTRUCTORS */
    Cjt_productes();
    Cjt_productes(int mida);

    /* MODIFICADORS */
    void afegirProducte(double pes, double volumen);
    void modificarProducte(int id, const Producte& prod);

    /* CONSULTORS */
    bool existeixProducte(int id) const;
    int consultarQuantitatProd() const;
    Producte consultarProducte(int id) const;
};

#endif