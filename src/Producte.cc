#include "Producte.hh"
using namespace std;

/* === CONSTRUCTORS === */


Producte::Producte() {
    id = pes = volum = 0;
}

Producte::Producte(int id, int pes, int volum) {
    this->id = id;
    this->pes = pes;
    this->volum = volum;
}

/* === CONSULTORS === */

int Producte::consultarPes() const {
    return pes;
}

int Producte::consultarVolum() const {
    return volum;
}

/* === ESCRIPTURA === */

void Producte::escriure() const {
    cout << id << ' ' << pes << ' ' << volum << endl;
}