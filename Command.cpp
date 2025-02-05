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
            // �I���R�[�h�܂ł��ǂ蒅����
            return true;
        }
        current++;
    }
    return false;
}