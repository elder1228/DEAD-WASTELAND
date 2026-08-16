#include "generated_offsets.h"
#include "xbox_helpers.h"
#include <cstdint>
#include <cmath>

namespace DeadWastelandXbox 
{
    struct Vector3 { float x, y, z; };

    void UpdateProfessionSelector() 
    {
        uintptr_t playerPed = *(uintptr_t*)PLAYER_PED_PTR;
        Vector3 pCoords;
        InvokeNative(HASH_GET_ENTITY_COORDS, playerPed, TRUE, &pCoords);

        bool interactInput = false;
        InvokeNative(HASH_IS_DISABLED_CONTROL_JUST_PRESSED, 0, 51, &interactInput);
        if (!interactInput) InvokeNative(HASH_IS_DISABLED_CONTROL_JUST_PRESSED, 0, 175, &interactInput);

        if (interactInput) 
        {
            // Varredura manual do Ped Pool (Bitmask)
            uintptr_t pedPoolBase = PED_POOL_PTR;
            if (pedPoolBase == 0) return;

            void** pedItems = (void**)(pedPoolBase + PED_POOL_ITEMS_OFFSET); 
            uint32_t* pedBitset = (uint32_t*)(pedPoolBase + PED_POOL_BITSET_OFFSET);
            int maxPeds = PED_POOL_MAX_ITEMS;

            for (int i = 0; i < maxPeds; i++) 
            {
                int index = i / 32;
                int bit = i % 32;
                if (!(pedBitset[index] & (1 << bit))) continue;

                uintptr_t targetPed = (uintptr_t)pedItems[i];
                if (targetPed == 0 || targetPed == playerPed) continue;

                bool isPlayer = false;
                InvokeNative(HASH_IS_PED_A_PLAYER, targetPed, &isPlayer);
                if (isPlayer) continue;

                Vector3 npcCoords;
                InvokeNative(HASH_GET_ENTITY_COORDS, targetPed, TRUE, &npcCoords);
                
                float dx = pCoords.x - npcCoords.x;
                float dy = pCoords.y - npcCoords.y;
                float dist = sqrtf(dx*dx + dy*dy);

                if (dist < 3.0f) 
                {
                    InvokeNative(HASH_SET_NOTIFICATION_TEXT_ENTRY, "STRING");
                    InvokeNative(HASH_ADD_TEXT_COMPONENT_STRING, "~b~[PROFISSÃO] Função atribuída com sucesso ao Aliado!");
                    InvokeNative(HASH_DRAW_NOTIFICATION, FALSE, TRUE);
                    break;
                }
            }
        }
    }
}
