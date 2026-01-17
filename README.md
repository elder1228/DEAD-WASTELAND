# DEAD-WASTELAND
# 𝐃𝐄𝐀𝐃 𝐖𝐀𝐒𝐓𝐄𝐋𝐀𝐍𝐃 🧟‍♂️🏜️
**Versão:** 1.0 | **Desenvolvedor:** Elder
**Gênero:** Sobrevivência Zumbi / Logística Pesada / Construção

## ✨ FUNCIONALIDADES
- **Logística Pesada:** Comandos `/A` (Assalto) e `/D` (Descarregar).
- **Construção:** Modo `F10` para posicionar e girar barreiras.
- **Frota (Bolinha Roxa 🟣):** Sistema de persistência para QUALQUER veículo.
- **Dificuldade Dinâmica:** Zumbis tornam-se corredores fatais após as 16:00h.
- **Facções:** Aliados (🔵), Hostis (🔴) e Exército (🟢).

## ⌨️ COMANDOS (HOTKEYS)
- **SHIFT + P:** Salva o veículo atual na frota (Gera a Bolinha Roxa 🟣).
- **F10:** Entra no Modo de Construção/Crafting.
- **G:** Trava/Destrava veículos em cegonhas e reboques.
- **R + S:** Abre o Menu de Rádio e Status.
- ** /A:** Inicia Modo Assalto (Saque).
- ** /D:** Descarrega suprimentos na base.

## 🛠️ INSTALAÇÃO
1. Instale o ScriptHookV e ScriptHookVDotNet.
2. Arraste a pasta `DeadWasteland` para `/Grand Theft Auto V/scripts/`.

# GTA V - Sistema de Transporte Realista (Cavalo e Reboques)

Este repositório contém scripts em C# para o ScriptHookVDotNet que adicionam mecânicas de montaria e transporte de carga com física de peso realista ao GTA V.

## 🛠️ Funcionalidades

* **Montaria Funcional**: Permite montar e conduzir cavalos (Franklin/Player).
* **Sistema de Engate Dinâmico**: Acoplagem de carroças e reboques modernos.
* **Física de Peso Realista**: A carga lida no reboque afeta diretamente a aceleração e a velocidade máxima do cavalo ou veículo.
* **Compatibilidade de Modelos**: Suporte para carroças de madeira e reboques de metal modernos.

## 🎮 Controles

* **Tecla [F]**: Montar ou desmontar do cavalo/veículo.
* **Tecla [J]**: Engatar ou desengatar a carroça/reboque (necessário estar montado e próximo ao objeto).

## 📋 Lista de Modelos (Hashes)

Substitua no código conforme os modelos instalados no seu jogo:

| Tipo | Hash/Modelo |
| :--- | :--- |
| Cavalo | `a_c_horse` |
| Carroça | `prop_wagon_01` |
| Reboque Moto | `trailersmall` |
| Reboque Lona | `trailerlogs` ou `boattrailer` |

## 🏗️ Configuração de Física (Offsets)

Para ajuste fino da posição do engate no arquivo `TransporteRealista.cs`:
* **Ajuste de Distância**: `new Vector3(0.0f, -2.5f, 0.0f)`
    * `X (0.0)`: Centralizado.
    * `Y (-2.5)`: Distância atrás do cavalo.
    * `Z (0.0)`: Altura em relação ao solo.

## 🚀 Como Instalar (Quando estiver no Notebook)

1.  Certifique-se de ter o **ScriptHookV** e o **ScriptHookVDotNet** instalados na pasta raiz do GTA V.
2.  Abra o **Visual Studio** e crie um novo projeto de "Biblioteca de Classes (.NET Framework)".
3.  Adicione as referências `ScriptHookVDotNet2.dll` e `ScriptHookVDotNet3.dll`.
4.  Cole o código dos arquivos `.cs` deste repositório.
5.  Compile o projeto (Build) para gerar o arquivo `.dll`.
6.  Mova o arquivo `.dll` gerado para a pasta `/scripts` dentro do diretório do seu GTA V.

___