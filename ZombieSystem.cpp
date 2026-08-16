#include "natives.h"

namespace DeadWastelandXbox 
{
    void UpdateZombieSystem() 
    {
        int hour = TIME::GET_CLOCK_HOURS();

        // Dificuldade Dinâmica às 16:00h (Zumbis Corredores)
        bool isRunnerTime = (hour >= 16 || hour < 5);

        // Blackout Noturno (20:00h - 05:00h)
        bool isBlackout = (hour >= 20 || hour < 5);
        GRAPHICS::_SET_BLACKOUT(isBlackout);

        const int maxPeds = 20;
        Ped nearbyPeds[maxPeds];
        int foundCount = worldGetAllPeds(nearbyPeds, maxPeds);

        for (int i = 0; i < foundCount; i++) 
        {
            Ped zPed = nearbyPeds[i];
            Ped playerPed = PLAYER::PLAYER_PED_ID();

            if (zPed != playerPed && !PED::IS_PED_A_PLAYER(zPed)) 
            {
                if (isRunnerTime) 
                {
                    // Força comportamento de zumbi corredor agressivo
                    PED::SET_PED_MOVE_RATE_OVERRIDE(zPed, 2.0f);
                    TASK::TASK_COMBAT_PED(zPed, playerPed, 0, 16);
                }
            }
        }
    }
}
