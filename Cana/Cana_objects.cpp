//
//  Cana_objects.cpp
//  Cana
//
//  Created by Stachu on 29.12.2025.
//

#include "Cana_objects.h"

/* Cana_VertexArrayObject2 */
    /* Constructors */
Cana_VertexArrayObject2::Cana_VertexArrayObject2()
    : m_vertices(nullptr), m_vertexCount(0), m_indices(nullptr), m_indexCount(0), m_outlineIndices(nullptr), m_outlineIndexCount(0)
{
}
Cana_VertexArrayObject2::Cana_VertexArrayObject2(const int vertexCount, const int indexCount, const int outlineIndexCount)
    : m_vertices(new Cana_Vec2[vertexCount]), m_vertexCount(vertexCount),
        m_indices(new Cana_Vec3_int[indexCount]), m_indexCount(indexCount),
        m_outlineIndices(new Cana_Vec2_int[outlineIndexCount]), m_outlineIndexCount(outlineIndexCount)
{
}
    /* Destructor */
Cana_VertexArrayObject2::~Cana_VertexArrayObject2()
{
    delete[] m_vertices;
    delete[] m_indices;
    delete[] m_outlineIndices;
}
    /* Base */
        /* Init */
void Cana_VertexArrayObject2::createArrays(const int vertexCount, const int indexCount, const int outlineIndexCount)
{
    m_vertexCount = vertexCount;
    m_indexCount = indexCount;
    m_outlineIndexCount = outlineIndexCount;
    
    m_vertices = new Cana_Vec2[vertexCount];
    m_indices = new Cana_Vec3_int[indexCount];
    m_outlineIndices = new Cana_Vec2_int[outlineIndexCount];
}
        /* Vertices */
const Cana_Vec2* Cana_VertexArrayObject2::getVertices() const
{
    return m_vertices;
}
const int Cana_VertexArrayObject2::getVertexCount() const
{
    return m_vertexCount;
}
void Cana_VertexArrayObject2::setVertex(const int vertex_id, const Cana_Vec2 vertex)
{
    m_vertices[vertex_id] = vertex;
}
        /* Indices */
const Cana_Vec3_int* Cana_VertexArrayObject2::getIndices() const
{
    return m_indices;
}
const int Cana_VertexArrayObject2::getIndexCount() const
{
    return m_indexCount;
}
void Cana_VertexArrayObject2::setIndex(const int index_id, const Cana_Vec3_int index)
{
    m_indices[index_id] = index;
}
    /* Outline indices */
const Cana_Vec2_int* Cana_VertexArrayObject2::getOutlineIndices() const
{
    return m_outlineIndices;
}
const int Cana_VertexArrayObject2::getOutlineIndexCount() const
{
    return m_outlineIndexCount;
}
void Cana_VertexArrayObject2::setOutlineIndex(const int index_id, const Cana_Vec2_int index)
{
    m_outlineIndices[index_id] = index;
}

/* Cana_Drawable2 */
    /* Constructors */
Cana_Drawable2::Cana_Drawable2()
    : m_vertexArrayObject(), m_position(), m_scale(0.0f)
{
}
    /* Base */
        /* VAO */
const Cana_VertexArrayObject2* Cana_Drawable2::getVertexArrayObject() const
{
    return &m_vertexArrayObject;
}
        /* Appearance */
const Cana_Vec2 Cana_Drawable2::getPosition() const
{
    return m_position;
}
const float Cana_Drawable2::getScale() const
{
    return m_scale;
}

/* Cana_Primitive2 */
    /* Constructors */
Cana_Primitive2::Cana_Primitive2()
//    : m_position(0.0f, 0.0f), m_scale(1.0f)      // needs local declaration - ruins polymorphism
{
    reset();
}
Cana_Primitive2::Cana_Primitive2(const Cana_Vec2 position, const float scale)
//    : m_position(position), m_scale(scale)
{
    m_position = position;
    m_scale = scale;
}
    /* New */
void Cana_Primitive2::setPosition(const Cana_Vec2 location)
{
    m_position = location;
}
void Cana_Primitive2::changePosition(const Cana_Vec2 vector)
{
    m_position.x += vector.x;
    m_position.y += vector.y;
}
void Cana_Primitive2::setScale(const float scale)
{
    m_scale = scale;
}
void Cana_Primitive2::changeScale(const float factor)
{
    m_scale *= factor;
}
    /* Virtual*/
