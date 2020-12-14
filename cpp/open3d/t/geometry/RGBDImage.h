// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include "open3d/geometry/RGBDImage.h"
#include "open3d/t/geometry/Geometry2D.h"
#include "open3d/t/geometry/Image.h"

namespace open3d {
namespace t {
namespace geometry {

/// \class RGBDImage
///
/// \brief RGBDImage is for a pair of registered color and depth images,
///
/// viewed from the same view, of the same resolution.
/// If you have another format, convert it first.
class RGBDImage : public Geometry2D {
public:
    /// \brief Default Comnstructor.
    RGBDImage() : Geometry2D(Geometry::GeometryType::RGBDImage) {}
    /// \brief Parameterized Constructor.
    ///
    /// \param color The color image.
    /// \param depth The depth image.
    RGBDImage(const Image &color, const Image &depth)
        : Geometry2D(Geometry::GeometryType::RGBDImage),
          color_(color),
          depth_(depth) {}

    ~RGBDImage() override {
        color_.Clear();
        depth_.Clear();
    };

    /// Clear stored data
    RGBDImage &Clear() override;
    /// Is any data stored?
    bool IsEmpty() const override;
    /// Compute min 2D coordinates for the data (always {0,0})
    core::Tensor GetMinBound() const override {
        return core::Tensor::Zeros({2}, core::Dtype::Int64);
    };
    /// Compute max 2D coordinates for the data
    core::Tensor GetMaxBound() const override {
        return core::Tensor(
                std::vector<int64_t>{color_.GetCols() + depth_.GetCols(),
                                     color_.GetRows()},
                {2}, core::Dtype::Int64);
    };

    /// Convert to the legacy RGBDImage format
    open3d::geometry::RGBDImage ToLegacyRGBDImage() const {
        return open3d::geometry::RGBDImage(color_.ToLegacyImage(),
                                           depth_.ToLegacyImage());
    }

    /// Text description
    std::string ToString() const;

public:
    /// The color image.
    Image color_;
    /// The depth image.
    Image depth_;
};

}  // namespace geometry
}  // namespace t
}  // namespace open3d