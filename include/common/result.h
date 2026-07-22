#pragma once

typedef enum {
    /* Success */
    kResultOk = 0,
    
    /* Exit program without error (used in --help) */
    kResultExitSuccess,

    /* Configuration errors */
    kResultInvalidArgument,
    kResultInvalidConfiguration,
    kResultInvalidState,
    kResultNotSupported,

    /* Environment errors */
    kResultNotFound,
    kResultAlreadyExists,
    kResultNotDirectory,
    kResultPermissionDenied,
    kResultSystemError,

} Result;

const char *result_string(Result result);

Result result_errno_to_result(void);

