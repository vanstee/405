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

# xc  = Vector[0, 1, 2]
# vup = Vector[1, 0, 0]
# uc  = Vector[0, 0, -1]
# 
# x = uc.cross(vup) 
# ux = x/x.r
# y = ux.cross(uc)
# uy = y/y.r
# uz = uc * -1
# 
# puts "ux = #{ux}"
# puts "uy = #{uy}"
# puts "uz = #{uz}"
# 
# x = Matrix[
#       [1],
#       [2],
#       [3],
#       [1]]
#     
# puts "#{t * x}"
# 
# r = Matrix[
#       [0, -1, 0, 0],
#       [1, 0, 0, 0],
#       [0, 0, 1, 0],
#       [0, 0, 0, 1]]
#       
# puts "#{r * t}"

# t = Matrix[[ 1,  0,  0, -1],
#            [ 0,  1,  0, -2],
#            [ 0,  0,  1, -3],
#            [ 0,  0,  0,  1]]
# 
# 
# r = Matrix[[ 0, -1,  0,  0],
#            [ 1,  0,  0,  0],
#            [ 0,  0,  1,  0],
#            [ 0,  0,  0,  1]]
#            
# m = Matrix[[ 0, -1,  0, -1],
#            [ 1,  0,  0, -2],
#            [ 0,  0,  1, -3],
#            [ 0,  0,  0,  1]]
#            
# xc = Matrix[[0],
#             [0],
#             [-1],
#             [1]]
#             
# puts "#{m * xc}"

dn = 1.0
df = 11.0
w  = 0.5
h  = 0.4

orthographic = Matrix[[2.0 / w,     0,                    0,                           0],
                      [    0, 2.0 / h,                    0,                           0],
                      [    0,     0, (dn + df)/ (dn - df), 2.0 * ((dn * df) / (dn - df))],
                      [    0,     0,                    0,                           0]]

perspective = Matrix[[2.0 * (dn / w),            0, 0, 0],
                     [           0, 2.0 * (dn / h), 0, 0],
                     [           0,            0, -(2.0 / (df - dn)), -((df + dn) / (df - dn))],
                     [           0,            0, 0, 0]]
                     
puts "#{orthographic}"
puts "#{perspective}"