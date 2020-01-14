require_relative "triangle"
require_relative "functions"

meshfile = File.readlines("temp.mesh", "r")[0].split("\n")
output = "output.txt"
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
        puts "inside first if"
        widths = {
            x_width: highest("x", triangles) - lowest("x", triangles),
            y_width: highest("y", triangles) - lowest("y", triangles),
            z_width: highest("z", triangles) - lowest("z", triangles),
        }

        first = []
        second = []

        puts widths.max_by{|k,v| v}[0].to_s()
        puts widths[:x_width].class

        if widths.values().max == widths[:x_width]
            min_x = lowest("x", triangles)
            center_x = min_x + (widths[:x_width] / 2)
            puts "#{min_x} #{center_x}"
            puts triangles
            for triangle in triangles
                in_box("x", triangle, min_x, center_x) ? first << triangle : second << triangle
            end
            puts first
            puts second

        elsif widths.values().max == widths[:y_width]
            min_y = lowest("y", triangles)
            center_y = min_y + (widths[:y_width] / 2)
            puts "#{min_x} #{center_x}"
            for triangle in triangles
                in_box("y", triangle, min_y, center_y) ? first << triangle : second << triangle
            end

        elsif widths.values().max == widths[:z_width]
            min_z = lowest("z", triangles)
            center_z = min_z + (widths[:z_width] / 2)
            puts "#{min_x} #{center_x}"
            for triangle in triangles
                in_box("z", triangle, min_z, center_z) ? first << triangle : second << triangle
            end
        end

        if first.length() == 0
            for i in 0..(second.length.to_f() / 2).ceil
                first << second.slice!(0)
            end
        end

        create_box_structure(first)
        create_box_structure(second)
        @result.concat("box 2\n")

    elsif triangles.length() > 0
        puts "inside second if"
        for triangle in triangles do
            @result.concat(triangle.to_s())
        end
        @result.concat("box #{triangles.length()}")
    end
end

create_box_structure(triangles)
@result.concat("stop")
puts @result
File.open(output, "w") { |f| f.write @result}
puts "mesh file succesfully written to #{output}"