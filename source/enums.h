#pragma once

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

enum eScriptEvents {
	CEO_BAN = -764524031,
	CEO_KICK = 248967238,
	CEO_MONEY = 1890277845,
	SET_BOUNTY = 1294995624,
	CLEAR_WANTED = -91354030,
	FAKE_DEOPOSIT = 677240627,
	FORCE_MISSION = 2020588206,
	GTA_BANNER = 1572255940,
	ROTATE_CAM = 801199324,
};