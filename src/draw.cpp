#include "draw.h"

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