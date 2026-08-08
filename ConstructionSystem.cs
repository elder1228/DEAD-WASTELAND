using System;
using GTA;
using GTA.Math;

namespace DeadWastelandXbox
{
    public class ConstructionSystem : Script
    {
        private bool isBuilding = false;
        private Prop currentPreviewProp = null;
        private float currentHeading = 0.0f;
        private int selectedIndex = 0;

        // Hashes oficiais de construção do Simple Zombies
        private string[] buildables = new string[]
        {
            "prop_barier_conc_01a", // Barreira Concreto
            "prop_sandbag_01",      // Bloco de Areia (Sandbag)
            "prop_skid_tent_01",    // Barraca de Acampamento
            "prop_beach_fire",      // Fogueira (Camp Fire)
            "prop_fncsec_01a",      // Cerca/Grade de Proteção
            "prop_gate_airport_01"  // Portão de Metal para a Base
        };

        public ConstructionSystem()
        {
            Tick += OnTick;
        }

        private void OnTick(object sender, EventArgs e)
        {
            // F10 no Teclado ou LB + RB no Controle para Abrir Menu de Construção
            bool toggleKey = Game.IsKeyPressed(System.Windows.Forms.Keys.F10) || 
                            (Game.IsControlPressed(0, Control.SelectWeapon) && Game.IsControlPressed(0, Control.CharacterWheel));

            if (toggleKey)
            {
                isBuilding = !isBuilding;

                if (isBuilding)
                {
                    UI.Notify("~g~[CONSTRUÇÃO] Modo de Base Ativado!");
                    SpawnPreview(buildables[selectedIndex]);
                }
                else
                {
                    CancelBuilding();
                    UI.Notify("~r~[CONSTRUÇÃO] Modo de Base Fechado.");
                }
                Script.Wait(500);
            }

            if (isBuilding && currentPreviewProp != null)
            {
                Ped player = Game.Player.Character;
                Vector3 targetPos = player.Position + player.ForwardVector * 3.5f;
                
                currentPreviewProp.Position = targetPos;
                currentPreviewProp.Heading = currentHeading;

                // Rotação: Q / E no Teclado
                if (Game.IsKeyPressed(System.Windows.Forms.Keys.Q)) currentHeading -= 4.0f;
                if (Game.IsKeyPressed(System.Windows.Forms.Keys.E)) currentHeading += 4.0f;

                // Trocar Estrutura: Setas Esquerda / Direita
                if (Game.IsKeyPressed(System.Windows.Forms.Keys.Left))
                {
                    selectedIndex = (selectedIndex - 1 + buildables.Length) % buildables.Length;
                    SwitchProp();
                    Script.Wait(200);
                }
                if (Game.IsKeyPressed(System.Windows.Forms.Keys.Right))
                {
                    selectedIndex = (selectedIndex + 1) % buildables.Length;
                    SwitchProp();
                    Script.Wait(200);
                }

                // ENTER ou Botão X confirma a posição
                if (Game.IsKeyPressed(System.Windows.Forms.Keys.Enter))
                {
                    currentPreviewProp.IsPersistent = true;
                    currentPreviewProp = null;
                    UI.Notify("~g~[ESTRUTURA] Fixada com sucesso na Base!");
                    isBuilding = false;
                    Script.Wait(500);
                }
            }
        }

        private void SwitchProp()
        {
            if (currentPreviewProp != null) currentPreviewProp.Delete();
            SpawnPreview(buildables[selectedIndex]);
        }

        private void SpawnPreview(string modelName)
        {
            Ped player = Game.Player.Character;
            Model model = new Model(modelName);
            model.Request(250);

            if (model.IsInCdImage && model.IsValid)
            {
                currentPreviewProp = World.CreateProp(model, player.Position + player.ForwardVector * 3.5f, false, false);
            }
        }

        private void CancelBuilding()
        {
            if (currentPreviewProp != null)
            {
                currentPreviewProp.Delete();
                currentPreviewProp = null;
            }
        }
    }
}
