#include "objloader.h"
#include <stdio.h>
#include <iostream>


OBJLoader::OBJLoader () : 
	mFileName (""), mVertices(NULL), mTextureCoordinates(NULL), mNormals(NULL), mIndices(NULL), nIndices(0)
{
}

OBJLoader::OBJLoader (const char* file) : 
	mFileName (file), mVertices(NULL), mTextureCoordinates(NULL), mNormals(NULL), mIndices(NULL), nIndices(0)
{
}

void OBJLoader::setFile(const char* file) {
	this->mFileName = file;
}

OBJLoader::~OBJLoader (void)
{
	if (NULL != mVertices) {
		delete [] mVertices;
	}
	if (NULL != mTextureCoordinates) {
		delete [] mTextureCoordinates;
	}
	if (NULL != mNormals) {
		delete [] mNormals;
	}
	if (NULL != mIndices) {
		delete [] mIndices;
	}
}


bool OBJLoader::init (void) 
{

	std::vector<float> tVertices;
	std::vector<float> tTextureCoordinates;
	std::vector<float> tNormals;
	std::vector<vertexInfo> tIndices;

	char line[256];

	FILE *f = fopen (mFileName.c_str(), "r");
	if (!f) {
		return false;
	}

	while(!feof(f)) {
		memset(line, 0, 256);
		fgets(line, 256, f);

		std::vector<std::string> tokens = tokenize(line, ' ', true);

		if (!tokens[0].compare("v")) {
			//vertex position

			for (unsigned int i = 1; i <= 3; ++i) {
				tVertices.push_back((float)atof(tokens[i].c_str()));
			}

		} else if (!tokens[0].compare("vt")) {
			//texture co-ordinate
			for (unsigned int i = 1; i <= 2; ++i) {
				tTextureCoordinates.push_back((float)atof(tokens[i].c_str()));
			}

		} else if (!tokens[0].compare("vn")) {
			//vertex normal
			for (unsigned int i = 1; i <= 3; ++i) {
				tNormals.push_back((float)atof(tokens[i].c_str()));
			}
		} else if (!tokens[0].compare("f")) {
			//face

			for (unsigned int i = 1; i < 4; ++i) {
				std::vector<std::string> indices = tokenize(tokens[i].c_str(),'/');
				if (indices.size() > 1) {
					int vIndice = atoi(indices[0].c_str()) - 1;
					int tIndice = -1;
					int nIndice = -1;

					if (indices[1].compare("")) { // texture coordinate provided
						tIndice = atoi(indices[1].c_str()) - 1;
					}
					if (indices[2].compare("")) { //normal provided
						nIndice = atoi(indices[2].c_str()) - 1;
					}

					vertexInfo newVertex(vIndice, tIndice, nIndice);

					tIndices.push_back(newVertex);

				} else {
					int vIndice = atoi(indices[0].c_str()) - 1;

					vertexInfo newVertex(vIndice);

					tIndices.push_back(newVertex);
				}
			}
		} else if (!tokens[0].compare("o")) {
			//object name
		} else if (!tokens[0].compare("g")) {
			//group name
		} else if (!tokens[0].compare("usemtl")) {
			//material name
		}
	}
	fclose(f);	

	fprintf(stdout, "Indexing...\n");

	for (unsigned int i = 0; i < tIndices.size() - 1; ++i) {
		vertexInfo vi_base = tIndices[i];
		for (unsigned int j = i + 1; j < tIndices.size(); ++j) {
			vertexInfo vi = tIndices[j];
			if (vi_base.tIndice != -1) {
				if (vi_base.vIndice == vi.vIndice && vi_base.tIndice != vi.tIndice) {
					vi.vIndice = tVertices.size() / 3;
					tVertices.push_back(tVertices[vi_base.vIndice * 3]);
					tVertices.push_back(tVertices[vi_base.vIndice * 3 + 1]);
					tVertices.push_back(tVertices[vi_base.vIndice * 3 + 2]);
					tIndices[j] = vi;
				}
			}
		}
	}

	fprintf(stdout, "Done!\n");

	nIndices = tIndices.size();
	nVertices = tVertices.size() / 3;


	if (NULL == mIndices) {
		mIndices = new unsigned int[tIndices.size()];
	}

	std::vector<vertexInfo>::iterator vertexInfoInterator = tIndices.begin();

	for (unsigned int i = 0; vertexInfoInterator != tIndices.end(); ++vertexInfoInterator, ++i) {
		vertexInfo vi = *vertexInfoInterator;

		mIndices[i] = vi.vIndice;

		if (NULL == mVertices) {
			mVertices = new float[nVertices * 3];
		}


		mVertices[vi.vIndice * 3] = tVertices[vi.vIndice * 3];
		mVertices[vi.vIndice * 3 + 1] = tVertices[vi.vIndice * 3 + 1];
		mVertices[vi.vIndice * 3 + 2] = tVertices[vi.vIndice * 3 + 2];

		if (vi.tIndice > -1) {
			if (NULL == mTextureCoordinates) {
				mTextureCoordinates = new float[nVertices * 2];
			}
			mTextureCoordinates[vi.vIndice * 2] = tTextureCoordinates[vi.tIndice * 2];
			mTextureCoordinates[vi.vIndice * 2 + 1] = tTextureCoordinates[vi.tIndice * 2 + 1];
		}

		if (vi.nIndice > -1) {
			if (NULL == mNormals) {
				mNormals = new float[nVertices * 3];
			}
			mNormals[vi.vIndice * 3] = tNormals[vi.nIndice * 3];
			mNormals[vi.vIndice * 3 + 1] = tNormals[vi.nIndice * 3 + 1];
			mNormals[vi.vIndice * 3 + 2] = tNormals[vi.nIndice * 3 + 2];
		}
	}

	return true;
}

