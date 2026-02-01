//
//  Cana_objects3.cpp
//  Cana
//
//  Created by Stachu on 27.01.2026.
//

#include "Cana_objects3.h"

/* Cana_VertexArrayObject3 */
    /* Constructors */
Cana_VertexArrayObject3::Cana_VertexArrayObject3()
    : m_vertices(nullptr), m_vertexCount(0), m_indices(nullptr), m_indexCount(0), m_outlineIndices(nullptr), m_outlineIndexCount(0)
{
}
Cana_VertexArrayObject3::Cana_VertexArrayObject3(const int vertexCount, const int indexCount, const int outlineIndexCount)
    : m_vertices(new Cana_Vec3[vertexCount]), m_vertexCount(vertexCount),
        m_indices(new Cana_Vec3_int[indexCount]), m_indexCount(indexCount),
        m_outlineIndices(new Cana_Vec2_int[outlineIndexCount]), m_outlineIndexCount(outlineIndexCount)
{
}
    /* Destructor */
Cana_VertexArrayObject3::~Cana_VertexArrayObject3()
{
    delete[] m_vertices;
    delete[] m_indices;
    delete[] m_outlineIndices;
}
    /* Base */
        /* Init */
void Cana_VertexArrayObject3::createArrays(const int vertexCount, const int indexCount, const int outlineIndexCount)
{
    m_vertexCount = vertexCount;
    m_indexCount = indexCount;
    m_outlineIndexCount = outlineIndexCount;
    
    m_vertices = new Cana_Vec3[vertexCount];
    m_indices = new Cana_Vec3_int[indexCount];
    m_outlineIndices = new Cana_Vec2_int[outlineIndexCount];
}
        /* Vertices */
const Cana_Vec3* Cana_VertexArrayObject3::getVertices() const
{
    return m_vertices;
}
const int Cana_VertexArrayObject3::getVertexCount() const
{
    return m_vertexCount;
}
void Cana_VertexArrayObject3::setVertex(const int vertex_id, const Cana_Vec3 vertex)
{
    m_vertices[vertex_id] = vertex;
}
        /* Indices */
const Cana_Vec3_int* Cana_VertexArrayObject3::getIndices() const
{
    return m_indices;
}
const int Cana_VertexArrayObject3::getIndexCount() const
{
    return m_indexCount;
}
void Cana_VertexArrayObject3::setIndex(const int index_id, const Cana_Vec3_int index)
{
    m_indices[index_id] = index;
}
    /* Outline indices */
const Cana_Vec2_int* Cana_VertexArrayObject3::getOutlineIndices() const
{
    return m_outlineIndices;
}
const int Cana_VertexArrayObject3::getOutlineIndexCount() const
{
    return m_outlineIndexCount;
}
void Cana_VertexArrayObject3::setOutlineIndex(const int index_id, const Cana_Vec2_int index)
{
    m_outlineIndices[index_id] = index;
}

/* Cana_Drawable2 */
    /* Constructors */
Cana_Drawable3::Cana_Drawable3()
    : m_vertexArrayObject(), m_position(), m_scale(0.0f)
{
}
    /* Base */
        /* VAO */
const Cana_VertexArrayObject3* Cana_Drawable3::getVertexArrayObject() const
{
    return &m_vertexArrayObject;
}
        /* Appearance */
const Cana_Vec3 Cana_Drawable3::getPosition() const
{
    return m_position;
}
const float Cana_Drawable3::getScale() const
{
    return m_scale;
}

/* Cana_Primitive3 */
    /* Constructors */
Cana_Primitive3::Cana_Primitive3()
//    : m_position(0.0f, 0.0f, 0.0f), m_scale(1.0f)      // needs local declaration - ruins polymorphism
{
    reset();
}
Cana_Primitive3::Cana_Primitive3(const Cana_Vec3 position, const float scale)
//    : m_position(position), m_scale(scale)
{
    m_position = position;
    m_scale = scale;
}
    /* New */
