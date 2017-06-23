#include "stdafx.h"

HRESULT captureSampleFromService(WINBIO_UNIT_ID *UnitId, PWINBIO_BIR *Sample, SIZE_T *SampleSize, WINBIO_REJECT_DETAIL *RejectDetail);
HRESULT cancelSession();
HRESULT closeSession();

HRESULT deleteTemplate();

HRESULT enrollBegin(WINBIO_BIOMETRIC_SUBTYPE subFactor);
HRESULT enrollCapture(WINBIO_REJECT_DETAIL *RejectDetail);
HRESULT enrollCommit(WINBIO_IDENTITY *Identity, BOOLEAN *IsNewTemplate);
HRESULT enumBiometricUnits(PWINBIO_UNIT_SCHEMA *UnitSchema, SIZE_T *UnitCount);
HRESULT enumDatabases(PWINBIO_STORAGE_SCHEMA *StorageSchemaArray, SIZE_T *StorageCount);
HRESULT enumEnrollments(PWINBIO_BIOMETRIC_SUBTYPE *SubFactorArray, SIZE_T *SubFactorCount);
HRESULT enumServiceProviders(PWINBIO_BSP_SCHEMA *BspSchemaArray, SIZE_T *BspCount);

HRESULT freeAddress(PVOID address);

HRESULT getCredentialState(WINBIO_CREDENTIAL_STATE *CredState);
HRESULT getDomainLogonSetting(BOOLEAN *Value, WINBIO_SETTING_SOURCE_TYPE *Source);
HRESULT getEnabledSetting(BOOLEAN *Value, WINBIO_SETTING_SOURCE_TYPE *Source);
HRESULT getLogonSetting(BOOLEAN *Value, WINBIO_SETTING_SOURCE_TYPE *Source);


HRESULT identify(WINBIO_UNIT_ID *UnitId, WINBIO_IDENTITY *Identity, WINBIO_BIOMETRIC_SUBTYPE *SubFactor);

HRESULT locateSensor(WINBIO_UNIT_ID *UnitId);
HRESULT lockUnit();
HRESULT logonIdentifiedUser();

HRESULT openSession(WINBIO_SESSION_FLAGS Flags);

HRESULT removeAllCredentials();
HRESULT removeAllDomainCredentials();
HRESULT removeCredential();

HRESULT setCredential();

HRESULT unlockUnit();

HRESULT verify(WINBIO_BIOMETRIC_SUBTYPE SubFactor, WINBIO_UNIT_ID *UnitId, BOOLEAN *Match);

HRESULT wait();
