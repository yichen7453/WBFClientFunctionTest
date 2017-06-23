#include "stdafx.h"

#include "winbio_api_ctl.h"

static WINBIO_SESSION_HANDLE sessionHandle = NULL;
static PWINBIO_UNIT_SCHEMA unitSchema = NULL;
static SIZE_T unitCount = 0;

static WINBIO_UNIT_ID getUnitId();
static HRESULT GetCredentials(PSID pSid, PVOID* ppvAuthBlob, ULONG* pcbAuthBlob);
static HRESULT GetCurrentUserIdentity(__inout PWINBIO_IDENTITY Identity);

HRESULT openSession(WINBIO_SESSION_FLAGS Flags);



HRESULT cancelSession()
{
	printf("\n  -- > cancelSession() <--\n");

	HRESULT hr = S_OK;

	hr = WinBioCancel(sessionHandle);

	if (FAILED(hr)) {
		printf("\n WinBioCancel failed. hr = 0x%x\n", hr);
	}

	return hr;
}

HRESULT captureSampleFromService(WINBIO_UNIT_ID *UnitId, PWINBIO_BIR *Sample, SIZE_T *SampleSize, WINBIO_REJECT_DETAIL *RejectDetail)
{
	printf("\n  -- > captureSampleFromService() <--\n");

	HRESULT hr = S_OK;
	WINBIO_UNIT_ID unitId = NULL;
	PWINBIO_BIR sample = NULL;
	SIZE_T sampleSize = 0;
	WINBIO_REJECT_DETAIL rejectDetail = 0;

	hr = WinBioCaptureSample(
		sessionHandle,
		WINBIO_NO_PURPOSE_AVAILABLE,
		WINBIO_DATA_FLAG_RAW,
		&unitId,
		&sample,
		&sampleSize,
		&rejectDetail
		);

	if (FAILED(hr)) {
		if (hr == WINBIO_E_BAD_CAPTURE) {
			printf("\n Bad capture; reason: %d\n", rejectDetail);
		}
		else {
			printf("\n WinBioCaptureSample failed. hr = 0x%x\n", hr);
		}
	}

	*UnitId = unitId;
	*Sample = sample;
	*SampleSize = sampleSize;
	*RejectDetail = rejectDetail;

	return hr;
}

HRESULT closeSession()
{
	printf("\n  -- > closeSession() <--\n");

	HRESULT hr = S_OK;

	if (sessionHandle != NULL) {
		hr = WinBioCloseSession(sessionHandle);
		sessionHandle = NULL;
	}
	return hr;
}

HRESULT deleteTemplate()
{
	printf("\n  -- > deleteTemplate() <--\n");

	HRESULT hr = S_OK;
	WINBIO_IDENTITY identity = { 0 };

	hr = GetCurrentUserIdentity(&identity);
	if (FAILED(hr)) {
		printf("\n User identity not found. hr = 0x%x\n", hr);
	}

	hr = WinBioDeleteTemplate(sessionHandle, getUnitId(), &identity, WINBIO_SUBTYPE_ANY);
	if (FAILED(hr)) {
		printf("\n WinBioDeleteTemplate failed. hr = 0x%x\n", hr);
	}

	return hr;
}

HRESULT enrollBegin(WINBIO_BIOMETRIC_SUBTYPE subFactor)
{
	printf("\n  -- > enrollBegin() <--\n");

	HRESULT hr = S_OK;

	hr = WinBioEnrollBegin(
				sessionHandle,					// Handle to open biometric session
				subFactor,						//Finger to create template for
				getUnitId()						// Biometric unit ID
		);
	if (FAILED(hr)) {
		printf("\n WinBioEnrollBegin failed. hr = 0x%x\n", hr);
	}

	return hr;
}

HRESULT enrollCapture(WINBIO_REJECT_DETAIL *RejectDetail)
{
	printf("\n  -- > enrollCapture() <--\n");

	HRESULT hr = S_OK;
	WINBIO_REJECT_DETAIL rejectDetail = 0;

	hr = WinBioEnrollCapture(
		sessionHandle,			// Handle to open biometric session
		&rejectDetail			// [out] Failure information
		);

	if (FAILED(hr)) {
		printf("\n WinBioEnrollCapture failed. hr = 0x%x\n", hr);
	}
	*RejectDetail = rejectDetail;
	
	return hr;
}