void Cana_Primitive3::setPosition(const Cana_Vec3 location)
{
    m_position = location;
}
void Cana_Primitive3::changePosition(const Cana_Vec3 vector)
{
    m_position.x += vector.x;
    m_position.y += vector.y;
    m_position.z += vector.z;
}
void Cana_Primitive3::setScale(const float scale)
{
    m_scale = scale;
}
void Cana_Primitive3::changeScale(const float factor)
{
    m_scale *= factor;
}
    /* Virtual*/
void Cana_Primitive3::reset()
{
    m_position.x = 0.0f;
    m_position.y = 0.0f;
    m_position.z = 0.0f;
    m_scale = 1.0f;
}

/* Cana_Object3 */
    /* Constructors */
Cana_Object3::Cana_Object3()
//    : m_position(0.0f, 0.0f, 0.0f), m_scale(0.0f), m_orientationVectors()
{
    reset();
}
Cana_Object3::Cana_Object3(const Cana_Vec3 position)
//    : m_position(position), m_scale(0.0f), m_orientationVectors()
{
    reset();
    m_position = position;
}
Cana_Object3::Cana_Object3(const Cana_Vec3 position, const float scale, const Cana_Vec3 X, const Cana_Vec3 Y, const Cana_Vec3 Z)
//    : m_position(position), m_scale(scale), m_orientationVectors()
{
    m_position = position;
    m_scale = scale;
    m_orientationVectors[0] = X;
    m_orientationVectors[1] = Y;
    m_orientationVectors[2] = Z;
}
    /* Override */
void Cana_Object3::reset()
{
    m_position.x = 0.0f;
    m_position.y = 0.0f;
    m_position.z = 0.0f;
    m_scale = 0.0f;
    m_orientationVectors[0] = Cana_Vec3(0.0f, 0.0f, 0.0f);
    m_orientationVectors[1] = Cana_Vec3(0.0f, 0.0f, 0.0f);
    m_orientationVectors[2] = Cana_Vec3(0.0f, 0.0f, 0.0f);
}
    /* New */
const Cana_Vec3* Cana_Object3::getOrientationVectors() const
{
    return m_orientationVectors;
}
void Cana_Object3::setOrientationVectors(const Cana_Vec3 X, const Cana_Vec3 Y, const Cana_Vec3 Z)
{
    m_orientationVectors[0] = X;
    m_orientationVectors[1] = Y;
    m_orientationVectors[2] = Z;
}
void Cana_Object3::changeOrientationByAngles(const float X, const float Y, const float Z)
{
    // no f***in idea
}

/* Cana_Box */
    /* Constructors */
