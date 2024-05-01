#include "Vaixell.hh"

Vaixell::Vaixell() {
    comprar = make_pair(0,0);
    vendre = make_pair(0,0);
    registre_ultimes_ciutats = vector<string>();
}

void Vaixell::modificarMercancia(int id_compra, int quant_compra, int id_venta, int quant_venta) {
    comprar = std::make_pair(id_compra, quant_compra);
    vendre = std::make_pair(id_venta, quant_venta);
}