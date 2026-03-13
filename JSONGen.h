#ifndef JSONGEN_H
#define JSONGEN_H

#include <string>

void guardarCambioMAC(const std::string& old_mac,
                      const std::string& new_mac);

void guardarARPPacket(const std::string& source_ip,
                      const std::string& header);

void guardarAnomalia(const std::string& descripcion);

void exportarJSON(const std::string& archivo);

#endif