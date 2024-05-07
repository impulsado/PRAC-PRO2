#ifndef PRODUCTE_HH
#define PRODUCTE_HH

#include <iostream>

class Producte {

private:
    int id;
    int pes;
    int volum;

public:
    /* CONSTRUCTORS */
    Producte();
    Producte(int id, int pes, int volumen);

    /* CONSULTORS */
    int consultarId() const;
    int consultarPes() const;
    int consultarVolum() const;

    /* MODIFICADORS */
    // No es demanen en la practica

    /* ESCRIPTURA */
    void escriure() const;
};

#endif