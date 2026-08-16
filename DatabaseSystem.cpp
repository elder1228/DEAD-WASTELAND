#include "generated_offsets.h"
#include "xbox_helpers.h"
#include <cstdint>
#include <cstdio> // XDK usa stdio para file I/O nativo

namespace DeadWastelandXbox 
{
    // No XDK, usamos fopen/fprintf para game:\ ou usb:\
    void SaveDatabase() 
    {
        FILE* file = fopen("game:\\dead_wasteland_data.txt", "w");
        if (file != nullptr) 
        {
            uintptr_t playerPed = *(uintptr_t*)PLAYER_PED_PTR;
            float x = 0, y = 0, z = 0;
            InvokeNative(HASH_GET_ENTITY_COORDS, playerPed, TRUE, &x, &y, &z);

            fprintf(file, "POS_X=%f\n", x);
            fprintf(file, "POS_Y=%f\n", y);
            fprintf(file, "POS_Z=%f\n", z);
            fclose(file);

            InvokeNative(HASH_SET_NOTIFICATION_TEXT_ENTRY, "STRING");
            InvokeNative(HASH_ADD_TEXT_COMPONENT_STRING, "~g~[PERSISTÊNCIA] Dados salvos com sucesso.");
            InvokeNative(HASH_DRAW_NOTIFICATION, FALSE, TRUE);
        }
    }

    void LoadDatabase() 
    {
        FILE* file = fopen("game:\\dead_wasteland_data.txt", "r");
        if (file != nullptr) 
        {
            float x = 0, y = 0, z = 0;
            fscanf(file, "POS_X=%f\n", &x);
            fscanf(file, "POS_Y=%f\n", &y);
            fscanf(file, "POS_Z=%f\n", &z);
            fclose(file);

            if (x != 0 && y != 0) 
            {
                uintptr_t playerPed = *(uintptr_t*)PLAYER_PED_PTR;
                InvokeNative(HASH_SET_ENTITY_COORDS, playerPed, x, y, z, FALSE, FALSE, FALSE, TRUE);
            }
        }
    }
}
