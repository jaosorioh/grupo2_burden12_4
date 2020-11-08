#include "../include/Triangle.h"

using namespace std;

Triangle::Triangle(Point & E1_, Point & E2_, Point & E3_) {
    setE1(E1_);
    setE2(E2_);
    setE3(E3_);
}

Triangle::Triangle(){
    Point E1_;
    Point E2_;
    Point E3_;
    
    setE1(E1_);
    setE2(E2_);
    setE3(E3_);
}

void Triangle::setE1(Point & E1_) {
    E1 = E1_;
}

Point Triangle::getE1() const {
    return E1;
}

void Triangle::setE2(Point & E2_) {
    E2 = E2_;
}

Point Triangle::getE2() const {
    return E2;
}

void Triangle::setE3(Point & E3_) {
    E3 = E3_;
}

Point Triangle::getE3() const {
    return E3;
}

string Triangle::toStr() const {
    return getE1().toStr() + " " + getE2().toStr() + " " + getE3().toStr();

}
