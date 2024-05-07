#include <exception>
#include "Cjt_ciutats.hh"

/* CONSTANTS */
const char *ER1 = "Error: No existeix ciutat";

Cjt_ciutats::Cjt_ciutats() {
    cmap = map<string,Ciutat>();
}

/** 
 * @brief Modificar ciutat existent dintre del conjunt.
 * 
 * \pre Ciutat existeix. La ciutat per referència és vàlida.
 * \post Conjunt modificat amb la nova ciutat.
 */
void Cjt_ciutats::modificarCiutat(string id_city, const Ciutat& city) {
    cmap[id_city] = city;
}

/**
 * @brief Afegir un nou producte a la ciutat.
 * 
 * \todo La ciutat no té el producte?
 * \pre La ciutat existeix. El producte existeix. Oferta/Demanda/Pes/Volum son vàlids.
 * \post La ciutat té el producte al seu inventari i pes_total/volum_total actualitzats.
 */
void Cjt_ciutats::afegirProdACiutat(string id_city, int id_prod, int oferta, int demanda, int pes, int volum) {
    cmap[id_city].afegirProdAlInventari(id_prod,oferta,demanda,pes,volum);
}

/**
 * @brief Comerciar entre ciutats.
 * 
 * \pre Les dues ciutats existeixen.
 * \post Cada ciutat ha donat el seu excedent a l'altra ciutat.
 */
void Cjt_ciutats::comerciar(string id_city1, string id_city2, const Cjt_productes& productes) {
    // NOTA: Agafo de referencia ciutat1, però no afecta al resultat.
    Ciutat city1 = consultarCiutat(id_city1);
    Ciutat city2 = consultarCiutat(id_city2);
    if (not city1.teInventari()) {cout << "Error: La ciutat1 no té inventari" << endl; return;}
    if (not city2.teInventari()) {cout << "Error: La ciutat2 no té inventari" << endl; return;}

    vector<int> vids = city1.consultarProductes();
    for (int i = 0; i<vids.size(); i++) {
        // Ciutat2 no té el producte
        if (not city2.teProducte(vids[i])) continue;
        
        int dif1 = city1.consultarDiferencia(vids[i]); 
        int dif2 = city2.consultarDiferencia(vids[i]); 

        // No tenen quantitats vàlides per a realitzar intercanvi
        if ((dif1>0 and dif2>0) or (dif1<0 and dif2<0)) continue;

        Producte temp_prod = productes.consultarProducte(vids[i]);
        int pes = temp_prod.consultarPes();
        int volum = temp_prod.consultarVolum();
        
        int quantiat = determinarDiferencia(dif1,dif2);
        if (dif1<0 and dif2>0) {  // A la ciutat1 li falta, a la ciutat 2 li sobra
            city1.modificarOfertaProd(vids[i],quantiat,pes,volum);  // Afegir nova oferta de producte
            city2.modificarOfertaProd(vids[i],-quantiat,pes,volum);  // Treure els productes comerciats
        }
        else if (dif1>0 and dif2<0) {  // A la ciuta1 li sobra, a la ciutat2 li falta
            city1.modificarOfertaProd(vids[i],-quantiat,pes,volum);  // Treure els productes comerciats
            city2.modificarOfertaProd(vids[i],+quantiat,pes,volum);  // Afegir nova oferta de producte
        }
    }
}

/**
 * @brief Comprovar si la ciutat amb la id especificada existeix.
 * 
 * \pre id_city és un valor qualsevol.
 * \post Retorna "true" si la ciutat existeix. Altrament "false".
 */
bool Cjt_ciutats::existeixCiutat(string id_city) const {
    auto it = cmap.find(id_city);
    return it!=cmap.end();
}

/**
 * @brief Retornar ciutat especificada.
 * 
 * \pre La ciutat existeix.
 * \post Retorna còpia de la ciutat.
 */
Ciutat Cjt_ciutats::consultarCiutat(string id_city) const {
    auto it = cmap.find(id_city);
    return it->second;
}

/**
 * @brief Determinar la quantitat màxima de producte que es pot intercanviar entre dues ciutats.
 * 
 * \pre c1,c2 es la excedencia (positiva o negatriva) d'un determinat producte de les dues ciutats.
 * \post Retorna la quantiat que maxima que es pot intercanviar.
 */
int Cjt_ciutats::determinarDiferencia(int c1, int c2) const {
    return min(abs(c1), abs(c2));
}