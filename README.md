# 𝐃𝐄𝐀𝐃 𝐖𝐀𝐒𝐓𝐄𝐋𝐀𝐍𝐃 🧟‍♂️🏜️
**Versão:** 1.0 | **Desenvolvedor:** Elder  
**Gênero:** Sobrevivência Zumbi / Logística Pesada / Construção / Gerenciamento de Base

---

## ✨ FUNCIONALIDADES

- **👥 Sistema de Profissões Dinâmico:** Atribua até 10 funções exclusivas aos seus Aliados (🔵) diretamente no mapa.
- **🚛 Logística Pesada:** Comandos `/A` (Assalto) e `/D` (Descarregar) para coleta e entrega de suprimentos.
- **🏗️ Construção:** Modo `F10` para posicionar e girar barreiras, portões e fortificações.
- **🟣 Frota Persistente (Bolinha Roxa):** Registre qualquer veículo para que ele nunca desapareça do mapa.
- **💀 Dificuldade Dinâmica:** Zumbis tornam-se corredores fatais e agressivos após as 16:00h.
- **⚔️ Facções:** Aliados (🔵), Hostis (🔴) e Exército (🟢).

---

## 👥 SISTEMA DE PROFISSÕES DINÂMICO

- **Atribuição no Mapa:** Aproxime-se de qualquer Aliado (🔵) e pressione **E** (Teclado USB) ou **D-Pad Direita** (Controle) para abrir o painel de seleção.
- **10 Funções Disponíveis:** 1. **Mecânico:** Reparo de veículos da frota.
  2. **Engenheiro:** Redução de custos no Modo F10.
  3. **Sentinela:** Defesa fixa do perímetro.
  4. **Sucateiro:** Bônus em missões de saque (`/A`).
  5. **Armeiro:** Produção de munição e manutenção de armas.
  6. **Agricultor:** Cultivo de alimentos na base.
  7. **Fazendeiro:** Manutenção e cuidado de Cavalos Reais e Carroças.
  8. **Patrulheiro:** Patrulha de perímetro e varredura do mapa.
  9. **Médico:** Cura de ferimentos e tratamento de infecções.
  10. **Cozinheiro:** Preparo de refeições para recuperação de Stamina.
- **Persistência Total:** As funções atribuídas são salvas automaticamente no arquivo `Database.xml`.

---

## ⌨️ COMANDOS E CONTROLES (Teclado / Controle)

| Ação | Teclado USB | Controle |
| :--- | :--- | :--- |
| **Registrar Veículo (Bolinha Roxa 🟣)** | `SHIFT + P` | `LB + D-Pad Direita` |
| **Modo Construção / Crafting** | `F10` | Menu dedicado |
| **Engatar/Desengatar Reboques e Carroças** | `J` ou `G` | Botão de Ação / Interação |
| **Menu de Rádio & Status** | `R + S` | `RB + D-Pad Baixo` |
| **Gerenciar Profissão do Aliado** | `E` (Perto do NPC) | `D-Pad Direita` (Perto do NPC) |
| **Modo Assalto (Saque)** | `/A` | Comando via Rádio |
| **Descarregar Suprimentos** | `/D` | Comando via Rádio |
| **Montar / Desmontar (Cavalo/Veículo)** | `F` | `Y` / `Triângulo` |

---

# 🐎 GTA V - Sistema de Transporte Realista (Cavalo e Reboques)

Scripts integrados para acoplagem de cargas, montaria e transporte com física de peso realista.

## 🛠️ Funcionalidades do Transporte
* **Montaria Funcional:** Permite montar e conduzir cavalos reais.
* **Sistema de Engate Dinâmico:** Acoplagem rápida de carroças de madeira e reboques modernos.
* **Física de Peso Realista:** O peso da carga afeta diretamente a aceleração e velocidade máxima do cavalo ou veículo.

## 📋 Lista de Modelos (Hashes)

| Tipo | Hash / Modelo |
| :--- | :--- |
| **Cavalo** | `a_c_horse` |
| **Carroça** | `prop_wagon_01` |
| **Reboque Moto** | `trailersmall` |
| **Reboque Lona** | `trailerlogs` ou `boattrailer` |

## 🏗️ Configuração de Física (Offsets)

Ajuste fino da posição do engate no código de transporte (`new Vector3(0.0f, -2.5f, 0.0f)`):
* **X (0.0):** Eixo centralizado.
* **Y (-2.5):** Distância de recuo atrás do cavalo ou veículo.
* **Z (0.0):** Altura relativa ao solo.

---

## 🚀 ESTRUTURA DE INSTALAÇÃO E ARQUIVOS

### 💻 No PC / Visual Studio
1. Certifique-se de ter o **ScriptHookV** e o **ScriptHookVDotNet** instalados.
2. Abra o projeto no Visual Studio (Biblioteca de Classes .NET Framework).
3. Adicione as referências `ScriptHookVDotNet2.dll` e `ScriptHookVDotNet3.dll`.
4. Compile para gerar os arquivos `.dll` e mova para a pasta `/scripts/` do GTA V.

### 🎮 No Console / Xbox 360 (RGH)
1. Copie a pasta `DeadWasteland_Mod` para a raiz do seu **Pendrive (FAT32)** ou HD Interno.
2. Certifique-se de que a estrutura de arquivos esteja organizada assim:
   ```text
   DeadWasteland_Mod/
   ├── Scripts_X360/
   │    ├── PersistenceSystem.cs
   │    ├── ZombieSystem.cs
   │    ├── TowSystem.cs
   │    ├── MenuRS.cs
   │    └── ProfessionSelector.cs
   └── Config/
        └── Database.xml
