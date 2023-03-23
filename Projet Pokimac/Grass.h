#pragma once

#include "Case.h"

class Grass :
    public Case
{
private:
    int zone;
public:
    Grass(int x, char c, bool b, int z) : Case(x, c, b) 
    {
        zone = z;
    }
    void StartCombat(Player* player) override;
};

