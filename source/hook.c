#include "pch.h"
#include <stdlib.h>
#include "hook.h"
#include "pattern.h"
#include "script.h"
#include "logger.h"
#include "natives.h"
#include "globals.h"

lbls m_gameLabels[100];
int g_labelNum = 0;
enum eNetworkEvents {
	_CObjectIdFreedEvent,
	_CObjectIdRequestEvent,
	_CArrayDataVerifyEvent,
	_CScriptArrayDataVerifyEvent,
	_CRequestControlEvent,
	_CGiveControlEvent,
	_CWeaponDamageEvent,
	_CRequestPickupEvent,
	_CRequestMapPickupEvent,
	_CGameClockEvent,
	_CGameWeatherEvent,
	_CRespawnPlayerPedEvent,
	_CGiveWeaponEvent,
	_CRemoveWeaponEvent,
	_CRemoveAllWeaponsEvent,
	_CVehicleComponentControlEvent,
	_CFireEvent,
	_CExplosionEvent,
	_CStartProjectileEvent,
	_CUpdateProjectileTargetEvent,
	_CRemoveProjectileEntityEvent,
	_CBreakProjectileTargetLockEvent,
	_CAlterWantedLevelEvent,
	_CChangeRadioStationEvent,
	_CRagdollRequestEvent,
	_CPlayerTauntEvent,
	_CPlayerCardStatEvent,
	_CDoorBreakEvent,
	_CScriptedGameEvent,
	_CRemoteScriptInfoEvent,
	_CRemoteScriptLeaveEvent,
	_CMarkAsNoLongerNeededEvent,
	_CConvertToScriptEntityEvent,
	_CScriptWorldStateEvent,
	_CClearAreaEvent,
	_CClearRectangleAreaEvent,
	_CNetworkRequestSyncedSceneEvent,
	_CNetworkStartSyncedSceneEvent,
	_CNetworkStopSyncedSceneEvent,
	_CNetworkUpdateSyncedSceneEvent,
	_CIncidentEntityEvent,
	_CGivePedScriptedTaskEvent,
	_CGivePedSequenceTaskEvent,
	_CNetworkClearPedTasksEvent,
	_CNetworkStartPedArrestEvent,
	_CNetworkStartPedUncuffEvent,
	_CNetworkSoundCarHornEvent,
	_CNetworkEntityAreaStatusEvent,
	_CNetworkGarageOccupiedStatusEvent,
	_CPedConversationLineEvent,
	_CScriptEntityStateChangeEvent,
	_CNetworkPlaySoundEvent,
	_CNetworkStopSoundEvent,
	_CNetworkPlayAirdefenseFireEvent,
	_CNetworkBankRequestEvent,
	_CNetworkAudioBarkEvent,
	_CRequestDoorEvent,
	_CNetworkTrainReportEvent,
	_CNetworkTrainRequestEvent,
	_CNetworkIncrementStatEvent,
	_CModifyVehicleLockWordStateData,
	_CModifyPtfxWordStateDataScriptedEvolveEvent,
	_CRequestPhoneExplosionEvent,
	_CRequestDetachmentEvent,
	_CKickVotesEvent,
	_CGivePickupRewardsEvent,
	_CNetworkCrcHashCheckEvent,
	_CBlowUpVehicleEvent,
	_CNetworkSpecialFireEquippedWeapon,
	_CNetworkRespondedToThreatEvent,
	_CNetworkShoutTargetPosition,
	_CVoiceDrivenMouthMovementFinishedEvent,
	_CPickupDestroyedEvent,
	_CUpdatePlayerScarsEvent,
	_CNetworkCheckExeSizeEvent,
	_CNetworkPtfxEvent,
	_CNetworkPedSeenDeadPedEvent,
	_CRemoveStickyBombEvent,
	_CNetworkCheckCodeCrcsEvent,
	_CInformSilencedGunshotEvent,
	_CPedPlayPainEvent,
	_CCachePlayerHeadBlendDataEvent,
	_CRemovePedFromPedgroupEvent,
	_CUpdateFxnEvent,
	_CReportCashSpawnEvent,
	_CActivateVehicleSpecialAbilityEvent,
	_CBlockWeaponSelection,
	_CNetworkCheckCatalogCrc
};
GtaThread *getCurScrThr() { return *(GtaThread**)(*(char**)__readgsqword(0x58) + 0x830); }
void setCurScrThr(char* tls, GtaThread* thr) {
	*(GtaThread**)(tls + 0x828) = thr;
	*(bool*)(tls + 0x830) = thr != NULL;
}
GtaThread* getGtaThreadByHash(uint hash) {
	GtaThread** thrTable = (*g_pointers.m_gtaThreads).m_data;
	for (int i = 0; i < (*g_pointers.m_gtaThreads).m_size; i++)
		if (thrTable[i]->script_hash == 0x5700179C)
			return thrTable[i];
	return NULL;
}

