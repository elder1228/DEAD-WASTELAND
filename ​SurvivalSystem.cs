using System;
using GTA;
using GTA.Math;
using GTA.Native;

namespace DeadWastelandXbox
{
    public class SurvivalSystem : Script
    {
        private float hunger = 100.0f;
        private float thirst = 100.0f;
        private float infectionLevel = 0.0f; // 0% a 100%
        private bool isBitten = false;

        public SurvivalSystem()
        {
            Tick += OnTick;
        }

        private void OnTick(object sender, EventArgs e)
        {
            Ped player = Game.Player.Character;

            // 1. Drenagem natural de Fome e Sede
            if (hunger > 0) hunger -= 0.005f;
            if (thirst > 0) thirst -= 0.008f;

            // 2. Sistema de Infecção
            if (isBitten)
            {
                infectionLevel += 0.02f; // Vírus avança com o tempo

                if (infectionLevel >= 50.0f && infectionLevel < 80.0f)
                {
                    UI.Notify("~r~[SINTOMA] Você está com febre e visão turva devido à infecção!");
                }
                else if (infectionLevel >= 100.0f)
                {
                    player.Kill(); // Jogador morre e vira zumbi
                    UI.Notify("~r~Você sucumbiu à infecção do vírus!");
                }
            }

            // 3. Uso do Antídoto Virox (Teclado: H / Controle: Usar Item)
            if (Game.IsKeyPressed(System.Windows.Forms.Keys.H))
            {
                UseViroxAntidote();
                Script.Wait(1000);
            }

            // 4. Consumo de Combustível nos Veículos
            if (player.IsInVehicle())
            {
                Vehicle veh = player.CurrentVehicle;
                if (veh.IsEngineRunning)
                {
                    float currentFuel = veh.FuelLevel;
                    if (currentFuel > 0)
                    {
                        veh.FuelLevel -= 0.01f; // Consome gasolina rodando
                    }
                    else
                    {
                        veh.IsEngineRunning = false;
                        UI.Notify("~r~[VEÍCULO] O combustível acabou! Use um Galão de Gasolina.");
                    }
                }
            }
        }

        public void ApplyZombieBite()
        {
            isBitten = true;
            UI.Notify("~r~[ALERTA] Você foi mordido! Procure o Antídoto Virox ou fale com o Médico da base.");
        }

        private void UseViroxAntidote()
        {
            if (isBitten || infectionLevel > 0)
            {
                isBitten = false;
                infectionLevel = 0.0f;
                UI.Notify("~g~[MEDICAMENTO] Antídoto Virox aplicado! Infecção curada.");
            }
            else
            {
                UI.Notify("~w~Você não está infectado.");
            }
        }
    }
}