void Cana_Primitive2::reset()
{
    m_position.x = 0.0f;
    m_position.y = 0.0f;
    m_scale = 1.0f;
}

/* Cana_Object2 */
    /* Constructors */
Cana_Object2::Cana_Object2()
//    : m_position(0.0f, 0.0f), m_scale(0.0f), m_orientationAngle(0.0f)
{
    reset();
}
Cana_Object2::Cana_Object2(const Cana_Vec2 position)
//    : m_position(position), m_scale(0.0f), m_orientationAngle(0.0f)
{
    reset();
    m_position = position;
}
Cana_Object2::Cana_Object2(const Cana_Vec2 position, const float orientationAngle, const float scale)
//    : m_position(position), m_scale(scale), m_orientationAngle(orientationAngle)
{
    m_position = position;
    m_orientationAngle = orientationAngle;
    m_scale = scale;
}
    /* Override */
void Cana_Object2::reset()
{
    m_position.x = 0.0f;
    m_position.y = 0.0f;
    m_scale = 0.0f;
    m_orientationAngle = 0.0f;
}
    /* New */
const float Cana_Object2::getOrientationAngle() const
{
    return m_orientationAngle;
}
void Cana_Object2::setOrientationAngle(const float angle)
{
    m_orientationAngle = angle;
}
void Cana_Object2::changeOrientationAngle(const float angle)
{
    m_orientationAngle += angle;
}

/* Cana_Square */
    /* Constructors */
Cana_Square::Cana_Square(const Cana_Vec2 position, const float scale)
//    : m_position(position), m_scale(scale)      // needs local declaration - ruins polymorphism
{
    m_position = position;
    m_scale = scale;
    /* Create arrays */
    m_vertexArrayObject.createArrays(4, 2, 4);
    /* Vertices */
    m_vertexArrayObject.setVertex(0, Cana_Vec2(-0.5f, -0.5f));
    m_vertexArrayObject.setVertex(1, Cana_Vec2( 0.5f, -0.5f));
    m_vertexArrayObject.setVertex(2, Cana_Vec2( 0.5f,  0.5f));
    m_vertexArrayObject.setVertex(3, Cana_Vec2(-0.5f,  0.5f));
    /* Triangle indices */
    m_vertexArrayObject.setIndex(0, Cana_Vec3_int(0, 1, 2));
    m_vertexArrayObject.setIndex(1, Cana_Vec3_int(2, 3, 0));
    /* Outline indices */
    m_vertexArrayObject.setOutlineIndex(0, Cana_Vec2_int(0, 1));
    m_vertexArrayObject.setOutlineIndex(1, Cana_Vec2_int(1, 2));
    m_vertexArrayObject.setOutlineIndex(2, Cana_Vec2_int(2, 3));
    m_vertexArrayObject.setOutlineIndex(3, Cana_Vec2_int(3, 0));
}
    /* Override (from Cana_Primitive2) */
void Cana_Square::reset()
{
    m_position.x = 0.0f;
    m_position.y = 0.0f;
    m_scale = 1.0f;
}
/* Cana_EqualArmTriangle */
    /* Constructors */
Cana_EqualArmTriangle::Cana_EqualArmTriangle(const Cana_Vec2 position, const float scale)
//    : m_position(position), m_scale(scale)      // needs local declaration - ruins polymorphism
{
    m_position = position;
    m_scale = scale;
    /* Create arrays */
    m_vertexArrayObject.createArrays(3, 1, 3);
    /* Vertices */
    m_vertexArrayObject.setVertex(0, Cana_Vec2(-0.55f, -0.5f));
    m_vertexArrayObject.setVertex(1, Cana_Vec2( 0.55f, -0.5f));
    m_vertexArrayObject.setVertex(2, Cana_Vec2( 0.0f,  0.5f));
    /* Triangle indices */
    m_vertexArrayObject.setIndex(0, Cana_Vec3_int(0, 1, 2));
    /* Outline indices */
    m_vertexArrayObject.setOutlineIndex(0, Cana_Vec2_int(0, 1));
    m_vertexArrayObject.setOutlineIndex(1, Cana_Vec2_int(1, 2));
    m_vertexArrayObject.setOutlineIndex(2, Cana_Vec2_int(2, 0));
}
    /* Override (from Cana_Primitive2) */
void Cana_EqualArmTriangle::reset()
{
    m_position.x = 0.0f;
    m_position.y = 0.0f;
    m_scale = 1.0f;
}
