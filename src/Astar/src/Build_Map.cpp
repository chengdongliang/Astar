

/* --Includes-- */
#include <iostream>
#include <cmath>
#include <vector>
#include "../include/Build_Map.h"

/**
 * Build_Map 构造函数
 * _Boundary {xmin,ymin,zmin,xmax,ymax,zmax}
 * _xy_res 表示x，y的分标率，即一格的大小
 * _z_ 表示z的分标率
 * _margin 表示机器人的尺寸
 * World 储存世界尺寸
 */
Build_Map::Build_Map(std::vector<double> _Boundary, double _xy_res,
                     double _z_res, double _margin)
    : Boundary(_Boundary),
      xy_res(_xy_res),
      z_res(_z_res),
      margin(_margin) {
  int World_X = (Boundary[3] - Boundary[0]) / xy_res;  ///< X Dimension
  int World_Y = (Boundary[4] - Boundary[1]) / xy_res;  ///< Y Dimension
  int World_Z = (Boundary[5] - Boundary[2]) / z_res;  ///< Z Dimension
  World = {World_X, World_Y, World_Z};
}

/**
 * 返回World
 */
std::vector<int> Build_Map::World_Dimensions() {
  return World;
}

/**
 * 构建障碍物
 */
std::vector<int> Build_Map::Build_Obstacle(std::vector<double> v) {
  int minx = std::max(
      static_cast<int>(std::floor(((v[0] - Boundary[0] - margin) / xy_res))),
      0);
  int miny = std::max(
      static_cast<int>(std::floor(((v[1] - Boundary[1] - margin) / xy_res))),
      0);
  int minz = std::max(
      static_cast<int>(std::floor(((v[2] - Boundary[2] - margin) / z_res))), 0);
  int maxx = std::min(
      static_cast<int>(std::ceil(((v[3] - Boundary[0] + margin) / xy_res))),
      World[0]);
  int maxy = std::min(
      static_cast<int>(std::ceil(((v[4] - Boundary[1] + margin) / xy_res))),
      World[1]);
  int maxz = std::min(
      static_cast<int>(std::ceil(((v[5] - Boundary[2] + margin) / z_res))),
      World[2]);

  std::vector<int> Obstacle_Extrema = { minx, miny, minz, maxx, maxy, maxz };
  return Obstacle_Extrema;
}

/**
 * 构建障碍物的膨胀层
 */
std::vector<std::vector<std::vector<int>>> Build_Map::Build_costmap(std::vector<std::vector<double>> Obstacle){
  std::vector<std::vector<int>> inflationlayer1;
  std::vector<std::vector<int>> inflationlayer2;
  for (const std::vector<double> &v : Obstacle){
    int minx = std::max(
        static_cast<int>(std::floor(((v[0] - Boundary[0] - margin) / xy_res))),
        0);
    int miny = std::max(
        static_cast<int>(std::floor(((v[1] - Boundary[1] - margin) / xy_res))),
        0);
    int minz = std::max(
        static_cast<int>(std::floor(((v[2] - Boundary[2] - margin) / z_res))), 0);
    int maxx = std::min(
        static_cast<int>(std::ceil(((v[3] - Boundary[0] + margin) / xy_res))),
        World[0]);
    int maxy = std::min(
        static_cast<int>(std::ceil(((v[4] - Boundary[1] + margin) / xy_res))),
        World[1]);
    int maxz = std::min(
        static_cast<int>(std::ceil(((v[5] - Boundary[2] + margin) / z_res))),
        World[2]);
    //std::vector<int> inflationlayer1 = {minx-1, miny-1, minz-1, maxx+1, maxy+1, maxz+1}; //膨胀层 cost = 250
    //std::vector<int> inflationlayer2 = {minx-2, miny-2, minz-2, maxx+2, maxy+2, maxz+2}; //膨胀层 cost = 128
    inflationlayer1.push_back({minx-1, miny-1, minz-1, maxx+1, maxy+1, maxz+1});
    inflationlayer2.push_back({minx-2, miny-2, minz-2, maxx+2, maxy+2, maxz+2});
  }


  
  return {inflationlayer1, inflationlayer2};
}




/**
 * 构建节点
 */
std::vector<int> Build_Map::Build_Node(std::vector<double> Discrete) {
  int X_Init = (Discrete[0] - Boundary[0]) / xy_res;
  int Y_Init = (Discrete[1] - Boundary[1]) / xy_res;
  int Z_Init = (Discrete[2] - Boundary[2]) / z_res;
  std::vector<int> Built_Node = { X_Init, Y_Init, Z_Init };
  return Built_Node;
}

/**
 * 从将word中一个点，转化为坐标表示
 */
std::vector<double> Build_Map::Get_Coordinate(std::vector<int> Node_Init) {
  double X_Coordinate = Boundary[0] + (Node_Init[0] * xy_res);
  double Y_Coordinate = Boundary[1] + (Node_Init[1] * xy_res);
  double Z_Coordinate = Boundary[2] + (Node_Init[2] * z_res);
  std::vector<double> Coordinates_Generated = { X_Coordinate, Y_Coordinate,
      Z_Coordinate };
  return Coordinates_Generated;
}

/**
 * Build_Map 析构函数
 */
Build_Map::~Build_Map() {
}
