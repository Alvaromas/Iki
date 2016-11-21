
/** Example 019 Mouse and Joystick

This tutorial builds on example 04.Movement which showed how to
handle keyboard events in Irrlicht.  Here we'll handle mouse events
and joystick events, if you have a joystick connected and a device
that supports joysticks.  These are currently Windows, Linux and SDL
devices.
*/

#ifdef _MSC_VER
// We'll define this to stop MSVC complaining about sprintf().
#define _CRT_SECURE_NO_WARNINGS
#pragma comment(lib, "Irrlicht.lib")
#endif

#include <irrlicht.h>
#include "driverChoice.h"
#include <stdio.h>
#include <irrKlang.h>
#include <iostream>
#include <time.h>
#include <windows.h>


using namespace irrklang;
using namespace std;
using namespace irr;

#if defined(WIN32)
#include <conio.h>
#else
#include "conio.h"
#endif


/*
Just as we did in example 04.Movement, we'll store the latest state of the
mouse and the first joystick, updating them as we receive events.
*/
class MyEventReceiver : public IEventReceiver
{
    private:
        bool KeyDown[KEY_KEY_CODES_COUNT];
public:

	MyEventReceiver() {
            for(int i=0;i<KEY_KEY_CODES_COUNT;i++) {
                KeyDown[i] = false;
            }
        }

	struct SMouseState
	{
		core::position2di Position;
		bool LeftButtonDown;
		SMouseState() : LeftButtonDown(false) { }
	} MouseState;

	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember the mouse state
		if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
		{
			switch(event.MouseInput.Event)
			{
			case EMIE_LMOUSE_PRESSED_DOWN:
				MouseState.LeftButtonDown = true;
				break;

			case EMIE_LMOUSE_LEFT_UP:
				MouseState.LeftButtonDown = false;
				break;

			case EMIE_MOUSE_MOVED:
				MouseState.Position.X = event.MouseInput.X;
				MouseState.Position.Y = event.MouseInput.Y;
				break;

			default:
				// We won't use the wheel
				break;
			}
		}
		else if (event.EventType == irr::EET_KEY_INPUT_EVENT){
            KeyDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
		}

	}

    virtual bool isKeyDown(EKEY_CODE keyCode) const {
        return KeyDown[keyCode];
    }

    virtual bool isKeyUp(EKEY_CODE keyCode) const{
        return !KeyDown[keyCode];
    }
	const SMouseState & GetMouseState(void) const
	{
		return MouseState;
	}


};

/*
The event receiver for keeping the pressed keys is ready, the actual responses
will be made inside the render loop, right before drawing the scene. So lets
just create an irr::IrrlichtDevice and the scene node we want to move. We also
create some other additional scene nodes, to show that there are also some
different possibilities to move and animate scene nodes.
*/
int main()
{

    ISoundEngine* engine = createIrrKlangDevice();


	if (!engine)
		return 0; // error starting up the engine

	printf("Driver: %s\n",engine->getDriverName());
	printf("Volume: %f\n",engine->getSoundVolume());

	ISoundSource* pasos1 = engine->addSoundSourceFromFile("pasosnormales.wav");
	ISoundSource* pasos2 = engine->addSoundSourceFromFile("pasossigilosos.wav");
	vec3df posicion(0,0,0);
	ISound* s1;


	bool pasosP = false;
	bool pasos2P = false;

	if (pasos1 == 0 || pasos2 == 0)
        	fprintf(stderr,"Can't load sounds!");

    pasos1->setDefaultVolume(2.0f);
    pasos2->setDefaultVolume(1.0f);

	// ask user for driver
	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	if (driverType==video::EDT_COUNT)
		return 1;

	// create device
	MyEventReceiver receiver;

	IrrlichtDevice* device = createDevice(driverType,
			core::dimension2d<u32>(640, 480), 16, false, false, false, &receiver);

	if (device == 0)
		return 1; // could not create selected driver.

    video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	scene::IMeshSceneNode *cubeNode = smgr->addCubeSceneNode(10);
    if(cubeNode) {
          cubeNode->setMaterialFlag(video::EMF_LIGHTING, false);
          cubeNode->setPosition(core::vector3df(50,0,0));
    }

	scene::ICameraSceneNode * camera = smgr->addCameraSceneNode(0,core::vector3df(0,90,-40),core::vector3df(0,0,0));

	// As in example 04, we'll use framerate independent movement.
	u32 then = device->getTimer()->getTime();
	f32 MOVEMENT_SPEED;

        core::line3df ray;
        core::vector3df mousePosition;

	while(device->run())
	{
		// Work out a frame delta time.
		const u32 now = device->getTimer()->getTime();
		const f32 frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
		then = now;

		if(receiver.isKeyDown(KEY_LSHIFT))
            MOVEMENT_SPEED = 15.f;
        else
            MOVEMENT_SPEED = 25.f;


		f32 availableMovement = MOVEMENT_SPEED * frameDeltaTime;




        core::vector3df cameraPos = camera->getPosition();
        core::vector3df cameraTar = camera->getTarget();
		core::vector3df nodePosition = cubeNode->getPosition();
		core::plane3df plane(nodePosition, core::vector3df(0, -1, 0));



        if(receiver.isKeyDown(KEY_ESCAPE)) {
                device->closeDevice();
                return 0;
            }
            else if(receiver.isKeyDown(KEY_RIGHT)) {
                cameraPos.X+=0.1;
                cameraTar.X+=0.1;
            }
            else if (receiver.isKeyDown(KEY_LEFT)) {
                cameraPos.X-=0.1;
                cameraTar.X-=0.1;
            }
             else if(receiver.isKeyDown(KEY_UP)) {
                cameraPos.Z+=0.1;
                cameraTar.Z+=0.1;
            }
            else if (receiver.isKeyDown(KEY_DOWN)) {
                cameraPos.Z-=0.1;
                cameraTar.Z-=0.1;
            }

			else if(receiver.GetMouseState().LeftButtonDown){
			ray = smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(
				receiver.GetMouseState().Position, camera);

			}
			if(plane.getIntersectionWithLine(ray.start, ray.getVector(), mousePosition))
			{
				// We now have a mouse position in 3d space; move towards it.
				core::vector3df toMousePosition(mousePosition - nodePosition);

				 if(toMousePosition.getLength() <= availableMovement){
					nodePosition = mousePosition; // Jump to the final position
					if(pasosP==true || pasos2P==true){
                        s1->stop();
                        pasosP = false;
                        pasos2P = false;
					}

				 }
				else{
					nodePosition += toMousePosition.normalize() * availableMovement; // Move towards it
					if(pasosP==false && !receiver.isKeyDown(KEY_LSHIFT)){
                        if(engine->isCurrentlyPlaying(pasos2))
                            s1->stop();

                            s1 = engine->play3D(pasos1,posicion,true,false,true);

                        pasosP = true;
                        pasos2P = false;

                    }else if (pasos2P==false && receiver.isKeyDown(KEY_LSHIFT)){
                        if(engine->isCurrentlyPlaying(pasos1))
                            s1->stop();

                            s1 = engine->play3D(pasos2,posicion,true,false,true);
                        pasos2P = true;
                        pasosP = false;

                    }
                }
			}








		cubeNode->setPosition(nodePosition);
		camera->setPosition(cameraPos);
		camera->setTarget(cameraTar);


		driver->beginScene(true, true, video::SColor(255,113,113,133));
		smgr->drawAll(); // draw the 3d scene
		driver->endScene();
	}

	/*
	In the end, delete the Irrlicht device.
	*/
	device->drop();
	engine->drop();

	return 0;
}
