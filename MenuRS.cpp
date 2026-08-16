#include "natives.h"

namespace DeadWastelandXbox 
{
    bool g_menuOpen = false;

    void DrawMenuRS() 
    {
        // R + S no Teclado OU RB + D-Pad Baixo no Controle de Xbox
        bool openInput = (CONTROLS::IS_CONTROL_PRESSED(0, 45) && CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 31)) ||
                         (CONTROLS::IS_CONTROL_PRESSED(0, 206) && CONTROLS::IS_DISABLED_CONTROL_JUST_PRESSED(0, 19));

        if (openInput) 
        {
            g_menuOpen = !g_menuOpen;
        }

        if (g_menuOpen) 
        {
            // Desenha UI nativa do GTA V no Xbox (HUD Básica do Menu de Rádio)
            UI::SET_TEXT_FONT(0);
            UI::SET_TEXT_SCALE(0.4f, 0.4f);
            UI::SET_TEXT_COLOUR(255, 255, 255, 255);
            UI::SET_TEXT_ENTRY("STRING");
            UI::_ADD_TEXT_COMPONENT_STRING("--- DEAD WASTELAND RÁDIO ---");
            UI::DRAW_TEXT(0.1f, 0.2f);

            UI::SET_TEXT_ENTRY("STRING");
            UI::_ADD_TEXT_COMPONENT_STRING("1. Solicitar Airdrop (/9)");
            UI::DRAW_TEXT(0.1f, 0.24f);

            UI::SET_TEXT_ENTRY("STRING");
            UI::_ADD_TEXT_COMPONENT_STRING("2. Modo Assalto (/A)");
            UI::DRAW_TEXT(0.1f, 0.28f);

            UI::SET_TEXT_ENTRY("STRING");
            UI::_ADD_TEXT_COMPONENT_STRING("3. Descarregar Suprimentos (/D)");
            UI::DRAW_TEXT(0.1f, 0.32f);
        }
    }
}