Cana_Box::Cana_Box(const Cana_Vec3 position, const float scale)
//    : m_position(position), m_scale(scale)      // needs local declaration - ruins polymorphism
{
    m_position = position;
    m_scale = scale;
    /* Create arrays */
    m_vertexArrayObject.createArrays(8, 12, 24);
    /* Vertices */
        /* lower */
    m_vertexArrayObject.setVertex(0, Cana_Vec3(-0.5f, -0.5f, -0.5f));
    m_vertexArrayObject.setVertex(1, Cana_Vec3( 0.5f, -0.5f, -0.5f));
    m_vertexArrayObject.setVertex(2, Cana_Vec3( 0.5f,  0.5f, -0.5f));
    m_vertexArrayObject.setVertex(3, Cana_Vec3(-0.5f,  0.5f, -0.5f));
        /* upper */
    m_vertexArrayObject.setVertex(0, Cana_Vec3(-0.5f, -0.5f,  0.5f));
    m_vertexArrayObject.setVertex(1, Cana_Vec3( 0.5f, -0.5f,  0.5f));
    m_vertexArrayObject.setVertex(2, Cana_Vec3( 0.5f,  0.5f,  0.5f));
    m_vertexArrayObject.setVertex(3, Cana_Vec3(-0.5f,  0.5f,  0.5f));
    /* Triangle indices */
        /* bottom */
    m_vertexArrayObject.setIndex(0, Cana_Vec3_int(0, 1, 2));
    m_vertexArrayObject.setIndex(1, Cana_Vec3_int(2, 3, 0));
        /* top */
    m_vertexArrayObject.setIndex(2, Cana_Vec3_int(4, 5, 6));
    m_vertexArrayObject.setIndex(3, Cana_Vec3_int(6, 7, 4));
        /* left */
    m_vertexArrayObject.setIndex(4, Cana_Vec3_int(3, 0, 4));
    m_vertexArrayObject.setIndex(5, Cana_Vec3_int(4, 7, 3));
        /* right */
    m_vertexArrayObject.setIndex(6, Cana_Vec3_int(1, 2, 6));
    m_vertexArrayObject.setIndex(7, Cana_Vec3_int(6, 5, 1));
        /* front */
    m_vertexArrayObject.setIndex(8, Cana_Vec3_int(0, 1, 5));
    m_vertexArrayObject.setIndex(9, Cana_Vec3_int(5, 4, 0));
        /* back */
    m_vertexArrayObject.setIndex(10, Cana_Vec3_int(3, 2, 6));
    m_vertexArrayObject.setIndex(11, Cana_Vec3_int(6, 7, 3));
    /* Outline indices */
        /* bottom */
    m_vertexArrayObject.setOutlineIndex(0, Cana_Vec2_int(0, 1));
    m_vertexArrayObject.setOutlineIndex(1, Cana_Vec2_int(1, 2));
    m_vertexArrayObject.setOutlineIndex(2, Cana_Vec2_int(2, 3));
    m_vertexArrayObject.setOutlineIndex(3, Cana_Vec2_int(3, 0));
        /* top */
    m_vertexArrayObject.setOutlineIndex(4, Cana_Vec2_int(4, 5));
    m_vertexArrayObject.setOutlineIndex(5, Cana_Vec2_int(5, 6));
    m_vertexArrayObject.setOutlineIndex(6, Cana_Vec2_int(6, 7));
    m_vertexArrayObject.setOutlineIndex(7, Cana_Vec2_int(7, 4));
        /* left */
    m_vertexArrayObject.setOutlineIndex(8, Cana_Vec2_int(3, 0));
    m_vertexArrayObject.setOutlineIndex(9, Cana_Vec2_int(0, 4));
    m_vertexArrayObject.setOutlineIndex(10, Cana_Vec2_int(4, 7));
    m_vertexArrayObject.setOutlineIndex(11, Cana_Vec2_int(7, 3));
        /* right */
    m_vertexArrayObject.setOutlineIndex(12, Cana_Vec2_int(1, 2));
    m_vertexArrayObject.setOutlineIndex(13, Cana_Vec2_int(2, 6));
    m_vertexArrayObject.setOutlineIndex(14, Cana_Vec2_int(6, 5));
    m_vertexArrayObject.setOutlineIndex(15, Cana_Vec2_int(5, 1));
        /* front */
    m_vertexArrayObject.setOutlineIndex(16, Cana_Vec2_int(0, 1));
    m_vertexArrayObject.setOutlineIndex(17, Cana_Vec2_int(1, 5));
    m_vertexArrayObject.setOutlineIndex(18, Cana_Vec2_int(5, 4));
    m_vertexArrayObject.setOutlineIndex(19, Cana_Vec2_int(4, 0));
        /* back */
    m_vertexArrayObject.setOutlineIndex(20, Cana_Vec2_int(3, 2));
    m_vertexArrayObject.setOutlineIndex(21, Cana_Vec2_int(2, 6));
    m_vertexArrayObject.setOutlineIndex(22, Cana_Vec2_int(6, 7));
    m_vertexArrayObject.setOutlineIndex(23, Cana_Vec2_int(7, 3));
}
    /* Override (from Cana_Primitive2) */
void Cana_Box::reset()
{
    m_position.x = 0.0f;
    m_position.y = 0.0f;
    m_position.z = 0.0f;
    m_scale = 1.0f;
}
