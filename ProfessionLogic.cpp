#include "natives.h"

namespace DeadWastelandXbox 
{
    enum Profession { NONE, MECHANIC, ENGINEER, SENTINEL, SCRAPPER, GUNSMITH, FARMER_A, FARMER_B, PATROL, MEDIC, COOK };

    void ApplyProfessionEffect(Ped npc, Profession prof) 
    {
        switch (prof) 
        {
            case SENTINEL:
                WEAPON::GIVE_DELAYED_WEAPON_TO_PED(npc, GAMEPLAY::GET_HASH_KEY("WEAPON_CARBINERIFLE"), 999, TRUE);
                PED::SET_PED_COMBAT_ATTRIBUTES(npc, 5, TRUE); // Sempre em guarda
                break;
            case MEDIC:
                PED::SET_PED_MAX_HEALTH(npc, 200);
                ENTITY::SET_ENTITY_HEALTH(npc, 200);
                break;
            case PATROL:
                PED::SET_PED_COMBAT_MOVEMENT(npc, 3); // Movimento ostensivo
                break;
            default:
                break;
        }
    }
}
