#include "Vaixell.hh"
using namespace std;

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
 * @brief Constructora per còpia de la classe Vaixell
 * 
 * \pre Cert.
 * \post Vaixell amb mateixos parametres que el vaixell referenciat.
 */
Vaixell::Vaixell(const Vaixell& v) {
    comprar = v.comprar;
    vendre = v.vendre;
    registre_ultimes_ciutats = v.registre_ultimes_ciutats;
}

/**
 * @brief Quantitat d'unitats restants per vendre.
 * 
 * \pre Cert.
 * \post Quanitat d'unitats.
 */
int Vaixell::quantitatPerVendre() {
    return vendre.second;
}

/**
 * @brief Quantitat d'unitats restants per comprar.
 * 
 * \pre Cert.
 * \post Quanitat d'unitats.
 */
int Vaixell::quantitatPerComprar() {
    return comprar.second;
}

/**
 * @brief Actualitzar informació sobre quin producte vendrà i comprarà el vaixell.
 * 
 * \pre id_compra, id_venta existeixen. quant_compra_quant_venta son valors vàlids.
 * \post Vaixell te dades sobre el producte a comprar i vendre actualitzat.
 */
void Vaixell::modificarMercancia(int id_venta, int quant_venta, int id_compra, int quant_compra) {
    vendre = std::make_pair(id_venta, quant_venta);
    comprar = std::make_pair(id_compra, quant_compra);
}

int Vaixell::comerciar(Ciutat& city, const Cjt_productes& productes) {
    if (not city.teInventari()) return 0;  // No té inventari
    
    // Total comerciat
    int quant_total = 0;

    // Comprar de la ciutat
    int id_prod_comprar = comprar.first;
    int quant_comprar_barco = comprar.second;
    if (quant_comprar_barco>0 and city.teProducte(id_prod_comprar)) {
        int dif = city.consultarDiferencia(id_prod_comprar);

        if (dif>0) {  // Ciutat té quantitat per vendre al barco
            int quant_comerciar = min(quant_comprar_barco,dif);
            Producte tmp_prod = productes.consultarProducte(id_prod_comprar);
            // Treure la quantitat venuda per la ciutat
            city.modificarOfertaProd(id_prod_comprar, -quant_comerciar, tmp_prod.consultarPes(), tmp_prod.consultarVolum());
            // Actualitzar la nova quantitat necessaria
            comprar.second -= quant_comerciar;
            quant_total += quant_comerciar;
        }
    }

    // Vendre a la ciutat
    int id_prod_venta = vendre.first;
    int quant_vendre_barco = vendre.second;
    if (quant_vendre_barco>0 and city.teProducte(id_prod_venta)) {
        int dif = city.consultarDiferencia(id_prod_venta);
        
        if (dif<0) {  // La ciutat té necessitat del producte
            int quant_comerciar = min(quant_vendre_barco,-dif);
            Producte tmp_prod = productes.consultarProducte(id_prod_venta);
            // Treure la quantitat venuda per la ciutat
            city.modificarDemandaProd(id_prod_venta, -quant_comerciar, tmp_prod.consultarPes(), tmp_prod.consultarVolum());
            // Actualitzar la nova quantitat necessaria
            vendre.second -= quant_comerciar;
            quant_total += quant_comerciar;
        }
    }
    
    return quant_total;
}

/**
 * @brief LLegeix els valors necessaris del vaixell.
 * 
 * \pre Cert.
 * \post El vaixell té com atributs les dades llegides.
 */
void Vaixell::llegir(Cjt_productes productes) {
    int id_prod_comprar, quant_prod_comprar;
    cin >> id_prod_comprar >> quant_prod_comprar;
    if (not productes.existeixProducte(id_prod_comprar)) {cout << "Error: El producte no existeix" << endl; return;}
    int id_prod_vendre, quant_prod_vendre;
    cin >> id_prod_vendre >> quant_prod_vendre;
    if (not productes.existeixProducte(id_prod_vendre)) {cout << "Error: El producte no existeix" << endl; return;}
    comprar = make_pair(id_prod_comprar,quant_prod_comprar);
    vendre = make_pair(id_prod_vendre,quant_prod_vendre);
}

/**
 * @brief Mostra tota la informació del barco.
 * 
 * \pre Cert.
 * \post Mostra el producte a comprar i vendre, juntament amb la seva respectica quantitat i ultimes ciutats, per la terminal.
 */
void Vaixell::escriure() {
    cout << vendre.first << ' ' << vendre.second; 
    cout << ' ' << comprar.first << ' ' << comprar.second << endl; 
    
    for (int i = 0; i<registre_ultimes_ciutats.size(); i++) {
        cout << registre_ultimes_ciutats[i] << endl;
    }
}