#include <fstream>
#include <iostream>
#include <stack>
#include "primitives/primitives.h"
#include <istream>
#include <sstream>
#include "easylogging++.h"
#include "primitives/bounding-box-accelerator.h"

using namespace std;
using namespace raytracer;
using namespace math;
using namespace primitives;

Primitive primitives::mesh(const std::string& file)
{
	ifstream input(file);
	stack<Primitive> stapeltje;

	string sort;
	double x1, y1, z1, x2, y2, z2, x3, y3, z3;

	while (true)
	{
		input >> sort;
		// triangle, box or stop
		if (sort == "triangle")
		{
			// effe alle puntjes inlezen
			input >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
			// Daar gaan we dan wel degelijk punten van maken
			const Point3D& p1 = Point3D(x1, y1, z1);
			const Point3D& p2 = Point3D(x2, y2, z2);
			const Point3D& p3 = Point3D(x3, y3, z3);
			// Daar maken we een driehoek van
			Primitive t = triangle(p1, p2, p3);
			// Driehoek zetten we mooi op de stapel
			stapeltje.push(t);
		}
		else if (sort == "box")
		{
			// zien hoeveel we der in een doos moeten douwen
			int x = 0;
			input >> x;
			// we willen even lisjtje hebben van alle driehoeken en/of dozen
			// die we in onze doos steken
			std::vector<Primitive> lijstvandriehoeken;
			for (int i = 0; i < x; i++)
			{
				Primitive driehoekOFdoos = stapeltje.top();
				// we verwijderen den driehoek van de stapel
				stapeltje.pop();
				// we steken hem hier in onze lijst
				lijstvandriehoeken.push_back(driehoekOFdoos);

			}
			// driehoeken OF DOZEN zijn hier van de stapel gepegeld

			// we maken een leuke doos
			Primitive boundenDoos =
				bounding_box_accelerator(make_union(lijstvandriehoeken));
			// we bewaren deze doos even op de stapel goed?
			stapeltje.push(boundenDoos);
		}
		else if (sort == "stop")
		{
			// De laatste ?2? dozen staan hier nog op de stapel
			std::vector<Primitive> laatsteDozen;
			for (int i = 0; i < stapeltje.size(); i++)
			{
				Primitive doosje = stapeltje.top();
				stapeltje.pop();
				laatsteDozen.push_back(doosje);
				// zoals eerder hierboven maken we een lijstje
				// met deze keer onze laatste dozen
			}
			// stapeltje zou nu leeg moeten zijn, who knows
			// We maken onze aller laatste doos
			Primitive MeesterDoos =
				bounding_box_accelerator(make_union(laatsteDozen));
			// doos lekker trg op stapel, is al een zware doos nu
			stapeltje.push(MeesterDoos);
			// tis gedaan dan zeker
			break;
		}
		else
		{
			cout << "De soort op het begin van u lijn is ni just." <<
				" Salut en de kost. Aja dit is de soort da we gevonden hebben "
				<< sort << endl;
		}
	}
	Primitive GodDoos = stapeltje.top();
	return GodDoos;
}

