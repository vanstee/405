require 'matrix'

class Vector
  def cross(v)
    Vector[
      self[1] * v[2] - self[2] * v[1],
      self[2] * v[0] - self[0] * v[2],
      self[0] * v[1] - self[1] * v[0]]
  end
  
  alias :dot :inner_product
end

# x = Vector[1.4, 0.75, -2.5]
# 
# p0 = Vector[0.5, -0.5, 10]
# p1 = Vector[1.5, -0.5, 10]
# p2 = Vector[2, 0, 5]
# p3 = Vector[1, 0.5, 0]
# p4 = Vector[2, 1, -5]
# p5 = Vector[1.5, 1.5, -10]
# p6 = Vector[0.5, 1.5, -10]
# p7 = Vector[0, 1, -5]
# p8 = Vector[0, 0, 5]
# p9 = Vector[0.5, -0.5, 10]
# 
# points = [p0, p1, p2, p3, p4, p5, p6, p7, p8, p9]
# 
# e0 = p1 - p0
# e1 = p2 - p1
# 
# n = e0.cross(e1)
# n = n / n.r
# 
# if n[0] > n[1]
#   if n[0] > n[2]
#     max = 0
#   else
#     max = 2
#   end
# else
#   max = 1
# end
# 
# origin = Vector[0, 0, 0]
# delta = x - origin
# 
# points.collect! do |p|
#   p = p - delta
#   p = p.to_a
#   p[max] = 0
#   Vector[*p]
# end
# 
# points.each do |p|
#   puts p
# end

pr = Vector[6, 4, -2]
ur = Vector[-0.86, -0.47, 0.21]

p0 = Vector[1,  2, -1]
p1 = Vector[3, -1,  0]
p2 = Vector[2,  1, -1]

e0 = p1 - p0
e1 = p2 - p1
e2 = p0 - p2

n = e0.cross(e1)
n = n / n.r

t = -((pr - p0).dot(n)) / (ur.dot(n))
puts t

x = pr + (t * ur)

a = -0.5 * (e0.cross(e2)).dot(n)

puts a

au = 0.5 * (e1.cross(x - p1)).dot(n)
av = 0.5 * (e2.cross(x - p2)).dot(n)

u = au / a
v = av / a
w = 1 - u - v

x = Vector[u * p0, v * p1, w * p2]

puts "u = #{u}"
puts "v = #{v}"
puts "w = #{w}"

puts x