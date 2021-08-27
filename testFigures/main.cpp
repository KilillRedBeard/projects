#include "figures.h"

using namespace std;

int main() {
    Cicle cicle(25);
    cicle.draw();

    Square sq(Point(5, 5), 9);
    sq.draw();

    Rect rect(Point(2, 3), 15, 10);
    rect.draw();

    Triangle tr(Point(40, 1), 20);
    tr.draw();

    return 0;
}
