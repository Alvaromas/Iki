#ifndef MUROS_H
#define MUROS_H

#include "Structs.h"

class MapComponent;
class MeshSceneNode;

class Muros
{
    public:
        Muros(MapComponent*, MapComponent*);
        virtual ~Muros();

        b2Body* getBody(){ return body;}
        float calcularAngulo(Structs::TPosicion, Structs::TPosicion);

    protected:

    private:
        b2Body* body;
};

#endif // MUROS_H
