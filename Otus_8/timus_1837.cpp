#include <cctype>
#include <map>
#include <set>
#include <string>
#include <iostream> 
#include <vector>
#include <functional>
#include <algorithm>
#include <cstring>

namespace mystr {
    bool IsCorrectNumber(const char* aStr) {
        const auto len = strlen(aStr);
        for (auto i = 0U; i < len; i++) {
            if (!std::isdigit(aStr[i]))
                return false;
        }
        return true;
    }

    bool IsCorrectNumber(const std::string& aStr) {
        return IsCorrectNumber(aStr.c_str());
    }

    bool IsCorrectSurname(const std::string& aStr) {
        if (aStr.empty())
            return false;
        if (!std::isupper(aStr[0]))
            return false;

        for (auto i = 1U; i < aStr.size(); i++) {
            if (!std::islower(aStr[i]))
                return false;
        }
        return true;
    }

    std::vector<std::string> GetTokens(std::string aStr, const std::string& aDelimeters) {
        std::vector<std::string> tokens;
        char* str = (char*)aStr.c_str();
        char * pch = strtok(str, aDelimeters.c_str());
        while (pch) {
            if ((pch != nullptr))
                tokens.push_back(std::string(pch));
            pch = strtok(NULL, aDelimeters.c_str());
        }
        return tokens;
    }
}

namespace {
    using team_t = std::set<std::string>;
    using players_t = std::map<std::string, std::size_t>;
    const std::string kIsenbaev = "Isenbaev";
}

struct TeamWeight {
    static const std::size_t Undefined = -1;
    team_t Team;
    std::size_t Weight = Undefined;
};

team_t GetTeam(const std::string& aTeamStr, players_t& aPlayers) {
    team_t team;
    auto players = mystr::GetTokens(aTeamStr, " ");
    if (players.size() != 3)
        return {};
    for (const auto& player : players){
        if (team.find(player) != team.end())
            return {}; //Нет места однофамильцам в команде
        aPlayers[player] = TeamWeight::Undefined;
        team.insert(player);
    }
    return team;
}

void CalcWeight(std::vector<TeamWeight>& aTeams, const std::string& aPlayer, const std::size_t aWeight, players_t& aAllPlayers) {
    aAllPlayers[aPlayer] = std::min(aAllPlayers[aPlayer], aWeight);
    for (auto& team : aTeams) {
        if (team.Team.find(aPlayer) != team.Team.end()) {
            if (aWeight >= team.Weight)
                continue;
            team.Weight = aWeight;
            for (const auto& teamMate : team.Team) {
                if (teamMate == aPlayer)
                    continue;
                CalcWeight(aTeams, teamMate, aWeight + 1, aAllPlayers);
            }
        }
    }
}

players_t GetPlayersWeight(const std::vector<std::string>& aTeamList) {
    if (aTeamList.empty() || aTeamList.size() > 100)
        return {};
    std::vector<TeamWeight> teams;
    players_t allPlayers;
    for (const auto& str : aTeamList) {
        auto team = GetTeam(str, allPlayers);
        if (team.empty())
            return {};
        teams.push_back({ team, (std::size_t)(-1)});
    }

    if (allPlayers.find(kIsenbaev) == allPlayers.end())
        return allPlayers;
    CalcWeight(teams, kIsenbaev, 0, allPlayers);
    return allPlayers;
}

bool GetTeamsNumber(const std::string& aStr, std::size_t& aSize) {
    if (!mystr::IsCorrectNumber(aStr))
        return false;
    aSize = std::atoi(aStr.c_str());
    if (aSize < 1 || aSize > 100)
        return false;
    return true;
}

int main() {

    std::string str;
    std::size_t size = 0;
    std::size_t counter = 0;
    std::getline(std::cin, str);
    if (!GetTeamsNumber(str, size))
        return 0;

    std::vector<std::string> teams;

    while (((counter++) < size) && std::getline(std::cin, str)) {
        teams.push_back(str);
    }

    auto players = GetPlayersWeight(teams);

    for (const auto& player : players) {
        const auto& surname = player.first;
        const auto& weight = player.second;
        std::string weightStr = weight != TeamWeight::Undefined ? std::to_string(weight) : "undefined";
        std::cout << surname << " " << weightStr << std::endl;
    }
    return 0;
}

int Test() {
    std::size_t teamsNum = 7;
    std::vector<std::string> teams = {
        "Isenbaev Oparin Toropov",
        "Ayzenshteyn Oparin Samsonov",
        "Ayzenshteyn Chevdar Samsonov",
        "Fominykh Isenbaev Oparin",
        "Dublennykh Fominykh Ivankov",
        "Burmistrov Dublennykh Kurpilyanskiy",
        "Cormen Leiserson Rivest"
    };

    if (teamsNum != teams.size()) {
        return 0;
    }

    GetPlayersWeight(teams);
    return 0;
}
