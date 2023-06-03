#ifndef DRAW_H
#define DRAW_H

#include "app.h"
#include "geometry.h"

void drawPoints(SDL_Renderer *renderer, const vector<Coords> &points);
void drawSegments(SDL_Renderer *renderer, const vector<Segment> &segments);
void drawTriangles(SDL_Renderer *renderer, const vector<Triangle> &triangles);
void drawPolygone(SDL_Renderer *renderer, vector<Triangle> &reference);
void drawCircle(SDL_Renderer * renderer, vector<Coords> centers, vector<float> rads);

void draw(SDL_Renderer *renderer, Application &app);

#endif