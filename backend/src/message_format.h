#pragma once

#include <string>
#include <nlohmann/json.hpp>

const std::string k_join_message_type = "JOIN";
const std::string k_leave_message_type = "LEAVE";

struct JoinMessage {
  std::string username;

  std::string serialize_join_message() const {
    nlohmann::json json = {
    {"type", k_join_message_type},
    {"username", username}
    };
    return json.dump();
  }

  static JoinMessage deserialize(const std::string& message_str) {
    auto json_parsed = nlohmann::json::parse(message_str);
    if(json_parsed["type"] == k_join_message_type) {
      JoinMessage msg;
      msg.username = json_parsed["username"].get<std::string>();
      return msg;
    } else {
      throw std::runtime_error("Invalid message type: " + json_parsed["type"].get<std::string>());
    }
  }
};

struct LeaveMessage {
  std::string username;

  std::string serialize_leave_message() const {
    nlohmann::json json = {
      {"type", k_leave_message_type},
      {"username", username}
    };
    return json.dump();
  }

  static LeaveMessage deserialize(const std::string& message_str) {
    auto json_parsed = nlohmann::json::parse(message_str);
    if(json_parsed["type"] == k_leave_message_type) {
      LeaveMessage msg;
      msg.username = json_parsed["username"].get<std::string>();
      return msg;
    } else {
       throw std::runtime_error("Invalid message type: " + json_parsed["type"].get<std::string>());
    }
  }
};

