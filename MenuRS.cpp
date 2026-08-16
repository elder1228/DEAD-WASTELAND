#include "generated_offsets.h"
#include "xbox_helpers.h"
#include <cstdint>

namespace DeadWastelandXbox 
{
    bool g_menuOpen = false;

    void DrawMenuRS() 
    {
        bool rS = false, rbDown = false;
        InvokeNative(HASH_IS_CONTROL_PRESSED, 0, 45, &rS);
        InvokeNative(HASH_IS_DISABLED_CONTROL_JUST_PRESSED, 0, 31, &rbDown);
        bool rbDown2 = false;
        InvokeNative(HASH_IS_CONTROL_PRESSED, 0, 206, &rbDown2); // RB
        InvokeNative(HASH_IS_DISABLED_CONTROL_JUST_PRESSED, 0, 19, &rbDown); // Dpad Down

        bool openInput = (rS && rbDown) || (rbDown2 && rbDown);

        if (openInput) g_menuOpen = !g_menuOpen;

        if (g_menuOpen) 
        {
            InvokeNative(HASH_SET_TEXT_FONT, 0);
            InvokeNative(HASH_SET_TEXT_SCALE, 0.4f, 0.4f);
            InvokeNative(HASH_SET_TEXT_COLOUR, 255, 255, 255, 255);
            
            InvokeNative(HASH_SET_TEXT_ENTRY, "STRING");
            InvokeNative(HASH_ADD_TEXT_COMPONENT_STRING, "--- DEAD WASTELAND RÁDIO ---");
            InvokeNative(HASH_DRAW_TEXT, 0.1f, 0.2f);

            InvokeNative(HASH_SET_TEXT_ENTRY, "STRING");
            InvokeNative(HASH_ADD_TEXT_COMPONENT_STRING, "1. Solicitar Airdrop (/9)");
            InvokeNative(HASH_DRAW_TEXT, 0.1f, 0.24f);

            InvokeNative(HASH_SET_TEXT_ENTRY, "STRING");
            InvokeNative(HASH_ADD_TEXT_COMPONENT_STRING, "2. Modo Assalto (/A)");
            InvokeNative(HASH_DRAW_TEXT, 0.1f, 0.28f);

            InvokeNative(HASH_SET_TEXT_ENTRY, "STRING");
            InvokeNative(HASH_ADD_TEXT_COMPONENT_STRING, "3. Descarregar Suprimentos (/D)");
            InvokeNative(HASH_DRAW_TEXT, 0.1f, 0.32f);
        }
    }
}
