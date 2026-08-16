# 𝐃𝐄𝐀𝐃 𝐖𝐀𝐒𝐓𝐄𝐋𝐀𝐍𝐃 🧟‍♂️🏜️
**Versão:** 2.0 (Edição Sobrevivência Total - C++ Xbox 360 Edition)  
**Desenvolvedor:** Elder  
**Plataforma:** Xbox 360 (RGH / JTAG)  
**Linguagem & Arquitetura:** C++ / PowerPC Native Plugin (`.xex` / RAGE Engine)  
**Gênero:** Sobrevivência Zumbi / Logística Pesada / Construção / Gerenciamento de Base / Crafting

---

## ✨ FUNCIONALIDADES

- **👥 Sistema de Profissões Dinâmico:** Atribua até 10 funções exclusivas aos seus Aliados (🔵) diretamente no mapa.
- **🚛 Logística Pesada & Reboques:** Sistema de engate de reboques de carga com física de peso realista afetando o motor dos veículos.
- **🏗️ Construção & Crafting (`F10` / `LB+RB`):** Posicione e gire barreiras de concreto, sacos de areia, portões, barracas e fogueiras usando recursos coletados.
- **🟣 Frota Persistente (Bolinha Roxa):** Registre qualquer veículo para que ele nunca desapareça do mapa.
- **💀 Dificuldade Dinâmica (16:00h):** Zumbis tornam-se corredores fatais, agressivos e com velocidade ampliada a partir das 16:00h.
- **🌑 Blackout Total Noturno (20:00h - 05:00h):** Falha geral na rede elétrica da cidade. Visibilidade dependente de lanternas, fogueiras e faróis.
- **🧪 Sistema de Infecção & Antídoto Virox:** Mordidas causam infecção progressiva. Tratamento via Médicos da base ou Caixas de Virox de Airdrops.
- **📦 Airdrops de Emergência:** Queda de suprimentos da Merryweather com munição, remédios e resgate de sobreviventes neutros.
- **⛽ Gestão Realista de Combustível:** Veículos consomem combustível em tempo real. Abastecimento manual necessário via Galão de Gasolina.
- **⚔️ Facções:** Aliados (🔵), Hostis (🔴) e Exército (🟢).

---

## 👥 SISTEMA DE PROFISSÕES DINÂMICO

- **Atribuição no Mapa:** Aproxime-se de qualquer Aliado (🔵) e pressione **E** (Teclado USB) ou **D-Pad Direita** (Controle) para abrir o painel de seleção.
- **10 Funções Disponíveis:**
  1. **Mecânico:** Reparo de veículos da frota e recuperação de motores.
  2. **Engenheiro:** Redução de custos de recursos no Modo de Construção.
  3. **Sentinela:** Defesa fixa do perímetro da base com fuzil Carbine.
  4. **Sucateiro:** Bônus de obtenção de Peças (`Metal`, `Wood`) em missões de saque.
  5. **Armeiro:** Produção de munição e manutenção de armamento.
  6. **Agricultor:** Cultivo de alimentos para a base.
  7. **Fazendeiro:** Gestão de suprimentos pesados e manutenção da frota de transporte.
  8. **Patrulheiro:** Patrulha de perímetro, busca de Airdrops e varredura do mapa.
  9. **Médico:** Cura de ferimentos, vida ampliada e liberação do Antídoto Virox.
  10. **Cozinheiro:** Preparo de refeições para recuperação de Stamina e Fome.
- **Persistência Total:** As funções e dados são salvos no armazenamento interno do console.

---

## ⌨️ COMANDOS E CONTROLES (Teclado / Controle)

| Ação | Teclado USB | Controle Xbox 360 |
| :--- | :--- | :--- |
| **Registrar Veículo (Bolinha Roxa 🟣)** | `SHIFT + P` | `LB + D-Pad Direita` |
| **Modo Construção / Crafting** | `F10` | `LB + RB` (Juntos) |
| **Girar Objeto na Construção** | `Q` / `E` | Analógico Esquerdo |
| **Confirmar Posição da Estrutura** | `Enter` | Botão `X` |
| **Engatar/Desengatar Reboques** | `J` ou `G` | Botão `X` (Perto do Engate) |
| **Menu de Rádio & Status** | `R + S` | `RB + D-Pad Baixo` |
| **Gerenciar Profissão do Aliado** | `E` (Perto do NPC) | `D-Pad Direita` (Perto do NPC) |
| **Aplicar Antídoto Virox** | `H` | Atalho no Menu de Rádio |
| **Solicitar Airdrop de Emergência** | `9` | Comando via Rádio |
| **Modo Assalto (Saque)** | `/A` | Comando via Rádio |
| **Descarregar Suprimentos** | `/D` | Comando via Rádio |
| **Entrar / Sair do Veículo** | `F` | Botão `Y` |

---

## 🚛 SISTEMA DE TRANSPORTE E REBOQUES

Mecânica focada no transporte de suprimentos utilizando veículos terrestres modificados e reboques utilitários.

### 🛠️ Funcionalidades
* **Sistema de Engate Dinâmico:** Acoplagem rápida de reboques na traseira de caminhonetes, caminhões ou carros persistentes.
* **Física de Peso Realista:** O peso total dos suprimentos acumulados no reboque afeta dinamicamente a aceleração, frenagem e estabilidade do veículo motorizado.

### 📋 Lista de Modelos Utilizados (Hashes)

| Tipo | Hash / Modelo |
| :--- | :--- |
| **Reboque de Moto / Pequeno** | `trailersmall` |
| **Reboque de Lona / Carga** | `trailerlogs` |
| **Reboque de Barco / Ferro** | `boattrailer` |

---

## 🚀 ESTRUTURA DE COMPILAÇÃO E ARQUIVOS (C++)

### 🎮 No Console / Xbox 360 (RGH)
1. Crie o plugin compilado (`DeadWasteland.xex`) utilizando o Visual Studio com o XDK de Xbox 360.
2. Copie o arquivo `DeadWasteland.xex` para a pasta raiz do GTA V no HD/Pendrive do Xbox.
3. Defina o plugin na **Dashlaunch** ou execute via menu de carregamento.

### 📁 Estrutura do Código-Fonte em C++:
```text
src/
├── AirdropSystem.cpp
├── ConstructionSystem.cpp
├── DatabaseSystem.cpp
├── MenuRS.cpp
├── PersistenceSystem.cpp
├── ProfessionLogic.cpp
├── ProfessionSelector.cpp
├── SurvivalSystem.cpp
├── TowSystem.cpp
└── ZombieSystem.cpp
