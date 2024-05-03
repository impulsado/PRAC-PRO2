#include <exception>
#include "Cjt_ciutats.hh"

/* CONSTANTS */
const char *ER1 = "Error: No existeix ciutat";

Cjt_ciutats::Cjt_ciutats() {
    cmap = map<string,Ciutat>();
}

/**
 * \pre Ciutat existeix i la ciutat per referència es vàlida
 * \post 
 */
void Cjt_ciutats::modificarCiutat(string id_city, const Ciutat& city) {
    cmap[id_city] = city;
}

void Cjt_ciutats::afegirProdACiutat(string id_city, int id_prod, int oferta, int demanda, double pes, double volum) {
    cmap[id_city].afegirProdAlInventari(id_prod,oferta,demanda,pes,volum);
}

/**
 * \pre Les dues ciutats existeixen 
 */
void Cjt_ciutats::comerciar(string id_city1, string id_city2, const Cjt_productes& productes) {
    Ciutat city1 = consultarCiutat(id_city1);
    Ciutat city2 = consultarCiutat(id_city2);

    vector<int> vids = city1.consultarProductes();
    for (int i = 0; i<vids.size(); i++) {
        if (not city2.teProducte(vids[i])) continue;  // Ciutat2 no té el producte
        int dif1 = city1.consultarDiferencia(vids[i]); 
        int dif2 = city2.consultarDiferencia(vids[i]); 

        if (dif1>0 and dif2>0) continue;  // Les dues ciutats tenen el producte de sobres
        else if (dif1<0 and dif2>0) {  // A la ciutat2 li sobra pero a la ciutat1 li falta
            int quantiat = determinarDiferencia(dif1,dif2);
            Producte temp_prod = productes.consultarProducte(vids[i]);
            double pes = temp_prod.consultarPes();
            double volum = temp_prod.consultarVolum();
            city1.modificarOfertaProd(vids[i],quantiat,pes,volum);  // Afegir nova oferta de producte
            city2.modificarOfertaProd(vids[i],-quantiat,pes,volum);  // Treure els productes comerciats
        }
        else if (dif1>0 and dif2<0) {  // A la ciutat1 li sobra pero a la ciutat2 li falta
            int quantiat = determinarDiferencia(dif1,dif2);
            Producte temp_prod = productes.consultarProducte(vids[i]);
            double pes = temp_prod.consultarPes();
            double volum = temp_prod.consultarVolum();
            city1.modificarOfertaProd(vids[i],-quantiat,pes,volum);  // Treure els productes comerciats 
            city2.modificarOfertaProd(vids[i],quantiat,pes,volum);  // Afegir nova oferta de producte
        }
    }
}

// ?? No sé si ordre afecta en aquest cas ??
bool Cjt_ciutats::existeixCiutat(string id_city) const {
    auto it = cmap.find(id_city);
    return it!=cmap.end();
}

Ciutat Cjt_ciutats::consultarCiutat(string id_city) const {
    auto it = cmap.find(id_city);
    if (it==cmap.end()) throw PRO2Excepcio(ER1);
    return it->second;
}

int Cjt_ciutats::determinarDiferencia(int c1, int c2) const {
    if (abs(c1)>abs(c2)) return abs(c2);
    else if (abs(c1)<abs(c2)) return abs(c1);
}