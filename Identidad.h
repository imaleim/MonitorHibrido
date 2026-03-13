//LUIS SANTIAGO CANTU NIÑO

#ifndef IDENTIDAD_H
#define IDENTIDAD_H

#include <string>

std::string obtenerMAC(const std::string& iface);
std::string obtenerIP(const std::string& iface);

void monitorearIdentidad(std::string iface, int intervalo);

#endif