HRESULT enrollCommit(WINBIO_IDENTITY *Identity, BOOLEAN *IsNewTemplate)
{
	HRESULT hr = S_OK;
	WINBIO_IDENTITY identity = { 0 };
	BOOLEAN isNewTemplate = TRUE;

	hr = WinBioEnrollCommit(
		sessionHandle,		// Handle to open biometric session
		&identity,			// WINBIO_IDENTITY object for the user
		&isNewTemplate);	// Is this a new template

	if (FAILED(hr)) {
		printf("\n WinBioEnrollCommit failed. hr = 0x%x\n", hr);
	}
	else {
		*Identity = identity;
		*IsNewTemplate = isNewTemplate;
	}
	
	return hr;
}

HRESULT enumBiometricUnits(PWINBIO_UNIT_SCHEMA *UnitSchema, SIZE_T *UnitCount)
{
	printf("\n  -- > enumBiometricUnits() <--\n");

	HRESULT hr = S_OK;

	hr = WinBioEnumBiometricUnits(
		WINBIO_TYPE_FINGERPRINT,	// Type of biometric unit
		&unitSchema,				// Array of unit schemas
		&unitCount					// Count of unit schemas
		);

	if (FAILED(hr)) {
		printf("\n WinBioEnumBiometricUnits failed. hr = 0x%x\n", hr);
	}
	else {
		*UnitSchema = unitSchema;
		*UnitCount = unitCount;
	}

	return hr;
}

HRESULT enumDatabases(PWINBIO_STORAGE_SCHEMA *StorageSchemaArray, SIZE_T *StorageCount)
{
	HRESULT hr = S_OK;
	PWINBIO_STORAGE_SCHEMA storageSchemaArray = NULL;
	SIZE_T storageCount = 0;
	SIZE_T index = 0;

	hr = WinBioEnumDatabases(
				WINBIO_TYPE_FINGERPRINT,	// Type of biometric unit
				&storageSchemaArray,		// Array of database schemas
				&storageCount				// Number of database schemas
		);
	if (FAILED(hr)) {
		printf("\n WinBioEnumDatabases failed. hr = 0x%x\n", hr);
	}
	else {
		*StorageSchemaArray = storageSchemaArray;
		*StorageCount = storageCount;
	}
	return hr;
}

HRESULT enumEnrollments(PWINBIO_BIOMETRIC_SUBTYPE *SubFactorArray, SIZE_T *SubFactorCount)
{
	printf("\n  -- > enumEnrollments() <--\n");

	HRESULT hr = S_OK;
	WINBIO_IDENTITY identity = { 0 };
	PWINBIO_BIOMETRIC_SUBTYPE subFactorArray = NULL;
	SIZE_T subFactorCount = 0;
	WINBIO_REJECT_DETAIL rejectDetail = 0;
	WINBIO_BIOMETRIC_SUBTYPE subFactor = WINBIO_SUBTYPE_NO_INFORMATION;
	WINBIO_UNIT_ID unitId = 0;

	hr = WinBioIdentify(
				sessionHandle,		// Session handle
				&unitId,			// Biometric unit ID
				&identity,			// User SID
				&subFactor,			// Finger sub factor
				&rejectDetail		// Rejection information
		);
	if (FAILED(hr)) {
		if (hr == WINBIO_E_UNKNOWN_ID) {
			printf("\n Unknown identity.\n");
		}
		else if (hr == WINBIO_E_BAD_CAPTURE) {
			printf("\n Bad capture; reason: %d\n", rejectDetail);
		}
		else {
			printf("\n WinBioIdentify failed. hr = 0x%x\n", hr);
		}
	}

	hr = WinBioEnumEnrollments(
				sessionHandle,		// Session handle
				unitId,				// Biometric unit ID
				&identity,			// Template ID
				&subFactorArray,	// Subfactors
				&subFactorCount		// Count of subfactors
		);
	if (FAILED(hr)) {
		printf("\n WinBioEnumEnrollments failed. hr = 0x%x\n", hr);
	}
	else {
		*SubFactorArray = subFactorArray;
		*SubFactorCount = subFactorCount;
	}

	return 0;
}

