#include <iostream>
#include <string>
#include <list>
#include "Viatge.hh"
#include "BinTree.hh"
#include "Vaixell.hh"
#include "Cjt_ciutats.hh"
#include "Cjt_productes.hh"

using namespace std;

BinTree<string> leer_rio(Cjt_ciutats& ciutats) {
    string id_city;
    cin >> id_city;

    // Base Case
    if (id_city=="#") return BinTree<string>();

    // General Case
    Ciutat node(id_city);
    ciutats.afegirCiutat(id_city, node);
    BinTree<string> esq = leer_rio(ciutats);
    BinTree<string> dret = leer_rio(ciutats);
    
    return BinTree<string>(id_city,esq,dret);
}

void leer_inventario(Cjt_ciutats& ciutats, Cjt_productes& productes) {
    // Info sobre Ciutat
    string id_ciutat;
    cin >> id_ciutat;
    cout << ' ' << id_ciutat << endl;
    if (not ciutats.existeixCiutat(id_ciutat)) {cout << "error: no existe la ciudad" << endl; return;}
    ciutats.eliminarTotsProdDeCiutat(id_ciutat);
    
    // Info sobre els productes
    int quant_prod;
    cin >> quant_prod;
    for (int j = 0; j<quant_prod; j++) {
        // Info sobre el producte
        int id_prod, oferta, demanda;
        cin >> id_prod >> oferta >> demanda;

        if (oferta<0) {cout << "error: oferta no valida" << endl; continue;}
        if (demanda<=0) {cout << "error: demanda no valida" << endl; continue;}
        if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; continue;}
        
        // Saber les dades sobre el producte a afegir
        Producte temp_prod = productes.consultarProducte(id_prod);
        int pes = temp_prod.consultarPes();
        int volum = temp_prod.consultarVolum();
        
        // Afegir el producte a la ciutat directament
        ciutats.afegirProdACiutat(id_ciutat, id_prod, oferta, demanda, pes, volum);
    }
}

void leer_inventarios(Cjt_ciutats& ciutats, Cjt_productes& productes) {
    string id_ciutat;
    while (cin >> id_ciutat and id_ciutat!="#") {
        if (not ciutats.existeixCiutat(id_ciutat)) {cout << "error: no existe la ciudad" << endl; return;}
        ciutats.eliminarTotsProdDeCiutat(id_ciutat);
        
        // Info sobre els productes
        int quant_prod;
        cin >> quant_prod;
        for (int j = 0; j<quant_prod; j++) {
            // Info sobre el producte
            int id_prod, oferta, demanda;
            cin >> id_prod >> oferta >> demanda;
            
            if (oferta<0) {cout << "error: oferta no valida" << endl; continue;}
            if (demanda<=0) {cout << "error: demanda no valida" << endl; continue;}
            if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; continue;}

            // Saber les dades sobre el producte a afegir
            Producte temp_prod = productes.consultarProducte(id_prod);
            int pes = temp_prod.consultarPes();
            int volum = temp_prod.consultarVolum();
            
            // Afegir el producte a la ciutat directament
            ciutats.afegirProdACiutat(id_ciutat,id_prod,oferta,demanda,pes,volum);
        }
    }
}

void modificar_barco(Vaixell& barco, Cjt_productes& productes) {
    // NOTA: Es garantitza que les quantitats seràn valides.

    // Info sobre la Compra
    int prod_compra, quant_compra;
    cin >> prod_compra >> quant_compra;
    if (not productes.existeixProducte(prod_compra)) {cout << "error: no existe el producto" << endl; return;}
    
    // Info sobre la Venta
    int prod_venta, quant_venta;
    cin >> prod_venta >> quant_venta;
    if (not productes.existeixProducte(prod_venta)) {cout << "error: no existe el producto" << endl; return;}

    if (prod_compra==prod_venta) {cout<< "error: no se puede comprar y vender el mismo producto" << endl; return;}
    barco.modificarMercancia(prod_compra, quant_compra, prod_venta, quant_venta);
}

void escribir_barco(Vaixell& barco) {
    barco.escriure();
}

void agregar_productos(Cjt_productes& productes) {
    int usr_quant;
    cin >> usr_quant;
    cout << ' ' << usr_quant << endl;
    for (int i = 0; i<usr_quant; i++) {
        int pes, volum;
        cin >> pes >> volum;
        if (pes<=0) {cout << "error: peso no valido" << endl; return;}
        if (volum<=0) {cout << "error: volumen no valido" << endl; return;}
        productes.afegirProducte(pes,volum);
    }
}

