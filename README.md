# SVG library

This project implements a library to output vector images in SVG format
according to https://www.w3.org/2000/svg requirements.

<font size="3">This implementation are able to work with such figures as: </font>

1. `Circle`: described by `center coordinates` and `radius`.
2. `Polyline`: described by `vertex coordinates`.
3. `Text`: described by `reference point coordinates`, `offset from
   reference point`, `font size`, `font family` and `text data`.</font>

Moreover, all figures have the same common properties:
`stroke color`, `fill color`, `stroke width`, `stroke linecap`and `stroke linejoin`.

<br>

<font size="4">*To begin describing each figure let's firstly familiarize with auxiliary structures:* </font>

### svg::Point

<font size="3">Class with the following fields: </font>

| Field | Type  | Description  | Value by default |
|-------|-------|--------------|------------------|
| x     | float | x coordinate | 0.0              |
| y     | float | y coordinate | 0.0              |

### svg::Rgb

<font size="3">Class with the following fields: </font>

| Field | Type | Description                     | Value by default |
|-------|------|---------------------------------|------------------|
| red   | int  | Red intensity (from 0 to 255)   | 0                |
| green | int  | Green intensity (from 0 to 255) | 0                |
| blue  | int  | Blue intensity (from 0 to 255)  | 0                |

### svg::Rgba

<font size="3">Class with the following fields: </font>

| Field | Type  | Description                     | Value by default |
|-------|-------|---------------------------------|------------------|
| red   | int   | Red intensity (from 0 to 255)   | 0                |
| green | int   | Green intensity (from 0 to 255) | 0                |
| blue  | int   | Blue intensity (from 0 to 255)  | 0                |
| alpha | float | Alpha channel (from 0 to 1)     | 1.0              |

### svg::Color

<font size="3">Object of this type may be initialized with object of either `std::string`, `svg::Rgb` or `svg::Rgba`
type and equals to `"none"` by default. </font>

<br>

<font size="4">*Now let's describe each figure class separately:* </font>

### svg::Circle

Fields:

| Field  | Type       | Value by default |
|--------|------------|------------------|
| radius | float      | 1.0              |
| center | svg::Point | See above.       |

Methods:

| Method    | Parameter type | Description              | 
|-----------|----------------|--------------------------|
| SetCenter | svg::Point     | Sets center coordinates. |
| SetRadius | float          | Sets radius.             |

### svg::Polyline

Fields:

| Field  | Type                | Value by default |
|--------|---------------------|------------------|
| points | array of svg::Point | Empty            |

Methods:

| Method   | Parameter type | Description                                                                               | 
|----------|----------------|-------------------------------------------------------------------------------------------|
| AddPoint | svg::Point     | Adds the point to polyline and connects this point with the previous one(if such exists). |

### svg::Text

Fields:

| Field       | Type        | Value by default |
|-------------|-------------|------------------|
| ref_point   | svg::Point  | See above.       |
| offset      | svg::Point  | See above.       |
| font size   | int         | 1                |
| font family | std::string | null             |
| text        | std::string | ""               |

Methods:

| Method        | Parameter type | Description                       | 
|---------------|----------------|-----------------------------------|
| SetPoint      | svg::Point     | Sets reference point coordinates. |
| SetOffset     | svg::Point     | Sets offset from reference point. |
| SetFontSize   | float          | Sets font size.                   |
| SetFontFamily | std::string    | Sets font family.                 |
| SetData       | std::string    | Sets text message.                |

#### Common fields and methods:

| Field           | Type        | Value by default |
|-----------------|-------------|------------------|
| stroke color    | svg:Color   | See above.       |
| fill color      | svg::Color  | See above.       |
| stroke width    | float       | 1.0              |
| stroke linecap  | std::string | null             |
| stroke linejoin | std::string | null             |

| Method            | Parameter type | Description           | 
|-------------------|----------------|-----------------------|
| SetStrokeColor    | svg::Point     | Sets stroke color.    |
| SetFillColor      | svg::Point     | Sets fill color.      |
| SetStrokeWidth    | float          | Sets stroke width.    |
| SetStrokeLinecap  | std::string    | Sets stroke linecap.  |
| SetStrokeLineJoin | std::string    | Sets stroke linejoin. |

## Steps to generate SVG code.

1. Create an object of `svg::Document` type(in the following steps that object will be called `doc`).
2. Add all needed figures by repeatedly calling method `Add` on `doc` and passing the figure of
   any type.
3. Call non-parameterized method `Render` on `doc`.
