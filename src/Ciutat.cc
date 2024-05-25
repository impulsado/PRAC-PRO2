#include "Ciutat.hh"
using namespace std;

/* === CONSTRUCTORS === */

Ciutat::Ciutat() {
    id = "0";
    pes_total = 0;
    volum_total = 0;
}

Ciutat::Ciutat(string id_city) {
    id = id_city;
    pes_total = 0;
    volum_total = 0;
}

/* === MODIFICADORS === */

void Ciutat::afegirProdAlInventari(int id_prod, int oferta, int demanda, int pes, int volum) {
    inventari[id_prod].first.first = oferta;
    inventari[id_prod].first.second = demanda;
    inventari[id_prod].second = oferta-demanda;  // Necessitat del producte
    pes_total += oferta*pes;
    volum_total += oferta*volum;
}

void Ciutat::modificarProdDelInventari(int id, int oferta, int demanda, int pes, int volum) {
    auto it = inventari.find(id);
    
    if (it->second.first.first!=oferta) {  // No diferenciem entre casos perquè si la diferència és negativa, al fer la suma, ja farà resta.
        int diferencia = oferta-(it->second.first.first);
        pes_total += diferencia*pes;
        volum_total += diferencia*volum;
        it->second.first.first = oferta;
    }
    it->second.first.second = demanda;

    it->second.second = oferta-demanda;  // Actualitzar la necessitat del producte
}


void Ciutat::modificarOfertaProd(int id_prod, int quantitat, int pes, int volum) {
    auto it = inventari.find(id_prod);
    
    pes_total += quantitat*pes;
    volum_total += quantitat*volum;
    
    it->second.first.first += quantitat;  // Afegir la nova quantitat d'oferta
    it->second.second += quantitat;  // Actualitzar la necessitat del producte
}

void Ciutat::eliminarProdDelInventari(int id_prod, int pes, int volum) {
    int oferta = inventari[id_prod].first.first;
    
    pes_total -= oferta*pes;
    volum_total -= oferta*volum;
    inventari.erase(id_prod);
}

void Ciutat::eliminarTotsProd() {
    inventari.clear();
    pes_total = 0;
    volum_total = 0;
}

void Ciutat::comerciar(Ciutat& other, const Cjt_productes& productes) {
    if (not this->teInventari() or not other.teInventari()) return;

    auto it1 = this->inventari.begin();
    auto it2 = other.inventari.begin();

    while (it1!=this->inventari.end() and it2!=other.inventari.end()) {
        int prod_id1 = it1->first;
        int prod_id2 = it2->first;

        if (prod_id1 == prod_id2) {
            int dif1 = it1->second.second;
            int dif2 = it2->second.second;
            
            // A la ciutat1 li falta, a la ciutat2 li sobra
            if (dif1<0 and dif2>0) {  
                pair<int,int> pesVol = productes.consultarProducte(prod_id1);
                int quantiat = min(abs(dif1), abs(dif2));
                
                it1->second.first.first += quantiat;
                it1->second.second += quantiat;
                this->pes_total += quantiat*pesVol.first;
                this->volum_total += quantiat*pesVol.second;
                
                it2->second.first.first -= quantiat;
                it2->second.second -= quantiat;
                other.pes_total -= quantiat*pesVol.first;
                other.volum_total -= quantiat*pesVol.second;
            }
            // A la ciutat1 li sobra, a la ciutat2 li falta
            else if (dif1 > 0 and dif2 < 0) {  
                pair<int,int> pesVol = productes.consultarProducte(prod_id1);
                int quantiat = min(abs(dif1), abs(dif2));
                
                it1->second.first.first -= quantiat;
                it1->second.second -= quantiat;
                this->pes_total -= quantiat*pesVol.first;
                this->volum_total -= quantiat*pesVol.second;
                
                it2->second.first.first += quantiat;
                it2->second.second += quantiat;
                other.pes_total += quantiat*pesVol.first;
                other.volum_total += quantiat*pesVol.second;
            }
            it1++;
            it2++;
        }
        else if (prod_id1<prod_id2) it1 = this->inventari.lower_bound(prod_id2);
        else it2 = other.inventari.lower_bound(prod_id1);
    }
}

/* === CONSULTORS === */

bool Ciutat::teInventari() const {
    return !inventari.empty();
}

bool Ciutat::teProducte(int id_prod) const {
    return inventari.find(id_prod)!=inventari.end();
}

int Ciutat::consultarOferta(int id_prod) const {
    auto it = inventari.find(id_prod);
    return it->second.first.first;
}

int Ciutat::consultarDemanda(int id_prod) const {
    auto it = inventari.find(id_prod);
    return it->second.first.second;
}

int Ciutat::consultarDiferencia(int id_prod) const { 
    auto it = inventari.find(id_prod);
    return it->second.second;
}

int Ciutat::consultarPesTotal() const {
    return pes_total;
}

int Ciutat::consultarVolumTotal() const {
    return volum_total;
}

/* === ESCRIPTURA === */

void Ciutat::escriure() const {
    if (not teInventari()) {
        cout << "0 0" << endl;
        return;
    }
    
    for (auto it = inventari.begin(); it != inventari.end(); it++) {
        cout << it->first << ' ' << it->second.first.first << ' ' << it->second.first.second << endl;
    }
    cout << pes_total << ' ' << volum_total << endl;
}