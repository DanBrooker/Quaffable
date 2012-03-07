//
//  Damage.h
//  Roguelike
//
//  Created by Daniel Brooker on 6/06/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef DAMAGE_H_INC
#define DAMAGE_H_INC

#include <list>

#define DamageBlunt     1<<0
#define DamageSharp     1<<1
#define DamagePierce    1<<2
#define DamageMagic     1<<3
#define DamageFire      1<<4
#define DamageIce       1<<5
#define DamageWind      1<<6
#define DamageWater     1<<7
#define DamageLight     1<<8
#define DamageDark      1<<9
#define DamagePoison    1<<10
#define DamageCritical  1<<11

typedef int DamageMask;

class Damage
{
    public:
    int damage;
    DamageMask mask;
    
    Damage() {damage = 0;};
    Damage(int dmg, DamageMask damageMask = DamageBlunt ) { damage = dmg; mask = damageMask; }
};

typedef std::list<Damage> Damages;

#endif /* DAMAGE_H_INC */