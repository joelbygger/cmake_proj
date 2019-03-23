//
// Created by joel on 2019-03-22.
//

#ifndef ADVENTOFCODE2018_DECODER_HPP
#define ADVENTOFCODE2018_DECODER_HPP

#include "logs.hpp"
#include <string>

/**
 * Decodes a file with logs, places decoded stuff in storage, owned by caller.
 */
class decoder
{
public:
    decoder(logs::storage& logs) : m_currId(0), m_state(states::start), m_logs(logs), m_asleepMin(0), m_awakeMin(0) {}
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
        awake
    };

    int m_currId;
    states m_state;
    logs::storage& m_logs;
    int m_asleepMin;
    int m_awakeMin;
};

#endif // ADVENTOFCODE2018_DECODER_HPP
