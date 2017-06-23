#include "stdafx.h"
#include "winbio_return_code.h"

char* getReturnCode(HRESULT hr)
{
	char *returnCode = NULL;

	switch (hr)
	{
	case S_OK:
		returnCode = "Operation successful.";
		break;
	case E_ABORT:
		returnCode = "Operation aborted.";
		break;
	case E_ACCESSDENIED:
		returnCode = "General access denied error.";
		break;
	case E_FAIL:
		returnCode = "Unspecified failure.";
		break;
	case E_HANDLE:
		returnCode = "Handle that is not valid.";
		break;
	case E_INVALIDARG:
		returnCode = "One or more arguments are not valid.";
		break;
	case E_NOINTERFACE:
		returnCode = "No such interface supported";
		break;
	case E_NOTIMPL:
		returnCode = "Not implemented.";
		break;
	case E_OUTOFMEMORY:
		returnCode = "Failed to allocate necessary memory.";
		break;
	case E_POINTER:
		returnCode = "Pointer that is not valid.";
		break;
	case E_UNEXPECTED:
		returnCode = "Unexpected failure.";
		break;
	case WINBIO_E_UNSUPPORTED_FACTOR:
		returnCode = "The specified biometric factor is not supported.";
		break;
	case WINBIO_E_INVALID_UNIT:
		returnCode = "The unit ID number does not correspond to a valid biometric device.";
		break;
	case WINBIO_E_UNKNOWN_ID:
		returnCode = "The biometric sample does not match any known identity.";
		break;
	case WINBIO_E_CANCELED:
		returnCode = "The biometric operation was canceled \n\nbefore it could complete.";
		break;
	case WINBIO_E_NO_MATCH:
		returnCode = "The biometric sample does not match the specified identity or sub-factor.";
		break;
	case WINBIO_E_CAPTURE_ABORTED:
		returnCode = "A biometric sample could not be captured because the capture operation was aborted.";
		break;
	case WINBIO_E_ENROLLMENT_IN_PROGRESS:
		returnCode = "An enrollment transaction could not be started \n\nbecause another enrollment is already in progress.";
		break;
	case WINBIO_E_BAD_CAPTURE:
		returnCode = "The captured sample cannot be used for \n\nfurther biometric operations. (Bad capture)";
		break;
	case WINBIO_E_INVALID_CONTROL_CODE:
		returnCode = "The biometric unit does not support the specified unit control code.";
		break;
	case WINBIO_E_DATA_COLLECTION_IN_PROGRESS:
		returnCode = "A pending data collection operation is already in progress.";
		break;
	case WINBIO_E_UNSUPPORTED_DATA_FORMAT:
		returnCode = "The biometric sensor driver does not support the requested data format.";
		break;
	case WINBIO_E_UNSUPPORTED_DATA_TYPE:
		returnCode = "The biometric sensor driver does not support the requested data type.";
		break;
	case WINBIO_E_UNSUPPORTED_PURPOSE:
		returnCode = "The biometric sensor driver does not support the requested data purpose.";
		break;
	case WINBIO_E_INVALID_DEVICE_STATE:
		returnCode = "The biometric unit is not in the proper state to perform the specified operation.";
		break;
	case WINBIO_E_DEVICE_BUSY:
		returnCode = "The operation could not be performed because the sensor device was busy.";
		break;
	case WINBIO_E_DATABASE_CANT_CREATE:
		returnCode = "The storage adapter was not able to create a new database.";
		break;
	case WINBIO_E_DATABASE_CANT_OPEN:
		returnCode = "The storage adapter was not able to open an existing database.";
		break;
	case WINBIO_E_DATABASE_CANT_CLOSE:
		returnCode = "The storage adapter was not able to close a database.";
		break;
	case WINBIO_E_DATABASE_CANT_ERASE:
		returnCode = "The storage adapter was not able to erase a database.";
		break;
	case WINBIO_E_DATABASE_CANT_FIND:
		returnCode = "The storage adapter was not able to find a database.";
		break;
	case WINBIO_E_DATABASE_ALREADY_EXISTS:
		returnCode = "The storage adapter was not able to create a database because the specified database already exists.";
		break;
	case WINBIO_E_DATABASE_FULL:
		returnCode = "The storage adapter was not able to add a record to the database because the database is full.";
		break;
	case WINBIO_E_DATABASE_LOCKED:
		returnCode = "The database is locked and its contents are inaccessible.";
		break;
	case WINBIO_E_DATABASE_CORRUPTED:
		returnCode = "The contents of the database have become corrupted and are inaccessible.";
		break;
	case WINBIO_E_DATABASE_NO_SUCH_RECORD:
		returnCode = "No records were deleted because the specified identity and sub-factor are not present in the database.";
		break;
	case WINBIO_E_DUPLICATE_ENROLLMENT:
		returnCode = "The specified identity and sub-factor are \n\nalready enrolled in the database.";
		break;
	case WINBIO_E_DATABASE_READ_ERROR:
		returnCode = "An error occurred while trying to read from the database.";
		break;
	case WINBIO_E_DATABASE_WRITE_ERROR:
		returnCode = "An error occurred while trying to write to the database.";
		break;
	case WINBIO_E_DATABASE_NO_RESULTS:
		returnCode = "No records in the database matched the query.";
		break;
	case WINBIO_E_DATABASE_NO_MORE_RECORDS:
		returnCode = "All records from the most recent database query have been retrieved.";
		break;
	case WINBIO_E_DATABASE_EOF:
		returnCode = "A database operation unexpectedly encountered the end of the file.";
		break;
	case WINBIO_E_DATABASE_BAD_INDEX_VECTOR:
		returnCode = "A database operation failed due to a malformed index vector.";
		break;
	case WINBIO_E_INCORRECT_BSP:
		returnCode = "The biometric unit does not belong to the specified service provider.";
		break;
	case WINBIO_E_INCORRECT_SENSOR_POOL:
		returnCode = "The biometric unit does not belong to the specified sensor pool.";
		break;
	case WINBIO_E_NO_CAPTURE_DATA:
		returnCode = "The sensor adapter capture buffer is empty.";
		break;
	case WINBIO_E_INVALID_SENSOR_MODE:
		returnCode = "The sensor adapter does not support the sensor mode specified in the configuration.";
		break;
	case WINBIO_E_LOCK_VIOLATION:
		returnCode = "The requested operation cannot be performed \n\ndue to a locking conflict.";
		break;
	case WINBIO_E_DUPLICATE_TEMPLATE:
		returnCode = "The data in a biometric template matches that of \n\nanother template already in the database.";
		break;
	case WINBIO_E_INVALID_OPERATION:
		returnCode = "The requested operation is not valid for the current state of the session or the biometric unit.";
		break;
	case WINBIO_E_SESSION_BUSY:
		returnCode = "The session cannot begin a new operation \n\nbecause another operation is already in progress.";
		break;
	case WINBIO_E_CRED_PROV_DISABLED:
		returnCode = "System policy settings have disabled the biometric credential provider.";
		break;
	case WINBIO_E_CRED_PROV_NO_CREDENTIAL:
		returnCode = "The requested credential was not found.";
		break;
	case WINBIO_E_DISABLED:
		returnCode = "The requested credential was not found.";
		break;
	case WINBIO_E_CONFIGURATION_FAILURE:
		returnCode = "The biometric unit could not be configured.";
	case WINBIO_E_SENSOR_UNAVAILABLE:
		returnCode = "A private pool cannot be created because one or more biometric units are not available.";
		break;
	case WINBIO_E_SAS_ENABLED:
		returnCode = "A secure attention sequence (CTRL-ALT-DELETE) is required for logon.";
		break;
	case WINBIO_E_DEVICE_FAILURE:
		returnCode = "A biometric sensor has failed.";
		break;
	case WINBIO_E_FAST_USER_SWITCH_DISABLED:
		returnCode = ">Fast user switching is disabled.";
		break;
	case WINBIO_E_NOT_ACTIVE_CONSOLE:
		returnCode = "The System sensor pool cannot be opened from Terminal Server client sessions.";
		break;
	case WINBIO_E_EVENT_MONITOR_ACTIVE:
		returnCode = "There is already an active event monitor associated with the specified session.";
		break;
	case WINBIO_E_INVALID_PROPERTY_TYPE:
		returnCode = "The value specified is not a valid property type.";
		break;
	case WINBIO_E_INVALID_PROPERTY_ID:
		returnCode = "The value specified is not a valid property ID.";
		break;
	case WINBIO_E_UNSUPPORTED_PROPERTY:
		returnCode = "The biometric unit does not support the specified property.";
		break;
	case WINBIO_E_ADAPTER_INTEGRITY_FAILURE:
		returnCode = "The adapter did not pass its integrity check.";
		break;
	case WINBIO_I_MORE_DATA:
		returnCode = "Another sample is needed for the current enrollment template.";
		break;
	}

	return returnCode;
}