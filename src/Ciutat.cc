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
    // Les ciutats no tenen inventari (Optimització)
    if (not this->teInventari() or not other.teInventari()) return;

    // Iteradors per recórrer els inventaris
    auto it1 = this->inventari.begin();
    auto it2 = other.inventari.begin();

    // Comerç entre les ciutats
    while (it1!=this->inventari.end() and it2!=other.inventari.end()) {
        // Consultar els productes
        int prod_id1 = it1->first;
        int prod_id2 = it2->first;

        // Si els productes són iguals 
        if (prod_id1 == prod_id2) {
            // Consultar les diferències del producte de cada ciutat
            int dif1 = it1->second.second;
            int dif2 = it2->second.second;
            
            // A la ciutat1 li falta, a la ciutat2 li sobra
            if (dif1<0 and dif2>0) {
                // Consultar el pes i volum del producte
                pair<int,int> pesVol = productes.consultarProducte(prod_id1);
                
                // Determinar la màxima quantitat a intercanviar
                int quantiat = min(abs(dif1), abs(dif2));
                
                // Actualitzar l'inventari de la ciutat1
                it1->second.first.first += quantiat;  // Afegir la nova quantitat d'oferta
                it1->second.second += quantiat;  // Actualitzar la necessitat del producte
                this->pes_total += quantiat*pesVol.first;  // Actualitzar el pes total
                this->volum_total += quantiat*pesVol.second;  // Actualitzar el volum total
                
                // Actualitzar l'inventari de la ciutat2
                it2->second.first.first -= quantiat;  // Treure la quantitat venuda
                it2->second.second -= quantiat;  // Actualitzar la necessitat del producte
                other.pes_total -= quantiat*pesVol.first;  // Actualitzar el pes total
                other.volum_total -= quantiat*pesVol.second;  // Actualitzar el volum total
            }
            // A la ciutat1 li sobra, a la ciutat2 li falta
            else if (dif1 > 0 and dif2 < 0) {
                // Consultar el pes i volum del producte
                pair<int,int> pesVol = productes.consultarProducte(prod_id1);
                
                // Determinar la màxima quantitat a intercanviar
                int quantiat = min(abs(dif1), abs(dif2));
                
                // Actualitzar l'inventari de la ciutat1
                it1->second.first.first -= quantiat;  // Treure la quantitat venuda
                it1->second.second -= quantiat;  // Actualitzar la necessitat del producte
                this->pes_total -= quantiat*pesVol.first;  // Actualitzar el pes total
                this->volum_total -= quantiat*pesVol.second;  // Actualitzar el volum total
                
                // Actualitzar l'inventari de la ciutat2
                it2->second.first.first += quantiat;  // Afegir la nova quantitat d'oferta
                it2->second.second += quantiat;  // Actualitzar la necessitat del producte
                other.pes_total += quantiat*pesVol.first;  // Actualitzar el pes total
                other.volum_total += quantiat*pesVol.second;  // Actualitzar el volum total
            }
            // Avançar als següents productes
            it1++;
            it2++;
        }
        else if (prod_id1<prod_id2) {
            // Avançar els productes de la ciutat1 fins arribar a un producte comú amb la ciutat2
            it1 = this->inventari.lower_bound(prod_id2);
        }
        else {
            // Avançar els productes de la ciutat2 fins arribar a un producte comú amb la ciutat1
            it2 = other.inventari.lower_bound(prod_id1);
        }
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