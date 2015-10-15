#pragma once

#include <memory>
#include <vector>

namespace sling {

struct Computation;
typedef std::unique_ptr<Computation> ComputationUPtr;

struct Datum;
typedef std::unique_ptr<Datum> DatumUPtr;

struct Context
{
    std::vector<ComputationUPtr> computations;
    std::vector<DatumUPtr> data;
};

typedef Context* ContextPtr;
typedef std::unique_ptr<Context> ContextUPtr;

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

    void transmit_move(ContextPtr donor, ContextPtr recepient) const;
};

typedef std::unique_ptr<Transmitter> TransmitterUPtr;

inline void print_st(const std::string& fileName)
{
    using namespace std;
    ofstream fout(fileName, ios::app);

   auto positions =  backtrace();

   int i = 0;

   for (auto position: positions) {
        if (++i <= 2)
            continue;

        auto SL = translate(position);
        auto functionName = SL.functionName();
        if (functionName.find("renderer6") != string::npos) {
            functionName = functionName.substr(functionName.find("renderer6") + 8);
        } else if (functionName.find("tilerenderer5") != string::npos) {
            functionName = functionName.substr(functionName.find("tilerenderer5") + 12);
        }

        if (functionName.find("(") != string::npos) {
            functionName = functionName.substr(0, functionName.find("("));
        }

        auto fileName = SL.fileName();
        if (fileName.rfind("/") != string::npos) {
            fileName = fileName.substr(fileName.rfind("/") + 1);
        }
        fout << "        ->" << functionName << " @ " << fileName << ":" << SL.lineNumber() << endl;

        if (i >= 6)
            break;
   }
}

} // sling