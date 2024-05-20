    #include "Viatge.hh"
    using namespace std;

    Viatge::Viatge() {
        quant_comerciat = 0;
        ordre = "";
        distancia = 0;
        tot_comerciat = false;
    }

    void Viatge::afegirCiutat(string id_city, char dir, Cjt_ciutats& conjunt) {
        ultima_ciutat = id_city;
        ordre += dir;
        distancia++;
        snapshot = conjunt;  // ?? Això ho haig de fer personalitzat o el per defecte serveix ??
    }

    void Viatge::actQuant(int quant) {
        quant_comerciat += quant;
    }

    void Viatge::actTotComerciat() {
        tot_comerciat = true;
    }

    string Viatge::consultarOrdre() const {
        return ordre;
    }

    int Viatge::consultarQuant() const {
        return quant_comerciat;
    }

    int Viatge::consultarDist() const {
        return distancia;
    }

    string Viatge::consultarUltimaCiutat() const {
        return ultima_ciutat;
    }

    Cjt_ciutats Viatge::consultarSnapshot() const {
        return snapshot;
    }

    bool Viatge::estaTotComerciat() const {
        return tot_comerciat;
    }