void OBJLoader::print (void)
{
	std::cout << "printing..." << std::endl;
	std::cout << "vertices" << std::endl;
	if (NULL != mVertices) {
		for (unsigned int i = 0; i < nVertices * 3; i+=3) {
			std::cout << mVertices[i] << " " << mVertices[i + 1] << " " << mVertices[i + 2] << std::endl;
		}
	}
	std::cout << "texture coordinates" << std::endl;
	if (NULL != mTextureCoordinates) {
		for (unsigned int i = 0; i < nVertices * 2; i += 2) {
			std::cout << mTextureCoordinates[i] << " " << mTextureCoordinates[i+1]  << std::endl;
		}
	}
	std::cout << "normals" << std::endl;
	if (NULL != mNormals) {
		for (unsigned int i = 0; i < nVertices * 3; i+=3) {
			std::cout << mNormals[i] << " " << mNormals[i + 1] << " " << mNormals[i + 2] << std::endl;
		}
	}
	std::cout << "indices" << std::endl;
	if (NULL != mIndices) {
		for (unsigned int i = 0; i < nIndices; i+=3) {
			std::cout << mIndices[i] << " " << mIndices[i+1] << " " << mIndices[i+2] << std::endl;
		}
	}
}

std::vector<std::string> OBJLoader::tokenize(const char* line, const char token, bool skip)
{
	std::string sLine(line);
	std::vector<std::string> tokens;

	int begin = 0;
	int pos = sLine.find_first_of(token, begin);

	while (pos != std::string::npos) {
		std::string newToken;

		if (begin != pos) {
			newToken = sLine.substr(begin, pos - begin);
		} 

		begin = pos + 1;
		tokens.push_back(newToken);

		if (skip) {
			pos = sLine.find_first_not_of(token, begin);
			begin = pos;
		}

		pos = sLine.find_first_of(token, begin);
	}

	if (begin != std::string::npos) {
		std::string newToken = sLine.substr(begin);
		tokens.push_back(newToken);
	}
	return tokens;
}