void escribir_producto(Cjt_productes& productes) {
    int id_prod;
    cin >> id_prod;
    cout << ' ' << id_prod << endl;
    if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; return;}
    
    Producte temp_prod = productes.consultarProducte(id_prod);
    
    temp_prod.escriure();
}

void escribir_ciudad(Cjt_ciutats& ciutats) {
    string id_city;
    cin >> id_city;
    cout << ' ' << id_city << endl;
    if (not ciutats.existeixCiutat(id_city)) {cout << "error: no existe la ciudad" << endl; return;}
    
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    
    temp_city.escriure();
}

void poner_prod(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city;
    int id_prod, oferta, demanda;
    cin >> id_city >> id_prod >> oferta >> demanda;
    cout << ' ' << id_city << ' ' << id_prod << endl;
    if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "error: no existe la ciudad" << endl; return;}
    if (oferta<0) {cout << "error: oferta no valida" << endl; return;}
    if (demanda<=0) {cout << "error: demanda no valida" << endl; return;}
    
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (temp_city.teProducte(id_prod)) {cout << "error: la ciudad ya tiene el producto" << endl; return;}
    
    Producte temp_prod = productes.consultarProducte(id_prod);
    int pes = temp_prod.consultarPes();
    int volum = temp_prod.consultarVolum();

    temp_city.afegirProdAlInventari(id_prod,oferta,demanda,pes,volum);
    ciutats.modificarCiutat(id_city,temp_city);
    cout << temp_city.consultarPesTotal() << ' ' << temp_city.consultarVolumTotal() << endl;
}

void modificar_prod(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city;
    int id_prod, oferta, demanda;
    cin >> id_city >> id_prod >> oferta >> demanda;
    cout << ' ' << id_city << ' ' << id_prod << endl;
    if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "error: no existe la ciudad" << endl; return;}
    if (oferta<0) {cout << "error: oferta no valida" << endl; return;}
    if (demanda<=0) {cout << "error: demanda no valida" << endl; return;}
    
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (not temp_city.teProducte(id_prod)) {cout << "error: la ciudad no tiene el producto" << endl; return;}
    
    Producte temp_prod = productes.consultarProducte(id_prod);
    int pes = temp_prod.consultarPes();
    int volum = temp_prod.consultarVolum();
    
    temp_city.modificarProdDelInventari(id_prod,oferta,demanda,pes,volum);
    ciutats.modificarCiutat(id_city,temp_city);
    cout << temp_city.consultarPesTotal() << ' ' << temp_city.consultarVolumTotal() << endl;
}

void quitar_prod(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city;
    int id_prod;
    cin >> id_city >> id_prod;
    cout << ' ' << id_city << ' ' << id_prod << endl;
    if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "error: no existe la ciudad" << endl; return;}
    
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (not temp_city.teProducte(id_prod)) {cout << "error: la ciudad no tiene el producto" << endl; return;}
    
    Producte temp_prod = productes.consultarProducte(id_prod);
    int pes = temp_prod.consultarPes();
    int volum = temp_prod.consultarVolum();
    
    temp_city.eliminarProdDelInventari(id_prod,pes,volum);
    ciutats.modificarCiutat(id_city,temp_city);
    cout << temp_city.consultarPesTotal() << ' ' << temp_city.consultarVolumTotal() << endl;
}

void consultar_prod(Cjt_ciutats& ciutats, Cjt_productes& productes) {
    string id_city;
    int id_prod;
    cin >> id_city >> id_prod;
    cout << ' ' << id_city << ' ' << id_prod << endl;
    if (not productes.existeixProducte(id_prod)) {cout << "error: no existe el producto" << endl; return;}
    if (not ciutats.existeixCiutat(id_city)) {cout << "error: no existe la ciudad" << endl; return;}
    
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    if (not temp_city.teProducte(id_prod)) {cout << "error: la ciudad no tiene el producto" << endl; return;}
    
    cout << temp_city.consultarOferta(id_prod) << ' ' << temp_city.consultarDemanda(id_prod) << endl;
}

