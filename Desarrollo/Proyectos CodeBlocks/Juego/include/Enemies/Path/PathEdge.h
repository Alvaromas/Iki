#ifndef PATHEDGE_H
#define PATHEDGE_H

#include "Structs.h"

class PathEdge
{
    public:PathEdge(Structs::TPosicion Source,Structs::TPosicion Destination,int Behavior)
                    :desde(Source),
                     hasta(Destination),
                     behavior(Behavior){}

    Structs::TPosicion getDestination()const{return hasta;}
    void SetDestination(Structs::TPosicion NewDest){hasta=NewDest;}
    Structs::TPosicion getSource()const{return desde;}
    void SetSource(Structs::TPosicion NewSource){desde=NewSource;}
    int Behavior()const;


    protected:

    private:
        Structs::TPosicion desde;
        Structs::TPosicion hasta;
        //the behavior associated with traversing this edge
        int behavior;
};

#endif // PATHEDGE