HRESULT enumServiceProviders(PWINBIO_BSP_SCHEMA *BspSchemaArray, SIZE_T *BspCount)
{
	HRESULT hr = S_OK;
	PWINBIO_BSP_SCHEMA bspSchemaArray = NULL;
	SIZE_T bspCount = 0;
	SIZE_T index = 0;

	hr = WinBioEnumServiceProviders(
		WINBIO_TYPE_FINGERPRINT,		// Provider to enumerate
		&bspSchemaArray,				// Provider schema array
		&bspCount						// Number of schemas returned
		);
	if (FAILED(hr)) {
		printf("\n WinBioEnumServiceProviders failed. hr = 0x%x\n", hr);
	}
	else {
		*BspSchemaArray = bspSchemaArray;
		*BspCount = bspCount;
	}
	return hr;
}

HRESULT freeAddress(PVOID address)
{
	printf("\n  -- > freeAddress() <--\n");

	HRESULT hr = S_OK;

	hr = WinBioFree(address);

	if (FAILED(hr)) {
		printf("\n WinBioFree failed. hr = 0x%x\n", hr);
	}

	return hr;
}

HRESULT getCredentialState(WINBIO_CREDENTIAL_STATE *CredState)
{
	printf("\n  -- > getCredentialState() <--\n");

	HRESULT hr = S_OK;
	WINBIO_IDENTITY identity;
	WINBIO_CREDENTIAL_STATE credState;

	hr = GetCurrentUserIdentity(&identity);
	if (FAILED(hr)) {
		printf("\n User identity not found. hr = 0x%x\n", hr);
		return hr;
	}

	hr = WinBioGetCredentialState(
				identity,					// User GUID or SID
				WINBIO_CREDENTIAL_PASSWORD,	// Credential type
				&credState					// [out] Credential state
		);
	if (FAILED(hr)) {
		printf("\n WinBioGetCredentialState failed. hr = 0x%x\n", hr);
	}
	else {
		*CredState = credState;
	}
	return hr;
}

HRESULT getDomainLogonSetting(BOOLEAN *Value, WINBIO_SETTING_SOURCE_TYPE *Source)
{
	printf("\n  -- > getDomainLogonSetting() <--\n");

	HRESULT hr = S_OK;
	BOOLEAN value = FALSE;
	WINBIO_SETTING_SOURCE_TYPE source = WINBIO_SETTING_SOURCE_INVALID;

	WinBioGetDomainLogonSetting(
			&value,		// Whether biometric domain logons are enabled
			&source		// The source of the setting
		);

	if (source == WINBIO_SETTING_SOURCE_INVALID) {
		printf("\n WinBioGetDomainLogonSetting returned WINBIO_SETTING_SOURCE_INVALID\n");
		hr = E_FAIL;
	}
	else if (source != WINBIO_SETTING_SOURCE_INVALID &&
		source != WINBIO_SETTING_SOURCE_DEFAULT &&
		source != WINBIO_SETTING_SOURCE_POLICY &&
		source != WINBIO_SETTING_SOURCE_LOCAL) {
		printf("\n WinBioGetLogonSetting returned garbage\n");
		hr = E_FAIL;
	}
	else {
		//printf("\n Value: %s, Source: ", value ? "TRUE" : "FALSE");
		*Value = value;
		*Source = source;
	}
	return hr;
}

HRESULT getEnabledSetting(BOOLEAN *Value, WINBIO_SETTING_SOURCE_TYPE *Source)
{
	printf("\n  -- > getDomainLogonSetting() <--\n");

	HRESULT hr = S_OK;
	BOOLEAN value = FALSE;
	WINBIO_SETTING_SOURCE_TYPE source = WINBIO_SETTING_SOURCE_INVALID;

	WinBioGetEnabledSetting(
		&value,			// Whether biometric domain logons are enabled
		&source			// The source of the setting
		);

	if (source == WINBIO_SETTING_SOURCE_INVALID) {
		printf("\n WinBioGetEnabledSetting returned WINBIO_SETTING_SOURCE_INVALID.\n");
		hr = E_FAIL;
	}
	else if (source != WINBIO_SETTING_SOURCE_INVALID &&
		source != WINBIO_SETTING_SOURCE_DEFAULT &&
		source != WINBIO_SETTING_SOURCE_POLICY &&
		source != WINBIO_SETTING_SOURCE_LOCAL) {
		printf("\n WinBioGetEnabledSetting returned garbage\n");
		hr = E_FAIL;
	}
	else {
		//printf("\n Value: %s, Source: ", value ? "TRUE" : "FALSE");
		*Value = value;
		*Source = source;
	}
	return hr;
}

