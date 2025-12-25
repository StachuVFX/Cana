//
//  Cana_structs.cpp
//  Cana
//
//  Created by Stachu on 25.12.2025.
//

#include "Cana_structs.h"

/* Cana_Vec2 */
Cana_Vec2::Cana_Vec2() : x(0), y(0) {};
Cana_Vec2::Cana_Vec2(const int X, const int Y) : x(X), y(Y) {};

void Cana_Vec2::set(const int X, const int Y)
{
    this->x = X;
    this->y = Y;
}
