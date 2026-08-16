#pragma once
#include <cstdint>
#include <cmath>

// =========================================================
// 1. DEFINIÇÃO DE TIPOS (Substituindo o types.h do ScriptHook)
// =========================================================
// No Xbox 360, entidades são ponteiros diretos na memória.
typedef uintptr_t Entity;
typedef uintptr_t Ped;
typedef uintptr_t Vehicle;
typedef uintptr_t Object;
typedef uintptr_t Blip;
typedef uint32_t  Hash;

// =========================================================
// 2. STRUCTS MATEMÁTICAS
// =========================================================
struct Vector3 {
    float x, y, z;
};

struct Vector4 {
    float x, y, z, w;
};

// =========================================================
// 3. HELPERS DE SISTEMA (Substituindo o WAIT(0))
// =========================================================
// O XDK não tem o WAIT() do ScriptHook. Criamos um delay simples
// para não travar a thread principal do jogo enquanto carregamos modelos.
inline void XSleep(int ms) 
{
    // Em um ambiente XDK real, você usaria KeDelayExecutionThread ou similar.
    // Este é um loop de espera seguro para não crashar a CPU do PowerPC.
    volatile int dummy = 0;
    for (int i = 0; i < ms * 10000; i++) {
        dummy++; 
    }
}
#define Sleep(ms) XSleep(ms)

// =========================================================
// 4. O CORAÇÃO DO MOD: INVOCADOR DE NATIVES
// =========================================================
// Esta é a função mágica que o Python vai nos ajudar a calibrar.
// Ela pega o Hash da Native, acha o endereço na Native Table (que o Python achou)
// e executa a função no Assembly do PowerPC.

// Nota: A implementação exata do Assembly depende de como o GTA V organiza a tabela.
// Abaixo está a estrutura lógica que você vai preencher quando o Ghidra te der o formato da tabela.

inline void InvokeNative(Hash hash, ...) 
{
    // CONCEITO:
    // 1. O Python preencheu NATIVE_TABLE_BASE no generated_offsets.h
    // 2. O GTA V usa um "Dispatcher" para achar a função pelo Hash.
    // 3. Aqui nós chamamos esse Dispatcher.
    
    // Exemplo de como ficaria a chamada (isso será ajustado com o dump real):
    /*
    typedef void (*NativeDispatcher)(Hash hash, uint64_t* args);
    NativeDispatcher dispatcher = (NativeDispatcher)NATIVE_DISPATCHER_ADDR; 
    
    uint64_t args[10]; // Array de argumentos
    // ... preencher args com os parâmetros passados via '...'
    dispatcher(hash, args);
    */
}

// Helper para retornar valores de Natives (ex: GET_ENTITY_COORDS retorna Vector3)
template <typename T>
inline T InvokeNativeReturn(Hash hash, ...) 
{
    // Mesma lógica do InvokeNative, mas retornando o valor do registrador de retorno (r3 no PowerPC)
    return T(); 
}
