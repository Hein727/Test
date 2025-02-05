#pragma once

struct CommandData
{
    int trigger; // コマンドキー
    int interval; // 間隔
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
    /// コマンド解析の実行処理
    /// </summary>
    /// <param name="trigger">キーのトリガー</param>
    /// <returns>コマンド入力成功ならtrue</returns>
    bool operator()(int trigger);

private:
    CommandData* start;
    CommandData* current;
    int remainingInterval;
};
