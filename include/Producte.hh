#ifndef PRODUCTE_HH
#define PRODUCTE_HH

#include <iostream>

class Producte {

private:
    int id;
    double pes;
    double volum;

public:
    /* CONSTRUCTORS */
    Producte();
    Producte(int id, double pes, double volumen);

    /* CONSULTORS */
    int consultarId() const;
    double consultarPes() const;
    double consultarVolum() const;

    /* MODIFICADORS */
    // No es demanen en la practica

    /* ESCRIPTURA */
    void escriure() const;
};

#endif