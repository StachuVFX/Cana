//
//  Cana_objects2.h
//  Cana
//
//  Created by Stachu on 10.07.2026. (originally 29.12.2025)
//

#pragma once

#include "Cana_structs.h"

/**
 * Class for 2D vertex and index arrays
 */
class Cana_VertexArrayObject2 {
/* Member variables */
protected:
    Cana_Vec2* m_vertices;
    int m_vertexCount;
    Cana_Vec3_int* m_indices;
    int m_indexCount;
    Cana_Vec2_int* m_outlineIndices;
    int m_outlineIndexCount;
    
/* Methods */
protected:
    /* Constructors */
    Cana_VertexArrayObject2(const int vertexCount, const int indexCount, const int outlineIndexCount);   // not used, potential memory leak
    
public:
    /* Constructors */
    Cana_VertexArrayObject2();
    /* Destructor */
    ~Cana_VertexArrayObject2();
    
    /* Base */
        /* Init */
    void createArrays(const int vertexCount, const int indexCount, const int outlineIndexCount);
        /* Vertices */
    const Cana_Vec2* getVertices() const;
    const int getVertexCount() const;
    void setVertex(const int vertex_id, const Cana_Vec2 vertex);
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
 * 2D drawable class
 *
 * Base class for any drawable 2D object
 *
 * Can't be instantiated + read only
 */
class Cana_Drawable2 {
/* Member variables */
protected:
    /* Base */
        /* VAO */
    Cana_VertexArrayObject2 m_vertexArrayObject;
        /* Appearance */
    Cana_Vec2 m_position;   // 1 unit - 1 meter
    float m_scale;
    
/* Methods */
protected:
    /* Constructors */
    Cana_Drawable2();   // can't be instantiated, but child classes can (because it's protected)
    
public:
    /* Base */
        /* VAO */
    const Cana_VertexArrayObject2* getVertexArrayObject() const;
        /* Appearance */
    const Cana_Vec2 getPosition() const;
    const float getScale() const;
};

/**
 * 2D primitive class
 *
 * Base class for Cana\_Object2
 *
 * Extends Cana\_Drawable2 with methods
 */
class Cana_Primitive2 : public Cana_Drawable2 {
/* Member variables */
protected:
//    /* Inherited (from Cana_Drawable2) */   // need to be declared for member initializer list (but it's already included)
//        /* VAO */
//    Cana_VertexArrayObject2 m_vertexArrayObject;
//        /* Appearance */
//    Cana_Vec2 position;   // 1 unit - 1 meter
//    float scale;
    
/* Methods */
protected:
    /* Constructors */   // can't be instantiated
    Cana_Primitive2();
    Cana_Primitive2(const Cana_Vec2 position, const float scale);
    
public:
//    /* Inherited */   // (don't need to be declared, but good for readability)
//        /* VAO, position and scale (from Cana_Drawable2) */
//    const Cana_VertexArrayObject2* getVertexArrayObject() const;
//    const Cana_Vec2 getPosition() const;
//    const float getScale() const;
    
    /* New */
    void setPosition(const Cana_Vec2 location);
    void changePosition(const Cana_Vec2 vector);
    void setScale(const float scale);
    void changeScale(const float factor);
    
        /* Virtual */
    virtual void reset();   // for learning purposes
};

/**
 * 2D static object class
 *
 * Extends Cana\_Primitive2
 */
class Cana_Object2 : public Cana_Primitive2 {
/* Member variables */
protected:
//    /* Inherited (from Cana_Drawable2) */   // need to be declared for member initializer list (but it's already included)
//        /* VAO */
//    Cana_VertexArrayObject2 m_vertexArrayObject;
//        /* Appearance */
//    Cana_Vec2 position;   // 1 unit - 1 meter
//    float scale;
    
    /* New */
    float m_orientationAngle;   // rotation
    
/* Methods */
protected:
    /* Constructors */
        /* Old */
    Cana_Object2();
        /* New */
    Cana_Object2(const Cana_Vec2 position);
    Cana_Object2(const Cana_Vec2 position, const float scale);
    Cana_Object2(const Cana_Vec2 position, const float scale, const float orientationAngle);
    
public:
//    /* Inherited */   // (don't need to be declared, but good for readability)
//        /* VAO, position and scale (from Cana_Drawable2) */
//    const Cana_VertexArrayObject2* getVertexArrayObject() const;
//    const Cana_Vec2 getPosition() const;
//    const float getScale() const;
//        /* Position and scale (from Cana_Primitive2) */
//    void setPosition(const Cana_Vec2 location);
//    void changePosition(const Cana_Vec2 vector);
//    void setScale(const float scale);
//    void changeScale(const float factor);
    
