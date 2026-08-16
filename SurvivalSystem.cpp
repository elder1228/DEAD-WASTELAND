#include "natives.h"

namespace DeadWastelandXbox 
{
    float g_fuel = 100.0f;
    bool g_isInfected = false;

    void UpdateSurvivalSystem() 
    {
        Ped playerPed = PLAYER::PLAYER_PED_ID();

        // Consumo de combustível se estiver dirigindo
        if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE)) 
        {
            Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, FALSE);
            if (VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1) == playerPed) 
            {
                g_fuel -= 0.005f;
                if (g_fuel <= 0.0f) 
                {
                    g_fuel = 0.0f;
                    VEHICLE::SET_VEHICLE_ENGINE_ON(veh, FALSE, TRUE, TRUE);
                }
            }
        }

        // Aplicação do Antídoto Virox (Tecla H ou Atalho Rádio)
        if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 74)) 
        {
            if (g_isInfected) 
            {
                g_isInfected = false;
                UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
                UI::_ADD_TEXT_COMPONENT_STRING("~g~[VIROX] Infecção curada com sucesso!");
                UI::_DRAW_NOTIFICATION(FALSE, TRUE);
            }
        }
    }
}
