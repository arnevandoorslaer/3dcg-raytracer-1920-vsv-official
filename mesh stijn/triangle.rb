require_relative "point"



class Triangle

    def initialize(*points)
        @p1, @p2, @p3 = points
    end

    def to_s()
        "triangle #{@p1} #{@p2} #{@p3}\n"
    end

    def min(attr)
        [@p1.send(attr), @p2.send(attr), @p3.send(attr)].min
    end

    def max(attr)
        [@p1.send(attr), @p2.send(attr), @p3.send(attr)].max
    end
end