    /* Override (from Cana_Primitive2) */
    void reset() override;
    
    /* New */
        /* Orientation angle (in degrees) */
    const float getOrientationAngle() const;
    void setOrientationAngle(const float angle);
    void changeOrientationAngle(const float angle);
};

/**
 * 2D square class
 *
 * Extends Cana\_Object2
 */
class Cana_Square2 : public Cana_Object2 {
/* Member variables */
protected:
//    /* Inherited (from Cana_Drawable2) */   // need to be declared for member initializer list (but it's already included)
//        /* VAO */
//    Cana_VertexArrayObject2 m_vertexArrayObject;
//        /* Appearance */
//    Cana_Vec2 position;   // 1 unit - 1 meter
//    float scale;
//            /* (from Cana_Object2) */
//    float m_orientationAngle;   // rotation
    
/* Methods */
protected:
    /* Constructors */
    Cana_Square2();
    
public:
    /* Constructors */
    Cana_Square2(const Cana_Vec2 position, const float scale);
    Cana_Square2(const Cana_Vec2 position, const float scale, const float orientationAngle);
    
//    /* Inherited */      // (don't need to be declared, but good for readability)
//        /* VAO, position and scale (from Cana_Drawable2) */
//    const Cana_VertexArrayObject2* getVertexArrayObject() const;
//    const Cana_Vec2 getPosition() const;
//    const float getScale() const;
//        /* Position and scale (from Cana_Primitive2) */
//    void setPosition(const Cana_Vec2 location);
//    void changePosition(const Cana_Vec2 vector);
//    void setScale(const float scale);
//    void changeScale(const float factor);
//        /* Orientation angle (in degrees) */
//    const float getOrientationAngle() const;
//    void setOrientationAngle(const float angle);
//    void changeOrientationAngle(const float angle);
    
    /* Override (from Cana_Primitive2) */
    void reset() override;
    
    /* New */
protected:
        /* VAO init */
    void setVAO();   // potential memory leak if ran more than once
};

/**
 * 2D equal-arm triangle class
 *
 * Extends Cana\_Object2
 */
class Cana_EqualArmTriangle2 : public Cana_Object2 {
/* Member variables */
protected:
//    /* Inherited (from Cana_Drawable2) */   // need to be declared for member initializer list (but it's already included)
//        /* VAO */
//    Cana_VertexArrayObject2 m_vertexArrayObject;
//        /* Appearance */
//    Cana_Vec2 position;   // 1 unit - 1 meter
//    float scale;
//            /* (from Cana_Object2) */
//    float m_orientationAngle;   // rotation
    
/* Methods */
protected:
    /* Constructors */
    Cana_EqualArmTriangle2();
    
public:
    /* Constructors */
    Cana_EqualArmTriangle2(const Cana_Vec2 position, const float scale);
    Cana_EqualArmTriangle2(const Cana_Vec2 position, const float scale, const float orientationAngle);
    
//    /* Inherited */      // (don't need to be declared, but good for readability)
//        /* VAO, position and scale (from Cana_Drawable2) */
//    const Cana_VertexArrayObject2* getVertexArrayObject() const;
//    const Cana_Vec2 getPosition() const;
//    const float getScale() const;
//        /* Position and scale (from Cana_Primitive2) */
//    void setPosition(const Cana_Vec2 location);
//    void changePosition(const Cana_Vec2 vector);
//    void setScale(const float scale);
//    void changeScale(const float factor);
//        /* Orientation angle (in degrees) */
//    const float getOrientationAngle() const;
//    void setOrientationAngle(const float angle);
//    void changeOrientationAngle(const float angle);
    
    /* Override (from Cana_Primitive2) */
    void reset() override;
    
    /* New */
protected:
        /* VAO init */
    void setVAO();   // potential memory leak if ran more than once
};
