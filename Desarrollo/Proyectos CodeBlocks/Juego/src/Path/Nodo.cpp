#include "Nodo.h"

int Nodo::Index() const{
    return index;
}

void Nodo::setIndex(int idx){
    index=idx;
}
float Nodo::calcularCoste(Nodo b){
    return posicion.getDistanceFrom(b.posicion);
}