void comerciar(Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    string id_city1, id_city2;
    cin >> id_city1 >> id_city2;
    cout << ' ' << id_city1 << ' ' << id_city2 << endl;
    if (id_city1==id_city2) {cout << "error: ciudad repetida" << endl; return;}
    if (not ciutats.existeixCiutat(id_city1)) {cout << "error: no existe la ciudad" << endl; return;}
    if (not ciutats.existeixCiutat(id_city2)) {cout << "error: no existe la ciudad" << endl; return;}
    
    ciutats.comerciar(ciutats, id_city1, id_city2, productes);
}

void redistribuir(const BinTree<string>& Cuenca, Cjt_ciutats& ciutats, const Cjt_productes& productes) {
    // === Base Case
    if (Cuenca.left().empty() or Cuenca.right().empty()) return;

    // === General Case
    // Comerciar
    ciutats.comerciar(ciutats, Cuenca.value(), Cuenca.left().value(), productes);
    ciutats.comerciar(ciutats, Cuenca.value(), Cuenca.right().value(), productes);
    
    // Recursivitat
    redistribuir(Cuenca.left(),ciutats,productes);
    redistribuir(Cuenca.right(),ciutats,productes);
    return;
}

bool determinar_millor_viatge(const Viatge& viatge_act, const Viatge& viatge_top) {
    if (viatge_act.consultarQuant()>viatge_top.consultarQuant()) return true;
    else if (viatge_act.consultarQuant()==viatge_top.consultarQuant()) {
        if (viatge_act.consultarDist()<viatge_top.consultarDist()) return true;
        else if (viatge_act.consultarDist()==viatge_top.consultarDist()) {
            // Com que e>d dona preferencia a l'esquerra
            return viatge_act.consultarOrdre()>viatge_top.consultarOrdre();
        }
    }
    return false;
}

void determinar_viatge(const BinTree<string>& cuenca, const Cjt_productes& productes, Viatge& viatge_act, Viatge& viatge_top, Vaixell& barco, Cjt_ciutats ciutats, char direccio, int distancia) {
    // === Base Case
    if (cuenca.empty()) return;
    
    // Límitar distància de búsqueda
    if (viatge_top.estaTotComerciat() and distancia>viatge_top.consultarDist()) {
        //cout << "LIMIT reached at CITY: " << cuenca.value() << " with QUANT: " << distancia << " > " << viatge_top.consultarQuant() << endl;
        return;
    }
    
    // === General Case
    string id_city = cuenca.value();
    Ciutat temp_city = ciutats.consultarCiutat(id_city);
    //cout << "CITY: " << id_city << " DIST: " << distancia << endl;
    
    // Fer intercanvi
    int quant_comerciat = barco.comerciar(temp_city, productes);
    ciutats.modificarCiutat(id_city, temp_city);

    // Actualitzar viatge actual
    viatge_act.afegirCiutat(id_city, direccio, ciutats);
    viatge_act.actQuant(quant_comerciat);

    // Mirar si el viatge actual és millor que el millor viatge, llavors intercanvio.
    if (determinar_millor_viatge(viatge_act, viatge_top)) {
        viatge_top = viatge_act;
        //cout << "MILLOR VIATGE EN " << id_city << endl;
    }

    // Si el barco ja no té unitats per intercanviar, es para tot.
    if (barco.quantitatPerComprar()==0 and barco.quantitatPerVendre()==0) {
        viatge_top.actTotComerciat();  // Limitar futures exploracions
        //cout << "ESTA LIMITAT A : " << viatge_top.consultarDist() << endl;
        return;
    }

    // Explorar ciutat de l'esquerra
    if (not cuenca.left().empty()) {
        Vaixell nou_barco_esquerra = barco;
        Viatge nou_viatge_esquerra = viatge_act;
        determinar_viatge(cuenca.left(), productes, nou_viatge_esquerra, viatge_top, nou_barco_esquerra, ciutats, 'e', distancia+1);
    }

    // Explorar ciutat de la dreta
    if (not cuenca.right().empty()) {
        Vaixell nou_barco_dreta = barco;
        Viatge nou_viatge_dreta = viatge_act;
        determinar_viatge(cuenca.right(), productes, nou_viatge_dreta, viatge_top, nou_barco_dreta, ciutats, 'd', distancia+1);
    }
}

