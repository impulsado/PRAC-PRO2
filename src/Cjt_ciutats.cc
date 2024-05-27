/**
 * @file Cjt_ciutats.cc
 * @brief Implementació de la classe Cjt_ciutats
 */
#include "Cjt_ciutats.hh"
using namespace std;

/* === CONSTRUCTORS === */

Cjt_ciutats::Cjt_ciutats() {
    cmap = map<string, Ciutat>();
}

/* === MODIFICADORS === */

void Cjt_ciutats::afegirCiutat(const string& id_city, const Ciutat& city) {
    cmap[id_city] = city;
}

void Cjt_ciutats::modificarCiutat(const string& id_city, const Ciutat& city) {
    cmap[id_city] = city;
}

void Cjt_ciutats::afegirProdACiutat(const string& id_city, int id_prod, int oferta, int demanda, int pes, int volum) {
    cmap[id_city].afegirProdAlInventari(id_prod, oferta, demanda, pes, volum);
}

void Cjt_ciutats::comerciar(string& id_city1, string& id_city2, const Cjt_productes& productes) {
    cmap[id_city1].comerciar(cmap[id_city2], productes);
}

void Cjt_ciutats::redistribuir(const BinTree<string>& Cuenca, const Cjt_productes& productes) {
    // === Base Case
    if (Cuenca.left().empty() or Cuenca.right().empty()) return;

    // === General Case
    string id_city = Cuenca.value();
    // Comerciar Esquerra
    string id_left = Cuenca.left().value();
    cmap[id_city].comerciar(cmap[id_left], productes);
    // Comerciar Dreta
    string id_right = Cuenca.right().value();
    cmap[id_city].comerciar(cmap[id_right], productes);
    
    // Recursivitat
    redistribuir(Cuenca.left(), productes);
    redistribuir(Cuenca.right(), productes);
    
    return;
}

void Cjt_ciutats::realitzar_viatge(const Cjt_productes& productes, const Viatge& viatge_top, Vaixell barco) {
    list<string> llist_ciutats = viatge_top.consultarRuta();
    auto it = llist_ciutats.begin();

    while (it!=llist_ciutats.end()) {
        string id_city = *it;        
        // Comerç amb la ciutat
        barco.comerciar(cmap[id_city], productes);
        
        ++it;
    }
}

Viatge Cjt_ciutats::determinar_viatge(const BinTree<string>& cuenca, const Cjt_productes& productes, Llanxa lancha) {
    // === Base Case
    if (cuenca.empty()) return Viatge();
    
    // === General Case
    Viatge viatge_act;
    string id_city = cuenca.value();

    // Fer intercanvi
    int quant_comerciat = lancha.comerciarSenseMod(cmap[id_city]);

    // Actualitzar viatge actual
    viatge_act.afegirCiutat(id_city);
    viatge_act.actQuant(quant_comerciat);

    // Si el barco ja no té unitats per intercanviar, es para tot.
    if (lancha.quantitatPerComprar()==0 and lancha.quantitatPerVendre()==0) return viatge_act;

    // Recursivitat
    Viatge viatge_esquerra, viatge_dreta;
    // Explorar ciutat de l'esquerra
    if (not cuenca.left().empty()) viatge_esquerra = determinar_viatge(cuenca.left(), productes, lancha);
    // Explorar ciutat de la dreta
    if (not cuenca.right().empty()) viatge_dreta = determinar_viatge(cuenca.right(), productes, lancha);

    // Determinar millor viatge
    viatge_act.millorViatge(viatge_esquerra, viatge_dreta);
    
    return viatge_act;
}

void Cjt_ciutats::eliminarTotsProdDeCiutat(string id_city) {
    cmap[id_city].eliminarTotsProd();
}

/* === CONSULTORS === */

bool Cjt_ciutats::existeixCiutat(string id_city) const {
    return cmap.find(id_city) != cmap.end();
}

Ciutat Cjt_ciutats::consultarCiutat(string id_city) const {
    auto it = cmap.find(id_city);
    return it->second;
}

/* === ESCRIPTURA === */
void Cjt_ciutats::escriureCiutat(string id_city) const {
    auto it = cmap.find(id_city);
    it->second.escriure();
}

/* === LECTURA === */

BinTree<string> Cjt_ciutats::leer_rio_aux() {
    string id_city;
    cin >> id_city;

    // Base Case
    if (id_city=="#") return BinTree<string>();

    // General Case
    Ciutat node(id_city);
    afegirCiutat(id_city, node);
    BinTree<string> esq = leer_rio_aux();
    BinTree<string> dret = leer_rio_aux();
    
    return BinTree<string>(id_city,esq,dret);
}

BinTree<string> Cjt_ciutats::leer_rio() {
    cmap.clear();
    return leer_rio_aux();
}