#ifndef CONJ_PROD_HH
#define CONJ_PROD_HH

#include "Ciutat.hh"
#include <map>

class Cjt_ciutats {

private:
    map<string, Ciutat> cmap;

public:
    /* CONSTRUCTORS */
    Cjt_ciutats();

    /* MODIFICADORS */
    void modificarCiutat(string id, const Ciutat& city);

    /* CONSULTORS */
    bool existeixCiutat(string id);
};

#endif