void hacer_viaje(const BinTree<string>& cuenca, const Cjt_productes& productes, Vaixell& barco, Cjt_ciutats& ciutats) {
    Viatge ruta, ruta_top;
    Vaixell temp_barco = barco;
    Cjt_ciutats tmp_ciutats = ciutats;

    int distancia = 1;
    determinar_viatge(cuenca, productes, ruta, ruta_top, temp_barco, tmp_ciutats, 'r', distancia);

    int quantitat_comerciat = ruta_top.consultarQuant();
    cout << quantitat_comerciat << endl;

    if (quantitat_comerciat != 0) {
        string id_last_city = ruta_top.consultarUltimaCiutat();
        barco.afegirCiutat(id_last_city);  // Guardar l'última ciutat
        ciutats = ruta_top.consultarSnapshot();  // Restaura el riu que tenia després de realitzar-se la millor ruta.
    }
}

int main () {
    Cjt_ciutats ciutats;
    BinTree<string> cuenca;

    // === Introducció
    // Demanar productes
    int usr_quant_prod;
    cin >> usr_quant_prod;
    Cjt_productes productes;
    for (int i = 0; i<usr_quant_prod; i++) {
        int usr_prod_pes, usr_prod_volum;
        cin >> usr_prod_pes >> usr_prod_volum; 
        productes.afegirProducte(usr_prod_pes,usr_prod_volum);
    }

    // Demanar cuenca
    cuenca = leer_rio(ciutats);

    // Demanar vaixell
    Vaixell barco;
    barco.llegir(productes);

    // === Commandes
    string usr_op;
    while (cin >> usr_op and usr_op!="fin") {
        if (usr_op == "//") {
            getline(cin, usr_op);
            continue; // Anar a la següent iteració del bucle
        }
        else if (usr_op=="leer_rio" or usr_op=="lr") {
            cout << "#" << usr_op << endl;
            ciutats.eliminarCiutats();
            barco.eliminarRegistre();
            cuenca = leer_rio(ciutats);
        }
        else if (usr_op=="leer_inventario" or usr_op=="li") {
            cout << "#" << usr_op;
            leer_inventario(ciutats, productes);
        }
        else if (usr_op=="leer_inventarios" or usr_op=="ls") {
            cout << "#" << usr_op << endl;
            leer_inventarios(ciutats, productes);
        }
        else if (usr_op=="modificar_barco" or usr_op=="mb") {
            cout << "#" << usr_op << endl;
            modificar_barco(barco, productes);
        }
        else if (usr_op=="escribir_barco" or usr_op=="eb") {
            cout << "#" << usr_op << endl;
            escribir_barco(barco);
        }
        else if (usr_op=="consultar_num" or usr_op=="cn") {
            cout << "#" << usr_op << endl;
            cout << productes.consultarQuantitatProd() << endl;
        }
        else if (usr_op=="agregar_productos" or usr_op=="ap") {
            cout << "#" << usr_op;
            agregar_productos(productes);
        }
        else if (usr_op=="escribir_producto" or usr_op=="ep") {
            cout << "#" << usr_op;
            escribir_producto(productes);
        }
        else if (usr_op=="escribir_ciudad" or usr_op=="ec") {
            cout << "#" << usr_op;
            escribir_ciudad(ciutats);
        }
        else if (usr_op=="poner_prod" or usr_op=="pp") {
            cout << "#" << usr_op;
            poner_prod(ciutats,productes);
        }
        else if (usr_op=="modificar_prod" or usr_op=="mp") {
            cout << "#" << usr_op;
            modificar_prod(ciutats,productes);
        }
        else if (usr_op=="quitar_prod" or usr_op=="qp") {
            cout << "#" << usr_op;
            quitar_prod(ciutats,productes);
        }
        else if (usr_op=="consultar_prod" or usr_op=="cp") {
            cout << "#" << usr_op;
            consultar_prod(ciutats,productes);
        }
        else if (usr_op=="comerciar" or usr_op=="co") {
            cout << "#" << usr_op;
            comerciar(ciutats,productes);
        }
        else if (usr_op=="redistribuir" or usr_op=="re") {
            cout << "#" << usr_op << endl;
            redistribuir(cuenca, ciutats, productes);
        }
        else if (usr_op == "hacer_viaje" or usr_op == "hv") {
            cout << "#" << usr_op << endl;
            hacer_viaje(cuenca, productes, barco, ciutats);
        }
        // TO-DELETE
        else if (usr_op=="debug") {
            productes.mostrarProductes();
        }
    }
}