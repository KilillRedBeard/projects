#include "figures.h"

using namespace std;

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::Point(){}

Point::~Point(){}

Cicle::Cicle(){}

Cicle::Cicle(int radius) {
    this->radius = radius;
}

Cicle::~Cicle(){}

void Cicle::setRadius(int radius) {
    this->radius = radius;
}

void Cicle::draw() {
    for(int y = radius; y >= -radius; y-=2) {
        for(int x = -radius; x <= radius; ++x) {
            if((int)sqrt(pow(x, 2) + pow(y, 2)) <= radius) {
                cout << "*";
            } else {
                cout << " ";
            }
        }

        cout << endl;
    }
}

Square::Square(){}

Square::Square(Point a, int sideLen) {
    this->A = a;
    this->oneSideLen = sideLen;
    this->othreSideLen = sideLen;
}

void Square::setPoints(Point a) {
    this->A = a;
}

void Square::setSideLen(int sideLen) {
    this->oneSideLen = sideLen;
    this->othreSideLen = sideLen;
}

void Square::draw() {
    for(int i = 0; i < A.y + oneSideLen; ++i) {
        if(i >= A.y) {
            for(int j = 0; j < A.x + othreSideLen; ++j) {
                if(j >= A.x) {
                    std::cout << "*";
                } else {
                    std::cout << " ";
                }
            }
        }

        std::cout << std::endl;
    }
}

Rect::Rect() {}

Rect::Rect(Point a, int oneSide, int otherSide) {
    this->A = a;
    this->oneSideLen = oneSide;
    this->othreSideLen = otherSide;
}

void Rect::setPoints(Point a) {
    this->A = a;
}

void Rect::setSides(int oneSide, int otherSide) {
    this->oneSideLen = oneSide;
    this->othreSideLen = otherSide;
}

Triangle::Triangle() {}

Triangle::Triangle(Point A, int height) {
    this->A = A;
    this->height = height;
}

void Triangle::setPoints(Point A) {
    this->A = A;
}

void Triangle::setHeight(int height) {
    this->height = height;
}

void Triangle::func(int i, char c) {
    while(i-- > 0)
        cout << c;
}

void Triangle::draw() {
    for(int i = 0; i < A.y; ++i) {
        cout << endl;
    }

    func(A.x, ' ');
    cout << '*' << endl;

    for(int i = 0; i < height; ++i) {
        func(A.x - i - 1, ' '); cout << '*';
        func(2 * i + 1, '*'); cout << "*" << endl;
    }
}