HRESULT getLogonSetting(BOOLEAN *Value, WINBIO_SETTING_SOURCE_TYPE *Source)
{
	HRESULT hr = S_OK;
	BOOLEAN value = FALSE;
	WINBIO_SETTING_SOURCE_TYPE source = WINBIO_SETTING_SOURCE_INVALID;
	WCHAR *sourceName = NULL;

	WinBioGetLogonSetting(
		&value,			// Whether biometric domain logons are enabled
		&source			// The source of the setting
		);
	if (source == WINBIO_SETTING_SOURCE_INVALID) {
		printf("\n WinBioGetLogonSetting returned WINBIO_SETTING_SOURCE_INVALID.\n");
		hr = E_FAIL;
	}
	else if (source != WINBIO_SETTING_SOURCE_INVALID &&
		source != WINBIO_SETTING_SOURCE_DEFAULT &&
		source != WINBIO_SETTING_SOURCE_POLICY &&
		source != WINBIO_SETTING_SOURCE_LOCAL) {
		printf("\n WinBioGetLogonSetting returned garbage\n");
		hr = E_FAIL;
	}
	else {
		//printf("\n Value: %s, Source: ", value ? "TRUE" : "FALSE");
		*Value = value;
		*Source = source;
	}
	return hr;
}

HRESULT identify(WINBIO_UNIT_ID *UnitId, WINBIO_IDENTITY *Identity, WINBIO_BIOMETRIC_SUBTYPE *SubFactor)
{
	printf("\n  -- > identify() <--\n");

	HRESULT hr = S_OK;
	WINBIO_IDENTITY identity = { 0 };
	WINBIO_UNIT_ID unitId = 0;
	WINBIO_BIOMETRIC_SUBTYPE subFactor = WINBIO_SUBTYPE_NO_INFORMATION;
	WINBIO_REJECT_DETAIL rejectDetail = 0;

	hr = WinBioIdentify(
				sessionHandle,		// Session handle
				&unitId,			// Biometric unit ID
				&identity,			// User SID
				&subFactor,			// Finger sub factor
				&rejectDetail		// Rejection information
		);
	if (FAILED(hr)) {
		if (hr == WINBIO_E_UNKNOWN_ID) {
			printf("\n Unknown identity.\n");
		}
		else if (hr == WINBIO_E_BAD_CAPTURE) {
			printf("\n Bad capture; reason: %d\n", rejectDetail);
		}
		else {
			printf("\n WinBioIdentify failed. hr = 0x%x\n", hr);
		}
	}
	else {
		*UnitId = unitId;
		*Identity = identity;
		*SubFactor = subFactor;
	}

	return hr;
}

HRESULT locateSensor(WINBIO_UNIT_ID *UnitId)
{
	printf("\n  -- > locateSensor() <--\n");

	HRESULT hr = S_OK;
	WINBIO_UNIT_ID unitId = 0;

	hr = WinBioLocateSensor(sessionHandle, &unitId);
	if (FAILED(hr)) {
		printf("\n WinBioLocateSensor failed. hr = 0x%x\n", hr);
	}
	else {
		*UnitId = unitId;
		printf("\n unitId: %d\n", unitId);
	}
	return hr;
}

HRESULT lockUnit()
{
	printf("\n  -- > lockUnit() <--\n");

	HRESULT hr = S_OK;
	WINBIO_IDENTITY identity = { 0 };
	WINBIO_REJECT_DETAIL rejectDetail = 0;
	WINBIO_BIOMETRIC_SUBTYPE subFactor = WINBIO_SUBTYPE_NO_INFORMATION;
	BOOL lockAcquired = FALSE;

	hr = WinBioLockUnit(sessionHandle, getUnitId());
	if (FAILED(hr)) {
		printf("\n WinBioLockUnit failed. hr = 0x%x\n", hr);
	}
	return hr;
}

