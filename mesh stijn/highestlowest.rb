require_relative "triangle"

def lowest(attr, triangles)
    triangles.map{ |triangle| triangle.send("min", attr) }.min
end

def highest(attr, triangles)
    triangles.map{ |triangle| triangle.send("max", attr) }.min
end