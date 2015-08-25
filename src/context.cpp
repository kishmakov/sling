#include "sling/context.h"

#include "sling/computation.h"
#include "sling/datum.h"

#include <assert.h>

namespace sling {

template<typename T>
void transmitImpl(
    const std::vector<IdMap>& idMaps,
    std::vector<std::unique_ptr<T>>& src,
    std::vector<std::unique_ptr<T>>& dst)
{
    uint32_t maxToId = 0;

    for (auto idMap: idMaps) {
        assert(src.size() > idMap.from);
        maxToId = std::max(maxToId, idMap.to);
    }

    if (maxToId > dst.size())
        dst.resize(maxToId);

    for (auto idMap: idMaps)
        dst[idMap.to].reset(src[idMap.from].release());
}

void Transmitter::transmit(Context& donor, Context& recepient) const
{
    transmitImpl(computationsMaps, donor.computations, recepient.computations);
    transmitImpl(dataMaps, donor.data, recepient.data);
}

} // sling
