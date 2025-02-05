#pragma once

struct CommandData
{
    int trigger; // �R�}���h�L�[
    int interval; // �Ԋu
};

class CommandParser
{
public:
    CommandParser()
        :start(nullptr)
        , current(nullptr)
        , remainingInterval(0) {}
    ~CommandParser() = default;

    void init(CommandData* data);

    /// <summary>
    /// �R�}���h��͂̎��s����
    /// </summary>
    /// <param name="trigger">�L�[�̃g���K�[</param>
    /// <returns>�R�}���h���͐����Ȃ�true</returns>
    bool operator()(int trigger);

private:
    CommandData* start;
    CommandData* current;
    int remainingInterval;
};
