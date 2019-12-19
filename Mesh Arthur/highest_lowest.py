import sys
from PointAndTriangle import Point
from PointAndTriangle import Triangle

def lowest_x(driehoeken):
    res = driehoeken[0].min_x()
    for d in driehoeken:
        if d.min_x() < res:
            res = d.min_x()
    return res
def highest_x(driehoeken):
    res = driehoeken[0].max_x()
    for d in driehoeken:
        if d.max_x() > res:
            res = d.max_x()
    return res
def lowest_y(driehoeken):
    res = driehoeken[0].min_y()
    for d in driehoeken:
        if d.min_y() < res:
            res = d.min_y()
    return res
def highest_y(driehoeken):
    res = driehoeken[0].max_y()
    for d in driehoeken:
        if d.max_y() > res:
            res = d.max_y()
    return res
def lowest_z(driehoeken):
    res = driehoeken[0].min_z()
    for d in driehoeken:
        if d.min_z() < res:
            res = d.min_z()
    return res
def highest_z(driehoeken):
    res = driehoeken[0].max_z()
    for d in driehoeken:
        if d.max_z() > res:
            res = d.max_z()
    return res