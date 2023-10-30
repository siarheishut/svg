#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

#include "svg/common.h"
#include "svg/document.h"
#include "svg/figures.h"

#define PREFIX "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"                \
               "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"
#define POSTFIX "</svg>"
#define SVG_DOC(body) PREFIX body POSTFIX

#define DEFAULT_CIRCLE "<circle fill=\"none\" stroke=\"none\" "             \
                       "stroke-width=\"1\" cx=\"0\" cy=\"0\" r=\"1\"/>"

#define DEFAULT_POLYLINE "<polyline fill=\"none\" stroke=\"none\" "         \
                         "stroke-width=\"1\" points=\"\"/>"

#define DEFAULT_TEXT "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" " \
                     "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\""       \
                     "></text>"

#define DEFAULT_RECTANGLE "<rect x=\"0\" y=\"0\" width=\"0\" height=\"0\" "    \
                          "fill=\"none\" stroke=\"none\" stroke-width=\"1\" />"

TEST(TestFigures, TestCircle) {
  struct TestCase {
    std::string name;
    svg::Circle circle;
    std::string want;
  };

  std::vector<TestCase> test_cases{
      TestCase{
          .name = "Default ctor",
          .circle = svg::Circle{},
          .want = SVG_DOC(DEFAULT_CIRCLE)
      },
      TestCase{
          .name = "Set fill-color(rvalue-ref)",
          .circle = svg::Circle{}.SetFillColor(svg::Color{"red"}),
          .want = SVG_DOC(
                      "<circle fill=\"red\" stroke=\"none\" stroke-width=\"1\" "
                      "cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set fill-color(lvalue-ref)",
          .circle = [] {
            svg::Circle circle;
            svg::Color color = "red";
            circle.SetFillColor(color);
            return circle;
          }(),
          .want = SVG_DOC(
                      "<circle fill=\"red\" stroke=\"none\" stroke-width=\"1\" "
                      "cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set stroke-color(rvalue-ref)",
          .circle = svg::Circle{}.SetStrokeColor(svg::Color{"blue"}),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"blue\" "
                      "stroke-width=\"1\" cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set stroke-color(lvalue-ref)",
          .circle = [] {
            svg::Circle circle;
            svg::Color color = "blue";
            circle.SetStrokeColor(color);
            return circle;
          }(),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"blue\" stroke-width=\"1\""
                      " cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set stroke-width",
          .circle = svg::Circle{}.SetStrokeWidth(4.5),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"4.5\" cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set stroke-linecap(rvalue-ref)",
          .circle = svg::Circle{}.SetStrokeLineCap("default"),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" stroke-linecap=\"default\" "
                      "cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set stroke-linecap(lvalue-ref)",
          .circle = [] {
            svg::Circle circle;
            std::string linecap = "default";
            circle.SetStrokeLineCap(linecap);
            return circle;
          }(),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" stroke-linecap=\"default\" "
                      "cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set stroke-linejoin(rvalue-ref)",
          .circle = svg::Circle{}.SetStrokeLineJoin("not-default"),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" stroke-linejoin=\"not-default\" "
                      "cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set stroke-linejoin(lvalue-ref)",
          .circle = [] {
            svg::Circle circle;
            std::string linejoin = "not-default";
            circle.SetStrokeLineJoin(linejoin);
            return circle;
          }(),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" stroke-linejoin=\"not-default\" "
                      "cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set center",
          .circle = svg::Circle{}.SetCenter(svg::Point{.x = 3.005, .y = 12.1}),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" cx=\"3.005\" cy=\"12.1\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set radius",
          .circle = svg::Circle{}.SetRadius(18.1284),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" cx=\"0\" cy=\"0\" r=\"18.1284\"/>")
      },
      TestCase{
          .name = "Set all",
          .circle = svg::Circle{}
              .SetStrokeLineCap("some linecap")
              .SetStrokeColor(svg::Color{"purple"})
              .SetCenter(svg::Point{.x = -13, .y = -24})
              .SetStrokeWidth(-5)
              .SetStrokeLineJoin("some linejoin")
              .SetRadius(4)
              .SetFillColor("pink"),
          .want = SVG_DOC(
                      "<circle fill=\"pink\" stroke=\"purple\" "
                      "stroke-width=\"-5\" stroke-linecap=\"some linecap\" "
                      "stroke-linejoin=\"some linejoin\" cx=\"-13\" cy=\"-24\" "
                      "r=\"4\"/>")
      },
  };

  for (auto &[name, circle, want] : test_cases) {
    svg::Document doc;
    doc.Add(std::move(circle));

    std::ostringstream ss;
    doc.Render(ss);
    auto got = ss.str();

    EXPECT_EQ(want, got) << name;
  }
}

TEST(TestFigures, TestPolyline) {
  struct TestCase {
    std::string name;
    svg::Polyline polyline;
    std::string want;
  };

  std::vector<TestCase> test_cases{
      TestCase{
          .name = "Default ctor",
          .polyline = svg::Polyline{},
          .want = SVG_DOC(DEFAULT_POLYLINE)

      },
      TestCase{
          .name = "Set fill-color(rvalue-ref)",
          .polyline = svg::Polyline{}
              .SetFillColor(svg::Color{"color"}),
          .want = SVG_DOC(
                      "<polyline fill=\"color\" stroke=\"none\" "
                      "stroke-width=\"1\" points=\"\"/>")
      },
      TestCase{
          .name = "Set fill-color(lvalue-ref)",
          .polyline = [] {
            svg::Polyline polyline;
            svg::Color color = "color";
            polyline.SetFillColor(color);
            return polyline;
          }(),
          .want = SVG_DOC(
                      "<polyline fill=\"color\" stroke=\"none\" "
                      "stroke-width=\"1\" points=\"\"/>")
      },
      TestCase{
          .name = "Set stroke-color(rvalue-ref)",
          .polyline = svg::Polyline{}
              .SetStrokeColor(svg::Color{"color1"}),
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"color1\" "
                      "stroke-width=\"1\" points=\"\"/>")
      },
      TestCase{
          .name = "Set stroke-color(lvalue-ref)",
          .polyline = [] {
            svg::Polyline polyline;
            svg::Color color = "color1";
            polyline.SetStrokeColor(color);
            return polyline;
          }(),
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"color1\" "
                      "stroke-width=\"1\" points=\"\"/>")
      },
      TestCase{
          .name = "Set stroke-width",
          .polyline = svg::Polyline{}
              .SetStrokeWidth(4.5),
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"4.5\" points=\"\"/>")
      },
      TestCase{
          .name = "Set stroke-linecap(rvalue-ref)",
          .polyline = svg::Polyline{}
              .SetStrokeLineCap("default"),
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" stroke-linecap=\"default\" "
                      "points=\"\"/>")
      },
      TestCase{
          .name = "Set stroke-linecap(lvalue-ref)",
          .polyline = [] {
            svg::Polyline polyline;
            std::string linecap = "default";
            polyline.SetStrokeLineCap(linecap);
            return polyline;
          }(),
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" stroke-linecap=\"default\" "
                      "points=\"\"/>")
      },
      TestCase{
          .name = "Set stroke-linejoin(rvalue-ref)",
          .polyline = svg::Polyline{}
              .SetStrokeLineJoin("not-default"),
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" stroke-linejoin=\"not-default\" "
                      "points=\"\"/>")
      },
      TestCase{
          .name = "Set stroke-linejoin(lvalue-ref)",
          .polyline = [] {
            svg::Polyline polyline;
            std::string linejoin = "not-default";
            polyline.SetStrokeLineJoin(linejoin);
            return polyline;
          }(),
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" stroke-linejoin=\"not-default\" "
                      "points=\"\"/>")
      },
      TestCase{
          .name = "Add point",
          .polyline = svg::Polyline{}
              .AddPoint(svg::Point{.x = 3.005, .y = 12.1}),
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" points=\"3.005,12.1\"/>")
      },
      TestCase{
          .name = "Set add several points",
          .polyline = svg::Polyline{}
              .AddPoint(svg::Point{.x = -13.4, .y = 12.7})
              .AddPoint(svg::Point{.x = 41.9231, .y = -11.1111}),
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" points=\"-13.4,12.7 "
                      "41.9231,-11.1111\"/>")
      },
      TestCase{
          .name = "Set all",
          .polyline = svg::Polyline{}
              .SetStrokeLineCap("some linecap")
              .SetStrokeColor(svg::Color{"green"})
              .AddPoint(svg::Point{.x = -131.101, .y = 91.73})
              .SetStrokeWidth(54)
              .SetFillColor("red")
              .SetStrokeLineJoin("linejoin"),
          .want = SVG_DOC(
                      "<polyline fill=\"red\" stroke=\"green\" "
                      "stroke-width=\"54\" stroke-linecap=\"some linecap\" "
                      "stroke-linejoin=\"linejoin\" points=\"-131.101,91.73\""
                      "/>")
      },
  };

  for (auto &[name, polyline, want] : test_cases) {
    svg::Document doc;
    doc.Add(std::move(polyline));

    std::ostringstream ss;
    doc.Render(ss);
    auto got = ss.str();

    EXPECT_EQ(want, got) << name;
  }
}

