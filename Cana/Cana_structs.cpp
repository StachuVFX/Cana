//
//  Cana_structs.cpp
//  Cana
//
//  Created by Stachu on 25.12.2025.
//

#include "Cana_structs.h"

/* Cana_Vec2 */
Cana_Vec2::Cana_Vec2() : x(0), y(0) {};
Cana_Vec2::Cana_Vec2(const float X, const float Y) : x(X), y(Y) {};

void Cana_Vec2::set(const float X, const float Y)
{
    x = X;
    y = Y;
}
/* Cana_Vec2 */
Cana_Vec3::Cana_Vec3() : x(0), y(0), z(0) {};
Cana_Vec3::Cana_Vec3(const float X, const float Y, const float Z) : x(X), y(Y), z(Z) {};

void Cana_Vec3::set(const float X, const float Y, const float Z)
{
    x = X;
    y = Y;
    z = Z;
}
