#include <fstream>
#include <string>
#include "natives.h"

namespace DeadWastelandXbox 
{
    // C++ no Xbox 360 usa salvamento binário/texto direto no drive (hdd0:/ or usbdrive:/)
    void SaveDatabase() 
    {
        std::ofstream file("game:\dead_wasteland_data.txt");
        if (file.is_open()) 
        {
            // Salva posição e estado dos recursos do jogador
            Ped playerPed = PLAYER::PLAYER_PED_ID();
            Vector3 coords = ENTITY::GET_ENTITY_COORDS(playerPed, TRUE);

            file << "POS_X=" << coords.x << "\n";
            file << "POS_Y=" << coords.y << "\n";
            file << "POS_Z=" << coords.z << "\n";
            file.close();

            UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
            UI::_ADD_TEXT_COMPONENT_STRING("~g~[PERSISTÊNCIA] Dados salvos com sucesso.");
            UI::_DRAW_NOTIFICATION(FALSE, TRUE);
        }
    }

    void LoadDatabase() 
    {
        std::ifstream file("game:\dead_wasteland_data.txt");
        if (file.is_open()) 
        {
            std::string line;
            float x = 0, y = 0, z = 0;
            while (std::getline(file, line)) 
            {
                if (line.find("POS_X=") == 0) x = std::stof(line.substr(6));
                if (line.find("POS_Y=") == 0) y = std::stof(line.substr(6));
                if (line.find("POS_Z=") == 0) z = std::stof(line.substr(6));
            }
            file.close();

            if (x != 0 && y != 0) 
            {
                Ped playerPed = PLAYER::PLAYER_PED_ID();
                ENTITY::SET_ENTITY_COORDS(playerPed, x, y, z, FALSE, FALSE, FALSE, TRUE);
            }
        }
    }
}
