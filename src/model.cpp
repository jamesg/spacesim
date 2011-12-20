#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "graphics.hpp"
#include "model.hpp"

using namespace std;

model::model() {
}

model::model(string filename) {
	colour = (matrix<3,1>){{ {0.5,0.5,0.5} }};
	
	ifstream mFile(filename, ifstream::in);
	
	string s;
	while (mFile >> s) {
		if (s == "v") {
			matrix<3,1> v;
			mFile >> v.values[0][0];
			mFile >> v.values[0][1];
			mFile >> v.values[0][2];
			vertices.push_back(v);
		} else if (s == "f") {
			vector<int> f;
			int i;
			while (mFile.peek() == ' ') {
				mFile >> i;
				f.push_back(i-1);
			}
			faces.push_back(f);
		}
	}
	
	mFile.close();
}

void model::scale(float s) {
	vector< matrix<3,1> > newvertices;
	vector< matrix<3,1> >::iterator i;
	for (i = vertices.begin(); i != vertices.end(); i++) {
		newvertices.push_back(*i * s);
	}
	vertices = newvertices;
}

