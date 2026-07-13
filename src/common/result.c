#include "common/result.h"

#include <errno.h>

const char *result_string(Result result) {
    switch (result) {

    case kResultOk:
        return "success";

    case kResultInvalidArgument:
        return "invalid argument";

    case kResultInvalidConfiguration:
        return "invalid configuration";

    case kResultInvalidState:
        return "invalid state";

    case kResultNotSupported:
        return "not supported";

    case kResultNotFound:
        return "not found";

    case kResultAlreadyExists:
        return "already exists";

    case kResultPermissionDenied:
        return "permission denied";

    case kResultSystemError:
        return "system error";

    default:
        return "unknown error";

    }
}

Result result_errno_to_result(void) {
    switch (errno) {

    case ENOENT:
        return kResultNotFound;

    case EEXIST:
        return kResultAlreadyExists;

    case EACCES:
    case EPERM:
        return kResultPermissionDenied;

    default:
        return kResultSystemError;

    }
}

