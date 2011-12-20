#ifndef WAVEFRONT_FILE_H
#define WAVEFRONT_FILE_H

#include <vector>
#include "matrix.hpp"

class model {
	public:
		model();
		model(string filename);
		vector< matrix<3,1> > vertices;
		vector< vector< int > > faces;
		matrix<3,1> colour;
	private:
		void scale(float s); // don't use this
};

#endif
