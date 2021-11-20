/* Skip Death Knight Module
   Original Module From Single Player Project Consolidated Skip Module
   Rewritten for TC 335 By Single Player Project Developer MDic
   Original Concept from conanhun513
   Assistance and Review by JinnaiX
   Modified for Azerothcore
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

class AzerothCore_skip_deathknight_announce : public PlayerScript
{
public:
    AzerothCore_skip_deathknight_announce() : PlayerScript("AzerothCore_skip_deathknight_announce") { }

    void OnLogin(Player* Player)
    {
        if (sConfigMgr->GetBoolDefault("Skip.Deathknight.Starter.Announce.enable", true))
        {
            ChatHandler(Player->GetSession()).SendSysMessage("This server is running the |cff4CFF00Azerothcore Skip Deathknight Starter |rmodule.");
        }
    }
};

class AzerothCore_skip_deathknight : public PlayerScript
{
public:
    AzerothCore_skip_deathknight() : PlayerScript("AzerothCore_skip_deathknight") { }

    void OnFirstLogin(Player* player)
    {
        int DKL = sConfigMgr->GetFloatDefault("Skip.Deathknight.Start.Level", 58);

        if (sConfigMgr->GetBoolDefault("Skip.Deathknight.Starter.Enable", true))
        {
            if (player->GetAreaId() == 4342)
            {
                player->SetLevel(DKL);
                player->learnSpell(53428);//runeforging
                player->learnSpell(53441);//runeforging
                player->learnSpell(53344);//runeforging
                player->learnSpell(62158);//runeforging
                player->learnSpell(33391);//journeyman riding
                player->learnSpell(54586);//runeforging credit
                player->learnSpell(48778);//acherus deathcharger
                player->learnSkillRewardedSpells(776, 375);//Runeforging
                player->learnSkillRewardedSpells(960, 375);//Runeforging
                player->AddItem(38661, true);//player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 38661, true);//Greathelm of the Scourge Champion
                player->AddItem(38666, true);//player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 38666, true);//Plated Saronite Bracers
                player->AddItem(38668, true);//player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 38668, true);//The Plaguebringer's Girdle
                player->AddItem(38667, true);//player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 38667, true);//Bloodbane's Gauntlets of Command
                player->AddItem(38665, true);//player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 38665, true);//Saronite War Plate
                player->AddItem(38669, true);//player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 38669, true);//Engraved Saronite Legplates
                player->AddItem(38663, true);//player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 38663, true);// Blood-Soaked Saronite Plated Spaulders
                player->AddItem(38670, true);//player->EquipNewItem(EQUIPMENT_SLOT_FEET, 38670, true);//Greaves of the Slaughter
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 38675, true);//Signet of the Dark Brotherhood
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 38674, true);//Soul Harvester's Charm
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 38671, true);//Valanar's Signet Ring
                player->AddItem(34658, true);//Original ring1 added to inventory
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 38672, true);// Keleseth's Signet Ring
                player->AddItem(38147, true);//Original ring2 added to inventory                
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 38662, true);//Bladed Ebon Amulet
                player->AddItem(34657, true);//Original necklace added to inventory
                player->AddItem(39320, true);//Sky Darkener's Shroud of Blood
                player->AddItem(38664, true);//Sky Darkener's Shroud of the Unholy
                player->AddItem(39322, true);//Shroud of the North Wind
                player->AddItem(38632, true);//Greatsword of the Ebon Blade
                player->AddItem(6948, true);//Hearthstone
                player->AddItem(38707, true);//Runed Soulblade
                player->AddItem(40483, true);//Insignia of the Scourge

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
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
                else if (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(13189) == QUEST_STATUS_NONE)//Saurfang's Blessing
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);
                if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->TeleportTo(0, -8452.56f, 347.08f, 120.89f, 5.38f);//Stormwind
                else
                    player->TeleportTo(1, 1920.80f, -4138.36f, 40.57f, 1.64f);//Orgrimmar
                ObjectAccessor::SaveAllPlayers();//Save
            }
        }

        if (sConfigMgr->GetBoolDefault("GM.Skip.Deathknight.Starter.Enable", true))
        {
            if (player->GetSession()->GetSecurity() >= SEC_MODERATOR && player->GetAreaId() == 4342)
            {
                player->SetLevel(DKL);
                player->learnSpell(53428);//runeforging
                player->learnSpell(53441);//runeforging
                player->learnSpell(53344);//runeforging
                player->learnSpell(62158);//runeforging
                player->learnSpell(33391);//journeyman riding
                player->learnSpell(54586);//runeforging credit
                player->learnSpell(48778);//acherus deathcharger
                player->learnSkillRewardedSpells(776, 375);//Runeforging
                player->learnSkillRewardedSpells(960, 375);//Runeforging
                player->AddItem(38661, true);//player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 38661, true);//Greathelm of the Scourge Champion
                player->AddItem(38666, true);//player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 38666, true);//Plated Saronite Bracers
                player->AddItem(38668, true);//player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 38668, true);//The Plaguebringer's Girdle
                player->AddItem(38667, true);//player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 38667, true);//Bloodbane's Gauntlets of Command
                player->AddItem(38665, true);//player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 38665, true);//Saronite War Plate
                player->AddItem(38669, true);//player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 38669, true);//Engraved Saronite Legplates
                player->AddItem(38663, true);//player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 38663, true);// Blood-Soaked Saronite Plated Spaulders
                player->AddItem(38670, true);//player->EquipNewItem(EQUIPMENT_SLOT_FEET, 38670, true);//Greaves of the Slaughter
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 38675, true);//Signet of the Dark Brotherhood
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 38674, true);//Soul Harvester's Charm
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 38671, true);//Valanar's Signet Ring
                player->AddItem(34658, true);//Original ring1 added to inventory
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 38672, true);// Keleseth's Signet Ring
                player->AddItem(38147, true);//Original ring2 added to inventory                
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 38662, true);//Bladed Ebon Amulet
                player->AddItem(34657, true);//Original necklace added to inventory
                player->AddItem(39320, true);//Sky Darkener's Shroud of Blood
                player->AddItem(38664, true);//Sky Darkener's Shroud of the Unholy
                player->AddItem(39322, true);//Shroud of the North Wind
                player->AddItem(38632, true);//Greatsword of the Ebon Blade
                player->AddItem(6948, true);//Hearthstone
                player->AddItem(38707, true);//Runed Soulblade
                player->AddItem(40483, true);//Insignia of the Scourge

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
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
                else if (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(13189) == QUEST_STATUS_NONE)//Saurfang's Blessing
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);
                if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->TeleportTo(0, -8452.56f, 347.08f, 120.89f, 5.38f);//Stormwind
                else
                    player->TeleportTo(1, 1920.80f, -4138.36f, 40.57f, 1.64f);//Orgrimmar
                ObjectAccessor::SaveAllPlayers();//Save
            }
        }
    }
};

#define LOCALE_LICHKING_0 "I wish to skip the Death Knight starter questline."
#define LOCALE_LICHKING_1 "죽음의 기사 스타터 퀘스트 라인을 건너뛰고 싶습니다."
#define LOCALE_LICHKING_2 "Je souhaite sauter la série de quêtes de démarrage du Chevalier de la mort."
#define LOCALE_LICHKING_3 "Ich möchte die Todesritter-Starter-Questreihe überspringen."
#define LOCALE_LICHKING_4 "我想跳過死亡騎士新手任務線。"
#define LOCALE_LICHKING_5 "我想跳過死亡騎士新手任務線。"
#define LOCALE_LICHKING_6 "Deseo saltarme la línea de misiones de inicio del Caballero de la Muerte."
#define LOCALE_LICHKING_7 "Deseo saltarme la línea de misiones de inicio del Caballero de la Muerte."
#define LOCALE_LICHKING_8 "Я хочу пропустить начальную цепочку заданий Рыцаря Смерти."

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
                char const* localizedEntry;
                switch (player->GetSession()->GetSessionDbcLocale())
                {
                case LOCALE_koKR: localizedEntry = LOCALE_LICHKING_1; break;
                case LOCALE_frFR: localizedEntry = LOCALE_LICHKING_2; break;
                case LOCALE_deDE: localizedEntry = LOCALE_LICHKING_3; break;
                case LOCALE_zhCN: localizedEntry = LOCALE_LICHKING_4; break;
                case LOCALE_zhTW: localizedEntry = LOCALE_LICHKING_5; break;
                case LOCALE_esES: localizedEntry = LOCALE_LICHKING_6; break;
                case LOCALE_esMX: localizedEntry = LOCALE_LICHKING_7; break;
                case LOCALE_ruRU: localizedEntry = LOCALE_LICHKING_8; break;
                case LOCALE_enUS: localizedEntry = LOCALE_LICHKING_0; break;
                default: localizedEntry = LOCALE_LICHKING_0;
                }
                AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, localizedEntry, GOSSIP_SENDER_MAIN, 11);
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
                AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Je souhaite passer l'introduction du Chevalier de la mort (ce choix est irrévocable).", GOSSIP_SENDER_MAIN, 12);
                AddGossipItemFor(player, GOSSIP_ICON_INTERACT_1, "Non merci, pas pour l'instant.", GOSSIP_SENDER_MAIN, 13);
                SendGossipMenuFor(player, player->GetGossipTextId(creature), creature->GetGUID());
                break;

            case 12:
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
                player->AddItem(38661, true);//player->EquipNewItem(EQUIPMENT_SLOT_HEAD, 38661, true);//Greathelm of the Scourge Champion
                player->AddItem(38666, true);//player->EquipNewItem(EQUIPMENT_SLOT_WRISTS, 38666, true);//Plated Saronite Bracers
                player->AddItem(38668, true);//player->EquipNewItem(EQUIPMENT_SLOT_WAIST, 38668, true);//The Plaguebringer's Girdle
                player->AddItem(38667, true);//player->EquipNewItem(EQUIPMENT_SLOT_HANDS, 38667, true);//Bloodbane's Gauntlets of Command
                player->AddItem(38665, true);//player->EquipNewItem(EQUIPMENT_SLOT_CHEST, 38665, true);//Saronite War Plate
                player->AddItem(38669, true);//player->EquipNewItem(EQUIPMENT_SLOT_LEGS, 38669, true);//Engraved Saronite Legplates
                player->AddItem(38663, true);//player->EquipNewItem(EQUIPMENT_SLOT_SHOULDERS, 38663, true);// Blood-Soaked Saronite Plated Spaulders
                player->AddItem(38670, true);//player->EquipNewItem(EQUIPMENT_SLOT_FEET, 38670, true);//Greaves of the Slaughter
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET1, 38675, true);//Signet of the Dark Brotherhood
                player->EquipNewItem(EQUIPMENT_SLOT_TRINKET2, 38674, true);//Soul Harvester's Charm
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER1, 38671, true);//Valanar's Signet Ring
                player->AddItem(34658, true);//Original ring1 added to inventory
                player->EquipNewItem(EQUIPMENT_SLOT_FINGER2, 38672, true);// Keleseth's Signet Ring
                player->AddItem(38147, true);//Original ring2 added to inventory                
                player->EquipNewItem(EQUIPMENT_SLOT_NECK, 38662, true);//Bladed Ebon Amulet
                player->AddItem(34657, true);//Original necklace added to inventory
                player->AddItem(39320, true);//Sky Darkener's Shroud of Blood
                player->AddItem(38664, true);//Sky Darkener's Shroud of the Unholy
                player->AddItem(39322, true);//Shroud of the North Wind
                player->AddItem(38632, true);//Greatsword of the Ebon Blade
                player->AddItem(6948, true);//Hearthstone
                player->AddItem(38707, true);//Runed Soulblade
                player->AddItem(40483, true);//Insignia of the Scourge

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
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13188), nullptr);
                else if (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(13189) == QUEST_STATUS_NONE)//Saurfang's Blessing
                    player->AddQuest(sObjectMgr->GetQuestTemplate(13189), nullptr);
                if (player->GetTeamId() == TEAM_ALLIANCE)
                    player->TeleportTo(0, -8452.56f, 347.08f, 120.89f, 5.38f);//Stormwind
                else
                    player->TeleportTo(1, 1920.80f, -4138.36f, 40.57f, 1.64f);//Orgrimmar
                ObjectAccessor::SaveAllPlayers();//Save
                CloseGossipMenuFor(player);
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
    new AzerothCore_skip_deathknight_announce;
    new AzerothCore_skip_deathknight;
    new Azerothcore_optional_deathknight_skip;
}
