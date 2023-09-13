#ifndef SVG_DOCUMENT_H_
#define SVG_DOCUMENT_H_

#include <ostream>
#include <variant>
#include <vector>

#include "figures.h"

namespace svg {
using Object = std::variant<Circle, Polyline, Text>;

class Document {
 public:
  Document() = default;

  void Add(const Object &figure);
  void Add(Object &&figure);
  void Render(std::ostream &out) const;

 private:
  std::vector<Object> objects_;
};
}

#endif // SVG_DOCUMENT_H_
