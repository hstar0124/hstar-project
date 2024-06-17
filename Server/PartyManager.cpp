#include "PartyManager.h"


PartyManager::PartyManager()
{
}

PartyManager::~PartyManager()
{
    m_MapParties.clear(); // 모든 파티 제거
}

std::shared_ptr<Party> PartyManager::CreateParty(std::shared_ptr<User> user, const std::string& partyName)
{
    if (user == nullptr || partyName == "")
    {
        std::cout << "[SERVER] Invalid Party Name" << std::endl;
        return nullptr;
    }


    auto party = std::make_shared<Party>(m_PartyIdCounter++, user->GetID(), partyName); // 파티 생성
    party->AddMember(user->GetID());                                                    // 파티 생성자를 파티 멤버로 추가
    m_MapParties[party->GetId()] = party;                                               // 파티를 해시 맵에 추가

    std::cout << "Party Count : " << m_MapParties.size() << "\n";
    return party;
}

bool PartyManager::DeleteParty(std::shared_ptr<User> user, const std::string& partyName)
{
    // 파티 이름에 해당하는 파티를 찾음|
    auto party = FindPartyByName(partyName);
    if (!party)
    {
        std::cout << "[SERVER] Not found party: " << partyName << std::endl;
        return false;
    }

    // 파티가 존재하고 파티 창설자인 경우
    if (party->GetPartyCreator() == user->GetID())
    {
        m_MapParties.erase(party->GetId()); // 파티를 해시 맵에서 삭제
        std::cout << "[SERVER] Deleted party: " << partyName << std::endl;
    }
    else
    {
        std::cout << "[SERVER] Fail Deleted Party : " << partyName << std::endl;
        return false;
    }

    std::cout << "Party Count : " << m_MapParties.size() << "\n";
    return true;
}

bool PartyManager::LeaveParty(std::shared_ptr<User> user, const std::string& partyName)
{
    auto party = FindPartyByName(partyName);
    if (!party)
    {
        std::cout << "[SERVER] Not found party: " << partyName << std::endl;
        return false;
    }


    if (party->GetPartyCreator() == user->GetID())
    {
        std::cout << "[SERVER] Sorry, as the party leader, you cannot leave the party. Deletion is the only option." << std::endl;        
        return false;
    }

    return true;
}

bool PartyManager::HasParty(uint32_t partyId)
{
    return m_MapParties.find(partyId) != m_MapParties.end();
}


std::shared_ptr<Party> PartyManager::FindPartyById(uint32_t partyId)
{
    auto it = m_MapParties.find(partyId);
    if (it != m_MapParties.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

std::shared_ptr<Party> PartyManager::FindPartyByName(const std::string& partyName)
{
    for (const auto& entry : m_MapParties)
    {
        if (entry.second->GetName() == partyName)
        {
            return entry.second;
        }
    }
    return nullptr;
}


bool PartyManager::IsPartyNameTaken(const std::string& partyName)
{
    for (const auto& pair : m_MapParties)
    {
        if (pair.second->GetName() == partyName)
        {
            return true;
        }
    }
    return false;
}