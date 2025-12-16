#pragma once

#include <algorithm>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

class ConsoleVar
{
 public:
  
  class Type {
   public:
    Type() = delete;

    ~Type() = default;
    
    Type(const Type&) = delete;
    Type& operator=(const Type&) = delete;

    Type(Type&&) = delete;
    Type& operator=(Type&&) = delete;

    operator bool() const {
      return ConsoleVar::GetBool(m_name);
    }
    
    operator int() const {
      return ConsoleVar::GetInt(m_name);
    }
    
    operator float() const {
      return ConsoleVar::GetFloat(m_name);
    }
    
    operator std::string() const {
      return ConsoleVar::GetString(m_name);
    }

    friend class ConsoleVar;

   private:
    Type(const std::string& name) : m_name(name) {
    }

    const std::string m_name;
  };
  
  ConsoleVar(const ConsoleVar&) = delete;
  ConsoleVar& operator=(const ConsoleVar&) = delete;

  ConsoleVar(ConsoleVar&&) = delete;
  ConsoleVar& operator=(ConsoleVar&&) = delete;

#pragma region GENERIC GET/SET
  static Type
  Get(const std::string& name) {
    return Type(name);
  }

  static bool
  Get(const std::string& name, const bool defaultValue) {
    return GetBool(name, defaultValue);
  }

  static int
  Get(const std::string& name, const int defaultValue) {
    return GetInt(name, defaultValue);
  }

  static float
  Get(const std::string& name, const float defaultValue) {
    return GetFloat(name, defaultValue);
  }
  
  static std::string
  Get(const std::string& name, const char* defaultValue) {
    return GetString(name, std::string(defaultValue));
  }

  static std::string
  Get(const std::string& name, const std::string& defaultValue) {
    return GetString(name, defaultValue);
  }

  static bool
  Set(const std::string& name, const bool value) {
    return SetBool(name, value);
  }

  static int
  Set(const std::string& name, const int value) {
    return SetInt(name, value);
  }

  static float
  Set(const std::string& name, const float value) {
    return SetFloat(name, value);
  }
  
  static std::string
  Set(const std::string& name, const char* value) {
    return SetString(name, std::string(value));
  }

  static std::string
  Set(const std::string& name, const std::string& value) {
    return SetString(name, value);
  }

  template<typename T>
  static void Set(const std::string& name, T value) = delete;
#pragma endregion

#pragma region GET/SET BOOL
  static bool
  GetBool(const std::string& name, const bool defaultValue = false) {
    ConsoleVar& instance = GetInstance();

    auto it = instance.m_bools.find(name);
    if (it != instance.m_bools.end())
      return it->second;

    return SetBool(name, defaultValue);
  }

  static bool
  SetBool(const std::string& name, const bool value) {
    ConsoleVar& instance = GetInstance();

    if (name.empty())
      throw std::runtime_error("Console var name cannot be empty!");
    
    auto [it, inserted] = instance.m_bools.try_emplace(name, value);
    if (inserted) {
      if (instance.m_ints.count(name) || 
          instance.m_floats.count(name) || 
          instance.m_strings.count(name)) {
        instance.m_bools.erase(it);
        throw std::runtime_error("Console var name is already used in another type!");
      }
    }
    else {
      it->second = value;
    }
    
    return it->second;
  }
#pragma endregion

#pragma region GET/SET INT
  static int
  GetInt(const std::string& name, const int defaultValue = 0) {
    ConsoleVar& instance = GetInstance();

    auto it = instance.m_ints.find(name);
    if (it != instance.m_ints.end())
      return it->second;

    return SetInt(name, defaultValue);
  }

  static int
  SetInt(const std::string& name, const int value) {
    ConsoleVar& instance = GetInstance();

    if (name.empty())
      throw std::runtime_error("Console var name cannot be empty!");
    
    auto [it, inserted] = instance.m_ints.try_emplace(name, value);
    if (inserted) {
      if (instance.m_bools.count(name) || 
          instance.m_floats.count(name) || 
          instance.m_strings.count(name)) {
        instance.m_ints.erase(it);
        throw std::runtime_error("Console var name is already used in another type!");
      }
    }
    else {
      it->second = value;
    }
    
    return it->second;
  }
#pragma endregion

#pragma region GET/SET FLOAT
  static float
  GetFloat(const std::string& name, const float defaultValue = 0) {
    ConsoleVar& instance = GetInstance();

    auto it = instance.m_floats.find(name);
    if (it != instance.m_floats.end())
      return it->second;

    return SetFloat(name, defaultValue);
  }

  static float
  SetFloat(const std::string& name, const float value) {
    ConsoleVar& instance = GetInstance();
    
    if (name.empty())
      throw std::runtime_error("Console var name cannot be empty!");
    
    auto [it, inserted] = instance.m_floats.try_emplace(name, value);
    if (inserted) {
      if (instance.m_bools.count(name) || 
          instance.m_ints.count(name) || 
          instance.m_strings.count(name)) {
        instance.m_floats.erase(it);
        throw std::runtime_error("Console var name is already used in another type!");
      }
    }
    else {
      it->second = value;
    }
    
    return it->second;
  }
#pragma endregion

#pragma region GET/SET STRING
  static std::string
  GetString(const std::string& name, const std::string& defaultValue = "") {
    ConsoleVar& instance = GetInstance();

    auto it = instance.m_strings.find(name);
    if (it != instance.m_strings.end())
      return it->second;

    return SetString(name, defaultValue);
  }

  static std::string
  SetString(const std::string& name, const std::string& value) {
    ConsoleVar& instance = GetInstance();

    if (name.empty())
      throw std::runtime_error("Console var name cannot be empty!");
    
    auto [it, inserted] = instance.m_strings.try_emplace(name, value);
    if (inserted) {
      if (instance.m_bools.count(name) || 
          instance.m_ints.count(name) || 
          instance.m_floats.count(name)) {
        instance.m_strings.erase(it);
        throw std::runtime_error("Console var name is already used in another type!");
      }
    }
    else {
      it->second = value;
    }
    
    return it->second;
  }
#pragma endregion

  static std::vector<std::string>
  GetAllVarNames() {
    ConsoleVar& instance = GetInstance();

    std::vector<std::string> names;
    for (const auto& [name, _] : instance.m_bools)
      names.push_back(name);

    for (const auto& [name, _] : instance.m_ints)
      names.push_back(name);

    for (const auto& [name, _] : instance.m_floats)
      names.push_back(name);

    for (const auto& [name, _] : instance.m_strings)
      names.push_back(name);

    std::sort(names.begin(), names.end());

    return names;
  }

 private:
  ConsoleVar() = default;

  ~ConsoleVar() = default;

  static ConsoleVar&
  GetInstance() {
    static ConsoleVar instance;
    return instance;
  }

  std::unordered_map<std::string, bool>         m_bools;
  std::unordered_map<std::string, int>          m_ints;
  std::unordered_map<std::string, float>        m_floats;
  std::unordered_map<std::string, std::string>  m_strings;
};