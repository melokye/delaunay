#include "app.h"

void construitVoronoi(Application &app){   
    recursivQuickSort(app.points);
    app.triangles.clear();
    app.triangles.push_back(Triangle{Point{-1000, -1000}, Point{500, 3000}, Point{1500, -1000}});

    for(size_t i = 0 ; i < app.points.size(); i++){
        Point p = app.points.at(i); // == points[i]
        vector <Segment> LS;
        for(unsigned int j = 0; j < app.triangles.size(); j++){
            Triangle t = app.triangles.at(j);
            Coords center; float radius; // variable not used but need to be here

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
                Segment s1 = LS.at(j);
                Segment s2 = LS.at(k);

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
                construitVoronoi(app);
            }
        }
    }
    return true;
}

void recursivQuickSort(vector<Point>& toSort){
    unsigned int size = toSort.size();

    if(size <= 1){return;}

    Point pivot = toSort.at(0);
    vector<Point> lowers;
    vector<Point> greaters;
    
    for(unsigned int i = 1; i < size; i++){
        Coords compare = toSort.at(i);
        if(compareCoords(compare, pivot)){
            lowers.push_back(compare);
        }else{
            greaters.push_back(compare);
        }
    }

    recursivQuickSort(lowers);
    recursivQuickSort(greaters);

    unsigned int i = 0;
    for(; i < lowers.size(); i++){
        toSort.at(i) = lowers.at(i);
    }

    toSort.at(i++) = pivot;

    unsigned int begin = i;
    for(; i < size; i++){
        toSort.at(i) = greaters.at(i - begin);
    }
}
