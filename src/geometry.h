#ifndef GEOMETRY
#include <iostream>
using namespace std;
#include <vector>

#include "SDL2_gfxPrimitives.h"


#define EPSILON 0.0001f

typedef struct Coords{
    float x, y; 

    Coords(){}
    
    Coords(float x, float y){
        this->x = x;
        this->y = y;
    }

    Coords(const Coords& other){
        this->x = other.x;
        this->y = other.y;
    }

    Coords operator=(const Coords& other){
        this->x = other.x;
        this->y = other.y;
        return other;
    }

    bool operator==(const Coords& other){
        return x == other.x and y == other.y;
    }

}Coords, Point;

struct Segment{
    Coords p1, p2;
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
};

struct Application{
    int width, height;
    Coords focus{100, 100};

    vector<Coords> points;
    vector<Triangle> triangles;
};

void drawPoints(SDL_Renderer *renderer, const vector<Coords> &points);
void drawSegments(SDL_Renderer *renderer, const vector<Segment> &segments);
void drawTriangles(SDL_Renderer *renderer, const vector<Triangle> &triangles);

void draw(SDL_Renderer *renderer, const Application &app);

bool CircumCircle(
    Point p,
    Point p1, Point p2, Point p3,
    Point *center, float *radius
);

void construitVoronoi(Application &app);
bool handleEvent(Application &app);

#endif