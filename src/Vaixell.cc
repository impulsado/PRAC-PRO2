#include "Vaixell.hh"
using namespace std;

/* === CONSTRUCTORS === */

/**
 * @brief Constructora per defecte de la classe Vaixell.
 * 
 * \pre Cert.
 * \post Vaixell amb tots els paràmetres inicialitzats a 0 o buits.
 */
Vaixell::Vaixell() {
    comprar = make_pair(0, 0);
    vendre = make_pair(0, 0);
    registre_ultimes_ciutats = vector<string>();
}

/* === MODIFICADORS === */

/**
 * @brief Actualitzar informació sobre quin producte vendrà i comprarà el vaixell.
 * 
 * \pre id_compra i id_venta existeixen. quant_compra i quant_venta són valors vàlids.
 * \post El vaixell té les dades sobre el producte a comprar i vendre actualitzades.
 */
void Vaixell::modificarMercancia(int id_compra, int quant_compra, int id_venta, int quant_venta) {
    comprar = make_pair(id_compra, quant_compra);
    vendre = make_pair(id_venta, quant_venta);
}

/**
 * @brief Realitza l'operació de comerç amb una ciutat.
 * 
 * \pre La ciutat té un inventari vàlid. Els productes existeixen en el conjunt de productes.
 * \post Actualitza el vaixell i la ciutat segons l'operació de comerç. Retorna la quantitat total comerciada.
 */
int Vaixell::comerciar(Ciutat& city, const Cjt_productes& productes) {
    if (not city.teInventari()) return 0;  // La ciutat no té inventari
    
    // Total comerciat
    int quant_total = 0;

    // Comprar de la ciutat
    int id_prod_comprar = comprar.first;
    int quant_comprar_barco = comprar.second;
    if (quant_comprar_barco>0 and city.teProducte(id_prod_comprar)) {
        int dif = city.consultarDiferencia(id_prod_comprar);

        if (dif>0) {  // La ciutat té quantitat per vendre al vaixell
            int quant_comerciar = min(quant_comprar_barco, dif);
            Producte tmp_prod = productes.consultarProducte(id_prod_comprar);
            // Treure la quantitat venuda per la ciutat
            city.modificarOfertaProd(id_prod_comprar, -quant_comerciar, tmp_prod.consultarPes(), tmp_prod.consultarVolum());
            // Actualitzar la nova quantitat necessària
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
            int quant_comerciar = min(quant_vendre_barco, -dif);
            Producte tmp_prod = productes.consultarProducte(id_prod_venta);
            // Afegir la quantitat venuda a la ciutat
            city.modificarOfertaProd(id_prod_venta, quant_comerciar, tmp_prod.consultarPes(), tmp_prod.consultarVolum());
            // Actualitzar la nova quantitat necessària
            vendre.second -= quant_comerciar;
            quant_total += quant_comerciar;
        }
    }
    
    return quant_total;
}

/**
 * @brief Afegir una ciutat al registre de les últimes ciutats visitades.
 * 
 * \pre id_city és vàlid.
 * \post El registre de les últimes ciutats conté id_city.
 */
void Vaixell::afegirCiutat(string id_city) {
    registre_ultimes_ciutats.push_back(id_city);
}

/**
 * @brief Eliminar totes les ciutats del registre.
 * 
 * \pre Cert.
 * \post El vaixell no conté cap registre de les últimes ciutats visitades.
 */
void Vaixell::eliminarRegistre() {
    if (not registre_ultimes_ciutats.empty()) registre_ultimes_ciutats.clear();
}

/* === CONSULTORS === */

/**
 * @brief Quantitat d'unitats restants per vendre.
 * 
 * \pre Cert.
 * \post Retorna la quantitat d'unitats restants per vendre.
 */
int Vaixell::quantitatPerVendre() {
    return vendre.second;
}

/**
 * @brief Quantitat d'unitats restants per comprar.
 * 
 * \pre Cert.
 * \post Retorna la quantitat d'unitats restants per comprar.
 */
int Vaixell::quantitatPerComprar() {
    return comprar.second;
}

/* === LECTURA === */

/**
 * @brief Llegir els valors necessaris del vaixell des de l'entrada estàndard.
 * 
 * \pre Cert.
 * \post El vaixell té com atributs les dades llegides.
 */
void Vaixell::llegir(Cjt_productes productes) {
    int id_prod_comprar, quant_prod_comprar;
    cin >> id_prod_comprar >> quant_prod_comprar;
    if (not productes.existeixProducte(id_prod_comprar)) {
        cout << "Error: El producte no existeix" << endl;
        return;
    }
    
    int id_prod_vendre, quant_prod_vendre;
    cin >> id_prod_vendre >> quant_prod_vendre;
    if (not productes.existeixProducte(id_prod_vendre)) {
        cout << "Error: El producte no existeix" << endl;
        return;
    }
    
    comprar = make_pair(id_prod_comprar, quant_prod_comprar);
    vendre = make_pair(id_prod_vendre, quant_prod_vendre);
}

/* === ESCRIPTURA === */

/**
 * @brief Mostra tota la informació del vaixell.
 * 
 * \pre Cert.
 * \post Mostra per consola el producte a comprar i vendre, juntament amb les respectives quantitats, i les últimes ciutats visitades.
 */
void Vaixell::escriure() {
    cout << comprar.first << ' ' << comprar.second;
    cout << ' ' << vendre.first << ' ' << vendre.second << endl;
    
    for (int i = 0; i<registre_ultimes_ciutats.size(); i++) {
        cout << registre_ultimes_ciutats[i] << endl;
    }
}