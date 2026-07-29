#ifndef MODULE_INSTANCE_ID_H
#define MODULE_INSTANCE_ID_H

#include <string>

namespace LogosCore {

// Transport routing has two distinct identities:
//
// - an explicit runtime ID selects a scoped module endpoint;
// - no runtime ID preserves the inherited process-wide endpoint.
//
// Instance persistence is storage metadata. Its directory name must never
// become a transport ID: callers that use the legacy name-only client address
// the inherited LOGOS_INSTANCE_ID, not a persistence directory component.
inline std::string resolveRuntimeInstanceId(
    const std::string& explicitInstanceId,
    const std::string& /*instancePersistencePath*/)
{
    return explicitInstanceId;
}

} // namespace LogosCore

#endif // MODULE_INSTANCE_ID_H
