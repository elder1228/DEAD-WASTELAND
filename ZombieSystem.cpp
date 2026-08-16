#include "generated_offsets.h"
#include "xbox_helpers.h"
#include <cstdint>
#include <cmath>

namespace DeadWastelandXbox 
{
    // Helper para chamar Natives complexas via Tabela de Nativas (mais seguro que reimplementar a lógica de Task em Assembly)
    // O Python vai preencher NATIVE_TABLE_BASE no generated_offsets.h
    void InvokeNative(uint64_t hash, uintptr_t arg1 = 0, uintptr_t arg2 = 0) {
        // Lógica de chamada da Native Table usando NATIVE_TABLE_BASE
        // (Aqui entraria o código de montagem da chamada PowerPC)
    }

    void UpdateZombieSystem() 
    {
        // 1. Ler o Horário do Jogo diretamente da Memória
        // O Python preencheu CLOCK_HOURS_PTR com o endereço do byte da hora
        uint8_t* clockPtr = (uint8_t*)CLOCK_HOURS_PTR;
        int hour = (clockPtr != nullptr) ? *clockPtr : 12; // Fallback para meio-dia se falhar

        // Dificuldade Dinâmica às 16:00h (Zumbis Corredores)
        bool isRunnerTime = (hour >= 16 || hour < 5);

        // Blackout Noturno (20:00h - 05:00h)
        bool isBlackout = (hour >= 20 || hour < 5);
        
        // Escrever diretamente no flag de Blackout do Timecycle/Graphics
        uint8_t* blackoutPtr = (uint8_t*)BLACKOUT_FLAG_PTR;
        if (blackoutPtr != nullptr) {
            *blackoutPtr = isBlackout ? 1 : 0;
        }

        // 2. Iterar o Pool de Peds manualmente (Substituindo worldGetAllPeds)
        // A estrutura do Pool do RAGE usa um array de itens e um bitmask de existência
        uintptr_t pedPoolBase = PED_POOL_PTR;
        if (pedPoolBase == 0) return;

        // *Nota: O Python/IA deve preencher esses offsets específicos do Pool no generated_offsets.h*
        void** pedItems = (void**)(pedPoolBase + PED_POOL_ITEMS_OFFSET); 
        uint32_t* pedBitset = (uint32_t*)(pedPoolBase + PED_POOL_BITSET_OFFSET);
        int maxPeds = PED_POOL_MAX_ITEMS;

        // Pegar o Player atual (Lendo o ponteiro global do Player Ped)
        uintptr_t playerPed = *(uintptr_t*)PLAYER_PED_PTR;

        for (int i = 0; i < maxPeds; i++) 
        {
            // Checar se o ped existe no pool via bitmask (Otimização crucial para não crashar)
            int index = i / 32;
            int bit = i % 32;
            if (!(pedBitset[index] & (1 << bit))) continue;

            uintptr_t zPed = (uintptr_t)pedItems[i];
            if (zPed == 0 || zPed == playerPed) continue;

            // Checar se não é o player (lendo o flag de isPlayer na struct do Ped)
            bool isPlayer = *(uint8_t*)(zPed + CPED_IS_PLAYER_OFFSET);
            if (isPlayer) continue;

            if (isRunnerTime) 
            {
                // 3. Modificar a CPedIntelligence para forçar comportamento de zumbi
                
                // Pegar o ponteiro da CPedIntelligence
                uintptr_t pedIntelligence = *(uintptr_t*)(zPed + CPED_INTELLIGENCE_OFFSET);
                if (pedIntelligence == 0) continue;

                // Forçar taxa de movimento (Move Rate Override)
                float* moveRatePtr = (float*)(pedIntelligence + MOVE_RATE_OVERRIDE_OFFSET);
                *moveRatePtr = 2.0f; // Zumbi corredor (2x mais rápido)

                // 4. Forçar Combate (Task Combat)
                // No Xbox 360, a maneira mais estável de dar uma Task complexa é via Native Table
                // O Python vai preencher HASH_TASK_COMBAT_PED no generated_offsets.h
                
                // Equivalente a: TASK::TASK_COMBAT_PED(zPed, playerPed, 0, 16);
                InvokeNative(HASH_TASK_COMBAT_PED, zPed, playerPed);
                
                // OU, se quiser fazer via memória pura (escrevendo o target direto na struct):
                // *(uintptr_t*)(pedIntelligence + COMBAT_TARGET_OFFSET) = playerPed;
            }
        }
    }
}
