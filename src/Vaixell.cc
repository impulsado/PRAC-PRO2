#include "Vaixell.hh"
using namespace std;

/* === CONSTRUCTORS === */

Vaixell::Vaixell() {
    comprar = make_pair(0, 0);
    vendre = make_pair(0, 0);
    registre_ultimes_ciutats = vector<string>();
}

/* === MODIFICADORS === */

void Vaixell::modificarMercancia(int id_compra, int quant_compra, int id_venta, int quant_venta) {
    comprar = make_pair(id_compra, quant_compra);
    vendre = make_pair(id_venta, quant_venta);
}

int Vaixell::comerciar(Ciutat& city, const Cjt_productes& productes, bool modificar_ciutat) {
    // La ciutat no té inventari (Optimització)
    if (not city.teInventari()) return 0;
    
    // Total comerciat
    int quant_total = 0;

    // Comprar de la ciutat
    int id_prod_comprar = comprar.first;
    int quant_comprar_barco = comprar.second;
    
    // La ciutat té el producte i el vaixell pot comprar
    if (quant_comprar_barco>0 and city.teProducte(id_prod_comprar)) {
        // Saber quantitat disponible a la ciutat
        int dif = city.consultarDiferencia(id_prod_comprar);

        // La ciutat té quantitat per vendre al vaixell
        if (dif>0) {
            // Determinar la maxima quantitat a comerciar
            int quant_comerciar = min(quant_comprar_barco, dif);
            // Consultar el producte
            Producte tmp_prod = productes.consultarProducte(id_prod_comprar);
            // Treure la quantitat venuda per la ciutat
            if (modificar_ciutat) city.modificarOfertaProd(id_prod_comprar, -quant_comerciar, tmp_prod.consultarPes(), tmp_prod.consultarVolum());
            // Actualitzar la nova quantitat necessària del vaixell
            comprar.second -= quant_comerciar;
            // Actualitzar la quantitat total comerciada
            quant_total += quant_comerciar;
        }
    }

    // Vendre a la ciutat
    int id_prod_venta = vendre.first;
    int quant_vendre_barco = vendre.second;

    // La ciutat necessita el producte i el vaixell pot vendre
    if (quant_vendre_barco>0 and city.teProducte(id_prod_venta)) {
        // Saber quantitat necessària a la ciutat
        int dif = city.consultarDiferencia(id_prod_venta);
        
        // La ciutat té necessitat del producte
        if (dif<0) {
            // Determinar la maxima quantitat a comerciar
            int quant_comerciar = min(quant_vendre_barco, -dif);
            // Consultar el producte
            Producte tmp_prod = productes.consultarProducte(id_prod_venta);
            // Afegir la quantitat venuda a la ciutat
            if (modificar_ciutat) city.modificarOfertaProd(id_prod_venta, quant_comerciar, tmp_prod.consultarPes(), tmp_prod.consultarVolum());
            // Actualitzar la nova quantitat necessària del vaixell
            vendre.second -= quant_comerciar;
            // Actualitzar la quantitat total comerciada
            quant_total += quant_comerciar;
        }
    }
    
    return quant_total;
}

void Vaixell::afegirCiutat(string id_city) {
    registre_ultimes_ciutats.push_back(id_city);
}

void Vaixell::eliminarRegistre() {
    if (not registre_ultimes_ciutats.empty()) registre_ultimes_ciutats.clear();
}

/* === CONSULTORS === */

int Vaixell::quantitatPerVendre() {
    return vendre.second;
}

int Vaixell::quantitatPerComprar() {
    return comprar.second;
}

/* === LECTURA === */

void Vaixell::llegir(Cjt_productes productes) {
    // Demanar informació producte a comprar
    int id_prod_comprar, quant_prod_comprar;
    cin >> id_prod_comprar >> quant_prod_comprar;
    if (not productes.existeixProducte(id_prod_comprar)) {
        cout << "Error: El producte no existeix" << endl;
        return;
    }
    
    // Demanar informació producte a vendre
    int id_prod_vendre, quant_prod_vendre;
    cin >> id_prod_vendre >> quant_prod_vendre;
    if (not productes.existeixProducte(id_prod_vendre)) {
        cout << "Error: El producte no existeix" << endl;
        return;
    }
    
    // Actualitzar la informació del vaixell
    comprar = make_pair(id_prod_comprar, quant_prod_comprar);
    vendre = make_pair(id_prod_vendre, quant_prod_vendre);
}

/* === ESCRIPTURA === */

void Vaixell::escriure() {
    // Mostrar la informació sobre els productes a comprar i vendre
    cout << comprar.first << ' ' << comprar.second;
    cout << ' ' << vendre.first << ' ' << vendre.second << endl;
    
    // Mostrar les ciutats visitades
    for (int i = 0; i<registre_ultimes_ciutats.size(); i++) {
        cout << registre_ultimes_ciutats[i] << endl;
    }
}