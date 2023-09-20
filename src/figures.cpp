#include "svg/figures.h"

#include <ostream>
#include <utility>
#include <cstdint>
#include <string>

#include "svg/common.h"

namespace svg {
void Circle::Render(std::ostream &out) const {
  out << "<circle ";
  RenderProperties(out);
  out << "cx=\"" << center_.x << "\" " <<
      "cy=\"" << center_.y << "\" " <<
      "r=\"" << radius_ << "\"" << "/>";
}

Circle &Circle::SetCenter(Point point) {
  center_ = point;
  return *this;
}

Circle &Circle::SetRadius(double radius) {
  radius_ = radius;
  return *this;
}

void Polyline::Render(std::ostream &out) const {
  out << "<polyline ";
  RenderProperties(out);
  out << "points=\"";

  bool first = true;
  for (auto point : points_) {
    if (!first) {
      out << ' ';
    }
    first = false;
    out << point.x << ',' << point.y;
  }

  out << "\"/>";
}

Polyline &Polyline::AddPoint(Point point) {
  points_.push_back(point);
  return *this;
}

void Text::Render(std::ostream &out) const {
  out << "<text ";
  RenderProperties(out);
  out << "x=\"" << coords_.x << "\" " <<
      "y=\"" << coords_.y << "\" " <<
      "dx=\"" << offset_.x << "\" " <<
      "dy=\"" << offset_.y << "\" " <<
      "font-size=\"" << font_size_ << "\"";
  if (font_family_.has_value()) {
    out << " font-family=\"" << *font_family_ << "\"";
  }
  if (font_weight_.has_value()) {
    out << " font-weight=\"" << *font_weight_ << "\"";
  }
  out << '>' << text_ << "</text>";
}

Text &Text::SetPoint(Point point) {
  coords_ = point;
  return *this;
}

Text &Text::SetOffset(Point offset) {
  offset_ = offset;
  return *this;
}

Text &Text::SetFontSize(uint32_t font_size) {
  font_size_ = font_size;
  return *this;
}

Text &Text::SetFontFamily(const std::string &font_family) {
  font_family_ = font_family;
  return *this;
}
Text &Text::SetFontFamily(std::string &&font_family) {
  font_family_ = std::move(font_family);
  return *this;
}

Text &Text::SetFontWeight(const std::string &font_weight) {
  font_weight_ = font_weight;
  return *this;
}
Text &Text::SetFontWeight(std::string &&font_weight) {
  font_weight_ = std::move(font_weight);
  return *this;
}

Text &Text::SetData(const std::string &text) {
  text_ = text;
  return *this;
}
Text &Text::SetData(std::string &&text) {
  text_ = std::move(text);
  return *this;
}
}
