/**
 * @file Viatge.cc
 * @brief Implementació de la classe Viatge
 */
#include "Viatge.hh"
using namespace std;

/* === CONSTRUCTORS === */

Viatge::Viatge() {
    ruta = list<string>();
    quant_comerciat = 0;
    distancia = 0;
}

/* === MODIFICADORS === */

void Viatge::afegirCiutat(string id_city) {
    ruta.push_back(id_city);
    distancia++;
}

void Viatge::actQuant(int quant) {
    quant_comerciat += quant;
}

void Viatge::actViatge(Viatge &v) {
    quant_comerciat += v.quant_comerciat;
    distancia += v.distancia;
    // Afegir ciutats del subviatge
    // NOTA: Aquesta funció simplement modifica els punters en comptes d'anar eliminant i afegint.
    ruta.splice(ruta.end(), v.ruta);
}

/* === CONSULTORS === */

list<string> Viatge::consultarRuta() const {
    return ruta;
}

int Viatge::consultarQuant() const {
    return quant_comerciat;
}

int Viatge::consultarDist() const {
    return distancia;
}

string Viatge::consultarUltimaCiutat() const {
    return ruta.back();
}