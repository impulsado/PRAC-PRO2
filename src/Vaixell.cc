#include "Vaixell.hh"

/**
 * @brief Constructora per defecte de la classe Vaixell
 * 
 * \pre Cert.
 * \post Vaixell amb tots els paràmetres a 0 o buits.
 */
Vaixell::Vaixell() {
    comprar = make_pair(0,0);
    vendre = make_pair(0,0);
    registre_ultimes_ciutats = vector<string>();
}

/**
 * @brief Mostrar el producte que ha de comprar el vaixell.
 * 
 * \pre Cert.
 * \post Mostra la quantitat per la terminal.
 */
void Vaixell::mostrarProdAComprar() {
    cout << "Id: " << comprar.first << "Quantitat: " << comprar.second << endl; 
}

/**
 * @brief Mostrar el producte que ha de vendre el vaixell.
 * 
 * \pre Cert.
 * \post Mostra la quantitat per la terminal.
 */
void Vaixell::mostrarProdAVendre() {
    cout << "Id: " << vendre.first << "Quantitat: " << vendre.second << endl; 
}

/**
 * @brief Mostra les ultimes ciutats visitades a cadascun dels viatges realitzats.
 * 
 * \pre Cert.
 * \post Mostra les ultimes ciutats per la terminal.
 */
void Vaixell::mostrarRegistreViatjes() {
    for (int i = 0; i<registre_ultimes_ciutats.size(); i++) {
        cout << registre_ultimes_ciutats[i] << endl;
    }
}

/**
 * @brief Actualitzar informació sobre quin producte vendrà i comprarà el vaixell.
 * 
 * \pre id_compra, id_venta existeixen. quant_compra_quant_venta son valors vàlids.
 * \post Vaixell te dades sobre el producte a comprar i vendre actualitzat.
 */
void Vaixell::modificarMercancia(int id_compra, int quant_compra, int id_venta, int quant_venta) {
    comprar = std::make_pair(id_compra, quant_compra);
    vendre = std::make_pair(id_venta, quant_venta);
}