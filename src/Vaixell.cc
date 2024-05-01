#include "Vaixell.hh"

Vaixell::Vaixell() {
    comprar = make_pair(0,0);
    vendre = make_pair(0,0);
    registre_ultimes_ciutats = vector<string>();
}

// ?? Revisar format ??
void Vaixell::mostrarProdAComprar() {
    cout << "Id: " << comprar.first << "Quantitat: " << comprar.second << endl; 
}

// ?? Revisar format ??
void Vaixell::mostrarProdAVendre() {
    cout << "Id: " << vendre.first << "Quantitat: " << vendre.second << endl; 
}

// ?? Revisar format ??
void Vaixell::mostrarRegistreViatjes() {
    for (int i = 0; i<registre_ultimes_ciutats.size(); i++) {
        cout << registre_ultimes_ciutats[i] << endl;
    }
}

void Vaixell::modificarMercancia(int id_compra, int quant_compra, int id_venta, int quant_venta) {
    comprar = std::make_pair(id_compra, quant_compra);
    vendre = std::make_pair(id_venta, quant_venta);
}