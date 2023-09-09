#ifndef SVG_SRC_FIGURES_H_
#define SVG_SRC_FIGURES_H_

#include <cstdint>
#include <optional>
#include <ostream>
#include <vector>
#include <string>
#include <utility>

#include "common.h"

namespace svg {
template<typename FigureType>
class Figure {
 public:
  Figure() = default;

  FigureType &SetFillColor(const Color &color) {
    fill_color_ = color;
    return *static_cast<FigureType *>(this);
  }
  FigureType &SetFillColor(Color &&color) {
    fill_color_ = std::move(color);
    return *static_cast<FigureType *>(this);
  }

  FigureType &SetStrokeColor(const Color &color) {
    stroke_color_ = color;
    return *static_cast<FigureType *>(this);
  }
  FigureType &SetStrokeColor(Color &&color) {
    stroke_color_ = std::move(color);
    return *static_cast<FigureType *>(this);
  }

  FigureType &SetStrokeWidth(double width) {
    stroke_width_ = width;
    return *static_cast<FigureType *>(this);
  }

  FigureType &SetStrokeLineCap(const std::string &linecap) {
    linecap_ = linecap;
    return *static_cast<FigureType *>(this);
  }
  FigureType &SetStrokeLineCap(std::string &&linecap) {
    linecap_ = std::move(linecap);
    return *static_cast<FigureType *>(this);
  }

  FigureType &SetStrokeLineJoin(const std::string &linejoin) {
    linejoin_ = linejoin;
    return *static_cast<FigureType *>(this);
  }
  FigureType &SetStrokeLineJoin(std::string &&linejoin) {
    linejoin_ = std::move(linejoin);
    return *static_cast<FigureType *>(this);
  }

 protected:
  void RenderProperties(std::ostream &out) const {
    out << "fill=\"" << fill_color_ << "\" " <<
        "stroke=\"" << stroke_color_ << "\" " <<
        "stroke-width=\"" << stroke_width_ << "\" ";
    if (linecap_.has_value())
      out << "stroke-linecap=\"" << *linecap_ << "\" ";
    if (linejoin_.has_value())
      out << "stroke-linejoin=\"" << *linejoin_ << "\" ";
  }

 private:
  Color fill_color_;
  Color stroke_color_;
  double stroke_width_ = 1.0;
  std::optional<std::string> linecap_;
  std::optional<std::string> linejoin_;
};

class Circle : public Figure<Circle> {
 public:
  Circle() = default;

  void Render(std::ostream &out) const;

  Circle &SetCenter(Point center);
  Circle &SetRadius(double radius);

 private:
  Point center_;
  double radius_ = 1.0;
};

class Polyline : public Figure<Polyline> {
 public:
  Polyline() = default;

  void Render(std::ostream &out) const;

  Polyline &AddPoint(Point point);

 private:
  std::vector<Point> points_;
};

class Text : public Figure<Text> {
 public:
  Text() = default;

  void Render(std::ostream &out) const;

  Text &SetPoint(Point point);
  Text &SetOffset(Point offset);
  Text &SetFontSize(uint32_t font_size);
  Text &SetFontFamily(const std::string &font_family);
  Text &SetFontFamily(std::string &&font_family);
  Text &SetData(const std::string &text);
  Text &SetData(std::string &&text);

 private:
  Point coords_;
  Point offset_;
  uint32_t font_size_ = 1;
  std::optional<std::string> font_family_;
  std::string text_;
};
}

#endif // SVG_SRC_FIGURES_H_
