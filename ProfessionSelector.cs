using System;
using System.IO;
using System.Xml.Linq;
using GTA;
using GTA.Math;
using GTA.Native;

namespace DeadWastelandXbox
{
    public class ProfessionSelector : Script
    {
        private Ped currentTargetAlly = null;
        private bool isMenuOpen = false;
        private readonly string dbPath = @"game:\DeadWasteland_Mod\Config\Database.xml";

        // Lista das 10 Profissões
        private readonly string[] professions = new string[]
        {
            "Mecânico", "Engenheiro", "Sentinela", "Sucateiro", "Armeiro",
            "Agricultor", "Fazendeiro", "Patrulheiro", "Médico", "Cozinheiro"
        };

        public ProfessionSelector()
        {
            Tick += OnTick;
        }

        private void OnTick(object sender, EventArgs e)
        {
            Ped player = Game.Player.Character;

            // Busca por Aliados (🔵) num raio de 3 metros
            if (!isMenuOpen)
            {
                Ped[] nearbyPeds = World.GetNearbyPeds(player.Position, 3.0f);
                currentTargetAlly = null;

                foreach (Ped ped in nearbyPeds)
                {
                    // Checa se não é o player e se possui o Blip Azul de Aliado
                    if (ped != player && !ped.IsDead && ped.CurrentBlip != null && ped.CurrentBlip.Color == BlipColor.Blue)
                    {
                        currentTargetAlly = ped;
                        break;
                    }
                }

                if (currentTargetAlly != null)
                {
                    UI.ShowSubtitle("Pressione ~g~E ~w~[Teclado] ou ~g~D-Pad Direita ~w~[Controle] para designar Profissão.");

                    // Teclado: E | Controle: D-Pad Direita
                    bool interactKey = Game.IsKeyPressed(System.Windows.Forms.Keys.E) || Game.IsControlPressed(0, Control.PhoneRight);

                    if (interactKey)
                    {
                        isMenuOpen = true;
                        Script.Wait(500);
                    }
                }
            }
            else
            {
                // Exibe o painel de seleção no topo da tela
                UI.Notify("~b~=== DEFINIR PROFISSÃO DO ALIADO ===\n~w~Use as teclas de 1 a 0 no Teclado USB para atribuir:");
                UI.Notify("1.Mecânico | 2.Engenheiro | 3.Sentinela\n4.Sucateiro | 5.Armeiro | 6.Agricultor\n7.Fazendeiro | 8.Patrulheiro | 9.Médico | 0.Cozinheiro");

                CheckProfessionInput();
            }
        }

        private void CheckProfessionInput()
        {
            int selectedIndex = -1;

            // Leitura simples das teclas numéricas do Teclado USB
            if (Game.IsKeyPressed(System.Windows.Forms.Keys.D1)) selectedIndex = 0;
            else if (Game.IsKeyPressed(System.Windows.Forms.Keys.D2)) selectedIndex = 1;
            else if (Game.IsKeyPressed(System.Windows.Forms.Keys.D3)) selectedIndex = 2;
            else if (Game.IsKeyPressed(System.Windows.Forms.Keys.D4)) selectedIndex = 3;
            else if (Game.IsKeyPressed(System.Windows.Forms.Keys.D5)) selectedIndex = 4;
            else if (Game.IsKeyPressed(System.Windows.Forms.Keys.D6)) selectedIndex = 5;
            else if (Game.IsKeyPressed(System.Windows.Forms.Keys.D7)) selectedIndex = 6;
            else if (Game.IsKeyPressed(System.Windows.Forms.Keys.D8)) selectedIndex = 7;
            else if (Game.IsKeyPressed(System.Windows.Forms.Keys.D9)) selectedIndex = 8;
            else if (Game.IsKeyPressed(System.Windows.Forms.Keys.D0)) selectedIndex = 9;

            if (selectedIndex != -1)
            {
                string chosenJob = professions[selectedIndex];
                AssignProfession(currentTargetAlly, chosenJob);
                
                UI.Notify("~g~[Sucesso] Aliado designado como: " + chosenJob + "! 🔵");
                isMenuOpen = false;
                Script.Wait(1000);
            }
        }

        private void AssignProfession(Ped ally, string job)
        {
            // Salva a tag no XML do pendrive
            try
            {
                if (File.Exists(dbPath))
                {
                    XDocument doc = XDocument.Load(dbPath);
                    XElement root = doc.Root;

                    XElement allyData = new XElement("AllyNPC",
                        new XAttribute("Handle", ally.Handle.ToString()),
                        new XElement("Profession", job)
                    );

                    root.Add(allyData);
                    doc.Save(dbPath);
                }
            }
            catch { }

            // Configura o comportamento dinâmico baseado na profissão
            switch (job)
            {
                case "Sentinela":
                    ally.Task.GuardCurrentPosition();
                    ally.Accuracy = 90; // Aumenta mira
                    break;
                case "Patrulheiro":
                    ally.Task.WanderAround(ally.Position, 50.0f);
                    break;
                case "Médico":
                    ally.Health = 200;
                    break;
                default:
                    ally.Task.StandStill(-1); // Fica aguardando tarefas de base
                    break;
            }
        }
    }
}
