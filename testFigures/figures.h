#ifndef FIGURES_H
#define FIGURES_H

#include <iostream>
#include <math.h>

class Point {
public:
    int x;
    int y;

    Point();
    Point(int x, int y);
    ~Point();
};

class Figure {
public:
    virtual void draw() = 0;
};

class Cicle : public Figure {
private:
    int radius;

public:
    Cicle();
    Cicle(int radius);
    ~Cicle();

    void setRadius(int radius);
    void draw();
};

class Square : public Figure {
protected:
    int oneSideLen;
    int othreSideLen;
    Point A;

public:
    Square();
    Square(Point a, int sideLen);

    void setPoints(Point a);
    void setSideLen(int sideLen);

    void draw();
};

class Rect : public Square {
private:

public:
    Rect();
    Rect(Point a, int oneSide, int otherSide);

    void setPoints(Point a);
    void setSides(int oneSide, int otherSide);
};

class Triangle : public Figure {
private:
    Point A;
    int height;

public:
    Triangle();
    Triangle(Point A, int height);

    void setPoints(Point A);
    void setHeight(int height);
    void func(int i, char c);
    void draw();
};
#endif // FIGURES_H
