#include <ai/decision/ActionDecoder.hpp>

namespace minesweeper {

Action ActionDecoder::decode(const ModelOutput& output) const
{
    const auto candidates = _interpreter->interpret(output);
    return _strategy->select(candidates);
}

} // namespace minesweeper