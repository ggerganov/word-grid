#include <iostream>
#include <string>
#include <algorithm>

#include <server/Universe.hpp>
#include <server/Game.hpp>
#include <server/Player.hpp>
#include <server/BoardProducer.hpp>

#include <core/Grid.hpp>
#include <core/Word.hpp>
#include <core/Dictionary.hpp>
#include <core/GameData.hpp>
#include <core/Scoring.hpp>
#include <core/Board.hpp>
#include <core/ScoredDictionary.hpp>

#include <core/lib/PlatformUtil.hpp>

namespace core
{
template <size_t N, typename Child>
std::ostream& operator<<(std::ostream& out, const LetterSequence<N, Child>& w)
{
    for (auto l : w)
    {
        out.put(l);
    }
    return out;
}
}

std::vector<uint8_t> readFile(const char* path)
{
    auto f = fopen(path, "rb");

    if (!f) return {};

    int pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size_t fileSize = ftell(f);
    fseek(f, pos, SEEK_SET);

    std::vector<uint8_t> r(fileSize);

    fread(r.data(), 1, fileSize, f);

    fclose(f);
    return r;
}

using namespace std;
using namespace core;
using namespace server;

class TestProducer final : public BoardProducer
{
public:
    TestProducer(const Dictionary& d)
        : m_dictionary(d)
    {}

    virtual void addGame(Game&) override {}
    virtual core::Board getBoard(const Game*) override
    {
        std::vector<WordElement> gridElements = {
            WordElement::fromAscii("o"), WordElement::fromAscii("p"), WordElement::fromAscii("w"), WordElement::fromAscii("g"),
            WordElement::fromAscii("t"), WordElement::fromAscii("s"), WordElement::fromAscii("-y"), WordElement::fromAscii("e"),
            WordElement::fromAscii("d-"), WordElement::fromAscii("i"), WordElement::fromAscii("t"), WordElement::fromAscii("r"),
            WordElement::fromAscii("e"), WordElement::fromAscii("n"), WordElement::fromAscii("s"), WordElement::fromAscii("e"),
        };

        Grid g(4, 4, chobo::make_memory_view(gridElements));
        g.acquireElementOwnership();

        ScoredDictionary sd;
        g.findAllWords(m_dictionary, sd);

        auto scoring = Scoring::flat(13);
        sd.scoreWords(g, scoring);

        return Board(std::move(g), std::move(sd), 60000);
    }
private:
    const Dictionary& m_dictionary;
};

int main()
{
    auto mpath = PlatformUtil::getModulePath();
    auto assetPath = PlatformUtil::getAssetPath(std::move(mpath), "assets");
    //auto commonDicPath = assetPath + "/dictionaries/common-en.txt";
    auto commonDicPath = assetPath + "/dictionaries/words_alpha.txt";
    auto commonDicData = readFile(commonDicPath.c_str());
    Dictionary dictionary = Dictionary::fromUtf8Buffer(chobo::make_memory_view(commonDicData));
    cout << "Dictionary words: " << dictionary.words().size() << endl;

    TestProducer producer(dictionary);

    return 0;
}
