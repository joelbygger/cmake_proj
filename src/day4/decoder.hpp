//
// Created by joel on 2019-03-22.
//

#ifndef ADVENTOFCODE2018_DECODER_HPP
#define ADVENTOFCODE2018_DECODER_HPP

#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace log
{
    /**
     * Where decoded logs are stored.
     * First: Id of the santa this log belongs to.
     * Second: Vector of minutes (60), each will contains the
     * number of times the elf has been asleep that minute.
     */
    using storage = std::map<int, std::vector<int>>;
} // namespace log

/**
 * Decodes a file with logs, places decoded stuff in storage, owned by caller.
 */
class decoder
{
public:
    decoder(log::storage& logs) : m_currId(0), m_state(states::start), m_logs(logs), m_asleepMin(0), m_awakeMin(0){}
    /**
     * Run state machine once.
     * @param log Input, a log line.
     */
    void run(const std::string& log);

private:
    void runStateTransitions(const std::string& log);
    void runStateSupervision(const std::string& log);

    enum class states
    {
        start,
        id,
        sleep,
        awake,
        end
    };

    int m_currId;
    states m_state;
    log::storage& m_logs;
    int m_asleepMin;
    int m_awakeMin;
};

#endif // ADVENTOFCODE2018_DECODER_HPP
