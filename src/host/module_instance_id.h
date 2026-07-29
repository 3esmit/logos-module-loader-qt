#ifndef MODULE_INSTANCE_ID_H
#define MODULE_INSTANCE_ID_H

#include <filesystem>
#include <string>

namespace LogosCore {

// The container owns an explicit instance ID. Older callers only provide an
// instance-persistence path, whose final directory component is the existing
// runtime identity convention. Resolve that compatibility form before any
// transport endpoint is bound.
inline std::string resolveRuntimeInstanceId(
    const std::string& explicitInstanceId,
    const std::string& instancePersistencePath)
{
    if (!explicitInstanceId.empty()) return explicitInstanceId;

    std::filesystem::path candidate(instancePersistencePath);
    while (!candidate.empty()) {
        const std::string filename = candidate.filename().string();
        if (!filename.empty() && filename != ".") return filename;

        const std::filesystem::path parent = candidate.parent_path();
        if (parent == candidate) break;
        candidate = parent;
    }

    return {};
}

} // namespace LogosCore

#endif // MODULE_INSTANCE_ID_H
