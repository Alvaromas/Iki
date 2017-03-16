#ifndef STRUCTS_H
#define STRUCTS_H

#include <irrlicht.h>
#include <stdio.h>
#include "vector"
#include "string"
#include <math.h>
#include <windows.h>
#include <iosfwd>
#include <limits>

#include <Box2D/Box2D.h>

using namespace irr;

using namespace core; //namespace fundamentales;
using namespace scene; //namespace de escena;
using namespace video; //namespace de v�deo;
using namespace io; //namespace io;
using namespace gui; //namespace gui;

class Structs
{
    public:
        Structs();
        virtual ~Structs();

        struct TPosicion{
            float X;
            float Y;
            float Z;

            TPosicion():X(0.0),Y(0.0),Z(0.0){}
            TPosicion(float a, float b, float c):X(a),Y(b),Z(c){}

            //returns the length of the vector
            inline float Length()const{
                return sqrt(X * X + Y * Y + Z * Z);
            }

            inline void Normalize()
            {
              float vector_length = this->Length();
              if(vector_length != 0){
                this->X = (this->X / vector_length);
                this->Y = (this->Y / vector_length);
                this->Z = (this->Z / vector_length);
              }
            }
            //returns the distance between this vector and th one passed as a parameter
            inline float Distance(const TPosicion &v2)const{
                float zSeparation = v2.Z - Z;
                float xSeparation = v2.X - X;

                return sqrt(zSeparation*zSeparation + xSeparation*xSeparation);
            }
            const TPosicion operator+(const TPosicion &rhs){

                float  x = X +rhs.X;
                float  y = Y +rhs.Y;
                float  z = Z +rhs.Z;

                TPosicion result(x,y,z);
                return result;
            }
            const TPosicion operator-(const TPosicion &rhs) {
                float  x = X - rhs.X;
                float  y = Y - rhs.Y;
                float  z = Z - rhs.Z;

                TPosicion result(x,y,z);
                return result;
            }

            const TPosicion operator*(const TPosicion &rhs){
                float  x = X *rhs.X;
                float  y = Y *rhs.Y;
                float  z = Z *rhs.Z;
                TPosicion result (x,y,z);
                return result;
            }
            const TPosicion operator*(float rhs){
                float  x = X *rhs;
                float  y = Y *rhs;
                float  z = Z *rhs;
                TPosicion result (x,y,z);
                return result;
            }

            const TPosicion operator/(float rhs){
                float  x = X /rhs;
                float  y = Y /rhs;
                float  z = Z /rhs;
                TPosicion result (x,y,z);
                return result;
            }

            const TPosicion& operator+=(const TPosicion &rhs)
            {
                X += rhs.X;
                Y += rhs.Y;
                Z += rhs.Z;

                return *this;
            }

            const TPosicion& operator-=(const TPosicion &rhs)
            {
                X -= rhs.X;
                Y -= rhs.Y;
                Z -= rhs.Z;

                return *this;
            }

            const TPosicion& operator*=(const float& rhs)
            {
                X *= rhs;
                Y *= rhs;
                Z *= rhs;

                return *this;
            }

            const TPosicion& operator/=(const float& rhs)
            {
                X /= rhs;
                Y /= rhs;
                Z /= rhs;

                return *this;
            }

            bool operator==(const TPosicion& rhs)const
            {

                  if (fabs(X-rhs.X) < 1E-12 && fabs(Y-rhs.Y) < 1E-12 && fabs(Z-rhs.Z) < 1E-12 )
                  {
                    return true;
                  }
                  else{
                    return false;
                  }

            }

            bool operator!=(const TPosicion& rhs)const
            {
                return (X != rhs.X) || (Y != rhs.Y) || (Z != rhs.Z);
            }

        };

        typedef struct{
            int opacity;
            int r;
            int g;
            int b;
        }TColor;

        typedef struct{
            float ancho;
            float alto;
            float profundo;
        }TMedida;

        typedef struct{
            int X_inicio;
            int Y_inicio;
            int X_final;
            int Y_final;
        }TRectangulo;

    protected:

    private:
};



#endif // STRUCTS_H
