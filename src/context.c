#include "context.h"

#include <assert.h>

static_assert(sizeof(void*) == sizeof(computation_ptr));
static_assert(sizeof(void*) == sizeof(datum_ptr));

void transmit_pointes(const id_map_type*)

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

void transmit(transmitter_ptr map, context_ptr donor, context_ptr recepient)
{
    transmitImpl(computationsMaps, donor->computations, recepient->computations);
    transmitImpl(dataMaps, donor->data, recepient->data);
}
