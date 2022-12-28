#ifndef CORAZZATA_H
#define CORAZZATA_H
#include "ship.h"
class Corazzata : public Ship{
public:
    Corazzata(XY *);
    void action() const override;
    bool isHit(XY) const;
    bool isCore(/**/) const;
private:
    static int constexpr size = 5;
};

#endif