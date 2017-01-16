/******************************************************************************
 * Copyright (c) 2016 Thomas Faeulhammer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ******************************************************************************/

#pragma once

#include <v4r/core/macros.h>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/shared_ptr.hpp>
#include <Eigen/Core>
#include <fstream>
#include <stdlib.h>

namespace v4r
{
/**
 * @brief The Camera class represents a pinhole camera model
 * @author Thomas Faeulhammer
 */
class V4R_EXPORTS Camera
{
protected:
    size_t width_; /// image width in pixel
    size_t height_; /// image height in pixel
    float focal_length_;   ///< focal length
    float cx_;  ///< central point of projection in x
    float cy_; ///< central point of projection in y
    float horizontal_fov_deg_; ///< camera's horizontal field of view in degree
    float vertical_fov_deg_; ///< camera's vertical field of view in degree


    friend class boost::serialization::access;

//    BOOST_CLASS_VERSION(HV_Parameter, 1)

    template<class Archive> V4R_EXPORTS void serialize(Archive & ar, const unsigned int version)
    {
        (void) version;
        ar      & BOOST_SERIALIZATION_NVP(width_)
                & BOOST_SERIALIZATION_NVP(height_)
                & BOOST_SERIALIZATION_NVP(focal_length_)
                & BOOST_SERIALIZATION_NVP(cx_)
                & BOOST_SERIALIZATION_NVP(cy_)
                & BOOST_SERIALIZATION_NVP(horizontal_fov_deg_)
                & BOOST_SERIALIZATION_NVP(vertical_fov_deg_);
    }

public:

    typedef boost::shared_ptr< Camera > Ptr;
    typedef boost::shared_ptr< Camera const> ConstPtr;

    Camera(
            float focal_length = 525.f,
            size_t width = 640,
            size_t height = 480,
            float cx = 319.5f,
            float cy = 239.5f,
            float horizontal_fov_deg = 58.f,
            float vertical_fov_deg = 45.f
            )
        :
          width_ (width),
          height_(height),
          focal_length_(focal_length),
          cx_(cx),
          cy_ (cy),
          horizontal_fov_deg_ (horizontal_fov_deg),
          vertical_fov_deg_ (vertical_fov_deg)
    {}

    /**
     * @brief getWidth
     * @return
     */
    size_t getWidth() const { return width_; }

    /**
     * @brief getHeight
     * @return
     */
    size_t getHeight() const { return height_; }

    /**
     * @brief getFocalLength
     * @return
     */
    float getFocalLength() const { return focal_length_; }

    /**
     * @brief getCx
     * @return
     */
    float getCx() const { return cx_; }

    /**
     * @brief getCy
     * @return
     */
    float getCy() const { return cy_; }

    /**
     * @brief getHorizontalFOV
     * @return
     */
    float getHorizontalFOV() const { return horizontal_fov_deg_; }

    /**
     * @brief getVerticalFOV
     * @return
     */
    float getVerticalFOV() const { return vertical_fov_deg_; }


    /**
     * @brief save save the parameters into an XML file
     * @param filename
     */
    void
    save(const std::string &filename) const
    {
        std::ofstream ofs(filename);
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP( *this );
        ofs.close();
    }

    /**
     * @brief Camera initialize the camera with the parameters from an XML file
     * @param filename
     */
    Camera(const std::string &filename)
    {
        std::ifstream ifs(filename);
        boost::archive::xml_iarchive ia(ifs);
        ia >> BOOST_SERIALIZATION_NVP( *this );
        ifs.close();
    }
};

}