//0x5700179C: main_persistent
int (*ogScrThreadRun)(uint32_t ops_to_execute);
int scrThreadRunHk(uint32_t ops_to_execute) {
	GtaThread* main_persistent = getGtaThreadByHash(0x5700179C);
	if (g_running) {
		if (main_persistent != NULL) {
			char* tls = *(char**)__readgsqword(0x58);
			GtaThread* ogThr = getCurScrThr();
			setCurScrThr(tls, main_persistent);
			fbrTick(&g_mainFbr);
			setCurScrThr(tls, ogThr);
		}
		//Disables screenblur, non thread specific
		if (NETWORK_NETWORK_IS_SESSION_ACTIVE()) {
			//We need to not do this in story mode, it breaks the hospital teleport and creates a indefinite suicide scneen
			GRAPHICS_DISABLE_SCREENBLUR_FADE();
			if (CAM_IS_SCREEN_FADED_OUT())
				CAM_DO_SCREEN_FADE_IN(0);
			else if (CAM_IS_SCREEN_FADED_IN())
				CAM_DO_SCREEN_FADE_IN(0);
		}
		if (*(int*)getScriptGlobalPtr(1574988) == 26) {
			STREAMING_STOP_PLAYER_SWITCH();
			*(int*)getScriptGlobalPtr(1574988) = 29;
		}
	}
	return ogScrThreadRun(ops_to_execute);
}

const char*(*ogGetLabelText)(void* unk, const char* lbl);
const char* getLabelTextHk(void* unk, const char* lbl) {
	for (int i = 0; i < g_labelNum; i++) {
		if (!strcmp(m_gameLabels[i].label, lbl))
			return m_gameLabels[i].contents;
	}
	return ogGetLabelText(unk, lbl);
}

bool scriptedGameEvent(CScriptedGameEvent* sge, CNetGamePlayer* sender) {
	int64_t* args = sge->m_args;
	switch (args[0]) {
	case -764524031: {
		sendLog(consoleWhiteOnBlack, "Event Protections", "%s Event from %s", "CEO Kick", sender->m_player_info->m_net_player_data.m_name);
		return true;
	} break;
	}
	return false;
}
void (*ogReceivedEvent)(uint64_t eventMgr, struct CNetGamePlayer* source, struct CNetGamePlayer* target, uint16_t id, int idx, int handledBitset, int bufferSize, struct datBitBuffer* buffer);
void receivedEventHk(uint64_t eventMgr, struct CNetGamePlayer* source, struct CNetGamePlayer* target, uint16_t id, int idx, int handledBitset, int bufferSize, struct datBitBuffer* buffer) {
	char const* eventName = *(char**)(eventMgr + 8ULL * id + 0x3B6B0);
	if (eventName == NULL || source == NULL || source->m_player_id < 0 || source->m_player_id >= 32 || !NETWORK_NETWORK_IS_SESSION_ACTIVE()) {
		g_pointers.m_sendEventAck(eventMgr, source, target, id, handledBitset);
		return;
	}
	switch (id) {
	case _CScriptedGameEvent: {
		struct CScriptedGameEvent* sge = malloc(sizeof(struct CScriptedGameEvent));
		buffer_ReadDword(buffer , &sge->m_args_size, 0x20);
		if (sge->m_args_size - 1 <= 0x1AF)
			buffer_ReadArray(buffer , &sge->m_args, 8 * sge->m_args_size);
		if (scriptedGameEvent(sge, source)) {
			g_pointers.m_sendEventAck(eventMgr, source, target, id, handledBitset);
			return;
		}
		free((void*)sge);
		buffer_Seek(buffer, 0);
	} break;
	}
	return ogReceivedEvent(eventMgr, source, target, id, idx, handledBitset, bufferSize, buffer);
}

void initHooks() {
	lbls_addText("HUD_JOINING", "Isn't BigBaseC the fucking best?");
	lbls_addText("HUD_TRANSP", "Isn't BigBaseC the fucking best?");
	if (MH_CreateHook((LPVOID)g_pointers.m_scrThreadRun, (LPVOID)&scrThreadRunHk, (LPVOID)&ogScrThreadRun) == MH_OK)
		sendLog(consoleGrayOnBlack, "Hooks", "Created hook STR");
	if (MH_CreateHook((LPVOID)g_pointers.m_getLabelText, (LPVOID)&getLabelTextHk, (LPVOID)&ogGetLabelText) == MH_OK)
		sendLog(consoleGrayOnBlack, "Hooks", "Created hook GLT");
	if (MH_CreateHook((LPVOID)g_pointers.m_receivedEvent, (LPVOID)&receivedEventHk, (LPVOID)&ogReceivedEvent) == MH_OK)
		sendLog(consoleGrayOnBlack, "Hooks", "Created hook RE");
	MH_EnableHook(MH_ALL_HOOKS);
	sendLog(consoleGrayOnBlack, "Hooks", "Enabled all hooks");
}
void uninitHooks() {
	MH_DisableHook(MH_ALL_HOOKS);
	sendLog(consoleGrayOnBlack, "Hooks", "Disabled all hooks");
	MH_RemoveHook(MH_ALL_HOOKS);
	sendLog(consoleGrayOnBlack, "Hooks", "Removed all hooks");
}
