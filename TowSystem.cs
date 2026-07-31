using System;
using GTA;
using GTA.Math;

namespace DeadWastelandXbox
{
    public class TowSystem : Script
    {
        private Entity attachedTrailer = null;

        public TowSystem()
        {
            Tick += OnTick;
        }

        private void OnTick(object sender, EventArgs e)
        {
            // Atalho Teclado USB: J  OR  Controle: Tecla de Ação
            bool isJKey = Game.IsKeyPressed(System.Windows.Forms.Keys.J);

            if (isJKey)
            {
                Ped player = Game.Player.Character;
                if (player.IsInVehicle())
                {
                    Vehicle veh = player.CurrentVehicle;

                    if (attachedTrailer == null)
                    {
                        // Procura reboque ou carroça próxima atrás do veículo
                        Prop[] props = World.GetNearbyProps(veh.Position, 6.0f);
                        foreach (Prop p in props)
                        {
                            if (p.Model.Hash == Game.GenerateHash("prop_wagon_01") || p.Model.Hash == Game.GenerateHash("trailersmall"))
                            {
                                attachedTrailer = p;
                                p.AttachTo(veh, 0, new Vector3(0.0f, -2.5f, 0.0f), Vector3.Zero);
                                UI.Notify("~g~Reboque/Carroça engatada com sucesso!");
                                break;
                            }
                        }
                    }
                    else
                    {
                        attachedTrailer.Detach();
                        attachedTrailer = null;
                        UI.Notify("~y~Reboque/Carroça desengatada.");
                    }
                    Script.Wait(1000);
                }
            }
        }
    }
}
