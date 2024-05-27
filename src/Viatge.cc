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

void Viatge::millorViatge(Viatge& viatge_esquerra, Viatge& viatge_dreta) {
    // 1. No hi ha viatges a l'esquerra ni a la dreta
    if (viatge_esquerra.quant_comerciat==0 and viatge_dreta.quant_comerciat==0) return;
    // 2. No hi ha comerç a l'esquerra
    else if (viatge_esquerra.quant_comerciat==0) {
        actViatge(viatge_dreta);
        return;
    }
    // 3. No hi ha comerç a la dreta
    else if (viatge_dreta.quant_comerciat==0) {
        actViatge(viatge_esquerra);
        return;
    }
    // 4. Hi ha comerç a ambdues bandes
    // 4.1. La quantitat de la esquerra és més gran
    else if (viatge_esquerra.quant_comerciat>viatge_dreta.quant_comerciat) {
        actViatge(viatge_esquerra);
        return;
    }
    // 4.1 Tenen la mateixa quantitat
    else if (viatge_esquerra.quant_comerciat==viatge_dreta.quant_comerciat) {
        // 4.1.1 La distància de la esquerra és més petita o igual
        if (viatge_esquerra.distancia <= viatge_dreta.distancia) {
            actViatge(viatge_esquerra);
            return;
        }
    }
    // 4.2. La quantitat de la dreta és més gran
    actViatge(viatge_dreta);
    return;
}