TEST(TestFigures, TestText) {
  struct TestCase {
    std::string name;
    svg::Text text;
    std::string want;
  };

  std::vector<TestCase> test_cases{
      TestCase{
          .name = "Default ctor",
          .text = svg::Text{},
          .want = SVG_DOC(DEFAULT_TEXT)
      },
      TestCase{
          .name = "Set fill-color(rvalue-ref)",
          .text = svg::Text{}
              .SetFillColor(svg::Rgba{1, 2, 3, 0.52}),
          .want = SVG_DOC(
                      "<text fill=\"rgba(1,2,3,0.52)\" stroke=\"none\" "
                      "stroke-width=\"1\" x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" "
                      "font-size=\"1\"></text>")
      },
      TestCase{
          .name = "Set fill-color(lvalue-ref)",
          .text = [] {
            svg::Text text;
            svg::Color color = svg::Rgba{1, 2, 3, 0.52};
            text.SetFillColor(color);
            return text;
          }(),
          .want = SVG_DOC(
                      "<text fill=\"rgba(1,2,3,0.52)\" stroke=\"none\" "
                      "stroke-width=\"1\" x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" "
                      "font-size=\"1\"></text>")
      },
      TestCase{
          .name = "Set stroke-color(rvalue-ref)",
          .text = svg::Text{}
              .SetStrokeColor(svg::Color{"color1"}),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"color1\" "
                      "stroke-width=\"1\" x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" "
                      "font-size=\"1\"></text>")
      },
      TestCase{
          .name = "Set stroke-color(lvalue-ref)",
          .text = [] {
            svg::Text text;
            svg::Color color = "color1";
            text.SetStrokeColor(color);
            return text;
          }(),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"color1\" "
                      "stroke-width=\"1\" x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" "
                      "font-size=\"1\"></text>")
      },
      TestCase{
          .name = "Set stroke-width",
          .text = svg::Text{}
              .SetStrokeWidth(4.5),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"4.5\" x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" "
                      "font-size=\"1\"></text>")
      },
      TestCase{
          .name = "Set stroke-linecap(rvalue-ref)",
          .text = svg::Text{}
              .SetStrokeLineCap("linecap1"),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "stroke-linecap=\"linecap1\" x=\"0\" y=\"0\" "
                      "dx=\"0\" dy=\"0\" font-size=\"1\"></text>")
      },
      TestCase{
          .name = "Set stroke-linecap(lvalue-ref)",
          .text = [] {
            svg::Text text;
            std::string linecap = "linecap1";
            text.SetStrokeLineCap(linecap);
            return text;
          }(),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "stroke-linecap=\"linecap1\" x=\"0\" y=\"0\" "
                      "dx=\"0\" dy=\"0\" font-size=\"1\"></text>")
      },
      TestCase{
          .name = "Set stroke-linejoin(rvalue-ref)",
          .text = svg::Text{}
              .SetStrokeLineJoin("not-default"),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "stroke-linejoin=\"not-default\" x=\"0\" y=\"0\" "
                      "dx=\"0\" dy=\"0\" font-size=\"1\"></text>")
      },
      TestCase{
          .name = "Set stroke-linejoin(lvalue-ref)",
          .text = [] {
            svg::Text text;
            std::string linejoin = "not-default";
            text.SetStrokeLineJoin(linejoin);
            return text;
          }(),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "stroke-linejoin=\"not-default\" x=\"0\" y=\"0\" "
                      "dx=\"0\" dy=\"0\" font-size=\"1\"></text>")
      },
      TestCase{
          .name = "Set point",
          .text = svg::Text{}
              .SetPoint(svg::Point{.x = 3.005, .y = 12.1}),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"3.005\" y=\"12.1\" dx=\"0\" dy=\"0\" font-size=\"1\""
                      "></text>")
      },
      TestCase{
          .name = "Set offset",
          .text = svg::Text{}
              .SetOffset(svg::Point{.x = -13.4, .y = 12.7}),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"-13.4\" dy=\"12.7\" font-size=\"1\""
                      "></text>")
      },
      TestCase{
          .name = "Set font-size",
          .text = svg::Text{}
              .SetFontSize(1423),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1423\""
                      "></text>")
      },
      TestCase{
          .name = "Set font-weight(rvalue-ref)",
          .text = svg::Text{}
              .SetFontWeight("bold"),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\" "
                      "font-weight=\"bold\"></text>")
      },
      TestCase{
          .name = "Set font-weight(lvalue-ref)",
          .text = [] {
            svg::Text text;
            std::string weight = "bold";
            text.SetFontWeight(weight);
            return text;
          }(),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\" "
                      "font-weight=\"bold\"></text>")
      },
      TestCase{
          .name = "Set font-family(rvalue-ref)",
          .text = svg::Text{}
              .SetFontFamily("some_family"),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\" "
                      "font-family=\"some_family\"></text>")
      },
      TestCase{
          .name = "Set font-family(lvalue-ref)",
          .text = [] {
            svg::Text text;
            std::string fam = "some_family";
            text.SetFontFamily(fam);
            return text;
          }(),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\" "
                      "font-family=\"some_family\"></text>")
      },
      TestCase{
          .name = "Set data(rvalue-ref)",
          .text = svg::Text{}
              .SetData("some text"),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\""
                      ">some text</text>")
      },
      TestCase{
          .name = "Set data(lvalue-ref)",
          .text = [] {
            svg::Text text;
            std::string data = "some text";
            text.SetData(data);
            return text;
          }(),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\""
                      ">some text</text>")
      },
      TestCase{
          .name = "Set all",
          .text = svg::Text{}
              .SetStrokeLineCap("linecap1")
              .SetStrokeColor(svg::Color{
                  svg::Rgb{.red = 93, .green = 31, .blue = 17}})
              .SetPoint(svg::Point{.x = -131.101, .y = 91.73})
              .SetStrokeWidth(94)
              .SetFillColor(svg::Color{
                  svg::Rgb{.red = 10, .green = 20, .blue = 30}})
              .SetData("some text")
              .SetStrokeLineJoin("linejoin1")
              .SetOffset({.x = 12, .y = 15})
              .SetFontFamily("family1")
              .SetFontWeight("bold"),
          .want = SVG_DOC(
                      "<text fill=\"rgb(10,20,30)\" stroke=\"rgb(93,31,17)\" "
                      "stroke-width=\"94\" stroke-linecap=\"linecap1\" "
                      "stroke-linejoin=\"linejoin1\" x=\"-131.101\" y=\"91.73\" "
                      "dx=\"12\" dy=\"15\" font-size=\"1\" "
                      "font-family=\"family1\" font-weight=\"bold\">some text"
                      "</text>")
      },
  };

  for (auto &[name, text, want] : test_cases) {
    svg::Document doc;
    doc.Add(std::move(text));

    std::ostringstream ss;
    doc.Render(ss);
    auto got = ss.str();

    EXPECT_EQ(want, got) << name;
  }
}

