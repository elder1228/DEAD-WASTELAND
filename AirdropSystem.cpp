#include "generated_offsets.h"
#include "xbox_helpers.h"
#include <cstdint>
#include <cstdlib>

namespace DeadWastelandXbox 
{
    struct Vector3 { float x, y, z; };

    Vector3 g_lastAirdropPos;
    bool g_airdropActive = false;

    void SpawnAirdrop() 
    {
        uintptr_t playerPed = *(uintptr_t*)PLAYER_PED_PTR;
        Vector3 pCoords;
        InvokeNative(HASH_GET_ENTITY_COORDS, playerPed, TRUE, &pCoords);

        float offsetX = (float)(rand() % 100 + 100);
        float offsetY = (float)(rand() % 100 + 100);
        g_lastAirdropPos = { pCoords.x + offsetX, pCoords.y + offsetY, pCoords.z + 150.0f };

        uint32_t crateHash = 0;
        InvokeNative(HASH_GET_HASH_KEY, "prop_box_wood02a", &crateHash);
        InvokeNative(HASH_REQUEST_MODEL, crateHash);
        
        bool loaded = false;
        while (!loaded) {
            InvokeNative(HASH_HAS_MODEL_LOADED, crateHash, &loaded);
            Sleep(0);
        }

        uintptr_t crate = 0;
        InvokeNative(HASH_CREATE_OBJECT, crateHash, g_lastAirdropPos.x, g_lastAirdropPos.y, g_lastAirdropPos.z, TRUE, TRUE, FALSE, &crate);
        InvokeNative(HASH_SET_ENTITY_DYNAMIC, crate, TRUE);
        
        InvokeNative(HASH_ADD_PETROL_DECAL, g_lastAirdropPos.x, g_lastAirdropPos.y, g_lastAirdropPos.z, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
        
        uintptr_t crateBlip = 0;
        InvokeNative(HASH_ADD_BLIP_FOR_ENTITY, crate, &crateBlip);
        InvokeNative(HASH_SET_BLIP_SPRITE, crateBlip, 306);
        InvokeNative(HASH_SET_BLIP_COLOUR, crateBlip, 2);

        InvokeNative(HASH_SET_NOTIFICATION_TEXT_ENTRY, "STRING");
        InvokeNative(HASH_ADD_TEXT_COMPONENT_STRING, "~g~[AIRDROP] Suprimentos da Merryweather a caminho!");
        InvokeNative(HASH_DRAW_NOTIFICATION, FALSE, TRUE);

        g_airdropActive = true;
    }

    void UpdateAirdropSystem() 
    {
        bool pressed = false;
        InvokeNative(HASH_IS_DISABLED_CONTROL_JUST_PRESSED, 0, 118, &pressed);
        if (pressed) SpawnAirdrop();
    }
}
