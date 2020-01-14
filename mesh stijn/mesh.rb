require_relative "triangle"
require_relative "functions"

infile = "temp.mesh"
meshfile = File.readlines(infile, "r")[0].split("\n")
output = infile.concat(".out.txt")
@result = ""

no_of_points = meshfile.slice!(0)
points = []
for i in 0..no_of_points.to_i()-1 do
    coords = meshfile.slice!(0).split(' ')
    point = Point.new(coords[0], coords[1], coords[2])
    points << point
end

no_of_triangles = meshfile.slice!(0)
triangles = []
for i in 0..no_of_triangles.to_i()-1 do
    coords = meshfile.slice!(0).split(' ')
    triangle = Triangle.new(points[coords[0].to_i()], points[coords[1].to_i()], points[coords[2].to_i()])
    triangles << triangle
end

def create_box_structure(triangles)
    if triangles.length() > 2
        widths = {
            x_width: highest("x", triangles) - lowest("x", triangles),
            y_width: highest("y", triangles) - lowest("y", triangles),
            z_width: highest("z", triangles) - lowest("z", triangles),
        }

        first = []
        second = []

        if widths.values().max == widths[:x_width]
            min_x = lowest("x", triangles)
            center_x = min_x + (widths[:x_width] / 2)
            for triangle in triangles
                in_box("x", triangle, min_x, center_x) ? first << triangle : second << triangle
            end

        elsif widths.values().max == widths[:y_width]
            min_y = lowest("y", triangles)
            center_y = min_y + (widths[:y_width] / 2)
            for triangle in triangles
                in_box("y", triangle, min_y, center_y) ? first << triangle : second << triangle
            end

        elsif widths.values().max == widths[:z_width]
            min_z = lowest("z", triangles)
            center_z = min_z + (widths[:z_width] / 2)
            for triangle in triangles
                in_box("z", triangle, min_z, center_z) ? first << triangle : second << triangle
            end
        end

        if first.length() == 0
            range = (second.length().to_f() / 2).floor
            for i in 1..range
                first << second.slice!(0)
            end
        end

        create_box_structure(first)
        create_box_structure(second)
        @result.concat("box 2\n")

    elsif triangles.length() > 0
        for triangle in triangles do
            @result.concat(triangle.to_s())
        end
        @result.concat("box #{triangles.length()}\n")
    end
end

create_box_structure(triangles)
@result.concat("stop")
File.open(output, "w") { |f| f.write @result}
puts "mesh file succesfully written to #{output}"