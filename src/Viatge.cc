#include "Viatge.hh"
using namespace std;

Viatge::Viatge() {
    ruta = list<string>();
    quant_comerciat = 0;
    ordre = "";
}

void Viatge::afegirCiutat(string id_city, char dir) {
    ruta.push_back(id_city);
    ordre += dir;
}

void Viatge::eliminarCiutat() {
    if (not ruta.empty()) ruta.pop_front();
}

void Viatge::actQuant(int quant) {
    quant_comerciat += quant;
}

list<string> Viatge::consultarRuta() const {
    return ruta;
}

string Viatge::consultarOrdre() const {
    return ordre;
}

string Viatge::consultarProxCiutat() {
    eliminarCiutat();
    if (not ruta.empty()) {
        return ruta.front();
    }
    return "";  // En aquest cas ja no hi ha ciutats per visitar
}

int Viatge::consultarQuant() const {
    return quant_comerciat;
}

string Viatge::consultarUltimaCiutat() const {
    return ruta.back();
}