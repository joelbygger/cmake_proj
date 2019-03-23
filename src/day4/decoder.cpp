//
// Created by joel on 2019-03-22.
//

#include "decoder.hpp"
#include <cstddef>
#include <stdexcept>
#include <vector>

/*************************************************
 *
 * Public functions.
 *
 ************************************************/
void decoder::run(const std::string& log)
{
    runStateTransitions(log);
    runStateSupervision(log);
}

/*************************************************
 *
 * Private functions.
 *
 ************************************************/
void decoder::runStateTransitions(const std::string& log)
{
    switch (m_state) {
    case states::start: {
        auto itPos = log.find_first_of('#');
        if (itPos != std::string::npos) {
            m_state = states::id;
        }
        else {
            throw std::runtime_error(std::string("Ill formed ID line: ") + log);
        }
    } break;

    case states::id: {
        auto itPos = log.find_first_of('#');
        if (itPos != std::string::npos) {
            m_state = states::id;
        }
        else {
            itPos = log.find_first_of("falls asleep");
            if (itPos != std::string::npos) {
                m_state = states::sleep;
            }
            else {
                throw std::runtime_error(std::string("Ill formed ID/ sleep line: ") + log);
            }
        }
    } break;

    case states::sleep: {
        auto itPos = log.find_first_of("wakes up");
        if (itPos != std::string::npos) {
            m_state = states::awake;
        }
        else {
            throw std::runtime_error(std::string("Ill formed wake up: ") + log);
        }
        break;
    }

    case states::awake: {
        auto itPos = log.find_first_of('#');
        if (itPos != std::string::npos) {
            m_state = states::id;
        }
        else {
            itPos = log.find_first_of("falls asleep");
            if (itPos != std::string::npos) {
                m_state = states::sleep;
            }
            else {
                throw std::runtime_error(std::string("Ill formed ID/ sleep line: ") + log);
            }
        }
        break;
    }
    }
}

void decoder::runStateSupervision(const std::string& log)
{
    switch (m_state) {
    case states::start:
        throw std::runtime_error(std::string("I don't think we should ever be in start state when doing supervision, log: ") + log);
        // break;
    case states::id: {
        auto itPos = log.find_first_of('#');
        m_currId = stoi(log.substr(itPos + 1));

        // If ID is missing add vector of size 60 initialized to 0, if ID exists nothing happens.
        m_logs.try_emplace(m_currId, 60, 0);
        break;
    }
    case states::sleep: {
        auto itPos = log.find_first_of(':'); // TODO(joel) inline in substr and search using regexp during transition?
        m_asleepMin = stoi(log.substr(itPos + 1));
        break;
    }
    case states::awake: {
        auto itPos = log.find_first_of(':');
        m_awakeMin = stoi(log.substr(itPos + 1));

        for (int j = m_asleepMin; j < m_awakeMin; ++j) {
            m_logs.at(m_currId).at(static_cast<size_t>(j))++;
        }
        break;
    }
    }
}
