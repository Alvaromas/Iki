#include "HUD_Element.h"
#include "Fachada/Image.h"
#include "MyEventReceiver.h"

HUD_Element::HUD_Element(int x, int y, Structs::TRectangulo rect, std::string cadena, bool act)
{
    cadena = "resources/Texturas/"+cadena+".png";
    const char * c = cadena.c_str();
    imagen = new Image(c);

    rec = rect;
    posicionX = x;
    posicionY = y;
    color = {255,255,255,255};
    active = act;
}

HUD_Element::~HUD_Element()
{
    delete imagen;
}

void HUD_Element::draw(){
    imagen->draw(posicionX, posicionY, rec, color);
}

void HUD_Element::cambiarRect(Structs::TRectangulo rect){
    rec = rect;
}

bool HUD_Element::comprobarEncima(){
    std::cout<<"Posicion(x,y): ("<<posicionX<<","<<posicionY<<")"<<std::endl;
    std::cout<<"Posicion raton(x,y): ("<<MyEventReceiver::getInstance().GetMouseState().Position.X<<","<<MyEventReceiver::getInstance().GetMouseState().Position.Y<<")"<<std::endl;

    if(   (MyEventReceiver::getInstance().GetMouseState().Position.X > posicionX
       && MyEventReceiver::getInstance().GetMouseState().Position.X < posicionX + 110)
       && (MyEventReceiver::getInstance().GetMouseState().Position.Y > posicionY
       && MyEventReceiver::getInstance().GetMouseState().Position.Y < posicionY + 109)){

       std::cout<<"holi"<<std::endl;
       color = {255,125,125,125};
        return true;
       }
    else
        return false;
}

void HUD_Element::setActive(bool act){
    active = act;
}
