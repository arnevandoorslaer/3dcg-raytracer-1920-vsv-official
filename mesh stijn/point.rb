class Point
    attr_accessor :x, :y, :z

    def initialize(x, y, z)
        @x = x.to_f
        @y = y.to_f
        @z = z.to_f
    end

    def to_s()
        "#{@x} #{@y} #{@z}"
    end
end