#pragma once

#include <type_traits>
#include <unordered_map>
#include <vector>

enum class ShaderType { FRAGMENT, GEOMETRY, VERTEX };

class ShaderProgram {
  unsigned int m_id;

  void setVal(const std::string &name, int val);
  void setVal(const std::string &name, float val);
  void setVal(const std::string &name, double val);

public:
  ShaderProgram(
      const std::vector<std::pair<ShaderType, const char *>> &shaders);

  template <typename T> void setValue(const std::string &name, T val) {
    if constexpr (std::is_integral_v<T>) {
      setVal(name, static_cast<int>(val));
    }
    else if constexpr (std::is_floating_point_v<T>) {
      if constexpr (std::is_same_v<T, float>) {
        setVal(name, val);
      }
      else {
        setVal(name, static_cast<double>(val));
      }
    }
    else {
      static_assert(true, "Not appropriate type for uniform variable.");
    }
  }

  void use();
};
