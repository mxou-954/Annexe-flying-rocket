#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct DotCross { double dot, cross; };
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

Vec2 generateQPoint(){
    std::srand(std::time({}));
    double randomCoordonates_x = std::rand() % 201;
    double randomCoordonates_y = std::rand() % 201;

    Vec2 q = {randomCoordonates_x, randomCoordonates_y};
    return q;
}

double distance(Vec2 a, Vec2 b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    return sqrt(dx*dx + dy*dy);
}

double vitesse(double t, Vec2 p0, Vec2 p1, Vec2 p2, Vec2 p3) {
    double dt = 0.001;
    Vec2 pNext = bezier(t + dt, p0, p1, p2, p3);
    Vec2 pPrev = bezier(t - dt, p0, p1, p2, p3);
    double dx = (pNext.x - pPrev.x) / (2*dt);
    double dy = (pNext.y - pPrev.y) / (2*dt);

    // Logs ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // std::cout << "===================== Vitesse Méthode Simpson ======================="<< "\n";
    // std::cout << "pNext  --->   x: " << pNext.x << "     y: " << pNext.y << "\n";
    // std::cout << "pPrev  --->   x: " << pPrev.x << "     y: " << pPrev.y << "\n";
    // std::cout << "dx/dy  --->   x: " << dx << "          y: " << dy << "\n";
    // std::cout << "sqrt_dx_dy  --->   " << sqrt(dx*dx + dy*dy) << "\n";
    // std::cout << "====================================================================="<< "\n\n";
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return sqrt(dx*dx + dy*dy);
}

// a -> current step
// b -> prev step
// c -> next step
DotCross dotAndCross(Vec2 a, Vec2 b, Vec2 c) {
    Vec2 d1 = { a.x - b.x, a.y - b.y };
    Vec2 d2 = { c.x - a.x, c.y - a.y };
    return { d1.x*d2.x + d1.y*d2.y,
             d1.x*d2.y - d1.y*d2.x };
}

int main() {

    Vec2 p0 = {  0.0,    0.0 };   // départ
    Vec2 p1 = { 20.0,  100.0 };   // contrôleur 1  ← tire la courbe
    Vec2 p2 = { 80.0,  100.0 };   // contrôleur 2  ← tire la courbe
    Vec2 p3 = { 100.0,  0.0 };    // arrivée

    Vec2 q = generateQPoint();

    // Methode des trapèzes
    // for (int nbPoints : {5, 10, 50, 200, 1000, 10000}) {
    //     double longueur = 0.0;
    //     double dt = 1.0 / nbPoints;
    //     for (int i = 0; i < nbPoints; ++i) {
    //         double t = (double)i / nbPoints;
    //         Vec2 p     = bezier(t,      p0, p1, p2, p3);
    //         Vec2 pNext = bezier(t + dt, p0, p1, p2, p3);
    //         longueur += distance(pNext, p);
    //     }
    //     std::cout << "nbPoints = " << nbPoints << "  →  " << longueur << "\n";
    // }

    for (int nbPoints : {5, 10, 50, 200, 1000, 10000}) {
        double longueurSimpson = 0.0;
        for (int i = 0; i < nbPoints; i += 2) {  // on avance de 2 en 2 !
            double a   = (double)i       / nbPoints;
            double mid = (double)(i+1)   / nbPoints;
            double b   = (double)(i+2)   / nbPoints;
            double h   = b - a;

            longueurSimpson += h/6 * (vitesse(a,p0,p1,p2,p3)
                     + 4* vitesse(mid,p0,p1,p2,p3)
                     +    vitesse(b,p0,p1,p2,p3));
        }
        std::cout << "nbPoints = " << nbPoints << "  →  " << longueurSimpson << "\n";
    }

    // ════════════════════════════════════════════

    std::ofstream f("bezier.csv");
    f << "x,y,dot,cross,angleDeg,t,qx,qy,bestCoordonatesx,bestCoordonatesy\n";

    int nbPoints = 1000;
    double dt = 1.0 / nbPoints;
    double longueur = 0.0;
    double bestDistance = 1000;
    Vec2 bestCoordonates = {0, 0};
    for (int i = 0; i < nbPoints; ++i) {
        double t = (double)i / nbPoints;
        
        Vec2 p     = bezier(t,      p0, p1, p2, p3);
        Vec2 pNext = bezier(t + dt, p0, p1, p2, p3);  // juste un pas devant
        Vec2 pPrev = bezier(t - dt, p0, p1, p2, p3);  // juste un pas derrière

        // TESTS /////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////
        DotCross dc = dotAndCross(p, pPrev, pNext);
        double dot   = dc.dot;
        double cross = dc.cross;

        double angle = atan2(cross, dot); // en radian
        double angleDeg = angle * 180.0 / M_PI;
        //////////////////////////////////////////////////////////////////////

        longueur += distance(pNext, p);

        double distanceQ = distance(p, q);

        if(distanceQ < bestDistance){
            bestDistance = distanceQ;
            bestCoordonates = {p.x, p.y};
        }

        f << p.x << "," << p.y << "," << dot << "," << cross << "," << angleDeg << "," << i << "," << q.x << "," << q.y << "," << bestCoordonates.x << "," << bestCoordonates.y << "\n";
    }

    std::cout << "===================== Coordonnés Newton-Raphson ======================="<< "\n";
    std::cout << "Q : (x: " << q.x << ", y: " << q.y << ")" << "\n";
    std::cout << "Coordonnés le plus proche : (x: " << bestCoordonates.x << ", y: " << bestCoordonates.y << ")" << "\n";
    std::cout << "Distance : " << bestDistance << "\n";
    std::cout << "======================================================================="<< "\n";

    // Export des points de contrôle pour les afficher
    std::ofstream fc("ctrl.csv");
    fc << "x,y,label\n";
    fc << p0.x << "," << p0.y << ",P0 depart\n";
    fc << p1.x << "," << p1.y << ",P1 ctrl\n";
    fc << p2.x << "," << p2.y << ",P2 ctrl\n";
    fc << p3.x << "," << p3.y << ",P3 arrivee\n";

    std::cout << "Longueur totale : " << longueur << "\n";
    std::cout << "OK — bezier.csv et ctrl.csv generes\n";
    return 0;
}