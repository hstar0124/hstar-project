#pragma once
#include "Common.h"
#include <mysql.h>
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

#include "UserEntity.hpp"

class MySQLConnector {
private:
    std::unique_ptr<MYSQL, decltype(&mysql_close)> m_Conn;

public:
    struct Condition 
    {
        std::string column;
        std::string value;
    };

    MySQLConnector(const std::string& host, const std::string& user, const std::string& password, const std::string& db, unsigned int port = 3306);
    
    void BeginTransaction();
    void CommitTransaction();
    void RollbackTransaction();

    bool AddFriendRequest(const std::string& sender_id, const std::string& receiver_id);
    bool AddFriendship(const std::string& sender_id, const std::string& receiver_id);
    bool HasFriendRequest(const std::string& sender_id, const std::string& receiver_id);

    std::shared_ptr<UserEntity> GetUserById(const std::string& user_id);
    std::shared_ptr<UserEntity> GetUserByConditions(const std::vector<Condition>& conditions);

    void UpdateFriendAccept(const std::string& username, const std::string& newEmail);



private:
    void executePreparedStatement(const std::string& query, std::vector<std::string>& params);
};
