using System;
using GTA;
using GTA.Math;
using GTA.Native;

namespace DeadWastelandXbox
{
    public class ProfessionLogic : Script
    {
        private int lastAmmoCraftTime = 0;

        public ProfessionLogic()
        {
            Tick += OnTick;
        }

        private void OnTick(object sender, EventArgs e)
        {
            int hours = World.CurrentDayTime.Hours;
            Ped player = Game.Player.Character;

            // Busca Aliados próximos no mapa
            Ped[] nearbyPeds = World.GetNearbyPeds(player.Position, 100.0f);

            foreach (Ped ally in nearbyPeds)
            {
                // Verifica se é um Aliado (🔵)
                if (ally != player && !ally.IsDead && ally.CurrentBlip != null && ally.CurrentBlip.Color == BlipColor.Blue)
                {
                    // 1. ROTINA DO PATRULHEIRO
                    // Entre 14:00 e 16:00 patrulha o mapa; às 16:00 volta correndo para a base
                    if (hours >= 14 && hours < 16)
                    {
                        if (!ally.IsInCombat)
                        {
                            ally.Task.WanderAround(ally.Position, 80.0f);
                        }
                    }
                    else if (hours == 16)
                    {
                        // Às 16:00h retoma corrida rápida de volta para a posição do jogador/base
                        ally.Task.RunTo(player.Position);
                    }

                    // 2. ROTINA DO FAZENDEIRO
                    // Mantém carroças e cura a resistência do cavalo próximo
                    Prop[] props = World.GetNearbyProps(ally.Position, 10.0f);
                    foreach (Prop p in props)
                    {
                        if (p.Model.Hash == Game.GenerateHash("prop_wagon_01"))
                        {
                            p.Health = 1000; // Mantém a integridade da Carroça
                        }
                    }

                    // 3. ROTINA DO ARMEIRO
                    // Fabrica munição periodicamente
                    if (Game.GameTime - lastAmmoCraftTime > 30000) // A cada 30 segundos
                    {
                        player.Weapons.Current.Ammo += 10;
                        UI.Notify("~g~[Armeiro] +10 Munições fabricadas na base! 🛠️");
                        lastAmmoCraftTime = Game.GameTime;
                    }
                }
            }
        }
    }
}
