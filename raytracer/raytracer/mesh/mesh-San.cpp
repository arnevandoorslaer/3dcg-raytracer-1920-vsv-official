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

Primitive primitives::mesh(const std::string& filename)
{
	ifstream in(filename);
	CHECK(in) << "Failed to open " << filename;

	stack <Primitive> stack_hierarchy;

	char tag;
	double x1, y1, z1, x2, y2, z2, x3, y3, z3;

	while (true)
	{
		in >> tag;

		if (tag == 't')
		{
			in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;

			const Point3D& p1 = Point3D(x1, y1, z1);
			const Point3D& p2 = Point3D(x2, y2, z2);
			const Point3D& p3 = Point3D(x3, y3, z3);

			Primitive t = triangle(p1, p2, p3);
			stack_hierarchy.push(t);
			// Maak triangle aan
			// Steek triangle op stack
		}
		else if (tag == 'b')
		{
			int amount = 0;
			in >> amount;

			std::vector<Primitive> list;

			for (int i = 0; i < amount; i++)
			{
				Primitive t = stack_hierarchy.top();
				stack_hierarchy.pop();
				list.push_back(t);

			}

			Primitive bb = bounding_box_accelerator(make_union(list));
			stack_hierarchy.push(bb);
		}
		else if (tag == 'x')
		{
			std::vector<Primitive> box_list;
			for (int i = 0; i < stack_hierarchy.size(); i++)
			{
				Primitive box = stack_hierarchy.top();
				stack_hierarchy.pop();
				box_list.push_back(box);
			}

			Primitive bigbox = bounding_box_accelerator(make_union(box_list));
			stack_hierarchy.push(bigbox);
			break;
		}
		else
		{
			CHECK(false) << "Unknown tag " << tag;
		}
	}

	Primitive final_bb = stack_hierarchy.top();
	return final_bb;

}


