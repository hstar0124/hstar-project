#pragma once
#include "Common.h"
#include "TcpSession.h"

class Party : public std::enable_shared_from_this<Party>
{
private:
    uint32_t m_PartyId;
    std::string m_PartyName;
    uint32_t m_PartyCreator;
    std::vector<uint32_t> m_Members;

public:
    Party(uint32_t partyId, uint32_t creator, const std::string& partyName);

    uint32_t GetId() const { return m_PartyId; }
    uint32_t GetPartyCreator() const { return m_PartyCreator; }
    std::string GetName() const { return m_PartyName; }
    bool SetPartyName(const std::string& partyName) { m_PartyName = partyName; }

    const std::vector<uint32_t>& GetMembers() const;
    bool AddMember(uint32_t sessionId);
    bool HasMember(uint32_t sessionId) const;
    bool RemoveMember(uint32_t sessionId);    
    
    void PrintMembers() const;
};