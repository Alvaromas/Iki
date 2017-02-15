#ifndef GRAPHICSFACADE_H
#define GRAPHICSFACADE_H

#include "MyEventReceiver.h"

#include "Camera.h"
#include "SceneNode.h"
#include "Structs.h"


class GraphicsFacade
{
    friend class SceneNode;
    friend class MeshSceneNode;
    friend class AnimatedMesh;
    friend class Camera;

    public:

        static GraphicsFacade& getInstance() {
            static GraphicsFacade singleton;
            return singleton;
        }
        ~GraphicsFacade();

        void draw();
        bool run();
        void drop();

        void setWindowCaption();
        void iniciarRay(Structs::TPosicion rayPos);
        void cambiarRay(Camera* camara);
        bool interseccionRayPlano(Structs::TPosicion &mousePosition);
        float calcularDistancia(Structs::TPosicion position);
        ISceneManager* getScene() { return smgr; }
        IrrlichtDevice* getDevice() { return device; }
        IVideoDriver* getDriver() { return driver; }
        IGUIEnvironment* getGUI() { return guienv; }
        ITimer* getTimer() { return timer; };

        SceneNode* createCubeSceneNode(float tam, Structs::TPosicion posicionInicial);
        Camera* createCamera(Structs::TPosicion position, Structs::TPosicion lookAt);

    protected:

    private:

        GraphicsFacade();
        IrrlichtDevice* device;
        IVideoDriver* driver;
        ISceneManager* smgr;
        IGUIEnvironment* guienv;
        ITimer* timer;
        plane3df plane;
        line3df ray;
};

#endif // GRAPHICSFACADE_H