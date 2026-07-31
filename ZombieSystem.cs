using System;
using GTA;
using GTA.Native;

namespace DeadWastelandXbox
{
    public class ZombieSystem : Script
    {
        private bool isRage = false;

        public ZombieSystem()
        {
            Tick += OnTick;
        }

        private void OnTick(object sender, EventArgs e)
        {
            int hours = World.CurrentDayTime.Hours;

            if (hours >= 16 || hours < 6)
            {
                if (!isRage)
                {
                    isRage = true;
                    UI.Notify("~r~[ALERTA] 16:00H! Os zumbis começaram a correr!");
                }

                // Varredura leve em raio de 80m para poupar a RAM do Xbox 360
                Ped[] peds = World.GetNearbyPeds(Game.Player.Character.Position, 80.0f);
                foreach (Ped p in peds)
                {
                    if (p != Game.Player.Character && !p.IsDead && p.CurrentBlip?.Color != BlipColor.Blue)
                    {
                        Function.Call(Hash.SET_PED_MOVE_RATE_OVERRIDE, p, 1.4f);
                        Function.Call(Hash.TASK_COMBAT_PED, p, Game.Player.Character, 0, 16);
                    }
                }
            }
            else
            {
                if (isRage)
                {
                    isRage = false;
                    UI.Notify("~g~[DIA] 06:00H. Zumbis acalmados.");
                }
            }
        }
    }
}
