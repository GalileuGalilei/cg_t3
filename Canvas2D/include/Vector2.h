#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__
#include <math.h>

class Vector2
{
public:
   float x, y;
   static Vector2 minimun;
   static Vector2 maximun;

   Vector2()
   {
      x = y = 0;
   }

   Vector2(float _x, float _y)
   {
       x = _x;
       y = _y;
   }

   void set(float _x, float _y)
   {
       x = _x;
       y = _y;
   }

   void normalize()
   {
       float norm = (float)sqrt(x*x + y*y);

       if(norm==0.0)
       {
          x = 1;
          y = 1;
          return;
       }
       x /= norm;
       y /= norm;
   }

   Vector2 operator - (const Vector2& v)
   {
        Vector2 aux( x - v.x, y - v.y);
        return( aux );
   }

   Vector2 operator + (const Vector2& v)
   {
       Vector2 aux( x + v.x, y + v.y);
       return( aux );
   }

   Vector2 operator * (const float escalar)
   {
	   Vector2 aux( x * escalar, y * escalar);
	   return( aux );
   }

   Vector2 operator / (const float escalar)
   {
	   Vector2 aux(x / escalar, y / escalar);
	   return( aux );
   }

   //Adicionem os demais overloads de operadores aqui.

   static float distance(Vector2 a, Vector2 b)
   {
	   return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
   }

   static Vector2 max(Vector2 a, Vector2 b)
   {
       float x;
       float y;
       x = a.x > b.x ? a.x : b.x;
       y = a.y > b.y ? a.y : b.y;

       return Vector2(x, y);
   }

   static Vector2 min(Vector2 a, Vector2 b)
   {
       float x;
       float y;
       x = a.x < b.x ? a.x : b.x;
       y = a.y < b.y ? a.y : b.y;

       return Vector2(x, y);
   }
};

#endif
