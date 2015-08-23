#pragma once

#include <memory>
#include <vector>

namespace sling {

struct Computation;
typedef std::unique_ptr<Computation> ComputationUPtr;

struct Datum;
typedef std::unique_ptr<Datum> DatumUPtr;

struct Determinacy
{
    std::vector<ComputationUPtr> computations;
    std::vector<DatumUPtr> data;
};

typedef std::unique_ptr<Determinacy> DeterminacyUPtr;

typedef uint32_t Index;

struct IdMap
{
    Index from;
    Index to;
};

struct Transmitter
{
    std::vector<IdMap> computationsMaps;
    std::vector<IdMap> dataMaps;

    void transmit(Determinacy& donor, Determinacy& recepient) const;
};

typedef std::unique_ptr<Transmitter> TransmitterUPtr;

} // sling