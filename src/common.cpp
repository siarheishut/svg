#include "common.h"

#include <ostream>
#include <variant>

namespace svg {
std::ostream &operator<<(std::ostream &out, const Color &col) {
  if (std::holds_alternative<std::monostate>(col)) {
    out << "none";
  } else if (std::holds_alternative<std::string>(col)) {
    out << std::get<std::string>(col);
  } else if (std::holds_alternative<Rgb>(col)) {
    auto rgb = std::get<Rgb>(col);
    out << "rgb(" << static_cast<int>(rgb.red) << ',' <<
        static_cast<int>(rgb.green) << ',' << static_cast<int>(rgb.blue) << ')';
  }
  return out;
}
}
