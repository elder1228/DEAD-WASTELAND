using System;
using GTA;
using GTA.Math;
using GTA.Native;

namespace DeadWastelandXbox
{
    public class ZombieSystem : Script
    {
        private bool isBlackoutActive = false;
        private bool isPanicHourActive = false;

        public ZombieSystem()
        {
            Tick += OnTick;
        }

        private void OnTick(object sender, EventArgs e)
        {
            TimeSpan currentTime = World.CurrentDayTime;
            int hours = currentTime.Hours;

            // 1. LÓGICA DAS 16:00h (Zumbis Corredores)
            if (hours >= 16 && hours < 20)
            {
                if (!isPanicHourActive)
                {
                    isPanicHourActive = true;
                    UI.Notify("~r~[ALERTA 16:00] Os zumbis estão mais agressivos e rápidos! Retorne à base!");
                }
            }
            else
            {
                isPanicHourActive = false;
            }

            // 2. LÓGICA DO BLACKOUT (20:00h até às 05:00h)
            if (hours >= 20 || hours < 5)
            {
                if (!isBlackoutActive)
                {
                    isBlackoutActive = true;
                    World.Blackout = true; // Apaga todas as luzes do mapa do GTA V
                    UI.Notify("~b~[BLACKOUT] Falha na rede elétrica! A iluminação da cidade foi desligada.");
                }
            }
            else
            {
                if (isBlackoutActive)
                {
                    isBlackoutActive = false;
                    World.Blackout = false; // Religa as luzes ao amanhecer
                    UI.Notify("~g~[AMANHECER] O sol nasceu. A energia da base foi restaurada.");
                }
            }

            // Aplicar comportamentos aos Zumbis no mapa
            Ped[] peds = World.GetAllPeds();
            foreach (Ped ped in peds)
            {
                if (ped != Game.Player.Character && !ped.IsPlayer)
                {
                    // Se for horário de pânico ou noite, aumenta a velocidade de corrida dos zumbis
                    if (isPanicHourActive || isBlackoutActive)
                    {
                        Function.Call(Hash.SET_PED_MOVE_RATE_OVERRIDE, ped, 1.3f); // Movem-se mais rápido
                        Function.Call(Hash.TASK_COMBAT_PED, ped, Game.Player.Character, 0, 16);
                    }
                }
            }
        }
    }
}
