#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "SDL2_gfxPrimitives.h"
#define EPSILON 0.0001f // for CircumCircle

typedef struct Coords{
    float x, y; 

    Coords(){}
    
    Coords(float x, float y){
        this->x = x;
        this->y = y;
    }

    Coords(int x, int y){
        this->x = x;
        this->y = y;
    }

    bool operator==(const Coords& other){
        return x == other.x && y == other.y;
    }

}Coords, Point;

bool compareCoords(Coords p, Coords other);
struct Segment{
    Coords p1, p2;

    Segment(){}

    Segment(Coords p1, Coords p2){
        this->p1 = p1;
        this->p2 = p2;
    }
};

struct Triangle{
    Point p1, p2, p3;
    bool complet;

    Triangle(Coords p1, Coords p2, Coords p3, bool complet=false){
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
        this->complet = complet;
    }

    bool isNeighbor(Triangle &compare);
    bool isEdge(Point p);
};

bool CircumCircle(
    Point p,
    Point p1, Point p2, Point p3,
    Coords *center, float *radius
);

#endif