#include "Scene.h"
#include "Fachada/GraphicsFacade.h"
#include "PhisicsWorld.h"
#include "EntityManager.h"

Scene::Scene()
{
    world = new World();
    player = new Player();
}

Scene::~Scene()
{
    triggersystem.Clear();
    delete world;
    delete player;

}

void Scene::inicializar_escena(){

    Structs::TPosicion posicionCamara (190,30,40);
    Structs::TPosicion targetCamara (70,-10,40);
    Structs::TPosicion rayPos (170,0,50);

    camara = GraphicsFacade::getInstance().createCamera(posicionCamara, targetCamara);
    GraphicsFacade::getInstance().iniciarRay(rayPos);

    world->inicializar_mundo();
    mapa = world->getMapa();
    player->inicializar_player(mapa);

    Trigger* ruido = player->getRuido();
    triggersystem.Register(ruido);
    triggersystem.LeerMapa();

    bucle_juego();
}

void Scene::bucle_juego(){

    while(GraphicsFacade::getInstance().run()){

        world->update_mundo();
        player->update(camara);
        triggersystem.Update();
        camara->render(player->getPosition());
        PhisicsWorld::getInstance()->Step();

        GraphicsFacade::getInstance().draw();
    }

    GraphicsFacade::getInstance().drop();

}
