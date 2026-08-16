#include "generated_offsets.h"
#include "xbox_helpers.h"
#include <cstdint>

namespace DeadWastelandXbox 
{
    struct Vector3 { float x, y, z; };

    bool g_buildMode = false;
    uintptr_t g_previewObj = 0;
    uint32_t g_currentPropHash = 0;
    float g_currentHeading = 0.0f;

    void ToggleBuildMode() 
    {
        g_buildMode = !g_buildMode;
        uintptr_t playerPed = *(uintptr_t*)PLAYER_PED_PTR;

        if (g_buildMode) 
        {
            InvokeNative(HASH_GET_HASH_KEY, "prop_barier_conc_05c", &g_currentPropHash);
            InvokeNative(HASH_REQUEST_MODEL, g_currentPropHash);
            
            bool loaded = false;
            while (!loaded) {
                InvokeNative(HASH_HAS_MODEL_LOADED, g_currentPropHash, &loaded);
                Sleep(0); // Substitui WAIT(0)
            }

            Vector3 pCoords;
            InvokeNative(HASH_GET_ENTITY_COORDS, playerPed, TRUE, &pCoords);
            
            InvokeNative(HASH_CREATE_OBJECT, g_currentPropHash, pCoords.x, pCoords.y + 3.0f, pCoords.z, FALSE, FALSE, FALSE, &g_previewObj);
            InvokeNative(HASH_SET_ENTITY_ALPHA, g_previewObj, 150, FALSE);
            InvokeNative(HASH_SET_ENTITY_COLLISION, g_previewObj, FALSE, FALSE);

            InvokeNative(HASH_SET_NOTIFICATION_TEXT_ENTRY, "STRING");
            InvokeNative(HASH_ADD_TEXT_COMPONENT_STRING, "~b~[CONSTRUÇÃO] Modo Ativado (F10 / LB+RB)");
            InvokeNative(HASH_DRAW_NOTIFICATION, FALSE, TRUE);
        } 
        else if (g_previewObj != 0) 
        {
            InvokeNative(HASH_DELETE_OBJECT, &g_previewObj);
            g_previewObj = 0;
        }
    }

    void UpdateConstructionSystem() 
    {
        bool inputToggle = false;
        InvokeNative(HASH_IS_DISABLED_CONTROL_JUST_PRESSED, 0, 57, &inputToggle);
        
        bool lbRb = false;
        InvokeNative(HASH_IS_CONTROL_PRESSED, 0, 20, &lbRb);
        bool rb = false;
        InvokeNative(HASH_IS_CONTROL_PRESSED, 0, 21, &rb);
        if (lbRb && rb) inputToggle = true;

        if (inputToggle) ToggleBuildMode();

        if (g_buildMode && g_previewObj != 0) 
        {
            uintptr_t playerPed = *(uintptr_t*)PLAYER_PED_PTR;
            Vector3 pCoords, forward;
            InvokeNative(HASH_GET_ENTITY_COORDS, playerPed, TRUE, &pCoords);
            InvokeNative(HASH_GET_ENTITY_FORWARD_VECTOR, playerPed, &forward);

            Vector3 targetPos = { pCoords.x + (forward.x * 4.0f), pCoords.y + (forward.y * 4.0f), pCoords.z };
            InvokeNative(HASH_SET_ENTITY_COORDS, g_previewObj, targetPos.x, targetPos.y, targetPos.z, FALSE, FALSE, FALSE, TRUE);

            bool qPressed = false, ePressed = false;
            InvokeNative(HASH_IS_CONTROL_PRESSED, 0, 44, &qPressed);
            InvokeNative(HASH_IS_CONTROL_PRESSED, 0, 38, &ePressed);
            
            if (qPressed) g_currentHeading += 2.0f;
            if (ePressed) g_currentHeading -= 2.0f;
            InvokeNative(HASH_SET_ENTITY_HEADING, g_previewObj, g_currentHeading);

            bool confirm = false;
            InvokeNative(HASH_IS_DISABLED_CONTROL_JUST_PRESSED, 0, 201, &confirm);
            if (!confirm) InvokeNative(HASH_IS_DISABLED_CONTROL_JUST_PRESSED, 0, 18, &confirm);

            if (confirm) 
            {
                uintptr_t finalObj = 0;
                InvokeNative(HASH_CREATE_OBJECT, g_currentPropHash, targetPos.x, targetPos.y, targetPos.z, TRUE, TRUE, FALSE, &finalObj);
                InvokeNative(HASH_SET_ENTITY_HEADING, finalObj, g_currentHeading);
                
                InvokeNative(HASH_DELETE_OBJECT, &g_previewObj);
                g_previewObj = 0;
                g_buildMode = false;

                InvokeNative(HASH_SET_NOTIFICATION_TEXT_ENTRY, "STRING");
                InvokeNative(HASH_ADD_TEXT_COMPONENT_STRING, "~g~[CONSTRUÇÃO] Estrutura posicionada!");
                InvokeNative(HASH_DRAW_NOTIFICATION, FALSE, TRUE);
            }
        }
    }
}
