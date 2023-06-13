#ifndef __VECTOR_2_H__
#define __VECTOR_2_H__
#include <math.h>

class Vector2
{
public:
   float x, y;
   static Vector2 MinVector;
   static Vector2 MaxVector;
   static Vector2 Random();

   Vector2();

   Vector2(float _x, float _y);

   void set(float _x, float _y);

   void normalize();

   void rotate(float angle);

   float dot(Vector2 other);

   float length();

   float lengthSqr();

   /// <summary>
   /// vetor perpendicular à esquerda
   /// </summary>
   Vector2 GetLeft();

   /// <summary>
   /// vetor perpendicular à direita
   /// </summary>
   Vector2 GetRight();

   Vector2(const Vector2& v)
   {
	   this->x = v.x;
	   this->y = v.y;
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

   bool operator == (const Vector2& v)
   {
	   return (this->x == v.x && this->y == v.y);
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
