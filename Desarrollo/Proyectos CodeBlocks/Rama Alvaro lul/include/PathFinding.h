#ifndef PATHFINDING
#define PATHFINDING

#include <irrlicht.h>
#include <enemigo.h>
#include <NavGraph.h>
#include <vector>
#include <fstream>
#include <string>
#include <list>

class PathFinding
{
    public:
        PathFinding(Enemigo* owner);
        virtual ~PathFinding();
        irr::core::vector3df getPunto();
        bool crearPath(irr::core::vector3df destino, list<vector3df>& path);
        //Busca el path menos costoso entre el enemigo y el destino, rellena el path con una lista de waypoints y devuelve true si lo cosnigue.


    protected:

    private:
        irr::core::vector3df punto;
        Enemigo* enemigo; //Puntero al propietario de esta clase
        NavGraph grafo;//const NavGraph& grafo;//Una referencia local al navgraph?
        irr::core::vector3df posicionDestino;
        int getNodoMasCercano(irr::core::vector3df pos);
};

#endif // PATHFINDING