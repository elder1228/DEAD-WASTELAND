#include "natives.h"
#include "types.h"

namespace DeadWastelandXbox 
{
    Vector3 g_lastAirdropPos;
    bool g_airdropActive = false;

    void SpawnAirdrop() 
    {
        Ped playerPed = PLAYER::PLAYER_PED_ID();
        Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(playerPed, TRUE);

        // Posição de queda (raio de 100m a 200m do jogador, 150m de altura)
        float offsetX = (float)(GAMEPLAY::GET_RANDOM_INT_IN_RANGE(100, 200));
        float offsetY = (float)(GAMEPLAY::GET_RANDOM_INT_IN_RANGE(100, 200));
        g_lastAirdropPos = { pCoords.x + offsetX, pCoords.y + offsetY, pCoords.z + 150.0f };

        // Spawna caixa de suprimentos da Merryweather
        Hash crateHash = GAMEPLAY::GET_HASH_KEY("prop_box_wood02a");
        STREAMING::REQUEST_MODEL(crateHash);
        while (!STREAMING::HAS_MODEL_LOADED(crateHash)) WAIT(0);

        Object crate = OBJECT::CREATE_OBJECT(crateHash, g_lastAirdropPos.x, g_lastAirdropPos.y, g_lastAirdropPos.z, TRUE, TRUE, FALSE);
        ENTITY::SET_ENTITY_DYNAMIC(crate, TRUE);
        
        // Aplica paraquedas/fumaça de sinalização
        GRAPHICS::_ADD_PETROL_DECAL(g_lastAirdropPos.x, g_lastAirdropPos.y, g_lastAirdropPos.z, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f);
        
        Blip crateBlip = UI::ADD_BLIP_FOR_ENTITY(crate);
        UI::SET_BLIP_SPRITE(crateBlip, 306); // Ícone de Caixa
        UI::SET_BLIP_COLOUR(crateBlip, 2);  // Verde

        UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
        UI::_ADD_TEXT_COMPONENT_STRING("~g~[AIRDROP] Suprimentos da Merryweather a caminho!");
        UI::_DRAW_NOTIFICATION(FALSE, TRUE);

        g_airdropActive = true;
    }

    void UpdateAirdropSystem() 
    {
        // Tecla 9 no Teclado USB para solicitar Airdrop de Emergência
        if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 118)) 
        {
            SpawnAirdrop();
        }
    }
}
