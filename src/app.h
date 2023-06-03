#ifndef APP_H
#define APP_H

#include <iostream>
using namespace std;
#include <vector> // need iostream to work

#include "geometry.h"

struct Application{
    int width, height;
    Coords focus;

    vector<Coords> points;
    vector<Triangle> triangles;

    Application(int width, int height, Coords focus){
        this->width = width;
        this->height = height;
        this->focus = focus;
    }
};

void construitVoronoi(Application &app);
bool handleEvent(Application &app);

void recursivQuickSort(vector<Point>& toSort);
#endif