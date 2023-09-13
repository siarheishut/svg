#ifndef SVG_COMMON_H_
#define SVG_COMMON_H_

#include <ostream>
#include <cstdint>
#include <variant>
#include <string>

namespace svg {
struct Point {
  double x = 0.0;
  double y = 0.0;
};

struct Rgb {
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
};

struct Rgba {
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  double alpha = 1.0;
};

using Color = std::variant<std::monostate, std::string, Rgb, Rgba>;

std::ostream &operator<<(std::ostream &out, const Color &col);

static const Color kNoneColor;
}

#endif // SVG_COMMON_H_
