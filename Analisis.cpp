//Joustin Joel Martinez Carranza
#include "Analisis.h"
#include "JSONGen.h"
#include <iostream>

static int contadorICMP = 0;

void registrarICMP() {

    contadorICMP++;

    if (contadorICMP == 6) {
        std::cout << "[ANOMALIA] demasiados ICMP\n";

        guardarAnomalia("Demasiados paquetes ICMP detectados");
    }
}

void registrarARP() {

    std::cout << "[INFO] ARP detectado\n";
}
