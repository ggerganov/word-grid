set(src)
src_group(lib src
    lib/UnicodeCharFromUtf8.hpp
    lib/PlatformUtil.cpp
    lib/PlatformUtil.hpp
)
src_group(core src
    Types.hpp
    LetterSequence.hpp
    Word.hpp
    WordTraits.hpp
    WordElement.hpp
    WordElement.cpp
    WordElementTraits.hpp
    Dictionary.cpp
    Dictionary.hpp
    DictionarySearch.hpp
    Grid.cpp
    Grid.hpp
    GridCoord.hpp
    Scoring.hpp
    Scoring.cpp
    Board.cpp
    Board.hpp
    GameData.cpp
    GameData.hpp
    ScoredDictionary.cpp
    ScoredDictionary.hpp
    ScoredWord.hpp
)

add_library(core STATIC
    ${src}
)

target_include_directories(core INTERFACE ..)

target_link_libraries(core PUBLIC
    chobo-shl
    ${CMAKE_DL_LIBS}
)


