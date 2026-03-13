//Joustin Joel Martinez Carranza
#include "JSONGen.h"
#include <nlohmann/json.hpp>
#include <vector>
#include <fstream>
#include <ctime>

using json = nlohmann::json;

std::vector<json> eventos;

std::string timestamp() {

    time_t now = time(0);
    char buf[80];

    strftime(buf, sizeof(buf),
             "%Y-%m-%dT%H:%M:%SZ",
             gmtime(&now));

    return std::string(buf);
}

void guardarCambioMAC(const std::string& old_mac,
                      const std::string& new_mac) {

    json e;

    e["event"] = "mac_change";
    e["old_value"] = old_mac;
    e["new_value"] = new_mac;
    e["timestamp"] = timestamp();

    eventos.push_back(e);
}

void guardarARPPacket(const std::string& source_ip,
                      const std::string& header) {

    json e;

    e["event"] = "arp_packet";
    e["source_ip"] = source_ip;
    e["header_bytes"] = header;
    e["timestamp"] = timestamp();

    eventos.push_back(e);
}

void guardarAnomalia(const std::string& descripcion) {

    json e;

    e["event"] = "anomaly";
    e["description"] = descripcion;
    e["timestamp"] = timestamp();

    eventos.push_back(e);
}

void exportarJSON(const std::string& archivo) {

    std::ofstream out(archivo);

    out << json(eventos).dump(4);
}
