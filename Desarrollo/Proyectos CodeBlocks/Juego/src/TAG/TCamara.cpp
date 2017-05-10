#include "TCamara.h"
#include "TLinea.h"

TCamara::TCamara(const vec3& pos, float grad, int anch, int alt, float cer, float lej)
{
    v_posicion = pos;

    setPerspectiva(grad, anch, alt, cer, lej);
}

TCamara::~TCamara()
{
    //dtor
}

void TCamara::setPerspectiva(float grad, int anch, int alt, float cer, float lej)
{
    cercano   = cer;
    lejano    = lej;
    ancho = anch;
    alto = alt; //comprobar

    viewpoint= ancho/alto;

    m_perspectiva= perspective((float) radians(grad), viewpoint, cer, lej);

    esPerspectiva = true;
}

void TCamara::setParalela(float izq, float dch, float inf, float sup, float cer, float lej)
{


    m_paralela= ortho(izq, dch, inf, sup, cer, lej);

    esPerspectiva = false;
}

mat4 TCamara::getMatrizProyeccion() const
{
    if(esPerspectiva)
        //return m_perspectiva;
         return m_perspectiva;// * lookAt(v_posicion, v_posicion + vec3(0,0,1), vec3(0,1,0));
    else
        return m_paralela;
}

void TCamara::beginDraw()
{
  //  std::cout << "  Camara detected " << std::endl;
}
void TCamara::endDraw()
{

}

TLinea TCamara::getRayFromScreenCoordinates(float x, float y){
    float x2 = ((derecha  - izquierda) * x) / ancho;
    float y2 = ((inferior - superior)  * x) / alto;

    return TLinea(0,0,0,x2,y2,cercano);
}
