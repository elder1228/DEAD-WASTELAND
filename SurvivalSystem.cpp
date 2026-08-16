#include "generated_offsets.h"
#include "xbox_helpers.h"
#include <cstdint>

namespace DeadWastelandXbox 
{
    float g_fuel = 100.0f;
    bool g_isInfected = false;

    void UpdateSurvivalSystem() 
    {
        uintptr_t playerPed = *(uintptr_t*)PLAYER_PED_PTR;

        // Checa se está em veículo via Native
        bool inVeh = false;
        InvokeNative(HASH_IS_PED_IN_ANY_VEHICLE, playerPed, FALSE, &inVeh);

        if (inVeh) 
        {
            uintptr_t veh = 0;
            InvokeNative(HASH_GET_VEHICLE_PED_IS_IN, playerPed, FALSE, &veh);

            uintptr_t driver = 0;
            InvokeNative(HASH_GET_PED_IN_VEHICLE_SEAT, veh, -1, FALSE, &driver);

            if (driver == playerPed) 
            {
                g_fuel -= 0.005f;
                if (g_fuel <= 0.0f) 
                {
                    g_fuel = 0.0f;
                    InvokeNative(HASH_SET_VEHICLE_ENGINE_ON, veh, FALSE, TRUE, TRUE);
                }
            }
        }

        // Aplicação do Antídoto Virox (Tecla H ou Atalho Rádio)
        bool pressed = false;
        InvokeNative(HASH_IS_DISABLED_CONTROL_JUST_PRESSED, 0, 74, &pressed);

        if (pressed && g_isInfected) 
        {
            g_isInfected = false;
            InvokeNative(HASH_SET_NOTIFICATION_TEXT_ENTRY, "STRING");
            InvokeNative(HASH_ADD_TEXT_COMPONENT_STRING, "~g~[VIROX] Infecção curada com sucesso!");
            InvokeNative(HASH_DRAW_NOTIFICATION, FALSE, TRUE);
        }
    }
}
