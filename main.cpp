#include <iostream>
#include <fstream>
#include <cmath>

struct Vec2 {
    double x, y;
};

// Bézier cubique : 4 points, t entre 0 et 1
Vec2 bezier(double t, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3) {
    double u  = 1.0 - t;
    return {
        u*u*u*p0.x + 3*u*u*t*p1.x + 3*u*t*t*p2.x + t*t*t*p3.x,
        u*u*u*p0.y + 3*u*u*t*p1.y + 3*u*t*t*p2.y + t*t*t*p3.y
    };
}

int main() {

    Vec2 p0 = {  0.0,    0.0 };   // départ
    Vec2 p1 = { 20.0,  100.0 };   // contrôleur 1  ← tire la courbe
    Vec2 p2 = { 80.0,  100.0 };   // contrôleur 2  ← tire la courbe
    Vec2 p3 = { 100.0,  0.0 };    // arrivée

    // ════════════════════════════════════════════

    std::ofstream f("bezier.csv");
    f << "x,y,dot,cross\n";

    int nbPoints = 200;
    double dt = 1.0 / nbPoints;
    for (int i = 0; i <= nbPoints; ++i) {
        double t = (double)i / nbPoints;
        
        Vec2 p     = bezier(t,      p0, p1, p2, p3);
        Vec2 pNext = bezier(t + dt, p0, p1, p2, p3);  // juste un pas devant
        Vec2 pPrev = bezier(t - dt, p0, p1, p2, p3);  // juste un pas derrière

        // TESTS /////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////
        Vec2 d1 = { p.x - pPrev.x, p.y - pPrev.y };
        Vec2 d2 = { pNext.x - p.x, pNext.y - p.y };

        double dot   = d1.x*d2.x + d1.y*d2.y;
        double cross = d1.x*d2.y - d1.y*d2.x;

        double angle = atan2(cross, dot); // en radian
        double angleDeg = angle * 180.0 / M_PI;
        std::cout << "Variation locale entre deux pas consécutifs : " << angleDeg << "°" << std::endl;
        //////////////////////////////////////////////////////////////////////

        f << p.x << "," << p.y << "," << dot << "," << cross << "," << angleDeg << "\n";
    }

    // Export des points de contrôle pour les afficher
    std::ofstream fc("ctrl.csv");
    fc << "x,y,label\n";
    fc << p0.x << "," << p0.y << ",P0 depart\n";
    fc << p1.x << "," << p1.y << ",P1 ctrl\n";
    fc << p2.x << "," << p2.y << ",P2 ctrl\n";
    fc << p3.x << "," << p3.y << ",P3 arrivee\n";

    std::cout << "OK — bezier.csv et ctrl.csv generes\n";
    return 0;
}