HRESULT logonIdentifiedUser()
{
	printf("\n  -- > logonIdentifiedUser() <--\n");

	HRESULT hr = S_OK;
	WINBIO_UNIT_ID unitId;
	WINBIO_IDENTITY identity;
	WINBIO_BIOMETRIC_SUBTYPE subFactor;
	WINBIO_REJECT_DETAIL rejectDetail;
	BOOL bContinue = TRUE;

	while (bContinue)
	{
		hr = WinBioIdentify(
			sessionHandle,
			&unitId,
			&identity,
			&subFactor,
			&rejectDetail
			);

		switch (hr)
		{
		case S_OK:
			bContinue = FALSE;
			break;
		default:
			printf("\n WinBioIdentify failed. hr = 0x%x\n", hr);
			return hr;
			break;
		}
	}

	if (SUCCEEDED(hr)) {
		hr = WinBioLogonIdentifiedUser(sessionHandle);

		switch (hr)
		{
		case S_FALSE:
			printf("\n Target is the logged on user. No action taken.\n");
			break;
		case S_OK:
			printf("\n Fast user switch initiated.\n");
			break;
		default:
			printf("\n WinBioLogonIdentifiedUser failed. hr = 0x%x\n", hr);
			break;
		}
	}
	return hr;
}

HRESULT openSession(WINBIO_SESSION_FLAGS Flags)
{
	printf("\n  -- > openSession() <--\n");

	HRESULT hr = S_OK;

	if (sessionHandle != NULL) {

		WinBioCloseSession(sessionHandle);
		sessionHandle = NULL;
	}

	hr = WinBioOpenSession(
		WINBIO_TYPE_FINGERPRINT,	// Service provider
		WINBIO_POOL_SYSTEM,			// Pool type
		Flags,						// Raw access
		NULL,						// Array of biometric unit IDs
		0,							// Count of biometric unit IDs
		WINBIO_DB_DEFAULT,			// Default database
		&sessionHandle				// [out] Session handle
		);

	if (FAILED(hr)) {
		printf("\n WinBioOpenSession failed. hr = 0x%x\n", hr);
	}

	return hr;
}

HRESULT removeAllCredentials()
{
	HRESULT hr = S_OK;
	hr = WinBioRemoveAllCredentials();
	if (FAILED(hr)) {
		printf("\n WinBioRemoveAllCredentials failed, hr = 0x%x\n", hr);
	}
	return hr;
}

HRESULT removeAllDomainCredentials()
{
	HRESULT hr = S_OK;

	hr = WinBioRemoveAllDomainCredentials();
	if (FAILED(hr)) {
		printf("\n WinBioRemoveAllDomainCredentials failed, hr = 0x%x\n", hr);
	}
	return hr;
}

HRESULT removeCredential()
{
	HRESULT hr = S_OK;
	WINBIO_IDENTITY identity;

	hr = GetCurrentUserIdentity(&identity);
	if (FAILED(hr)) {
		printf("\n User identity not found. hr = 0x%x\n", hr);
	}

	hr = WinBioRemoveCredential(identity, WINBIO_CREDENTIAL_ALL);
	if (FAILED(hr)) {
		printf("\n WinBioRemoveCredential failed. hr = 0x%x\n", hr);
	}
	printf("\n WinBioRemoveCredential success. hr = 0x%x\n", hr);
	return hr;
}

HRESULT unlockUnit()
{
	printf("\n  -- > unlockUnit() <--\n");

	HRESULT hr = S_OK;

	hr = WinBioUnlockUnit(sessionHandle, getUnitId());
	if (FAILED(hr)) {
		printf("\n WinBioUnlockUnit failed. hr = 0x%x\n", hr);
	}
	return hr;
}

