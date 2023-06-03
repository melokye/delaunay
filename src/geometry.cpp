/* TODO not used
#include <algorithm>
#include <list>
#include <map>
#include <queue>
*/

#include "geometry.h"

void drawPoints(SDL_Renderer *renderer, const vector<Coords> &points){
    for (size_t i = 0; i < points.size(); i++){
        filledCircleRGBA(renderer, points.at(i).x, points.at(i).y, 3, 240, 240, 23, SDL_ALPHA_OPAQUE);
    }
}

void drawSegments(SDL_Renderer *renderer, const vector<Segment> &segments){
    for (size_t i = 0; i < segments.size(); i++){
        lineRGBA(
            renderer,
            segments[i].p1.x, segments[i].p1.y,
            segments[i].p2.x, segments[i].p2.y,
            240, 240, 20, SDL_ALPHA_OPAQUE
        );
    }
}

void drawTriangles(SDL_Renderer *renderer, const vector<Triangle> &triangles){
    for (size_t i = 0; i < triangles.size(); i++){
        const Triangle& t = triangles[i];
        trigonRGBA(
            renderer,
            t.p1.x, t.p1.y,
            t.p2.x, t.p2.y,
            t.p3.x, t.p3.y,
            0, 240, 160, SDL_ALPHA_OPAQUE
        );
    }
}

bool compareCoords(Coords point1, Coords point2){
    if (point1.y == point2.y)
        return point1.x < point2.x;
    return point1.y < point2.y;
}

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

void drawPolygone(SDL_Renderer *renderer, vector<Triangle> &reference){
    vector<Segment> segments;
    vector<Point> centers;

    for(unsigned int i = 0; i < reference.size(); i++){
        vector<Triangle> neightbor;
        Triangle base = reference.at(i);

    // find neightbors
        for(unsigned int j = i + 1; j < reference.size(); j++ ){
            Triangle compare = reference.at(j);
        
            if(base.isNeighbor(compare)){                
                neightbor.push_back(compare);
            }
        }
        
    // find centerCircle of each neightbor
        Point center;
        float radius; // not used but important
        CircumCircle(base.p1, base.p1, base.p2, base.p3, &center, &radius);

        centers.push_back(center);
    // Create segment between base and neightbor
        for(unsigned int j = 0; j < neightbor.size(); j++){
            Triangle neighTriangle = neightbor.at(j);
            Point neighCenter;

            CircumCircle(neighTriangle.p1, neighTriangle.p1, neighTriangle.p2, neighTriangle.p3, &neighCenter, &radius);
            segments.push_back(Segment{center, neighCenter});

            centers.push_back(neighCenter);
        }
    }

    drawSegments(renderer, segments);
    drawPoints(renderer, centers);
}

