/* TODO not used
#include <algorithm>
#include <list>
#include <map>
#include <queue>
*/

#include "geometry.h"

/*
    Compare si le point p est plus petit que le point other
*/
bool compareCoords(Coords p, Coords other){
    if (p.y == other.y)
        return p.x < other.x;
    return p.y < other.y;
}

/*
   Détermine si un point se trouve dans un cercle définit par trois points
   Retourne, par les paramètres, le centre et le rayon
*/
bool CircumCircle(
    Point p, Point p1, Point p2, Point p3,
    Point *center, float *radius
){
    float m1, m2, mx1, mx2, my1, my2;
    float dx, dy, drsqr;

    // absolute value
    float fabsy1y2 = fabs(p1.y - p2.y);
    float fabsy2y3 = fabs(p2.y - p3.y);

    /* Check for coincident points */
    if (fabsy1y2 < EPSILON && fabsy2y3 < EPSILON)
        return false;

    if (fabsy1y2 < EPSILON){
        m2 = -(p3.x - p2.x) / (p3.y - p2.y);
        mx2 = (p2.x + p3.x) / 2.0;
        my2 = (p2.y + p3.y) / 2.0;
        center->x = (p2.x + p1.x) / 2.0;
        center->y = m2 * (center->x - mx2) + my2;
    }else if (fabsy2y3 < EPSILON){
        m1 = -(p2.x - p1.x) / (p2.y - p1.y);
        mx1 = (p1.x + p2.x) / 2.0;
        my1 = (p1.y + p2.y) / 2.0;
        center->x = (p3.x + p2.x) / 2.0;
        center->y = m1 * (center->x - mx1) + my1;
    }else{
        m1 = -(p2.x - p1.x) / (p2.y - p1.y);
        m2 = -(p3.x - p2.x) / (p3.y - p2.y);
        mx1 = (p1.x + p2.x) / 2.0;
        mx2 = (p2.x + p3.x) / 2.0;
        my1 = (p1.y + p2.y) / 2.0;
        my2 = (p2.y + p3.y) / 2.0;
        center->x = (m1 * mx1 - m2 * mx2 + my2 - my1) / (m1 - m2);
        if (fabsy1y2 > fabsy2y3){
            center->y = m1 * (center->x - mx1) + my1;
        }else{
            center->y = m2 * (center->x - mx2) + my2;
        }
    }

    dx = p2.x - center->x;
    dy = p2.y - center->y;
    *radius = dx * dx + dy * dy;

    dx = p.x - center->x;
    dy = p.y - center->y;
    drsqr = dx * dx + dy * dy;

    return (drsqr - *radius) <= EPSILON;
}


// GESTION DES TRIANGLES ---------------------------------------
bool Triangle::isEdge(Point p){
    return this->p1 == p || this->p2 == p || this->p3 == p;
}

bool Triangle::isNeighbor(Triangle &compare){
    int commun = 0;

    if(this->isEdge(compare.p1))
        commun++;

    if(this->isEdge(compare.p2))
        commun++;

    if(this->isEdge(compare.p3))
        commun++;
    // = un segment commun -> le triangle comparé est un voisin 
    return commun == 2;
}

// -------------------------------------------------------------