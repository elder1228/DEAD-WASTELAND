using System;
using GTA;
using GTA.Math;

namespace DeadWastelandXbox
{
    public class AirdropSystem : Script
    {
        private Blip airdropBlip = null;
        private Prop airdropCrate = null;

        public AirdropSystem()
        {
            Tick += OnTick;
        }

        private void OnTick(object sender, EventArgs e)
        {
            // Tecla 9 ou Comando via Rádio para chamar Airdrop de Emergência
            if (Game.IsKeyPressed(System.Windows.Forms.Keys.D9))
            {
                CallAirdrop();
                Script.Wait(2000);
            }

            // Checar se o jogador chegou perto da caixa de Airdrop
            if (airdropCrate != null && airdropCrate.Exists())
            {
                Ped player = Game.Player.Character;
                if (player.Position.DistanceTo(airdropCrate.Position) < 2.5f)
                {
                    UI.Notify("~g~[AIRDROP] Suprimentos Coletados: +50 Munições, +2 Antídotos Virox e Peças!");
                    if (airdropBlip != null) airdropBlip.Remove();
                    airdropCrate.Delete();
                    airdropCrate = null;
                }
            }
        }

        private void CallAirdrop()
        {
            Ped player = Game.Player.Character;
            Vector3 dropPosition = player.Position + player.ForwardVector * 25.0f;

            // Cria a caixa de suprimentos no solo
            Model crateModel = new Model("prop_boxwood01a");
            crateModel.Request(250);

            if (crateModel.IsValid)
            {
                airdropCrate = World.CreateProp(crateModel, dropPosition, true, false);
                
                // Marca no mapa com ícone de caixa/suprimento
                airdropBlip = airdropCrate.AddBlip();
                airdropBlip.Sprite = BlipSprite.Crate;
                airdropBlip.Color = BlipColor.Green;
                airdropBlip.Name = "Caixa de Suprimentos Virox 📦";

                UI.Notify("~b~[GOVERNO] Caixa de emergência lançada! Verifique o ícone verde no GPS.");
            }
        }
    }
}
