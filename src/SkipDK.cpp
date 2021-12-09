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

class Azerothcore_optional_deathknight_skip : public CreatureScript
{
public:
    Azerothcore_optional_deathknight_skip() : CreatureScript("npc_ac_skip_lich") { }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (!sConfigMgr->GetBoolDefault("Skip.Deathknight.Optional.Enable", true))
            return false;
        
        if (creature->IsQuestGiver())
        {
            player->PrepareQuestMenu(creature->GetGUID());
        }

        if (sConfigMgr->GetBoolDefault("Skip.Deathknight.Optional.Enable", true))
        {
            if (player->getClass() == CLASS_DEATH_KNIGHT)
            {
                if (player->GetQuestStatus(30009) != QUEST_STATUS_REWARDED && player->GetQuestStatus(30002) != QUEST_STATUS_REWARDED)//Jouer l'introduction du Chevalier de la mort //Passer l'introduction du Chevalier de la mort
                    AddGossipItemFor(player, GOSSIP_ICON_TALK, "Je souhaite sauter la série de quêtes de démarrage du Chevalier de la mort.", GOSSIP_SENDER_MAIN, 11);
                else if (player->GetQuestStatus(30002) != QUEST_STATUS_NONE && player->GetQuestStatus(30003) == QUEST_STATUS_REWARDED)//Passer l'introduction du Chevalier de la mort //Quitter les lieux
                    creature->Whisper("Vous avez passé l'introduction du Chevalier de la mort.", LANG_UNIVERSAL, player);
                else if (player->GetQuestStatus(30009) == QUEST_STATUS_REWARDED && player->GetQuestStatus(30003) == QUEST_STATUS_NONE)
                    creature->Whisper("Vous avez décidé de jouer l'introduction du Chevalier de la mort et ne pouvez plus la passer.", LANG_UNIVERSAL, player);
            }
            else
            {
                    creature->Whisper("Je ne propose mes services qu'aux Chevaliers de la mort.", LANG_UNIVERSAL, player);
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
            
            if (player->GetQuestStatus(30001) == QUEST_STATUS_NONE)//La liche passeuse
                player->AddQuest(sObjectMgr->GetQuestTemplate(30001), nullptr);
                
            if (player->GetQuestStatus(30001) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(30001), false, player);
            
            if (player->GetQuestStatus(30002) == QUEST_STATUS_NONE)//DK INTRO SKIPPED
                player->AddQuest(sObjectMgr->GetQuestTemplate(30002), nullptr);
                
            if (player->GetQuestStatus(30002) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(30002), false, player);
            
            if (player->GetQuestStatus(30009) == QUEST_STATUS_NONE)//Jouer l'introduction du Chevalier de la mort
                player->AddQuest(sObjectMgr->GetQuestTemplate(30009), nullptr);
                
            if (player->GetQuestStatus(30009) != QUEST_STATUS_REWARDED)                    
                player->RewardQuest(sObjectMgr->GetQuestTemplate(30009), false, player);
            
            if (player->GetQuestStatus(12593) == QUEST_STATUS_NONE)//Au service du roi-liche
                player->AddQuest(sObjectMgr->GetQuestTemplate(12593), nullptr);
                
            if (player->GetQuestStatus(12593) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12593), false, player);
            
            if (player->GetQuestStatus(12619) == QUEST_STATUS_NONE)//La lame runique blasonnée
                player->AddQuest(sObjectMgr->GetQuestTemplate(12619), nullptr);
                
            if (player->GetQuestStatus(12619) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12619), false, player);
            
            if (player->GetQuestStatus(12842) == QUEST_STATUS_NONE)//La forgerune : se préparer à la bataille
                player->AddQuest(sObjectMgr->GetQuestTemplate(12842), nullptr);
                
