/* Skip Death Knight Module
   Original Module From Single Player Project Consolidated Skip Module
   Rewritten for TC 335 By Single Player Project Developer MDic
   Original Concept from conanhun513
   Assistance and Review by JinnaiX
   Modified for Azerothcore
   
   Edited by The Legendary Kingdom for Legacy of Azeroth
*/

#include "AccountMgr.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "Config.h"
#include "Common.h"
#include "Chat.h"
#include "ObjectAccessor.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "SharedDefines.h"
#include "World.h"
#include "WorldSession.h"

class AzerothCore_skip_deathknight_login : public PlayerScript
{
public:
    AzerothCore_skip_deathknight_login() : PlayerScript("AzerothCore_skip_deathknight_login") { }

    void OnLogin(Player* player)
    {
        if (sConfigMgr->GetBoolDefault("Skip.Deathknight.Starter.Announce.Enable", true))
        {
            ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00Azerothcore Skip Deathknight Starter |rmodule.");
        }		
		/*if (player->getClass() == CLASS_DEATH_KNIGHT)
		{
		    if (player->GetQuestStatus(30002) == QUEST_STATUS_REWARDED && player->GetQuestStatus(30003) == QUEST_STATUS_NONE)
            {
				if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->TeleportTo(0, -8426.31f, 329.32f, 120.89f, 6.15f);//Stormwind
                else
                    player->TeleportTo(1, 1907.91f, -4143.45f, 40.64f, 2.99f);//Orgrimmar
                player->AddQuest(sObjectMgr->GetQuestTemplate(30003), nullptr);//DK INTRO ZONE LEFT
                player->RewardQuest(sObjectMgr->GetQuestTemplate(30003), false, player);
                
                ObjectAccessor::SaveAllPlayers();//Save
		    }	
        }*/
	}
};

class Azerothcore_optional_deathknight_skip : public CreatureScript
{
public:
    Azerothcore_optional_deathknight_skip() : CreatureScript("npc_ac_skip_lich") { }

        bool OnGossipHello(Player* player, Creature* creature) override
        {
            if (creature->IsQuestGiver())
            {
                player->PrepareQuestMenu(creature->GetGUID());
            }

            if (sConfigMgr->GetBoolDefault("Skip.Deathknight.Optional.Enable", true))
            {
                AddGossipItemFor(player, GOSSIP_ICON_TALK, "Je souhaite sauter la série de quêtes de démarrage du Chevalier de la mort.", GOSSIP_SENDER_MAIN, 11);
            }
            player->TalkedToCreature(creature->GetEntry(), creature->GetGUID());
            SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*menuId*/, uint32 gossipListId) override
        {
            int DKL = sConfigMgr->GetFloatDefault("Skip.Deathknight.Start.Level", 58);
            CloseGossipMenuFor(player);
            ClearGossipMenuFor(player);
            switch (gossipListId)
            {
            case 11:
                
				if (player->getClass() == CLASS_DEATH_KNIGHT)
				{
					if (player->GetQuestStatus(30009) == QUEST_STATUS_NONE)//Engagement dans l'introduction du Chevalier de la mort
					{	
						if (sConfigMgr->GetBoolDefault("Skip.Deathknight.Logout.Enable", true))
						{
							AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Passer l'introduction du Chevalier de la mort\n•votre personnage sera déconnecté pour finaliser l'opération\n•ce choix est irrévocable", GOSSIP_SENDER_MAIN, 12);
						}
						else
						{
							AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Passer l'introduction du Chevalier de la mort\n•ce choix est irrévocable", GOSSIP_SENDER_MAIN, 12);
						}
						AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "Annuler", GOSSIP_SENDER_MAIN, 13);
					}
					else
					{	
				        if (player->GetQuestStatus(30002) == QUEST_STATUS_NONE)
						{
						    AddGossipItemFor(player, GOSSIP_ICON_TALK, "J'ai décidé de jouer l'introduction du Chevalier de la mort.", GOSSIP_SENDER_MAIN, 13);
						    //Message "Vous êtes engagé dans l'introduction du Chevalier de la mort et ne pouvez plus la passer."
						    std::ostringstream ss;
						    ss << "|cffFF8000Liche passeuse :|cFFBDB76B Vous avez décidé de jouer l'introduction du Chevalier de la mort et ne pouvez plus la passer.";
						    ChatHandler(player->GetSession()).SendSysMessage(ss.str().c_str());
						}
						else
						{
							AddGossipItemFor(player, GOSSIP_ICON_TALK, "J'ai déja passé l'introduction du Chevalier de la mort.", GOSSIP_SENDER_MAIN, 13);
						    //Message "Vous avez déja passé l'introduction du Chevalier de la mort et ne pouvez plus la passer."
						    std::ostringstream ss;
						    ss << "|cffFF8000Liche passeuse :|cFFBDB76B Vous avez déja passé l'introduction du Chevalier de la mort.";
						    ChatHandler(player->GetSession()).SendSysMessage(ss.str().c_str());
						}
					}						
											
				}
				else
				{
					AddGossipItemFor(player, GOSSIP_ICON_TALK, "Je ne suis pas un Chevalier de la mort.", GOSSIP_SENDER_MAIN, 13);
					//Message "Vous n'êtes pas un Chevalier de la mort."
					std::ostringstream ss;
					ss << "|cffFF8000Liche passeuse :|cFFBDB76B Vous n'êtes pas un Chevalier de la mort.";
					ChatHandler(player->GetSession()).SendSysMessage(ss.str().c_str());
				}					
                SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());
                break;