void draw(SDL_Renderer *renderer, Application &app){
    SDL_GetRendererOutputSize(renderer, &(app.width), &(app.height));

    drawPoints(renderer, app.points);
    drawTriangles(renderer, app.triangles);

    drawPolygone(renderer, app.triangles);
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

void recursivQuickSort(vector<Point>& toSort){
    unsigned int size = toSort.size();

    if(size <= 1){return;}

    Point pivot = toSort.at(0);
    vector<Point> lowers;
    vector<Point> greaters;
    
    for(unsigned int i = 1; i < size; i++){
        if(toSort[i].x < pivot.x){ // TODO compareCoord
            lowers.push_back(toSort[i]);
        }else{
            greaters.push_back(toSort[i]);
        }
    }

    recursivQuickSort(lowers);
    recursivQuickSort(greaters);

    for(unsigned int i = 0; i < lowers.size(); i++){
        toSort[i] = lowers[i];
    }

    toSort[lowers.size()] = pivot;

    for(unsigned int temp = lowers.size() + 1; temp < size; temp++){
        toSort[temp] = greaters[temp - (lowers.size() + 1)];
    }
}

void construitVoronoi(Application &app){   
    recursivQuickSort(app.points);
    app.triangles.clear();
    app.triangles.push_back(Triangle{Point{-1000, -1000}, Point{500, 3000}, Point{1500, -1000}});

    for(size_t i = 0 ; i < app.points.size(); i++){
        Point p = app.points.at(i); // == points[i]
        vector <Segment> LS;
        for(unsigned int j = 0; j < app.triangles.size(); j++){
            Triangle t = app.triangles.at(j);
            Coords center;
            float radius;
            if(CircumCircle(p, t.p1, t.p2, t.p3, &center, &radius)){
                // TODO possible d'édit pour push back des triangles directement
                LS.push_back(Segment{t.p1, t.p2});
                LS.push_back(Segment{t.p2, t.p3});
                LS.push_back(Segment{t.p3, t.p1});
                app.triangles.erase(app.triangles.begin() + j);
                j--;
            }
        }

        for(size_t j = 0; j < LS.size(); j++){
            for(size_t k = j + 1; k < LS.size(); k++){
                Segment s1, s2;
                s1 = LS.at(j);
                s2 = LS.at(k);
                if((s1.p1 == s2.p2) && (s1.p2 == s2.p1)){
                    LS.erase(LS.begin() + k);
                    LS.erase(LS.begin() + j);
                    j--;
                    k = j + 1;
                }
            }
        }

        for(size_t j = 0; j < LS.size(); j++){
            Segment s = LS.at(j);
            Triangle t = Triangle{s.p1, s.p2, p};
            app.triangles.push_back(t);
        }
    }
}

bool handleEvent(Application &app){
    /* TODO Remplissez cette fonction pour gérer les inputs utilisateurs */
    SDL_Event e;
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT)
            return false;
        else if (e.type == SDL_WINDOWEVENT_RESIZED){
            app.width = e.window.data1;
            app.height = e.window.data1;
        }else if (e.type == SDL_MOUSEWHEEL){
            // TODO faire un truc ?
        }else if (e.type == SDL_MOUSEBUTTONUP){
            if (e.button.button == SDL_BUTTON_RIGHT){
                app.focus.x = e.button.x;
                app.focus.y = e.button.y;
                app.points.clear();
            }else if (e.button.button == SDL_BUTTON_LEFT){
                app.focus.y = 0;
                app.points.push_back(Coords{e.button.x, e.button.y});
                // pointsToTriangle(app); // Milestone 0
                construitVoronoi(app);
            }
        }
    }
    return true;
}

/* 
// Milestone 0 :
void pointsToTriangle(Application &app){
    int i = app.points.size() - 1;

    if(app.points.size() >= 3){
        Point p1, p2, p3;
        p1 = app.points.at(i--);
        p2 = app.points.at(i--);
        p3 = app.points.at(i);
        app.triangles.push_back(Triangle{p1, p2, p3});
    }
}
*/

/*
// Milestone 1 : 
void construitVoronoi(Application &app){   
    recursivQuickSort(app.points, app.points.size());
    app.triangles.clear();
    app.triangles.push_back(Triangle{Point{-1000, -1000}, Point{500, 3000}, Point{1500, -1000}});

    for(size_t i = 0 ; i < app.points.size(); i++){
        Point p = app.points.at(i); // == points[i]
        vector <Segment> LS;
        for(int j = 0; j < app.triangles.size(); j++){
            Triangle t = app.triangles.at(j);
            Point center;
            float radius;
            if(CircumCircle(p, t.p1, t.p2, t.p3, &center, &radius)){
                LS.push_back(Segment{t.p1, t.p2});
                LS.push_back(Segment{t.p2, t.p3});
                LS.push_back(Segment{t.p3, t.p1});
                app.triangles.erase(app.triangles.begin() + j);
                j--;
            }
        }

        for(size_t j = 0; j < LS.size(); j++){
            for(size_t k = j + 1; k < LS.size(); k++){
                Segment s1, s2;
                s1 = LS.at(j);
                s2 = LS.at(k);
                if((s1.p1 == s2.p2) && (s1.p2 == s2.p1)){
                    LS.erase(LS.begin() + k);
                    k--;
                }
            }
        }

        for(size_t j = 0; j < LS.size(); j++){
            Segment s = LS.at(j);
            app.triangles.push_back(Triangle{s.p1, s.p2, p});
        }
    }
}
*/