TEST(TestFigures, TestRectangle) {
  struct TestCase {
    std::string name;
    svg::Rectangle rect;
    std::string want;
  };

  std::vector<TestCase> test_cases{
      TestCase{
          .name = "Default ctor",
          .rect = svg::Rectangle{},
          .want = SVG_DOC(DEFAULT_RECTANGLE)
      },
      TestCase{
          .name = "Set point",
          .rect = svg::Rectangle{}
              .SetPoint({.x = 1.1, .y = 2.2}),
          .want = SVG_DOC("<rect x=\"1.1\" y=\"2.2\" width=\"0\" height=\"0\" "
                          "fill=\"none\" stroke=\"none\" stroke-width=\"1\" />")
      },
      TestCase{
          .name = "Set width",
          .rect = svg::Rectangle{}
              .SetWidth(11.9),
          .want = SVG_DOC("<rect x=\"0\" y=\"0\" width=\"11.9\" height=\"0\" "
                          "fill=\"none\" stroke=\"none\" stroke-width=\"1\" />")
      },
      TestCase{
          .name = "Set height",
          .rect = svg::Rectangle{}
              .SetHeight(9.1),
          .want = SVG_DOC("<rect x=\"0\" y=\"0\" width=\"0\" height=\"9.1\" "
                          "fill=\"none\" stroke=\"none\" stroke-width=\"1\" />")
      },
      TestCase{
          .name = "Set fill-color(rvalue-ref)",
          .rect = svg::Rectangle{}
              .SetFillColor(svg::Rgba{3, 2, 1, 0.4}),
          .want = SVG_DOC("<rect x=\"0\" y=\"0\" width=\"0\" height=\"0\" "
                          "fill=\"rgba(3,2,1,0.4)\" stroke=\"none\" "
                          "stroke-width=\"1\" />")
      },
      TestCase{
          .name = "Set fill-color(lvalue-ref)",
          .rect = [] {
            svg::Rectangle rectangle;
            svg::Color color = svg::Rgba{3, 2, 1, 0.4};
            rectangle.SetFillColor(color);
            return rectangle;
          }(),
          .want = SVG_DOC("<rect x=\"0\" y=\"0\" width=\"0\" height=\"0\" "
                          "fill=\"rgba(3,2,1,0.4)\" stroke=\"none\" "
                          "stroke-width=\"1\" />")
      },
      TestCase{
          .name = "Set stroke-color(rvalue-ref)",
          .rect = svg::Rectangle{}
              .SetStrokeColor(svg::Color{"color"}),
          .want = SVG_DOC("<rect x=\"0\" y=\"0\" width=\"0\" height=\"0\" "
                          "fill=\"none\" stroke=\"color\" stroke-width=\"1\""
                          " />")
      },
      TestCase{
          .name = "Set stroke-color(lvalue-ref)",
          .rect = [] {
            svg::Rectangle rectangle;
            svg::Color color = "color";
            rectangle.SetStrokeColor(color);
            return rectangle;
          }(),
          .want = SVG_DOC("<rect x=\"0\" y=\"0\" width=\"0\" height=\"0\" "
                          "fill=\"none\" stroke=\"color\" stroke-width=\"1\""
                          " />")
      },
      TestCase{
          .name = "Set stroke-width",
          .rect = svg::Rectangle{}
              .SetStrokeWidth(1.3),
          .want = SVG_DOC("<rect x=\"0\" y=\"0\" width=\"0\" height=\"0\" "
                          "fill=\"none\" stroke=\"none\" stroke-width=\"1.3\" "
                          "/>")
      },
      TestCase{
          .name = "Set stroke-linecap(rvalue-ref)",
          .rect = svg::Rectangle{}
              .SetStrokeLineCap("linecap"),
          .want = SVG_DOC("<rect x=\"0\" y=\"0\" width=\"0\" height=\"0\" "
                          "fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                          "stroke-linecap=\"linecap\" />")
      },
      TestCase{
          .name = "Set stroke-linecap(lvalue-ref)",
          .rect = [] {
            svg::Rectangle rectangle;
            std::string linecap = "linecap";
            rectangle.SetStrokeLineCap(linecap);
            return rectangle;
          }(),
          .want = SVG_DOC("<rect x=\"0\" y=\"0\" width=\"0\" height=\"0\" "
                          "fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                          "stroke-linecap=\"linecap\" />")
      },
      TestCase{
          .name = "Set stroke-linejoin(rvalue-ref)",
          .rect = svg::Rectangle{}
              .SetStrokeLineJoin("linejoin"),
          .want = SVG_DOC("<rect x=\"0\" y=\"0\" width=\"0\" height=\"0\" "
                          "fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                          "stroke-linejoin=\"linejoin\" />")
      },
      TestCase{
          .name = "Set stroke-linejoin(lvalue-ref)",
          .rect = [] {
            svg::Rectangle rectangle;
            std::string linejoin = "linejoin";
            rectangle.SetStrokeLineJoin(linejoin);
            return rectangle;
          }(),
          .want = SVG_DOC("<rect x=\"0\" y=\"0\" width=\"0\" height=\"0\" "
                          "fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                          "stroke-linejoin=\"linejoin\" />")
      },
      TestCase{
          .name = "Set all",
          .rect = svg::Rectangle{}
              .SetFillColor(svg::Rgba{3, 2, 1, 0.4})
              .SetStrokeColor(svg::Color{"color"})
              .SetStrokeWidth(1.3)
              .SetStrokeLineCap("linecap")
              .SetStrokeLineJoin("linejoin")
              .SetPoint({.x = 4, .y = 2})
              .SetWidth(11)
              .SetHeight(7),
          .want = SVG_DOC("<rect x=\"4\" y=\"2\" width=\"11\" height=\"7\" "
                          "fill=\"rgba(3,2,1,0.4)\" stroke=\"color\" "
                          "stroke-width=\"1.3\" stroke-linecap=\"linecap\" "
                          "stroke-linejoin=\"linejoin\" />")
      },
  };

  for (auto &[name, rect, want] : test_cases) {
    svg::Document doc;
    doc.Add(std::move(rect));

    std::ostringstream ss;
    doc.Render(ss);
    auto got = ss.str();

    EXPECT_EQ(want, got) << name;
  }
}

