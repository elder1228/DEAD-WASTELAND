using System;
using System.Collections.Generic;
using GTA;
using GTA.Math;

namespace DeadWastelandXbox
{
    public class ConstructionSystem : Script
    {
        private bool isBuilding = false;
        private Prop currentPreviewProp = null;
        private float currentHeading = 0.0f;

        // Lista de Hashes dos Objetos Estilo "Gamersamuka"
        private string[] availableProps = new string[]
        {
            "prop_barier_conc_01a", // Barreira de Concreto
            "prop_sandbag_01",      // Sacos de Areia
            "prop_skid_tent_01",    // Barraca
            "prop_beach_fire"       // Fogueira
        };

        public ConstructionSystem()
        {
            Tick += OnTick;
        }

        private void OnTick(object sender, EventArgs e)
        {
            // Atalho Teclado: F10  |  Controle: Menu Dedicado
            if (Game.IsKeyPressed(System.Windows.Forms.Keys.F10))
            {
                isBuilding = !isBuilding;

                if (isBuilding)
                {
                    UI.Notify("~g~[F10] Modo Construção ATIVADO!");
                    SpawnPreview("prop_barier_conc_01a");
                }
                else
                {
                    CancelBuilding();
                    UI.Notify("~r~[F10] Modo Construção DESATIVADO.");
                }
                Script.Wait(500);
            }

            if (isBuilding && currentPreviewProp != null)
            {
                Ped player = Game.Player.Character;
                
                // Posiciona o objeto 3 metros à frente do jogador
                Vector3 targetPos = player.Position + player.ForwardVector * 3.0f;
                currentPreviewProp.Position = targetPos;
                currentPreviewProp.Heading = currentHeading;

                // Gira o objeto com Q / E
                if (Game.IsKeyPressed(System.Windows.Forms.Keys.Q)) currentHeading -= 3.0f;
                if (Game.IsKeyPressed(System.Windows.Forms.Keys.E)) currentHeading += 3.0f;

                // Tecla ENTER confirma a construção no mapa
                if (Game.IsKeyPressed(System.Windows.Forms.Keys.Enter))
                {
                    // Deixa a estrutura fixa com colisão física
                    currentPreviewProp.IsPersistent = true;
                    currentPreviewProp = null; // Libera para a próxima
                    UI.Notify("~g~Estrutura posicionada com sucesso!");
                    isBuilding = false;
                    Script.Wait(500);
                }
            }
        }

        private void SpawnPreview(string modelName)
        {
            Ped player = Game.Player.Character;
            Model model = new Model(modelName);
            model.Request(250);

            if (model.IsInCdImage && model.IsValid)
            {
                currentPreviewProp = World.CreateProp(model, player.Position + player.ForwardVector * 3.0f, false, false);
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
