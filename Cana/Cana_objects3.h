//
//  Cana_objects3.h
//  Cana
//
//  Created by Stachu on 27.01.2026.
//

#pragma once

#include "Cana_structs.h"


/**
 * Class for 3D vertex and index arrays
 */
class Cana_VertexArrayObject3 {
/* Member variables */
private:
    /* Constructors */
    Cana_VertexArrayObject3(const int vertexCount, const int indexCount, const int outlineIndexCount);   // not used
    
    Cana_Vec3* m_vertices;
    int m_vertexCount;
    Cana_Vec3_int* m_indices;
    int m_indexCount;
    Cana_Vec2_int* m_outlineIndices;
    int m_outlineIndexCount;
    
/* Methods */
public:
    /* Constructors */
    Cana_VertexArrayObject3();
    /* Destructor */
    ~Cana_VertexArrayObject3();
    
    /* Base */
        /* Init */
    void createArrays(const int vertexCount, const int indexCount, const int outlineIndexCount);
        /* Vertices */
    const Cana_Vec3* getVertices() const;
    const int getVertexCount() const;
    void setVertex(const int vertex_id, const Cana_Vec3 vertex);
        /* Indices */
    const Cana_Vec3_int* getIndices() const;
    const int getIndexCount() const;
    void setIndex(const int index_id, const Cana_Vec3_int index);
        /* Outline indices */
    const Cana_Vec2_int* getOutlineIndices() const;
    const int getOutlineIndexCount() const;
    void setOutlineIndex(const int index_id, const Cana_Vec2_int index);
};

/**
 * 3D drawable class
 *
 * Base class for any drawable 3D object
 *
 * Can't be instantiated
 */
class Cana_Drawable3 {
/* Member variables */
protected:
    /* Constructors */
    Cana_Drawable3();   // can't be instantiated, but child classes can (because it's protected)
    
    /* Base */
        /* VAO */
    Cana_VertexArrayObject3 m_vertexArrayObject;
        /* Appearance */
    Cana_Vec3 m_position;   // 1 unit - 1 meter
    float m_scale;
    
/* Methods */
public:
    /* Base */
        /* VAO */
    const Cana_VertexArrayObject3* getVertexArrayObject() const;
        /* Appearance */
    const Cana_Vec3 getPosition() const;
    const float getScale() const;
};
/**
 * 3D primitive class
 *
 * Base class for Cana\_Object3
 *
 * Extends Cana\_Drawable3 with methods
 */
class Cana_Primitive3 : public Cana_Drawable3 {
/* Member variables */
protected:
    /* Constructors */
    Cana_Primitive3();
    Cana_Primitive3(const Cana_Vec3 position, const float scale);
    
    /* Inherited (from Cana_Drawable3) */   // need to be declared for member initializer list
        /* VAO */
//    Cana_VertexArrayObject3 m_vertexArrayObject;
        /* Appearance */
//    Cana_Vec3 m_position;   // 1 unit - 1 meter
//    float m_scale;
    
/* Methods */
public:
    /* Inherited */
        /* VAO, position and scale (from Cana_Drawable2) */
    const Cana_VertexArrayObject3 getVertexArrayObject() const;
    const Cana_Vec3 getPosition() const;
    const float getScale() const;
    
    /* New */
    void setPosition(const Cana_Vec3 location);
    void changePosition(const Cana_Vec3 vector);
    void setScale(const float scale);
    void changeScale(const float factor);
        /* Vitrual */
    virtual void reset();   // for learning purposes
};
/**
 * 3D static object class
 *
 * Inherits from Cana\_Primitive3
 */
class Cana_Object3 : public Cana_Primitive3 {
/* Member variables */
protected:
    /* Constructors */
        /* Old */
    Cana_Object3();
        /* New */
    Cana_Object3(const Cana_Vec3 position);
    Cana_Object3(const Cana_Vec3 position, const float scale, const Cana_Vec3 X, const Cana_Vec3 Y, const Cana_Vec3 Z);
    
    /* Inherited (from Cana_Drawable3) */   // need to be declared for member initializer list
//        /* VAO */
//    Cana_VertexArrayObject3 m_vertexArrayObject;
//        /* Appearance */
//    Cana_Vec3 m_position;   // 1 unit - 1 meter
//    float m_scale;
    
    /* New */
        /* Rotation vectors */
    Cana_Vec3 m_orientationVectors[3];
    
/* Methods */
public:
    /* Inherited */      // (don't need to be declared, but good for readability)
        /* VAO, position and scale (from Cana_Drawable3) */
    const Cana_VertexArrayObject3 getVertexArrayObject() const;
    const Cana_Vec3 getPosition() const;
    const float getScale() const;
        /* Position and scale (from Cana_Primitive3) */
    void setPosition(const Cana_Vec3 location);
    void changePosition(const Cana_Vec3 vector);
    void setScale(const float scale);
    void changeScale(const float factor);
    
    /* Override (from Cana_Primitive3) */
    void reset() override;
    
    /* New */
        /* Orientation vectors */
    const Cana_Vec3* getOrientationVectors() const;
    void setOrientationVectors(const Cana_Vec3 X, const Cana_Vec3 Y, const Cana_Vec3 Z);
    void changeOrientationByAngles(const float X, const float Y, const float Z);
};

/**
 * 3D square class
 *
 * Extends Cana\_Primitive3
 */
class Cana_Box : public Cana_Primitive3 {
/* Member variables */
protected:
    /* Constructors */
    Cana_Box();
    
    /* Inherited (from Cana_Drawable3) */   // need to be declared for member initializer list
        /* VAO */
//    Cana_VertexArrayObject3 m_vertexArrayObject;
        /* Appearance */
//    Cana_Vec3 m_position;   // 1 unit - 1 meter
//    float m_scale;
    
/* Methods */
public:
    /* Constructors */
    Cana_Box(const Cana_Vec3 position, const float scale);
    
    /* Inherited */      // (don't need to be declared, but good for readability)
        /* VAO, position and scale (from Cana_Drawable2) */
    const Cana_VertexArrayObject3 getVertexArrayObject() const;
    const Cana_Vec3 getPosition() const;
    const float getScale() const;
        /* Position and scale (from Cana_Primitive2) */
    void setPosition(const Cana_Vec3 location);
    void changePosition(const Cana_Vec3 vector);
    void setScale(const float scale);
    void changeScale(const float factor);
    
    /* New */
    
    /* Override (from Cana_Primitive2) */
    void reset() override;
};
