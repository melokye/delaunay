#include "geometry.h"

void drawPoints(SDL_Renderer *renderer, const vector<Coords> &points){
    for (size_t i = 0; i < points.size(); i++){
        filledCircleRGBA(renderer, points.at(i).x, points.at(i).y, 3, 240, 240, 23, SDL_ALPHA_OPAQUE);
        // TODO => provoque une erreur de segmentation
    }
}

void drawSegments(SDL_Renderer *renderer, const vector<Segment> &segments){
    for (size_t i = 0; i < segments.size(); i++)
    {
        lineRGBA(
            renderer,
            segments[i].p1.x, segments[i].p1.y,
            segments[i].p2.x, segments[i].p2.y,
            240, 240, 20, SDL_ALPHA_OPAQUE);
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

void draw(SDL_Renderer *renderer, const Application &app){
    /* TODO Remplissez cette fonction pour faire l'affichage du jeu */
    int width, height; // TODO supp ces variables, déjà présent dans app
    SDL_GetRendererOutputSize(renderer, &width, &height);
    drawPoints(renderer, app.points);
//    drawTriangles(renderer, app.triangles);
}

/*
   Détermine si un point se trouve dans un cercle définit par trois points
   Retourne, par les paramètres, le centre et le rayon
*/
bool CircumCircle(
    Point p,
    Point p1, Point p2, Point p3,
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

/*
void construitVoronoi(Application &app){
   // TODO construitVoronoi
}
*/

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
                // construitVoronoi(app);
            }
        }
    }
    return true;
}

/*
void pointsToTriangle(Application &app){
    if(app.points.size() % 3 == 0){
        Point p1, p2, p3;
        p1 = app.points.back();
        p2 = app.points.back();
        p3 = app.points.back();
        
        app.triangles.push_back(Triangle{p1, p2, p3});
    }
}
*/