#include "generated_offsets.h"
#include "xbox_helpers.h"
#include <cstdint>

namespace DeadWastelandXbox 
{
    void UpdatePersistenceSystem() 
    {
        uintptr_t playerPed = *(uintptr_t*)PLAYER_PED_PTR;

        bool shiftP = false, lbRight = false;
        InvokeNative(HASH_IS_CONTROL_PRESSED, 0, 21, &shiftP);
        InvokeNative(HASH_IS_DISABLED_CONTROL_JUST_PRESSED, 0, 199, &lbRight);
        bool ctrlP = false, lbRight2 = false;
        InvokeNative(HASH_IS_CONTROL_PRESSED, 0, 20, &ctrlP);
        InvokeNative(HASH_IS_DISABLED_CONTROL_JUST_PRESSED, 0, 175, &lbRight2);

        bool registerInput = (shiftP && lbRight) || (ctrlP && lbRight2);

        if (registerInput) 
        {
            bool inVeh = false;
            InvokeNative(HASH_IS_PED_IN_ANY_VEHICLE, playerPed, FALSE, &inVeh);

            if (inVeh) 
            {
                uintptr_t veh = 0;
                InvokeNative(HASH_GET_VEHICLE_PED_IS_IN, playerPed, FALSE, &veh);

                // Registra o veículo (Flag de Mission Entity via Native)
                InvokeNative(HASH_SET_ENTITY_AS_MISSION_ENTITY, veh, TRUE, TRUE);
                
                uintptr_t vehBlip = 0;
                InvokeNative(HASH_ADD_BLIP_FOR_ENTITY, veh, &vehBlip);
                InvokeNative(HASH_SET_BLIP_SPRITE, vehBlip, 225);
                InvokeNative(HASH_SET_BLIP_COLOUR, vehBlip, 7);

                InvokeNative(HASH_SET_NOTIFICATION_TEXT_ENTRY, "STRING");
                InvokeNative(HASH_ADD_TEXT_COMPONENT_STRING, "~p~[FROTA] Veículo registrado na Frota Persistente!");
                InvokeNative(HASH_DRAW_NOTIFICATION, FALSE, TRUE);
            }
        }
    }
}
