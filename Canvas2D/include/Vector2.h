#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__
#include <math.h>

class Vector2
{
public:
   float x, y;
   static Vector2 MinVector;
   static Vector2 MaxVector;

   Vector2();

   Vector2(float _x, float _y);

   void set(float _x, float _y);

   void normalize();

   float lenght();

   /// <summary>
   /// vetor perpendicular à esquerda
   /// </summary>
   Vector2 GetLeft();

   /// <summary>
   /// vetor perpendicular à direita
   /// </summary>
   Vector2 GetRight();

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

   Vector2& operator += (const Vector2& v)
   {
       this->x += v.x;
       this->y += v.y;
       return *this;
   }

   Vector2& operator -= (const Vector2& v)
   {
       this->x -= v.x;
       this->y -= v.y;
       return *this;
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
