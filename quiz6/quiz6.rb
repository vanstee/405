require 'matrix'

class Vector
  def cross(v)
    Vector[
      self[1] * v[2] - self[2] * v[1],
      self[2] * v[0] - self[0] * v[2],
      self[0] * v[1] - self[1] * v[0]]
  end
  
  def scale(d)
    Vector[
      self[0] * d,
      self[1] * d,
      self[2] * d]
  end  
  
  alias :dot :inner_product
end

r  = 1
c = Vector[1, 1, 0]
uc = c / c.r
x  = Vector[0, 5, 0]
p  = Vector[0, 0, 0]

xp = p - x
puts (((uc * uc.dot(xp)) + x) - p).r