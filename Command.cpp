#include "Command.h"

void CommandParser::init(CommandData* data)
{
    start = current = data;
    remainingInterval = 0;
}

bool CommandParser::operator()(int trigger)
{
    if (--remainingInterval <= 0)
    {
        current = start;
        remainingInterval = 0;
    }

    if (trigger && trigger == current->trigger)
    {
        remainingInterval = current->interval;
        if (remainingInterval == 0)
        {
            // 終了コードまでたどり着いた
            return true;
        }
        current++;
    }
    return false;
}