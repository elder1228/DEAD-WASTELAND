# 𝐃𝐄𝐀𝐃 𝐖𝐀𝐒𝐓𝐄𝐋𝐀𝐍𝐃 🧟‍♂️🏜️
**Versão:** 2.0 (Edição Sobrevivência Total) | **Desenvolvedor:** Elder  
**Gênero:** Sobrevivência Zumbi / Logística Pesada / Construção / Gerenciamento de Base / Crafting

---

## ✨ FUNCIONALIDADES

- **👥 Sistema de Profissões Dinâmico:** Atribua até 10 funções exclusivas aos seus Aliados (🔵) diretamente no mapa.
- **🚛 Logística Pesada & Montaria:** Sistema completo para montar em Cavalos Reais e engatar Carroças/Reboques com física de peso realista.
- **🏗️ Construção & Crafting (`F10`):** Posicione e gire barreiras de concreto, sacos de areia, portões, barracas e fogueiras usando recursos coletados.
- **🟣 Frota Persistente (Bolinha Roxa):** Registre qualquer veículo para que ele nunca desapareça do mapa.
- **💀 Dificuldade Dinâmica (16:00h):** Zumbis tornam-se corredores fatais, agressivos e com velocidade ampliada a partir das 16:00h.
- **🌑 Blackout Total Noturno (20:00h - 05:00h):** Falha geral na rede elétrica da cidade. Visibilidade dependente de lanternas, fogueiras e faróis.
- **🧪 Sistema de Infecção & Antídoto Virox:** Mordidas causam infecção progressiva, tontura e febre. Tratamento via Médicos da base ou Caixas de Virox.
- **📦 Airdrops de Emergência:** Queda de suprimentos da Merryweather com munição, remédios e resgate de sobreviventes neutros.
- **⛽ Gestão Realista de Combustível:** Veículos consomem combustível em tempo real. Abastecimento manual necessário via Galão de Gasolina.
- **⚔️ Facções:** Aliados (🔵), Hostis (🔴) e Exército (🟢).

---

## 👥 SISTEMA DE PROFISSÕES DINÂMICO

- **Atribuição no Mapa:** Aproxime-se de qualquer Aliado (🔵) e pressione **E** (Teclado USB) ou **D-Pad Direita** (Controle) para abrir o painel de seleção.
- **10 Funções Disponíveis:**
  1. **Mecânico:** Reparo de veículos da frota e recuperação de motores.
  2. **Engenheiro:** Redução de custos de recursos no Modo de Construção `F10`.
  3. **Sentinela:** Defesa fixa do perímetro da base.
  4. **Sucateiro:** Bônus de obtenção de Peças (`Metal`, `Wood`) em missões de saque (`/A`).
  5. **Armeiro:** Produção de munição e manutenção de armamento.
  6. **Agricultor:** Cultivo de alimentos para a base.
  7. **Fazendeiro:** Cuidado, manutenção e gestão de Cavalos e Carroças.
  8. **Patrulheiro:** Patrulha de perímetro, busca de Airdrops e varredura do mapa.
  9. **Médico:** Cura de ferimentos e fabricação do Antídoto Virox contra infecções.
  10. **Cozinheiro:** Preparo de refeições para recuperação de Stamina e Fome.
- **Persistência Total:** As funções atribuídas são salvas automaticamente no arquivo `Database.xml`.

---

## ⌨️ COMANDOS E CONTROLES (Teclado / Controle)

| Ação | Teclado USB | Controle Xbox |
| :--- | :--- | :--- |
| **Registrar Veículo (Bolinha Roxa 🟣)** | `SHIFT + P` | `LB + D-Pad Direita` |
| **Modo Construção / Crafting** | `F10` | `LB + RB` (Juntos) |
| **Girar Objeto na Construção** | `Q` / `E` | Analógico Esquerdo |
| **Confirmar Posição da Estrutura** | `Enter` | Botão `X` |
| **Engatar/Desengatar Reboques e Carroças** | `J` ou `G` | Botão `X` (Perto do Reboque) |
| **Menu de Rádio & Status** | `R + S` | `RB + D-Pad Baixo` |
| **Gerenciar Profissão do Aliado** | `E` (Perto do NPC) | `D-Pad Direita` (Perto do NPC) |
| **Aplicar Antídoto Virox** | `H` | Atalho no Menu de Rádio |
| **Solicitar Airdrop de Emergência** | `9` | Comando via Rádio |
| **Modo Assalto (Saque)** | `/A` | Comando via Rádio |
| **Descarregar Suprimentos** | `/D` | Comando via Rádio |
| **Montar / Desmontar (Cavalo/Veículo)** | `F` | Botão `Y` |

---

# 🐎 SISTEMA DE TRANSPORTE E CARROÇAS

Scripts integrados para acoplagem de cargas, montaria e transporte com física de peso realista.

## 🛠️ Funcionalidades do Transporte
* **Montaria Funcional:** Permite montar e conduzir cavalos reais (`a_c_horse`).
* **Sistema de Engate Dinâmico:** Acoplagem rápida de carroças de madeira (`prop_wagon_01`) e reboques modernos.
* **Física de Peso Realista:** O peso da carga afeta diretamente a aceleração e a velocidade máxima do animal ou veículo.

## 📋 Lista de Modelos (Hashes)

| Tipo | Hash / Modelo |
| :--- | :--- |
| **Cavalo** | `a_c_horse` |
| **Carroça de Madeira** | `prop_wagon_01` |
| **Reboque de Moto** | `trailersmall` |
| **Reboque de Lona** | `trailerlogs` ou `boattrailer` |

## 🏗️ Configuração de Física (Offsets)
* **Ajuste de Engate (`Vector3(0.0f, -2.5f, 0.0f)`):** Mantém a carroça alinhada e centralizada a 2.5 metros atrás do cavalo ou veículo.

---

## 🚀 ESTRUTURA DE INSTALAÇÃO E ARQUIVOS

### 💻 No PC (ScriptHookVDotNet)
1. Instale o **ScriptHookV** e o **ScriptHookVDotNet**.
2. Cole os arquivos `.cs` e o `Database.xml` diretamente na pasta `scripts/` do GTA V.

### 🎮 No Console / Xbox 360 (RGH)
1. Formate o seu pendrive em **FAT32**.
2. Copie a pasta `scripts` para o seu dispositivo USB ou HD Interno.
3. Estrutura de arquivos completa e atualizada:
   ```text
   scripts/
   ├── AirdropSystem.cs
   ├── ConstructionSystem.cs
   ├── Database.xml
   ├── MenuRS.cs
   ├── PersistenceSystem.cs
   ├── ProfessionLogic.cs
   ├── ProfessionSelector.cs
   ├── SurvivalSystem.cs
   ├── TowSystem.cs
   └── ZombieSystem.cs
