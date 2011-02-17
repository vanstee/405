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

# 1.
# # c0 = xc + (zp * uc)
# 
# xc = Vector[-2, 1, 1]
# zp = 0.5
# c = Vector[0, 4, 0] - Vector[-2, 1, 1]
# uc = c / c.r
# c0 = xc + (zp * uc)
# 
# # ux = (uc cross vup).normalized
# # uz = -uc
# # uy = uz cross ux
# # but x and y are flipped
# 
# vup = Vector[0, 1, 0]
# x = uc.cross(vup)
# ux = x / x.r
# uz = uc * -1
# uy = uz.cross(ux)
# 
# temp = ux
# ux = uy
# uy = temp
# 
# puts "ux = #{ux}"
# puts "uy = #{uy}"
# puts "uz = #{uz}"

# 2.

p = Vector[1, 5, 0]
e = Vector[8, 3, 0]
x = Vector[2, 2, 0]

px = p - x
upx = px / px.r
ex = e - x
uex = ex / ex.r
pe = upx.dot(uex)

xp = x - p
uxp = xp / xp.r
s0 = Vector[4, 1, 0]
s1 = Vector[0, 3, 0]
s = s1 - s0
us = s / s.r
n = us.cross(Vector[0, 0, 1])
pn = uxp.dot(n)

puts pn * 2
puts pe
puts pe - (pn * 2)
puts (pe - (pn * 2)) ** 30






# xl = Vector[1, 5, 0]
# xs = Vector[2, 2, 0]
# ls = xs - xl
# uls = ls / ls.r
# 
# 
# puts n.dot(uls) ** 2
# puts n.dot(uls)


# puts uex.dot(upx) ** 30