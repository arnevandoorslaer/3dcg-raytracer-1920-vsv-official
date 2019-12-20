import sys
from PointAndTriangle import Point
from PointAndTriangle import Triangle
import highest_lowest

# OP DESKTOP
# bunny = open("H:/Users/Gebruiker/Documents/3D/"
# "3dcg-raytracer-1920-vsv-official/Mesh Arthur/bunny.mesh", "r")
# schrijfbestand = "C:/Users/kinga/Documents/outputBunny2.txt"

# OP LAPTOP
bunny = open("temp.mesh", "r")
schrijfbestand = "D:/Documenten/Workspace3D/3dcg-raytracer-1920-vsv-official/Mesh Arthur/output.txt"


aantal_punten = int(float(bunny.readline()))
print('There are {} points to be created!'.format(aantal_punten))

# Even lekker alle punten inlezen goed ?
alle_punten = []
for i in range (0, aantal_punten):
    volgende_regel = bunny.readline()
    clean_regel = volgende_regel.strip('\n').strip('\r')
    coords = clean_regel.split(" ")
    punt = Point(coords[0], coords[1], coords[2])
    alle_punten.append(punt)
    print('added {} to the list!'.format(punt))

aantal_driehoeken = int(float(bunny.readline()))
print('There are {} triangles to be created!'.format(aantal_driehoeken))

# Even lekker alle driehoekjes inlezen dan
alle_driehoeken = []
for i in range (0, aantal_driehoeken):
    volgende_regel = bunny.readline()
    clean_regel = volgende_regel.strip('\n').strip('\r')
    punties = clean_regel.split(" ")
    driehoek = Triangle(alle_punten[int(punties[0])],
        alle_punten[int(punties[1])],alle_punten[int(punties[2])])
    alle_driehoeken.append(driehoek)
    print('added {} to the list!'.format(driehoek))

# REPETITIVE ===========================================
# CODE CODE CODE CODE CODE CODE CODE CODE CODE CODE CODE
def x_in_doos(t, min, max):
    return (t.min_x() > min) and (t.max_x() < max)
def y_in_doos(t, min, max):
    return (t.min_y() > min) and (t.max_y() < max)
def z_in_doos(t, min, max):
    return (t.min_z() > min) and (t.max_z() < max)
# CODE CODE CODE CODE CODE CODE CODE CODE CODE CODE CODE
# REPETITIVE ===========================================

def schrijf_doosje(driehoeken):
    schrijver = open(schrijfbestand, "a")
    for d in driehoeken:
        schrijver.write(str(d) + "\n")
    schrijver.write("box " + str(len(driehoeken)) + "\n")
    schrijver.close()

def create_box_structure(driehoeken):
    if len(driehoeken) > 2:
        x_width = highest_lowest.highest_x(driehoeken) - highest_lowest.lowest_x(driehoeken)
        y_width = highest_lowest.highest_y(driehoeken) - highest_lowest.lowest_y(driehoeken)
        z_width = highest_lowest.highest_z(driehoeken) - highest_lowest.lowest_z(driehoeken)
        
        deel1 = []
        deel2 = []
        # de breedste dimensie opsplitsen = optimaal
        if max(x_width, y_width, z_width) == x_width:
            min_x = highest_lowest.lowest_x(driehoeken)
            midden_x = min_x + (x_width / 2)
            for d in driehoeken:
                deel1.append(d) if x_in_doos(d, min_x, midden_x) else deel2.append(d)
        elif max(x_width, y_width, z_width) == y_width:
            min_y = highest_lowest.lowest_y(driehoeken)
            midden_y = min_y + (y_width / 2)
            for d in driehoeken:
                deel1.append(d) if y_in_doos(d, min_y, midden_y) else deel2.append(d)
        elif max(x_width, y_width, z_width) == z_width:
            min_z = highest_lowest.lowest_z(driehoeken)
            midden_z = min_z + (z_width / 2)
            for d in driehoeken:
                deel1.append(d) if z_in_doos(d, min_z, midden_z) else deel2.append(d)
        
        # kleine probleem fixen weetje
        if len(deel1) == 0:
            for i in range (len(deel2) // 2):
                deel1.append(deel2[0])
                deel2.remove(deel2[0])
        # hier is dan de recursie
        create_box_structure(deel1)
        create_box_structure(deel2)
        # wa dozen maken om de vorige dozen in te steken
        dozenmaken = open(schrijfbestand, "a")
        dozenmaken.write("box 2\n")
        dozenmaken.close()

    elif len(driehoeken) > 0:
        schrijf_doosje(driehoeken)
    else:
        return

# File leegmaken als die al bestaat
clearFile = open(schrijfbestand, "w")
clearFile.write("")
clearFile.close()

#laten schrijven he
print('Bounding boxes are being made...')
create_box_structure(alle_driehoeken)

# afsluiten
print("Processing done, closing file...")
sluit = open(schrijfbestand, "a")
sluit.write("stop\n")
sluit.close()
bunny.close()
print("Application finished!")







