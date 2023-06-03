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

    Coords(int x, int y){
        this->x = x;
        this->y = y;
    }

    void operator=(const Coords& other){
        this->x = other.x;
        this->y = other.y;
    }

    bool operator==(const Coords& other){
        return x == other.x && y == other.y;
    }

}Coords, Point;

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
};

struct Application{
    int width, height;
    Coords focus; // {100, 100}

    vector<Coords> points;
    vector<Triangle> triangles;

    Application(int width, int height, Coords focus){
        this->width = width;
        this->height = height;
        this->focus = focus;
        // this->points
        // this->triangles
    }
};

void drawPoints(SDL_Renderer *renderer, const vector<Coords> &points);
void drawSegments(SDL_Renderer *renderer, const vector<Segment> &segments);
void drawTriangles(SDL_Renderer *renderer, const vector<Triangle> &triangles);
void drawPolygone(SDL_Renderer *renderer, vector<Triangle> &reference);
void drawCircle(SDL_Renderer * renderer, vector<Coords> centers, vector<float> rads);

void draw(SDL_Renderer *renderer, Application &app);

bool CircumCircle(
    Point p,
    Point p1, Point p2, Point p3,
    Coords *center, float *radius
);

void construitVoronoi(Application &app);
bool handleEvent(Application &app);
void pointsToTriangle(Application &app);

void recursivQuickSort(vector<Point>& toSort, int size);
#endif