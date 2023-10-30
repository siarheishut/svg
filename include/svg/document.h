#ifndef SVG_DOCUMENT_H_
#define SVG_DOCUMENT_H_

#include <ostream>
#include <vector>

#include "figures.h"

namespace svg {
class Document final {
 public:
  Document() = default;

  void Add(const Object &object);
  void Add(Object &&object);
  void Render(std::ostream &out) const;

 private:
  std::vector<Object> objects_;
};
}

#endif // SVG_DOCUMENT_H_
