#ifndef TLUZ_H
#define TLUZ_H

#include <iostream>
#include <TEntidad.h>

#include "TShader.h"

class TLuz : public TEntidad
{
    public:
        TLuz(/*const glm::vec3& intensity*/);
        virtual ~TLuz();
        vec3 getPoscion(){return posicion;};
        vec3 getIntensidad(){return intensidad;};
        void setPosicion(vec3 pos);
        void setIntensidad(vec3 col);


        void beginDraw();
        void endDraw();

    protected:

    private:
        vec3 intensidad;
        vec3 posicion;

};

#endif // TLUZ_H