TEST(TestSection, TestSection) {
  struct TestCase {
    std::string name;
    std::vector<svg::Object> objects;
    bool is_rvalue;
    std::string want;
  };

  std::vector<TestCase> test_cases{
      TestCase{
          .name = "Empty section",
          .want = SVG_DOC()
      },
      TestCase{
          .name = "Base case(lvalue-ref)",
          .objects = {svg::Circle{}, svg::Text{}, svg::Text{}},
          .is_rvalue = false,
          .want = SVG_DOC(DEFAULT_CIRCLE DEFAULT_TEXT DEFAULT_TEXT)
      },
      TestCase{
          .name = "Base case",
          .objects = {svg::Circle{}, svg::Circle{}, svg::Circle{},
                      svg::Text{}, svg::Text{}, svg::Text{},
                      svg::SectionBuilder{}
                          .Add(svg::Circle{})
                          .Add(svg::Text{})
                          .Add(svg::SectionBuilder{}
                                   .Add(svg::Polyline{})
                                   .Add(svg::Polyline{})
                                   .Add(svg::Rectangle{})
                                   .Add(svg::SectionBuilder{}.Build())
                                   .Build())
                          .Build(),
                      svg::Rectangle{}, svg::Rectangle{}, svg::Rectangle{},
                      svg::Text{}, svg::Text{}, svg::Text{}},
          .is_rvalue = true,
          .want = SVG_DOC(DEFAULT_CIRCLE DEFAULT_CIRCLE DEFAULT_CIRCLE
                              DEFAULT_TEXT DEFAULT_TEXT DEFAULT_TEXT
                              DEFAULT_CIRCLE DEFAULT_TEXT DEFAULT_POLYLINE
                              DEFAULT_POLYLINE DEFAULT_RECTANGLE
                              DEFAULT_RECTANGLE DEFAULT_RECTANGLE
                              DEFAULT_RECTANGLE DEFAULT_TEXT DEFAULT_TEXT
                              DEFAULT_TEXT)
      },
  };

  for (auto &[name, objects, is_rvalue, want] : test_cases) {
    svg::SectionBuilder builder;
    for (auto &object : objects) {
      if (is_rvalue) {
        builder.Add(std::move(object));
      } else {
        builder.Add(object);
      }
    }

    svg::Document doc;
    doc.Add(builder.Build());
    std::ostringstream ss;
    doc.Render(ss);

    auto got = ss.str();
    EXPECT_EQ(want, got) << name;
  }
}

