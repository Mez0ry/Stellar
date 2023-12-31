#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__
#include <algorithm>
#include <math.h>
#include <iostream>

struct Vec2 {
  int x, y;

  Vec2() : x(0),y(0){}
  Vec2(int pos_x, int pos_y) : x(pos_x), y(pos_y) {}
  Vec2(const Vec2& other){x = other.x; y = other.y; }
  Vec2(Vec2&& other) : x(other.x),y(other.y) {}
  
  ~Vec2() = default;
  
  friend void swap(Vec2& lhs, Vec2& rhs){
    std::swap(lhs.x,rhs.x);
    std::swap(lhs.y,rhs.y);
  }
  /**
   * @brief used to get length/magnitude  of the vector
   * @return magnitude
  */
  double Magnitude() const {return std::sqrt(x * x + y * y);}
  
  /**
   * @brief used to get length/magnitude of the vector
   * @return length
  */
  double Length() const {return std::sqrt(DotProduct({x,y},{x,y}));}

  /**
   * @brief used to get distance
   * @return distance
  */
  static int Distance(const Vec2& lhs, const Vec2& rhs){
    Vec2 res{std::abs(lhs.x - rhs.x),std::abs(lhs.y - rhs.y)};
    return res.Length();
  }

  float GetMaxComponent() const{
    return std::max(x,y);
  }

  float GetMinComponent() const{
    return std::min(x,y);
  }

  float Angle(const Vec2& other) const
  {
    return std::acos(DotProduct((*this),other) / Magnitude() * other.Magnitude());
  }

  static float Angle(const Vec2& lhs,const Vec2& rhs){
    return std::acos(DotProduct(lhs,rhs) / lhs.Magnitude() * rhs.Magnitude());
  }

  /**
   * @brief normalize vector
   * @return unit vector on success otherwise empty vector
  */
  Vec2 Normalize() const{
    double magnitude = Magnitude();
    if(magnitude == 0) return {0,0};

    double inv_mag = 1.0f / magnitude;
    double res_x = (x * (inv_mag * 1.6));
    double res_y = (y * (inv_mag * 1.6));
    
    return {static_cast<int>(res_x),static_cast<int>(res_y)};
  }
  
  Vec2 PositivePerpendicular() const
  {
    return {-y, x};
  }

  Vec2 NegativePerpendicular() const
  {
    return {y, -x};
  }

  /**
   * @brief used to get dot product
   * @return dot product
  */
  static double DotProduct(const Vec2& lhs, const Vec2& rhs){
    return (lhs.x * rhs.x + lhs.y * rhs.y);
  }

  static Vec2 Lerp(const Vec2& lhs, const Vec2& rhs, float t)
  {
    t = std::clamp(t, 0.0f, 1.0f);
    return {(int)(lhs.x + (rhs.x - lhs.x) * t),(int)(lhs.y + (rhs.y - lhs.y) * t)};
  }
  
  /** Comparison operators*/
  Vec2 operator-(const Vec2& rhs) const{
    return {x - rhs.x, y - rhs.y};
  }

  Vec2 operator-(Vec2& rhs) const{
    return {x - rhs.x, y - rhs.y};
  }

  Vec2 operator+(const Vec2& rhs) const{
    return {x + rhs.x, y + rhs.y};
  }

  Vec2& operator+=(const Vec2& rhs){
    x += rhs.x;
    y += rhs.y;
    return *this; 
  }

  Vec2& operator-=(const Vec2& rhs){
    x -= rhs.x;
    y -= y - rhs.y;
    return *this; 
  }

  inline friend std::ostream& operator<< (std::ostream &out, const Vec2 &vec){
    out << "Vector(" << vec.x << "," << vec.y << ")";
    return out;
  }

  bool operator==(const Vec2 &rhs) const {
    return (x == rhs.x && y == rhs.y);
  }

  bool operator!=(const Vec2 &rhs) const {
    return !(x == rhs.x && y == rhs.y);
  }
  
  /** Assignment operators*/
  Vec2& operator=(Vec2 other){
    if (this == &other){//self assignment
      return (*this);
    }
    swap((*this),other);
    return (*this);
  }

  Vec2 operator+=(const float scalar)
  {
    x += scalar;
    y += scalar;
    return *this;
  }

  Vec2 operator-=(const float scalar)
  {
    x -= scalar;
    y -= scalar;
    return *this;
  }

  Vec2 operator*=(const float scalar)
  {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vec2 operator/=(const float scalar)
  {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  inline Vec2 operator+(const float scalar)
  {
    Vec2 tmp = (*this);
    return tmp += (int)scalar;
  }

  inline Vec2 operator-( const float scalar)
  {
    Vec2 tmp = (*this);
    return tmp -= (int)scalar;
  }

  inline Vec2 operator*(const float scalar)
  {
    Vec2 tmp = (*this);
    return tmp *= (int)scalar;
  }

  inline Vec2 operator*(const Vec2& vec)
  {
    return {x * vec.x, y * vec.y};
  }

  inline Vec2 operator/(const float scalar)
  {
    Vec2 tmp = (*this);
    return tmp /= scalar;
  }
};

/**@brief for compatability with stl unordered_map*/
template <>
struct std::hash<Vec2>
{
  std::size_t operator()(const Vec2& vec) const
  {
    return ((std::hash<int>()(vec.x) ^ (std::hash<int>()(vec.y) << 1)) >> 1);
  }
};

#endif //!__VECTOR_HPP__