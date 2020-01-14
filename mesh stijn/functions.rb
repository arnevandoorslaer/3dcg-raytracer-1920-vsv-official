require_relative "triangle"

def lowest(attr, triangles)
    triangles.map{ |triangle| triangle.min(attr) }.min
end

def highest(attr, triangles)
    triangles.map{ |triangle| triangle.max(attr) }.max
end

def in_box(attr, triangle, min, max)
    (triangle.min(attr) > min) && (triangle.max(attr) < max)
end 