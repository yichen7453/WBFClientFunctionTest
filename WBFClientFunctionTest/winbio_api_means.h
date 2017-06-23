
#define str_cancel "Cancels all pending biometric operations for a specified session.";
#define str_captureSample "Captures a biometric sample and fills a biometric information record (BIR) with the raw or processed data.";
#define str_closeSession "Closes a biometric session and releases associated resources.";

#define str_deleteTemplate "Deletes a biometric template from the template store.";

#define str_enrollBegin "Initiates a biometric enrollment sequence and creates an empty biometric template.";
#define str_enrollCapture "Captures a biometric sample and adds it to a template.";
#define str_enrollCommit "Finalizes a pending biometric template and saves it to the database associated with the biometric unit used for enrollment.";
#define str_enrollDiscard "Ends the enrollment sequence and discards a pending biometric template.";
#define str_enrollSelect "Specifies the individual that you want to enroll when data that represents multiple individuals is present in the sample buffer.";
#define str_enumBiometricUnits "Enumerates all attached biometric units that match the input type.";
#define str_enumDatabases "Enumerates all registered databases that match a specified type.";
#define str_enumEnrollments "Retrieves the biometric sub-factors enrolled for a specified identity and biometric unit.";
#define str_enumServiceProviders "Retrieves information about installed biometric service providers.";

#define str_free "Releases memory allocated for the client application by an earlier call to a Windows Biometric Framework API function.";

#define str_getCredentialState "Retrieves a value that specifies whether credentials have been set for the specified user.";
#define str_getDomainLogonSetting "Retrieves a value that specifies whether users can log on to a domain by using biometric information.";
#define str_getEnabledSetting "Retrieves a value that specifies whether the Windows Biometric Framework is currently enabled.";
#define str_getEnrolledFactors "Gets information about the biometric enrollments that the specified user has on the computer.";
#define str_getLogonSetting "Retrieves a value that indicates whether users can log on by using biometric information.";
#define str_getProperty "Retrieves a session, unit, or template property.";

#define str_identify "Captures a biometric sample and determines whether it matches an existing biometric template.";

#define str_locateSensor "Retrieves the ID number of a biometric unit selected interactively by a user.";
#define str_lockUnit "Locks a biometric unit for exclusive use by a single session.";
#define str_logonIdentifiedUser "Causes a fast user switch to the account associated with the last successful identification operation performed by the biometric session.";

#define str_monitorPresence "Turns on the face-recognition or iris-monitoring mechanism for the specified biometric unit.";

#define str_openSession "Connects to a biometric service provider and one or more biometric units.";

#define str_registerEventMonitor "Registers a callback function to receive event notifications from the service provider associated with an open session.";
#define str_releaseFocus "Releases window focus.";
#define str_removeAllCredentials "Removes all credentials from the store.";
#define str_removeAllDomainCredentials "Removes all user credentials for the current domain from the store.";
#define str_removeCredential "Deletes a biometric logon credential for a specified user.";

#define str_setCredential "Saves a biometric logon credential for the current user.";
#define str_setProperty "Sets the value of a standard property associated with a biometric session, unit, template, or account.";

#define str_unlockUnit "Releases the session lock on the specified biometric unit.";
#define str_unregisterEventMonitor "Cancels event notifications from the service provider associated with an open biometric session.";

#define str_verify "Captures a biometric sample and determines whether the sample corresponds to the specified user identity.";

#define str_wait "Blocks caller execution until all pending biometric operations for a session have been completed or canceled.";
