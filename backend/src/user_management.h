#pragma once

#include <unordered_map>
#include <string>

class User {
public:
  User(const std::string& name);

  const std::string& get_name() const;
  void set_name(const std::string& name);

  bool get_document_state() const;
  void set_document_state(bool state);

private:
  std::string name_;
  bool document_state_;
};

class UserManager {
public:
  static bool user_exists(const std::string& name);
  void add_user(const std::string& name);
  void remove_user(const std::string& name);
  void update_document_state(const std::string& name, bool state);

  const User* get_user(const std::string& name) const;

private:
  std::unordered_map<std::string, User> users_;
};

#endif /* USER_MANAGER_H */
