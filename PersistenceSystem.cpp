#include "natives.h"

namespace DeadWastelandXbox 
{
    void UpdatePersistenceSystem() 
    {
        Ped playerPed = PLAYER::PLAYER_PED_ID();

        // SHIFT + P ou LB + D-Pad Direita
        bool registerInput = (CONTROLS::IS_CONTROL_PRESSED(0, 21) && CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 199)) ||
                             (CONTROLS::IS_CONTROL_PRESSED(0, 20) && CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 175));

        if (registerInput && PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE)) 
        {
            Vehicle veh = PED::GET_VEHICLE_PED_IS_IN(playerPed, FALSE);

            // Registra o veículo para não sumir (Bolinha Roxa 🟣)
            ENTITY::SET_ENTITY_AS_MISSION_ENTITY(veh, TRUE, TRUE);
            
            Blip vehBlip = UI::ADD_BLIP_FOR_ENTITY(veh);
            UI::SET_BLIP_SPRITE(vehBlip, 225); // Ícone de Veículo
            UI::SET_BLIP_COLOUR(vehBlip, 7);   // Roxo

            UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
            UI::_ADD_TEXT_COMPONENT_STRING("~p~[FROTA] Veículo registrado na Frota Persistente!");
            UI::_DRAW_NOTIFICATION(FALSE, TRUE);
        }
    }
}
