#pragma once

#include <string>

class Texture {
  unsigned int m_id;

public:
  Texture(const std::string& filename);
  template<unsigned char> void use() {
    static_assert(true, "Not allowed texture number.");
  }
};