            if (player->GetQuestStatus(12842) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12842), false, player);
            
            if (player->GetQuestStatus(12848) == QUEST_STATUS_NONE)//La faim sans fin
                player->AddQuest(sObjectMgr->GetQuestTemplate(12848), nullptr);
                
            if (player->GetQuestStatus(12848) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12848), false, player);
            
            if (player->GetQuestStatus(12636) == QUEST_STATUS_NONE)//L'oeil d'Achérus
                player->AddQuest(sObjectMgr->GetQuestTemplate(12636), nullptr);
                
            if (player->GetQuestStatus(12636) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12636), false, player);
            
            if (player->GetQuestStatus(12636) == QUEST_STATUS_NONE)//La mort vient de l'oeil
                player->AddQuest(sObjectMgr->GetQuestTemplate(12636), nullptr);
                
            if (player->GetQuestStatus(12636) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12636), false, player);
            
            if (player->GetQuestStatus(12657) == QUEST_STATUS_NONE)//La puissance du fléau
                player->AddQuest(sObjectMgr->GetQuestTemplate(12657), nullptr);
                
            if (player->GetQuestStatus(12657) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12657), false, player);
            
            if (player->GetQuestStatus(12850) == QUEST_STATUS_NONE)//Rapport au commandant du fléau Thalanor
                player->AddQuest(sObjectMgr->GetQuestTemplate(12850), nullptr);
                
            if (player->GetQuestStatus(12850) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12850), false, player);
            
            if (player->GetQuestStatus(12670) == QUEST_STATUS_NONE)//La moisson écarlate
                player->AddQuest(sObjectMgr->GetQuestTemplate(12670), nullptr);
                
            if (player->GetQuestStatus(12670) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12670), false, player);                
            
            if (player->GetQuestStatus(12678) == QUEST_STATUS_NONE)//Si le chaos règne, laissons la souffrance tenir les rênes
                player->AddQuest(sObjectMgr->GetQuestTemplate(12678), nullptr);
                
            if (player->GetQuestStatus(12678) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12678), false, player);                
            
            if (player->GetQuestStatus(12679) == QUEST_STATUS_NONE)//Ce soir nous dînons à Havre-comté
                player->AddQuest(sObjectMgr->GetQuestTemplate(12679), nullptr);
                
            if (player->GetQuestStatus(12679) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12679), false, player);
            
            if (player->GetQuestStatus(12733) == QUEST_STATUS_NONE)//Le défi de la mort
                player->AddQuest(sObjectMgr->GetQuestTemplate(12733), nullptr);
                
            if (player->GetQuestStatus(12733) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12733), false, player);
            
            if (player->GetQuestStatus(12680) == QUEST_STATUS_NONE)//Voleurs de chevaux
                player->AddQuest(sObjectMgr->GetQuestTemplate(12680), nullptr);
                
            if (player->GetQuestStatus(12680) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12680), false, player);
            
            if (player->GetQuestStatus(12687) == QUEST_STATUS_NONE)//Dans le royaume des ombres
                player->AddQuest(sObjectMgr->GetQuestTemplate(12687), nullptr);
                
            if (player->GetQuestStatus(12687) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12687), false, player);
            
            if (player->GetQuestStatus(12697) == QUEST_STATUS_NONE)//Gothik le moissonneur
                player->AddQuest(sObjectMgr->GetQuestTemplate(12697), nullptr);
                
            if (player->GetQuestStatus(12697) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12697), false, player);
            
            if (player->GetQuestStatus(12698) == QUEST_STATUS_NONE)//Le don continu
                player->AddQuest(sObjectMgr->GetQuestTemplate(12698), nullptr);
                
            if (player->GetQuestStatus(12698) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12698), false, player);
            
            if (player->GetQuestStatus(12700) == QUEST_STATUS_NONE)//Une occasion d'attaquer
                player->AddQuest(sObjectMgr->GetQuestTemplate(12700), nullptr);
                
            if (player->GetQuestStatus(12700) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12700), false, player);
            
            if (player->GetQuestStatus(12701) == QUEST_STATUS_NONE)//Massacre à la halte de la lumière
                player->AddQuest(sObjectMgr->GetQuestTemplate(12701), nullptr);
                
            if (player->GetQuestStatus(12701) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12701), false, player);
            
            if (player->GetQuestStatus(12706) == QUEST_STATUS_NONE)//Victoire à Brèche-de-Mort !
                player->AddQuest(sObjectMgr->GetQuestTemplate(12706), nullptr);
                
            if (player->GetQuestStatus(12706) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12706), false, player);
            
            if (player->GetQuestStatus(12711) == QUEST_STATUS_NONE)//Du courrier abandonné
                player->AddQuest(sObjectMgr->GetQuestTemplate(12711), nullptr);
                
            if (player->GetQuestStatus(12711) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12711), false, player);
            
            if (player->GetQuestStatus(12714) == QUEST_STATUS_NONE)//La volonté du roi-liche
                player->AddQuest(sObjectMgr->GetQuestTemplate(12714), nullptr);
                
            if (player->GetQuestStatus(12714) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12714), false, player);
            
            if (player->GetQuestStatus(12715) == QUEST_STATUS_NONE)//La crypte du souvenir
                player->AddQuest(sObjectMgr->GetQuestTemplate(12715), nullptr);
                
            if (player->GetQuestStatus(12715) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12715), false, player);
            
            if (player->GetQuestStatus(12716) == QUEST_STATUS_NONE)//La requête du porte-peste
                player->AddQuest(sObjectMgr->GetQuestTemplate(12716), nullptr);
                
            if (player->GetQuestStatus(12716) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12716), false, player);
            
            if (player->GetQuestStatus(12717) == QUEST_STATUS_NONE)//La cuvée spéciale de Noth
                player->AddQuest(sObjectMgr->GetQuestTemplate(12717), nullptr);
                
            if (player->GetQuestStatus(12717) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12717), false, player);
            
            if (player->GetQuestStatus(12719) == QUEST_STATUS_NONE)//Nul lieu pour fuir ou se cacher
                player->AddQuest(sObjectMgr->GetQuestTemplate(12719), nullptr);
                
            if (player->GetQuestStatus(12719) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12719), false, player);
            
            if (player->GetQuestStatus(12722) == QUEST_STATUS_NONE)//Comme des agneaux à l'abattoir
                player->AddQuest(sObjectMgr->GetQuestTemplate(12722), nullptr);
                
            if (player->GetQuestStatus(12722) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12722), false, player);
            
            if (player->GetQuestStatus(12720) == QUEST_STATUS_NONE)//Comment se faire des amis et influencer ses ennemis
                player->AddQuest(sObjectMgr->GetQuestTemplate(12720), nullptr);
                
            if (player->GetQuestStatus(12720) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12720), false, player);
            
            if (player->GetQuestStatus(12723) == QUEST_STATUS_NONE)//Derrière les lignes écarlates
                player->AddQuest(sObjectMgr->GetQuestTemplate(12723), nullptr);
                
            if (player->GetQuestStatus(12723) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12723), false, player);
            
            if (player->GetQuestStatus(12724) == QUEST_STATUS_NONE)//Le chemin du croisé vertueux
                player->AddQuest(sObjectMgr->GetQuestTemplate(12724), nullptr);
                
            if (player->GetQuestStatus(12724) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12724), false, player);
            
            if (player->GetQuestStatus(12725) == QUEST_STATUS_NONE)//Frères dans la mort
                player->AddQuest(sObjectMgr->GetQuestTemplate(12725), nullptr);
                
            if (player->GetQuestStatus(12725) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12725), false, player);
            
            if (player->GetQuestStatus(12727) == QUEST_STATUS_NONE)//Une issue sanglante
                player->AddQuest(sObjectMgr->GetQuestTemplate(12727), nullptr);
                
            if (player->GetQuestStatus(12727) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12727), false, player);
            
            if (player->GetQuestStatus(12738) == QUEST_STATUS_NONE)//Vengeance !
                player->AddQuest(sObjectMgr->GetQuestTemplate(12738), nullptr);
                
            if (player->GetQuestStatus(12738) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12738), false, player);
            
            if (player->GetTeamId() == TEAM_ALLIANCE)//Une surprise spéciale
            {
                if (player->getRace(true) == RACE_HUMAN)
                {
                    if (player->GetQuestStatus(12742) == QUEST_STATUS_NONE)
                        player->AddQuest(sObjectMgr->GetQuestTemplate(12742), nullptr);
                
                    if (player->GetQuestStatus(12742) != QUEST_STATUS_REWARDED)
                        player->RewardQuest(sObjectMgr->GetQuestTemplate(12742), false, player);
                }
                else if (player->getRace(true) == RACE_NIGHTELF)
                {
                    if (player->GetQuestStatus(12743) == QUEST_STATUS_NONE)
                        player->AddQuest(sObjectMgr->GetQuestTemplate(12743), nullptr);
                
                    if (player->GetQuestStatus(12743) != QUEST_STATUS_REWARDED)
                        player->RewardQuest(sObjectMgr->GetQuestTemplate(12743), false, player);
                }
                else if (player->getRace(true) == RACE_DWARF)
                {
                    if (player->GetQuestStatus(12744) == QUEST_STATUS_NONE)
                        player->AddQuest(sObjectMgr->GetQuestTemplate(12744), nullptr);
                
                    if (player->GetQuestStatus(12744) != QUEST_STATUS_REWARDED)
                        player->RewardQuest(sObjectMgr->GetQuestTemplate(12744), false, player);
                }
                else if (player->getRace(true) == RACE_GNOME)
                {
                    if (player->GetQuestStatus(12745) == QUEST_STATUS_NONE)
                        player->AddQuest(sObjectMgr->GetQuestTemplate(12745), nullptr);
                
                    if (player->GetQuestStatus(12745) != QUEST_STATUS_REWARDED)
                        player->RewardQuest(sObjectMgr->GetQuestTemplate(12745), false, player);
                }
                else if (player->getRace(true) == RACE_DRAENEI)
                {
                    if (player->GetQuestStatus(12746) == QUEST_STATUS_NONE)
                        player->AddQuest(sObjectMgr->GetQuestTemplate(12746), nullptr);
                
                    if (player->GetQuestStatus(12746) != QUEST_STATUS_REWARDED)
                        player->RewardQuest(sObjectMgr->GetQuestTemplate(12746), false, player);
                }
            }
            else if (player->GetTeamId() == TEAM_HORDE)
            {
                if (player->getRace(true) == RACE_TAUREN)
                {
                    if (player->GetQuestStatus(12739) == QUEST_STATUS_NONE)
                        player->AddQuest(sObjectMgr->GetQuestTemplate(12739), nullptr);
                
                    if (player->GetQuestStatus(12739) != QUEST_STATUS_REWARDED)
                        player->RewardQuest(sObjectMgr->GetQuestTemplate(12739), false, player);
                }
                else if (player->getRace(true) == RACE_BLOODELF)
                {
                    if (player->GetQuestStatus(12747) == QUEST_STATUS_NONE)
                        player->AddQuest(sObjectMgr->GetQuestTemplate(12747), nullptr);
                
                    if (player->GetQuestStatus(12747) != QUEST_STATUS_REWARDED)
                        player->RewardQuest(sObjectMgr->GetQuestTemplate(12747), false, player);
                }
                else if (player->getRace(true) == RACE_ORC)
                {
                    if (player->GetQuestStatus(12748) == QUEST_STATUS_NONE)
                        player->AddQuest(sObjectMgr->GetQuestTemplate(12748), nullptr);
                
                    if (player->GetQuestStatus(12748) != QUEST_STATUS_REWARDED)
                        player->RewardQuest(sObjectMgr->GetQuestTemplate(12748), false, player);
                }
                else if (player->getRace(true) == RACE_TROLL)
                {
                    if (player->GetQuestStatus(12749) == QUEST_STATUS_NONE)
                        player->AddQuest(sObjectMgr->GetQuestTemplate(12749), nullptr);
                
                    if (player->GetQuestStatus(12749) != QUEST_STATUS_REWARDED)
                        player->RewardQuest(sObjectMgr->GetQuestTemplate(12749), false, player);
                }
                else if (player->getRace(true) == RACE_UNDEAD_PLAYER)
                {
                    if (player->GetQuestStatus(12750) == QUEST_STATUS_NONE)
                        player->AddQuest(sObjectMgr->GetQuestTemplate(12750), nullptr);
                
                    if (player->GetQuestStatus(12750) != QUEST_STATUS_REWARDED)
                        player->RewardQuest(sObjectMgr->GetQuestTemplate(12750), false, player);
                }
            }
            
            if (player->GetQuestStatus(12751) == QUEST_STATUS_NONE)//Un retour au pays... en quelques sortes
                player->AddQuest(sObjectMgr->GetQuestTemplate(12751), nullptr);
                
            if (player->GetQuestStatus(12751) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12751), false, player);
            
            if (player->GetQuestStatus(12754) == QUEST_STATUS_NONE)//Embuscade au surplomb
                player->AddQuest(sObjectMgr->GetQuestTemplate(12754), nullptr);
                
            if (player->GetQuestStatus(12754) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12754), false, player);
            
            if (player->GetQuestStatus(12755) == QUEST_STATUS_NONE)//Une rencontre avec le destin
                player->AddQuest(sObjectMgr->GetQuestTemplate(12755), nullptr);
                
            if (player->GetQuestStatus(12755) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12755), false, player);
            
            if (player->GetQuestStatus(12756) == QUEST_STATUS_NONE)//L'assaut écarlate émerge
                player->AddQuest(sObjectMgr->GetQuestTemplate(12756), nullptr);
                
            if (player->GetQuestStatus(12756) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12756), false, player);
            
            if (player->GetQuestStatus(12757) == QUEST_STATUS_NONE)//L'approche des armées écarlates
                player->AddQuest(sObjectMgr->GetQuestTemplate(12757), nullptr);
                
            if (player->GetQuestStatus(12757) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12757), false, player);
            
            if (player->GetQuestStatus(12778) == QUEST_STATUS_NONE)//L'apocalypse écarlate
                player->AddQuest(sObjectMgr->GetQuestTemplate(12778), nullptr);
                
            if (player->GetQuestStatus(12778) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12778), false, player);
            
            if (player->GetQuestStatus(12779) == QUEST_STATUS_NONE)//La fin de toutes choses...
                player->AddQuest(sObjectMgr->GetQuestTemplate(12779), nullptr);
                
            if (player->GetQuestStatus(12779) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12779), false, player);
            
            if (player->GetQuestStatus(12800) == QUEST_STATUS_NONE)//Le dernier ordre du roi-liche
                player->AddQuest(sObjectMgr->GetQuestTemplate(12800), nullptr);
                
            if (player->GetQuestStatus(12800) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12800), false, player);
            
            if (player->GetQuestStatus(12801) == QUEST_STATUS_NONE)//La lumière de l'Aube
                player->AddQuest(sObjectMgr->GetQuestTemplate(12801), nullptr);
                
            if (player->GetQuestStatus(12801) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(12801), false, player);
            
            if (player->GetQuestStatus(13165) == QUEST_STATUS_NONE)//Reprendre Achérus
                player->AddQuest(sObjectMgr->GetQuestTemplate(13165), nullptr);
                
            if (player->GetQuestStatus(13165) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(13165), false, player);
            
            if (player->GetQuestStatus(13166) == QUEST_STATUS_NONE)//La bataille pour le fort d'ébène
                player->AddQuest(sObjectMgr->GetQuestTemplate(13166), nullptr);
                
            if (player->GetQuestStatus(13166) != QUEST_STATUS_REWARDED)
                player->RewardQuest(sObjectMgr->GetQuestTemplate(13166), false, player);
            
            if (player->GetTeamId() == TEAM_ALLIANCE)//Là où marche le roi
            {
                if (player->GetQuestStatus(13188) == QUEST_STATUS_NONE)
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
                
                if (player->GetQuestStatus(13188) != QUEST_STATUS_REWARDED)
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(13188), false, player);
            }                
            else if (player->GetTeamId() == TEAM_HORDE)//La bénédiction du chef de guerre
            {
                if (player->GetQuestStatus(13189) == QUEST_STATUS_NONE)
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);
                
                if (player->GetQuestStatus(13189) != QUEST_STATUS_REWARDED)
                    player->RewardQuest(sObjectMgr->GetQuestTemplate(13189), false, player);
            }
            
            if (player->getLevel() != 58)
                player->GiveLevel(58);            
            
            player->learnSpell(54447, false);//Rune de Brise-sort
            player->learnSpell(53342, false);//Rune de Fracasse-sort
            
            
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
    new Azerothcore_optional_deathknight_skip;
}
