/*
 * Software License Agreement (BSD License)
 *
 * Point Cloud Library (PCL) - www.pointclouds.org
 * Copyright (c) 2009-2012, Willow Garage, Inc.
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following
 *   disclaimer in the documentation and/or other materials provided
 *   with the distribution.
 * * Neither the name of Willow Garage, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 *
 */


#ifndef PCL_SURFACE_BILATERAL_UPSAMPLING_H_
#define PCL_SURFACE_BILATERAL_UPSAMPLING_H_

#include <pcl/surface/processing.h>

namespace pcl
{

  template <typename PointInT, typename PointOutT>
  class BilateralUpsampling: public CloudSurfaceProcessing<PointInT, PointOutT>
  {
    public:
      using PCLBase<PointInT>::input_;
      using PCLBase<PointInT>::indices_;
      using PCLBase<PointInT>::initCompute;
      using PCLBase<PointInT>::deinitCompute;
      using CloudSurfaceProcessing<PointInT, PointOutT>::process;

      typedef pcl::PointCloud<PointOutT> PointCloudOut;

      Eigen::Matrix3f KinectVGAProjectionMatrix, KinectSXGAProjectionMatrix;


      /** \brief Constructor. */
      BilateralUpsampling () : window_size_ (5),
                               sigma_color_ (15),
                               sigma_depth_ (0.5)
      {
        KinectVGAProjectionMatrix << 575.0f, 0.0f, 320.0f,
                                     0.0f, 575.0f, 240.0f,
                                     0.0f, 0.0f, 1.0f;
        KinectSXGAProjectionMatrix << 1056.0f, 0.0f, 640.0f,
                                      0.0f, 1056.0f, 480.0f,
                                      0.0f, 0.0f, 1.0f;
      };


      inline void
      setWindowSize (int window_size) { window_size_ = window_size; }

      inline int
      getWindowSize () { return window_size_; }


      inline void
      setSigmaColor (double &sigma_color) { sigma_color_ = sigma_color; }

      inline double
      getSigmaColor () { return sigma_color_; }


      inline void
      setSigmaDepth (double &sigma_depth) { sigma_depth_ = sigma_depth; }

      inline double
      getSigmaDepth () { return sigma_depth_; }


      inline void
      setProjectionMatrix (Eigen::Matrix3f &projection_matrix) { projection_matrix_ = projection_matrix; }

      inline Eigen::Matrix3f
      getProjectionMatrix () { return projection_matrix_; }

      void
      process (pcl::PointCloud<PointOutT> &output);

    protected:
      void
      performProcessing (pcl::PointCloud<PointOutT> &output);

    private:
      int window_size_;
      double sigma_color_, sigma_depth_;
      Eigen::Matrix3f projection_matrix_, unprojection_matrix_;


    public:
      EIGEN_MAKE_ALIGNED_OPERATOR_NEW
  };
}

#endif /* PCL_SURFACE_BILATERAL_UPSAMPLING_H_ */