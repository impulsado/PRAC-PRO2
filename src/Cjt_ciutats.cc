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

Viatge Cjt_ciutats::determinar_viatge(const BinTree<string>& cuenca, const Cjt_productes& productes, Vaixell barco) {
    // === Base Case
    if (cuenca.empty()) return Viatge();
    
    // === General Case
    Viatge viatge_act;
    string id_city = cuenca.value();

    // Fer intercanvi
    int quant_comerciat = barco.comerciarSenseMod(cmap[id_city]);

    // Actualitzar viatge actual
    viatge_act.afegirCiutat(id_city);
    viatge_act.actQuant(quant_comerciat);

    // Si el barco ja no té unitats per intercanviar, es para tot.
    if (barco.quantitatPerComprar()==0 and barco.quantitatPerVendre()==0) return viatge_act;

    // Recursivitat
    Viatge viatge_esquerra, viatge_dreta;
    // Explorar ciutat de l'esquerra
    if (not cuenca.left().empty()) viatge_esquerra = determinar_viatge(cuenca.left(), productes, barco);
    // Explorar ciutat de la dreta
    if (not cuenca.right().empty()) viatge_dreta = determinar_viatge(cuenca.right(), productes, barco);

    // Determinar millor viatge
    // Casos:
    // 1. No hi ha viatges a l'esquerra ni a la dreta
    if (viatge_esquerra.consultarQuant()==0 and viatge_dreta.consultarQuant()==0) return viatge_act;
    // 2. No hi ha comerç a l'esquerra
    else if (viatge_esquerra.consultarQuant()==0) {
        viatge_act.actViatge(viatge_dreta);
        return viatge_act;
    }
    // 3. No hi ha comerç a la dreta
    else if (viatge_dreta.consultarQuant()==0) {
        viatge_act.actViatge(viatge_esquerra);
        return viatge_act;
    }
    // 4. Hi ha comerç a ambdues bandes
    // 4.1. La quantitat de la esquerra és més gran
    else if (viatge_esquerra.consultarQuant()>viatge_dreta.consultarQuant()) {
        viatge_act.actViatge(viatge_esquerra);
        return viatge_act;
    }
    // 4.1 Tenen la mateixa quantitat
    else if (viatge_esquerra.consultarQuant()==viatge_dreta.consultarQuant()) {
        // 4.1.1 La distància de la esquerra és més petita o igual
        if (viatge_esquerra.consultarDist()<=viatge_dreta.consultarDist()) {
            viatge_act.actViatge(viatge_esquerra);
            return viatge_act;
        }
    }
    // 4.2. La quantitat de la dreta és més gran
    viatge_act.actViatge(viatge_dreta);
    
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