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
				if (player->getClass() == CLASS_DEATH_KNIGHT)
				{
					if (player->GetQuestStatus(30009) != QUEST_STATUS_REWARDED && player->GetQuestStatus(30002) == QUEST_STATUS_NONE)//Jouer l'introduction du Chevalier de la mort //Passer l'introduction du Chevalier de la mort
					{
						AddGossipItemFor(player, GOSSIP_ICON_TALK, "Je souhaite sauter la série de quêtes de démarrage du Chevalier de la mort.", GOSSIP_SENDER_MAIN, 11);
					}
					else if (player->GetQuestStatus(30002) != QUEST_STATUS_NONE && player->GetQuestStatus(30003) == QUEST_STATUS_REWARDED)//Passer l'introduction du Chevalier de la mort //Quitter les lieux
					{
						std::ostringstream ss;
						ss << "|cffFF8000Liche passeuse :|cFFBDB76B Vous avez passé l'introduction du Chevalier de la mort.";
						ChatHandler(player->GetSession()).SendSysMessage(ss.str().c_str());							
					}
					else if (player->GetQuestStatus(30009) == QUEST_STATUS_REWARDED && player->GetQuestStatus(30003) == QUEST_STATUS_NONE)
					{
						std::ostringstream ss;
						ss << "|cffFF8000Liche passeuse :|cFFBDB76B Vous avez décidé de jouer l'introduction du Chevalier de la mort et ne pouvez plus la passer.";
						ChatHandler(player->GetSession()).SendSysMessage(ss.str().c_str());
					}                    					
				}
				else
				{
					std::ostringstream ss;
					ss << "|cffFF8000Liche passeuse :|cFFBDB76B Je ne propose mes services qu'aux Chevaliers de la mort.";
					ChatHandler(player->GetSession()).SendSysMessage(ss.str().c_str());
				}
            }
            player->TalkedToCreature(creature->GetEntry(), creature->GetGUID());
            SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());
            return true;
        }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*menuId*/, uint32 gossipListId) override
        {
            CloseGossipMenuFor(player);
            ClearGossipMenuFor(player);
            switch (gossipListId)
            {
            case 11:
                
				AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Passer l'introduction du Chevalier de la mort\n•ce choix est irrévocable", GOSSIP_SENDER_MAIN, 12);
				AddGossipItemFor(player, GOSSIP_ICON_INTERACT_2, "Annuler", GOSSIP_SENDER_MAIN, 13);											
                SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());
                break;

            case 12:
			/*
			TODO :
			-compléter TOUTES les quêtes de la zone de départ DK pour recevoir les points de talents
				-vérifier si les sorts sont également appris de cette façon, peut-être que l'xp est obtenue
				    -ajuster le player->SetLevel() en conséquence
					-attribuer les objets rémanents
					-apprendre les sorts qui ne le sont pas (automatiquement) en récompense de quête
			-gérer les menus de la liche pour éviter d'avoir une première option "Je souhaite passer" et ensuite "J'ai déja passé" ou "Je ne seuis pas DK" (la première option doit gérer ça ? ou pas de menu si non nécessaire)			
			*/
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
                }
				if (player->GetQuestStatus(30001) != QUEST_STATUS_REWARDED)
                {
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(30001), false, player);
                }
				if (player->GetQuestStatus(30002) == QUEST_STATUS_NONE)//DK INTRO SKIPPED
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(30002), nullptr);
                }
				if (player->GetQuestStatus(30002) != QUEST_STATUS_REWARDED)
                {
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(30002), false, player);
                }
				if (player->GetQuestStatus(30009) == QUEST_STATUS_NONE)//Jouer l'introduction du Chevalier de la mort
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(30009), nullptr);
                }
				if (player->GetQuestStatus(30009) != QUEST_STATUS_REWARDED)
                {
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
                if (player->GetTeamId() == TEAM_ALLIANCE && player->GetQuestStatus(13188) == QUEST_STATUS_NONE)//Where Kings Walk
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(13188), false, player);
                }
                else if (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(13189) == QUEST_STATUS_NONE)//Saurfang's Blessing
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);  
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(13189), false, player);
                }
                if (player->getLevel() < 58)
                {
					player->GiveLevel(58);
                  //player->SetLevel(58);
                }
				if (player->GetQuestStatus(30003) == QUEST_STATUS_NONE)//Quitter les lieux
                {
                    player->AddQuest(sObjectMgr->GetQuestTemplate(30003), nullptr);
					player->CompleteQuest(30003);
                }				
                CloseGossipMenuFor(player);
				ClearGossipMenuFor(player);				
                ObjectAccessor::SaveAllPlayers();//Save
                break;

            case 13://cancel, go back (previous menu)	
			
				ClearGossipMenuFor(player);
				if (creature->IsQuestGiver())
				{
					player->PrepareQuestMenu(creature->GetGUID());
				}
                AddGossipItemFor(player, GOSSIP_ICON_TALK, "Je souhaite sauter la série de quêtes de démarrage du Chevalier de la mort.", GOSSIP_SENDER_MAIN, 11);											
                SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());								
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
