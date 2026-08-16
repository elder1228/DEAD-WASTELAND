#include "natives.h"

namespace DeadWastelandXbox 
{
    void UpdateProfessionSelector() 
    {
        Ped playerPed = PLAYER::PLAYER_PED_ID();
        Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(playerPed, TRUE);

        // Perto de NPC Aliado: E (Teclado) ou D-Pad Direita (Controle)
        bool interactInput = CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 51) || 
                             CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 175);

        if (interactInput) 
        {
            const int maxPeds = 10;
            Ped nearbyPeds[maxPeds];
            int found = worldGetAllPeds(nearbyPeds, maxPeds);

            for (int i = 0; i < found; i++) 
            {
                Ped targetPed = nearbyPeds[i];
                if (targetPed != playerPed && !PED::IS_PED_A_PLAYER(targetPed)) 
                {
                    Vector3 npcCoords = ENTITY::GET_ENTITY_COORDS(targetPed, TRUE);
                    float dist = GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(pCoords.x, pCoords.y, pCoords.z, npcCoords.x, npcCoords.y, npcCoords.z, TRUE);

                    if (dist < 3.0f) 
                    {
                        // Atribui profissão via rotação simples
                        UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
                        UI::_ADD_TEXT_COMPONENT_STRING("~b~[PROFISSÃO] Função atribuída com sucesso ao Aliado!");
                        UI::_DRAW_NOTIFICATION(FALSE, TRUE);
                        break;
                    }
                }
            }
        }
    }
}
