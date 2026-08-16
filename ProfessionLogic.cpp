#include "generated_offsets.h"
#include "xbox_helpers.h"
#include <cstdint>

namespace DeadWastelandXbox 
{
    enum Profession { NONE, MECHANIC, ENGINEER, SENTINEL, SCRAPPER, GUNSMITH, FARMER_A, FARMER_B, PATROL, MEDIC, COOK };

    void ApplyProfessionEffect(uintptr_t npc, Profession prof) 
    {
        switch (prof) 
        {
            case SENTINEL:
                InvokeNative(HASH_GET_HASH_KEY, "WEAPON_CARBINERIFLE", nullptr); // Hash é retornado no registrador, simplificado aqui
                InvokeNative(HASH_GIVE_DELAYED_WEAPON_TO_PED, npc, 0x97EA53F8, 999, TRUE); // Hash do Carbine Rifle
                InvokeNative(HASH_SET_PED_COMBAT_ATTRIBUTES, npc, 5, TRUE);
                break;
            case MEDIC:
                InvokeNative(HASH_SET_PED_MAX_HEALTH, npc, 200);
                InvokeNative(HASH_SET_ENTITY_HEALTH, npc, 200, 0);
                break;
            case PATROL:
                InvokeNative(HASH_SET_PED_COMBAT_MOVEMENT, npc, 3);
                break;
            default:
                break;
        }
    }
}
