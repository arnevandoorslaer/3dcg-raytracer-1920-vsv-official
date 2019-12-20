import sys

class Point:
    def __init__(self, x, y, z):
        self.x = float(x)
        self.y = float(y)
        self.z = float(z)

    def __str__(self):
        return '{} {} {}'.format(self.x, self.y, self.z)

class Triangle:
    def __init__(self, punt1, punt2, punt3):
        self.p1 = punt1
        self.p2 = punt2
        self.p3 = punt3

    def __str__(self):
        return 'triangle {} {} {}'.format(self.p1, self.p2, self.p3)
    
    def min_x(self):
        return min(self.p1.x, self.p2.x, self.p3.x)

    def max_x(self):
        return max(self.p1.x, self.p2.x, self.p3.x)

    def min_y(self):
        return min(self.p1.y, self.p2.y, self.p3.y)

    def max_y(self):
        return max(self.p1.y, self.p2.y, self.p3.y)

    def max_z(self):
        return max(self.p1.z, self.p2.z, self.p3.z)

    def min_z(self):
        return min(self.p1.z, self.p2.z, self.p3.z)
