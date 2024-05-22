#include "Cjt_ciutats.hh"

/* === CONSTRUCTORS === */

/**
 * @brief Constructor per defecte de la classe Cjt_ciutats.
 * 
 * \pre Cert.
 * \post Conjunt de ciutats buit.
 */
Cjt_ciutats::Cjt_ciutats() {
    cmap = map<string, Ciutat>();
}

/* === MODIFICADORS === */

/**
 * @brief Afegir nova ciutat al conjunt.
 * 
 * \pre id_city i la ciutat són vàlids.
 * \post El conjunt conté la nova ciutat.
 */
void Cjt_ciutats::afegirCiutat(string id_city, const Ciutat& city) {
    cmap[id_city] = city;
}

/** 
 * @brief Modificar ciutat existent dintre del conjunt.
 * 
 * \pre La ciutat existeix. La ciutat per referència és vàlida.
 * \post Conjunt modificat amb la nova ciutat.
 */
void Cjt_ciutats::modificarCiutat(string id_city, const Ciutat& city) {
    cmap[id_city] = city;
}

/**
 * @brief Afegir un nou producte a la ciutat.
 * 
 * \pre La ciutat existeix. El producte existeix. Oferta/Demanda/Pes/Volum són vàlids.
 * \post La ciutat té el producte al seu inventari i pes_total/volum_total actualitzats.
 */
void Cjt_ciutats::afegirProdACiutat(string id_city, int id_prod, int oferta, int demanda, int pes, int volum) {
    cmap[id_city].afegirProdAlInventari(id_prod, oferta, demanda, pes, volum);
}

/**
 * @brief Comerciar entre ciutats.
 * 
 * \pre Les dues ciutats existeixen.
 * \post Cada ciutat ha donat el seu excés a l'altra ciutat.
 */
void Cjt_ciutats::comerciar(Cjt_ciutats& ciutats, string id_city1, string id_city2, const Cjt_productes& productes) {
    // NOTA: Agafo de referència ciutat1, però no afecta al resultat.
    Ciutat city1 = consultarCiutat(id_city1);
    Ciutat city2 = consultarCiutat(id_city2);
    
    // Si alguna de les dues ciutats no té inventari, no es fa cap comerç.
    if (not city1.teInventari() or not city2.teInventari()) return;

    vector<int> vids1 = city1.consultarProductes();
    vector<int> vids2 = city2.consultarProductes();
    auto it1 = vids1.begin();
    auto it2 = vids2.begin();

    while (it1!=vids1.end() and it2!=vids2.end()) {
        if (*it1==*it2) {
            int dif1 = city1.consultarDiferencia(*it1);
            int dif2 = city2.consultarDiferencia(*it2); 
            
            // Si ambdues ciutats tenen un excés o un dèficit del mateix producte, no es fa res.
            if ((dif1 > 0 and dif2 > 0) or (dif1 < 0 and dif2 < 0)) {
                it1++;
                it2++;
                continue;
            }

            Producte temp_prod = productes.consultarProducte(*it1);
            int pes = temp_prod.consultarPes();
            int volum = temp_prod.consultarVolum();

            int quantiat = determinarDiferencia(dif1, dif2);
            if (dif1<0 and dif2>0) {  // A la ciutat1 li falta, a la ciutat2 li sobra
                city1.modificarOfertaProd(*it1, quantiat, pes, volum);  // Afegir nova oferta de producte
                city2.modificarOfertaProd(*it1, -quantiat, pes, volum);  // Treure els productes comerciats
            }
            else if (dif1>0 and dif2<0) {  // A la ciutat1 li sobra, a la ciutat2 li falta
                city1.modificarOfertaProd(*it1, -quantiat, pes, volum);  // Treure els productes comerciats
                city2.modificarOfertaProd(*it1, quantiat, pes, volum);  // Afegir nova oferta de producte
            }
            ciutats.modificarCiutat(id_city1, city1);
            ciutats.modificarCiutat(id_city2, city2);
            it1++;
            it2++;
        }
        else if (*it1<*it2) {
            it1++;
        }
        else {
            it2++;
        }
    }
}

/**
 * @brief Eliminar totes les ciutats registrades.
 * 
 * \pre Cert.
 * \post Mapa de ciutats buit.
 */
void Cjt_ciutats::eliminarCiutats() {
    cmap.clear();
}

/**
 * @brief Eliminar tots els productes d'una ciutat.
 * 
 * \pre Cert.
 * \post La ciutat no té cap producte al seu inventari. Pes i volum total a 0.
 */
void Cjt_ciutats::eliminarTotsProdDeCiutat(string id_city) {
    Ciutat temp_city = consultarCiutat(id_city);
    temp_city.eliminarTotsProd();
    modificarCiutat(id_city, temp_city);
}

/* === CONSULTORS === */

/**
 * @brief Comprovar si la ciutat amb l'ID especificada existeix.
 * 
 * \pre id_city és un valor qualsevol.
 * \post Retorna true si la ciutat existeix, en cas contrari retorna false.
 */
bool Cjt_ciutats::existeixCiutat(string id_city) const {
    auto it = cmap.find(id_city);
    return it!=cmap.end();
}

/**
 * @brief Retorna la ciutat especificada.
 * 
 * \pre La ciutat existeix.
 * \post Retorna una còpia de la ciutat.
 */
Ciutat Cjt_ciutats::consultarCiutat(string id_city) const {
    auto it = cmap.find(id_city);
    return it->second;
}

/* === PRIVAT === */

/**
 * @brief Determinar la quantitat màxima de producte que es pot intercanviar entre dues ciutats.
 * 
 * \pre c1 i c2 són la diferència (positiva o negativa) d'un determinat producte de les dues ciutats.
 * \post Retorna la quantitat màxima que es pot intercanviar.
 */
int Cjt_ciutats::determinarDiferencia(int c1, int c2) const {
    return min(abs(c1), abs(c2));
}