HRESULT verify(WINBIO_BIOMETRIC_SUBTYPE SubFactor, WINBIO_UNIT_ID *UnitId, BOOLEAN *Match)
{
	printf("\n  -- > verify() <--\n");

	HRESULT hr = S_OK;
	WINBIO_UNIT_ID unitId = 0;
	WINBIO_REJECT_DETAIL rejectDetail = 0;
	WINBIO_IDENTITY identity = { 0 };
	BOOLEAN match = FALSE;

	hr = GetCurrentUserIdentity(&identity);
	if (FAILED(hr)) {
		printf("\n User ientity not found. hr = 0x%x\n", hr);
	}

	hr = WinBioVerify(
		sessionHandle,
		&identity,
		SubFactor,
		&unitId,
		&match,
		&rejectDetail);

	if (FAILED(hr)) {
		if (hr == WINBIO_E_NO_MATCH) {
			printf("\n No MATCH - identity verification failed.\n");
		}
		else if (hr == WINBIO_E_BAD_CAPTURE) {
			printf("\n Bad capture; reason: %d\n", rejectDetail);
		}
		else {
			printf("\n WinBioVerify failed. hr = 0x%x\n", hr);
		}
	}
	printf("\n Fingerprint verified: %d\n", unitId);
	printf("\n Match: %s, ", match ? "TRUE" : "FALSE");

	*UnitId = unitId;
	*Match = match;

	return hr;
}

HRESULT wait()
{
	HRESULT hr = S_OK;

	hr = WinBioWait(sessionHandle);
	if (FAILED(hr)) {
		printf("\n WinBioWait failed. hr = 0x%x\n", hr);
	}
	return hr;
}






WINBIO_UNIT_ID getUnitId()
{
	WINBIO_UNIT_ID unitId = 0;
	SIZE_T index = 0;

	if (unitCount > 0)
	{
		for (index = 0; index < unitCount; ++index) {
			unitId = unitSchema[index].UnitId;
		}
	}
	return unitId;
}

//----------------------------------------------------------------------
// The following function retrieves the identity of the current user.
// This is a helper function and is not part of the Windows Biometric
// Framework API.
//
HRESULT GetCurrentUserIdentity(__inout PWINBIO_IDENTITY Identity)
{
	HRESULT hr = S_OK;
	HANDLE tokenHandle = NULL;
	DWORD bytesReturned = 0;

	struct {
		TOKEN_USER tokenUser;
		BYTE buffer[SECURITY_MAX_SID_SIZE];
	} tokenInfoBuffer;

	// Zero the input identity and specify the type.
	ZeroMemory(Identity, sizeof(WINBIO_IDENTITY));
	Identity->Type = WINBIO_ID_TYPE_NULL;

	if (!OpenProcessToken(
				GetCurrentProcess(),	// Process handle
				TOKEN_READ,				// Read access only
				&tokenHandle))			// Access token handle
	{
		DWORD win32Status = GetLastError();
		printf("\n Cannot open token handle: %d\n", win32Status);
		hr = HRESULT_FROM_WIN32(win32Status);
		goto e_Exit;
	}

	// Zero the tokenInfoBuffer structure.
	ZeroMemory(&tokenInfoBuffer, sizeof(tokenInfoBuffer));

	if (!GetTokenInformation(
				tokenHandle,				// Access token handle
				TokenUser,					// User for the token
				&tokenInfoBuffer.tokenUser,	// Buffer to fill
				sizeof(tokenInfoBuffer),	// Size of the buffer
				&bytesReturned))			// Size needed
	{
		DWORD win32Status = GetLastError();
		printf("\n Cannot query token information: %d\n", win32Status);
		hr = HRESULT_FROM_WIN32(win32Status);
		goto e_Exit;
	}

	// Copy the SID from the tokenInfoBuffer structure to the WINBIO_IDENTITY structure.
	CopySid(SECURITY_MAX_SID_SIZE, Identity->Value.AccountSid.Data, tokenInfoBuffer.tokenUser.User.Sid);

	// Specify the size of the SID and assign WINBIO_ID_TYPE_SIZ
	// to the type member if the WINBIO_IDENTITY structure.
	Identity->Value.AccountSid.Size = GetLengthSid(tokenInfoBuffer.tokenUser.User.Sid);
	Identity->Type = WINBIO_ID_TYPE_SID;

e_Exit:
	if (tokenHandle != NULL) {
		CloseHandle(tokenHandle);
	}

	return hr;
}