TEST(TestDocument, TestDocument) {
  struct TestCase {
    std::string name;
    std::vector<svg::Object> objects;
    bool is_rvalue;
    std::string want;
  };

  std::vector<TestCase> test_cases{
      TestCase{
          .name = "Empty Document",
          .objects = {},
          .want = SVG_DOC("")
      },
      TestCase{
          .name = "Base case(lvalue-ref)",
          .objects = {svg::Circle{}, svg::Polyline{}},
          .is_rvalue = false,
          .want = SVG_DOC(DEFAULT_CIRCLE DEFAULT_POLYLINE)
      },
      TestCase{
          .name = "Several circles",
          .objects = {svg::Circle{}, svg::Circle{}, svg::Circle{},
                      svg::Circle{}},
          .is_rvalue = true,
          .want = SVG_DOC(
                      DEFAULT_CIRCLE DEFAULT_CIRCLE DEFAULT_CIRCLE
                      DEFAULT_CIRCLE)
      },
      TestCase{
          .name = "Several polylines",
          .objects = {svg::Polyline{}, svg::Polyline{}, svg::Polyline{}},
          .is_rvalue = true,
          .want = SVG_DOC(DEFAULT_POLYLINE DEFAULT_POLYLINE DEFAULT_POLYLINE)
      },
      TestCase{
          .name = "Several texts",
          .objects = {svg::Text{}, svg::Text{}, svg::Text{}, svg::Text{},
                      svg::Text{}},
          .is_rvalue = true,
          .want = SVG_DOC(
                      DEFAULT_TEXT DEFAULT_TEXT DEFAULT_TEXT DEFAULT_TEXT
                      DEFAULT_TEXT)

      },
      TestCase{
          .name = "Several rectangles",
          .objects = {svg::Rectangle{}, svg::Rectangle{}, svg::Rectangle{},
                      svg::Rectangle{}, svg::Rectangle{}},
          .is_rvalue = true,
          .want = SVG_DOC(
                      DEFAULT_RECTANGLE DEFAULT_RECTANGLE DEFAULT_RECTANGLE
                      DEFAULT_RECTANGLE DEFAULT_RECTANGLE)
      },
      TestCase{
          .name = "Several sections",
          .objects = {svg::SectionBuilder{}.Build(),
                      svg::SectionBuilder{}
                          .Add(svg::Circle{})
                          .Add(svg::Text{})
                          .Build(),
                      svg::SectionBuilder{}
                          .Add(svg::Polyline{})
                          .Add(svg::Rectangle{})
                          .Build()},
          .is_rvalue = true,
          .want = SVG_DOC(
                      DEFAULT_CIRCLE DEFAULT_TEXT DEFAULT_POLYLINE
                      DEFAULT_RECTANGLE)
      },
      TestCase{
          .name = "Different objects",
          .objects = {svg::Circle{}, svg::Polyline{}, svg::Circle{},
                      svg::Text{}, svg::Rectangle{},
                      svg::SectionBuilder{}.Add(svg::Polyline{}).Build(),
                      svg::Rectangle{}},
          .is_rvalue = true,
          .want = SVG_DOC(
                      DEFAULT_CIRCLE DEFAULT_POLYLINE DEFAULT_CIRCLE
                      DEFAULT_TEXT DEFAULT_RECTANGLE DEFAULT_POLYLINE
                      DEFAULT_RECTANGLE),
      },
  };

  for (auto &[name, objects, is_rvalue, want] : test_cases) {
    svg::Document doc;
    for (auto &object : objects) {
      if (is_rvalue) {
        doc.Add(std::move(object));
      } else {
        doc.Add(object);
      }
    }

    std::ostringstream ss;
    doc.Render(ss);
    auto got = ss.str();

    EXPECT_EQ(want, got) << name;
  }
}
