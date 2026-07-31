using System;
using GTA;
using GTA.Math;
using GTA.Native;

namespace DeadWastelandXbox
{
    public class PersistenceSystem : Script
    {
        public PersistenceSystem()
        {
            Tick += OnTick;
        }

        private void OnTick(object sender, EventArgs e)
        {
            Ped player = Game.Player.Character;

            // Atalho Teclado USB: SHIFT + P  OR  Controle Xbox: LB + D-PAD DIREITA
            bool isShiftP = Game.IsKeyPressed(System.Windows.Forms.Keys.ShiftKey) && Game.IsKeyPressed(System.Windows.Forms.Keys.P);
            bool isPadCombo = Game.IsControlPressed(0, Control.SelectWeapon) && Game.IsControlPressed(0, Control.PhoneRight);

            if (isShiftP || isPadCombo)
            {
                if (player.IsInVehicle())
                {
                    Vehicle veh = player.CurrentVehicle;
                    
                    // Bloqueia a exclusão de memória do Xbox 360
                    veh.IsPersistent = true;
                    
                    // Cria a Bolinha Roxa 🟣
                    Blip b = veh.AddBlip();
                    b.Color = BlipColor.Purple;
                    b.Sprite = BlipSprite.PersonalVehicleCar;
                    b.Name = "Frota Dead Wasteland";

                    UI.Notify("~p~[Dead Wasteland] Veículo salvo na Bolinha Roxa 🟣!");
                    Script.Wait(1000); // Debounce para evitar múltiplos cliques
                }
            }
        }
    }
}