            case 12:
			/*********TODO :
			-compléter TOUTES les queêtes de la zone de départ DK pour recevoir les points de talents
				-vérifier si les sorts sont également appris de cette façon, peut-être que l'xp est obtenue -> ajuster le player->SetLevel() en conséquence
			-gérer les menus de la liche pour téléporter le joueur si il a passé la zone (éviter d'avoir une première option "Je souhaite passer" et ensuite "J'ai déja passé" ou "Je ne seuis pas DK" : gérer la première option pour ça)
				-script en deux étapes : le joueur souhaite passer la zone alors on valide les quetes, niveaux, récompenses, sorts, etc... PUIS on le téléporte dans un second temps
					cela devrait éviter que l'écran de chargement du changement de zone empêche l'interface de récupérer correctement les informations de ce que le script ajoute au personnage
			
			*/
                if (player->getLevel() <= DKL)
                {
                    player->SetLevel(DKL);
                }
                player->learnSpell(53428, false);//runeforging
                player->learnSpell(53441, false);//runeforging
                player->learnSpell(53344, false);//runeforging
                player->learnSpell(62158, false);//runeforging
                player->learnSpell(33391, false);//journeyman riding
                player->learnSpell(54586, false);//runeforging credit
                player->learnSpell(48778, false);//acherus deathcharger
                player->learnSkillRewardedSpells(776, 375);//Runeforging
                player->learnSkillRewardedSpells(960, 375);//Runeforging			
                player->AddItem(6948, true);//Hearthstone
                player->AddItem(60074, true);//Paquetage de Chevalier de la mort d'Achérus
				if (player->GetQuestStatus(30001) == QUEST_STATUS_NONE)//La liche passeuse
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(30001), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(30001), false, player);
                }
				if (player->GetQuestStatus(30002) == QUEST_STATUS_NONE)//DK INTRO SKIPPED
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(30002), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(30002), false, player);
                }
				if (player->GetQuestStatus(30009) == QUEST_STATUS_NONE)//Jouer l'introduction du Chevalier de la mort
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(30009), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(30009), false, player);
                }
                if (player->GetQuestStatus(12657) == QUEST_STATUS_NONE)//The Might Of The Scourge
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(12657), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(12657), false, player);
                }
                if (player->GetQuestStatus(12801) == QUEST_STATUS_NONE)//The Light of Dawn
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(12801), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(12801), false, player);
                }
                /*if (player->GetTeamId() == TEAM_ALLIANCE && player->GetQuestStatus(13188) == QUEST_STATUS_NONE)//Where Kings Walk
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(13188), false, player);
                }
                else if (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(13189) == QUEST_STATUS_NONE)//Saurfang's Blessing
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);  
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(13189), false, player);
                }*/
                CloseGossipMenuFor(player);				
                ObjectAccessor::SaveAllPlayers();//Save
				//player->GetSession()->LogoutPlayer(true);//Logout forces ui to be fully (re)loaded at logback. COMMENT TO TEST IF NO TELEPORT ALLOWS UI TO CORRECTLY LOAD ITEMS
                break;

            case 13://close
                CloseGossipMenuFor(player);								
                break;

            default:

                break;
            }
            return true;
        }
};

void AddSkipDKScripts()
{
    new AzerothCore_skip_deathknight_login;
    new Azerothcore_optional_deathknight_skip;
}
