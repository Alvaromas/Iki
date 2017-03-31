#include "Patrullar.h"
#include "Vigilar.h"
#include "PedirAyuda.h"
#include "Investigar.h"
#include "Escanear.h"
#include "Enemy.h"
#include "StateMachine/Mensaje.h"


Patrullar* Patrullar::Instance()
{
  static Patrullar instance;

  return &instance;
}

void Patrullar::Enter(Enemy* enemigo){
}

void Patrullar::Execute(Enemy* enemigo){
    /*if(enemigo->isEnemySeeing(enemigo->getPosicionProta())){
        Structs::TColor color = {0,0,0,0};
        enemigo->cambiarColor(color);
    }
    else{
        Structs::TColor color = {0,0,0,255};
        enemigo->cambiarColor(color);
    }*/

    enemigo->patrullar();

    if(enemigo->getDistanciaPlayer() < 15){
        //std::cout<<"Escaneando..."<<std::endl;
        if(enemigo->isEnemySeeing(enemigo->getPosicionProta())){
            std::cout<<"Te he visto!..."<<std::endl;
            enemigo->GetFSM()->ChangeState(Escanear::Instance());
        }
    }

    if(enemigo->getPatrulla()->getInicial()->getNext()->getPunto() == enemigo->getPosition()){
        //std::cout<<"Vigilando..."<<std::endl;
        enemigo->GetFSM()->ChangeState(Vigilar::Instance());
    }

}

void Patrullar::Exit(Enemy* enemigo){}
bool Patrullar::OnMessage(Enemy* enemigo, const Mensaje& msg){
    switch( msg.Msg )
    {
        case Msg_NeedHelp:
        {
            std::cout<<"recibo el mensajeee"<<std::endl;
            enemigo->GetFSM()->ChangeState(Investigar::Instance());
        }
    }
}
