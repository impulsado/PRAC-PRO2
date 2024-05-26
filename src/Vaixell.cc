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

int Vaixell::comerciar(Ciutat& city, const Cjt_productes& productes) {
    // La ciutat no té inventari (Optimització)
    if (not city.teInventari()) return 0;
    
    // Total comerciat
    int quant_total = 0;

    // Comprar de la ciutat
    
    // La ciutat té el producte i el vaixell pot comprar
    if (comprar.second>0 and city.teProducte(comprar.first)) {
        // Saber quantitat disponible a la ciutat
        int dif = city.consultarDiferencia(comprar.first);

        // La ciutat té quantitat per vendre al vaixell
        if (dif>0) {
            // Determinar la maxima quantitat a comerciar
            int quant_comerciar = min(comprar.second, dif);
            // Consultar el producte
            pair<int,int> pesVol = productes.consultarProducte(comprar.first);
            // Treure la quantitat venuda per la ciutat
            city.modificarOfertaProd(comprar.first, -quant_comerciar, pesVol.first, pesVol.second);
            // Actualitzar la nova quantitat necessària del vaixell
            comprar.second -= quant_comerciar;
            // Actualitzar la quantitat total comerciada
            quant_total += quant_comerciar;
        }
    }

    // Vendre a la ciutat
    // La ciutat necessita el producte i el vaixell pot vendre
    if (vendre.second>0 and city.teProducte(vendre.first)) {
        // Saber quantitat necessària a la ciutat
        int dif = city.consultarDiferencia(vendre.first);
        
        // La ciutat té necessitat del producte
        if (dif<0) {
            // Determinar la maxima quantitat a comerciar
            int quant_comerciar = min(vendre.second, -dif);
            // Consultar el producte
            pair<int,int> pesVol = productes.consultarProducte(vendre.first);
            // Afegir la quantitat venuda a la ciutat
            city.modificarOfertaProd(vendre.first, quant_comerciar, pesVol.first, pesVol.second);
            // Actualitzar la nova quantitat necessària del vaixell
            vendre.second -= quant_comerciar;
            // Actualitzar la quantitat total comerciada
            quant_total += quant_comerciar;
        }
    }
    
    return quant_total;
}

int Vaixell::comerciarSenseMod(Ciutat& city) {
    // La ciutat no té inventari (Optimització)
    if (not city.teInventari()) return 0;
    
    // Total comerciat
    int quant_total = 0;

    // Comprar de la ciutat
    
    // La ciutat té el producte i el vaixell pot comprar
    if (comprar.second>0 and city.teProducte(comprar.first)) {
        // Saber quantitat disponible a la ciutat
        int dif = city.consultarDiferencia(comprar.first);

        // La ciutat té quantitat per vendre al vaixell
        if (dif>0) {
            // Determinar la maxima quantitat a comerciar
            int quant_comerciar = min(comprar.second, dif);
            // Actualitzar la nova quantitat necessària del vaixell
            comprar.second -= quant_comerciar;
            // Actualitzar la quantitat total comerciada
            quant_total += quant_comerciar;
        }
    }

    // Vendre a la ciutat
    // La ciutat necessita el producte i el vaixell pot vendre
    if (vendre.second>0 and city.teProducte(vendre.first)) {
        // Saber quantitat necessària a la ciutat
        int dif = city.consultarDiferencia(vendre.first);
        
        // La ciutat té necessitat del producte
        if (dif<0) {
            // Determinar la maxima quantitat a comerciar
            int quant_comerciar = min(vendre.second, -dif);
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