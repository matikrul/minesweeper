#pragma once

#include <ai/decision/ActionCandidate.hpp>
#include <ai/decision/ModelOutput.hpp>

namespace minesweeper {

/**
 * @brief Interface that converts a particular model output format into moves.
 *
 * This keeps `ActionDecoder` independent of the model tensor layout. An
 * implementation creates candidates but does not decide which one to choose.
 */
class IActionInterpreter
{
public:
    virtual ~IActionInterpreter() = default;

    /** @brief Converts raw model output into scored moves. */
    virtual ActionCandidates interpret(const ModelOutput& output) const = 0;
};

} // namespace minesweeper
