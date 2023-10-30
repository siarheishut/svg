#include "svg/document.h"

#include <ostream>
#include <utility>
#include <variant>

#include "svg/figures.h"

namespace svg {
void Document::Add(const Object &object) {
  objects_.push_back(object);
}
void Document::Add(Object &&object) {
  objects_.push_back(std::move(object));
}

void Document::Render(std::ostream &out) const {
  out << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
         "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">";

  for (auto &object : objects_) {
    std::visit([&out](auto &&obj) {
      obj.Render(out);
    }, object);
  }

  out << "</svg>";
}
}
