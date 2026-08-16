#include "natives.h"
#include "types.h"

namespace DeadWastelandXbox 
{
    bool g_buildMode = false;
    Object g_previewObj = 0;
    Hash g_currentPropHash = 0;
    float g_currentHeading = 0.0f;

    void ToggleBuildMode() 
    {
        g_buildMode = !g_buildMode;
        Ped playerPed = PLAYER::PLAYER_PED_ID();

        if (g_buildMode) 
        {
            // Barreira de concreto padrão
            g_currentPropHash = GAMEPLAY::GET_HASH_KEY("prop_barier_conc_05c");
            STREAMING::REQUEST_MODEL(g_currentPropHash);
            while (!STREAMING::HAS_MODEL_LOADED(g_currentPropHash)) WAIT(0);

            Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(playerPed, TRUE);
            g_previewObj = OBJECT::CREATE_OBJECT(g_currentPropHash, pCoords.x, pCoords.y + 3.0f, pCoords.z, FALSE, FALSE, FALSE);
            ENTITY::SET_ENTITY_ALPHA(g_previewObj, 150, FALSE); // Transparente para preview
            ENTITY::SET_ENTITY_COLLISION(g_previewObj, FALSE, FALSE);

            UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
            UI::_ADD_TEXT_COMPONENT_STRING("~b~[CONSTRUÇÃO] Modo Ativado (F10 / LB+RB)");
            UI::_DRAW_NOTIFICATION(FALSE, TRUE);
        } 
        else if (ENTITY::DOES_ENTITY_EXIST(g_previewObj)) 
        {
            OBJECT::DELETE_OBJECT(&g_previewObj);
            g_previewObj = 0;
        }
    }

    void UpdateConstructionSystem() 
    {
        // Tecla F10 OU LB + RB juntos
        bool inputToggle = CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 57) || 
                          (CONTROLS::IS_CONTROL_PRESSED(0, 20) && CONTROLS::IS_CONTROL_PRESSED(0, 21));

        if (inputToggle) ToggleBuildMode();

        if (g_buildMode && ENTITY::DOES_ENTITY_EXIST(g_previewObj)) 
        {
            Ped playerPed = PLAYER::PLAYER_PED_ID();
            Vector3 pCoords = ENTITY::GET_ENTITY_COORDS(playerPed, TRUE);
            Vector3 forward = ENTITY::GET_ENTITY_FORWARD_VECTOR(playerPed);

            // Posiciona a 4 metros na frente do jogador
            Vector3 targetPos = { pCoords.x + (forward.x * 4.0f), pCoords.y + (forward.y * 4.0f), pCoords.z };
            ENTITY::SET_ENTITY_COORDS(g_previewObj, targetPos.x, targetPos.y, targetPos.z, FALSE, FALSE, FALSE, TRUE);

            // Rotacionar: Q/E ou Analógico Esquerdo
            if (CONTROLS::IS_CONTROL_PRESSED(0, 44)) g_currentHeading += 2.0f; // Q
            if (CONTROLS::IS_CONTROL_PRESSED(0, 38)) g_currentHeading -= 2.0f; // E
            ENTITY::SET_ENTITY_HEADING(g_previewObj, g_currentHeading);

            // Confirmar: Enter / Botão X
            if (CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 201) || CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 18)) 
            {
                Object finalObj = OBJECT::CREATE_OBJECT(g_currentPropHash, targetPos.x, targetPos.y, targetPos.z, TRUE, TRUE, FALSE);
                ENTITY::SET_ENTITY_HEADING(finalObj, g_currentHeading);
                
                OBJECT::DELETE_OBJECT(&g_previewObj);
                g_previewObj = 0;
                g_buildMode = false;

                UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
                UI::_ADD_TEXT_COMPONENT_STRING("~g~[CONSTRUÇÃO] Estrutura posicionada!");
                UI::_DRAW_NOTIFICATION(FALSE, TRUE);
            }
        }
    }
}
