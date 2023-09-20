#include <string>
#include <vector>
#include <sstream>
#include <utility>

#include "gtest/gtest.h"

#include "svg/common.h"
#include "svg/figures.h"
#include "svg/document.h"

#define PREFIX "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"                \
               "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">"
#define POSTFIX "</svg>"
#define SVG_DOC(body) PREFIX body POSTFIX

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
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set fill-color",
          .circle = svg::Circle{}.SetFillColor(svg::Color{"red"}),
          .want = SVG_DOC(
                      "<circle fill=\"red\" stroke=\"none\" stroke-width=\"1\" "
                      "cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set stroke-color",
          .circle = svg::Circle{}.SetStrokeColor(svg::Color{"blue"}),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"blue\" "
                      "stroke-width=\"1\" cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set stroke-width",
          .circle = svg::Circle{}.SetStrokeWidth(4.5),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"4.5\" cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set stroke-linecap",
          .circle = svg::Circle{}.SetStrokeLineCap("default"),
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" stroke-linecap=\"default\" "
                      "cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Set stroke-linejoin",
          .circle = svg::Circle{}.SetStrokeLineJoin("not-default"),
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
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" points=\"\"/>")
      },
      TestCase{
          .name = "Set fill-color",
          .polyline = svg::Polyline{}
              .SetFillColor(svg::Color{"color"}),
          .want = SVG_DOC(
                      "<polyline fill=\"color\" stroke=\"none\" "
                      "stroke-width=\"1\" points=\"\"/>")
      },
      TestCase{
          .name = "Set stroke-color",
          .polyline = svg::Polyline{}
              .SetStrokeColor(svg::Color{"color1"}),
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
          .name = "Set stroke-linecap",
          .polyline = svg::Polyline{}
              .SetStrokeLineCap("default"),
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" stroke-linecap=\"default\" "
                      "points=\"\"/>")
      },
      TestCase{
          .name = "Set stroke-linejoin",
          .polyline = svg::Polyline{}
              .SetStrokeLineJoin("not-default"),
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
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\""
                      "></text>")
      },
      TestCase{
          .name = "Set fill-color",
          .text = svg::Text{}
              .SetFillColor(svg::Rgba{1, 2, 3, 0.52}),
          .want = SVG_DOC(
                      "<text fill=\"rgba(1,2,3,0.52)\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\""
                      "></text>")
      },
      TestCase{
          .name = "Set stroke-color",
          .text = svg::Text{}
              .SetStrokeColor(svg::Color{"color1"}),
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
          .name = "Set stroke-linecap",
          .text = svg::Text{}
              .SetStrokeLineCap("linecap1"),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "stroke-linecap=\"linecap1\" x=\"0\" y=\"0\" "
                      "dx=\"0\" dy=\"0\" font-size=\"1\"></text>")
      },
      TestCase{
          .name = "Set stroke-linejoin",
          .text = svg::Text{}
              .SetStrokeLineJoin("not-default"),
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
          .name = "Set font-weight",
          .text = svg::Text{}
              .SetFontWeight("bold"),
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\" "
                      "font-weight=\"bold\"></text>")
      },
      TestCase{
          .name = "Set data",
          .text = svg::Text{}
              .SetData("some text"),
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

TEST(TestDocument, TestDocument) {
  struct TestCase {
    std::string name;
    std::vector<svg::Object> figures;
    std::string want;
  };

  std::vector<TestCase> test_cases{
      TestCase{
          .name = "Empty Document",
          .figures = {},
          .want = SVG_DOC("")
      },
      TestCase{
          .name = "Several circles",
          .figures = {svg::Circle{}, svg::Circle{}, svg::Circle{},
                      svg::Circle{}},
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" cx=\"0\" cy=\"0\" r=\"1\"/>"
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" cx=\"0\" cy=\"0\" r=\"1\"/>"
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" cx=\"0\" cy=\"0\" r=\"1\"/>"
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" cx=\"0\" cy=\"0\" r=\"1\"/>")
      },
      TestCase{
          .name = "Several polylines",
          .figures = {svg::Polyline{}, svg::Polyline{}, svg::Polyline{}},
          .want = SVG_DOC(
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" points=\"\"/>"
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" points=\"\"/>"
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" points=\"\"/>")
      },
      TestCase{
          .name = "Several texts",
          .figures = {svg::Text{}, svg::Text{}, svg::Text{}, svg::Text{},
                      svg::Text{}},
          .want = SVG_DOC(
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\""
                      "></text>"
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\""
                      "></text>"
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\""
                      "></text>"
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\""
                      "></text>"
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\""
                      "></text>")
      },
      TestCase{
          .name = "Different figures",
          .figures = {svg::Circle{}, svg::Polyline{}, svg::Circle{},
                      svg::Text{}},
          .want = SVG_DOC(
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" cx=\"0\" cy=\"0\" r=\"1\"/>"
                      "<polyline fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" points=\"\"/>"
                      "<circle fill=\"none\" stroke=\"none\" "
                      "stroke-width=\"1\" cx=\"0\" cy=\"0\" r=\"1\"/>"
                      "<text fill=\"none\" stroke=\"none\" stroke-width=\"1\" "
                      "x=\"0\" y=\"0\" dx=\"0\" dy=\"0\" font-size=\"1\""
                      "></text>"),
      },
  };

  for (auto &[name, figures, want] : test_cases) {
    svg::Document doc;
    for (auto &figure : figures) {
      doc.Add(std::move(figure));
    }

    std::ostringstream ss;
    doc.Render(ss);
    auto got = ss.str();

    EXPECT_EQ(want, got);
  }
}
