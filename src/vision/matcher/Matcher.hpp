//
// Created by yongqi on 17-12-4.
//

#ifndef VFORCE_MATCHER_HPP
#define VFORCE_MATCHER_HPP

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>

namespace VForce {

class Matcher {
 public:
  typedef pcl::PointXYZ PointT;
  typedef typename pcl::PointCloud<PointT> PointTCloud;
  typedef typename boost::shared_ptr<PointTCloud> PointTCloudPtr;

  Matcher(const std::string &cfg_root = ".", const std::string &cfg_file = "Matcher") :
      cfg_root_(cfg_root), cfg_file_(cfg_file), init_(false) {
  }

  /**
   * Load config from file
   * @param s config filename
   * @return
   */
  virtual bool LoadConfig(const std::string &cfg_file) = 0;

  /**
   * Estimate transformation from model to target
   * @param model model pointcloud
   * @param model_size model size
   * @param target target pointcloud
   * @param id target pointcloud's class id
   * @param tf estimated transformation
   * @param final the transformed model(aligned to target)
   * @return match error
   */
  virtual double EstimatePose(const PointTCloudPtr &model, const float* model_size,
                              const PointTCloudPtr &target,
                              Eigen::Matrix4f &tf, PointTCloudPtr &final) = 0;

  // @TODO: filter some target based on target size

  /**
   * Calculate dist error between two clouds
   * @param model
   * @param target
   * @param max_dist
   * @return
   */
  double CalculateMatchError(const PointTCloudPtr &model, const PointTCloudPtr &target, double max_dist = 0.1);

 protected:

  bool init_;
  std::string cfg_root_, cfg_file_;
};

}
#endif //VFORCE_MATCHER_HPP
