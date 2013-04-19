#ifndef _OBJ_LOADER_H_
#define _OBJ_LOADER_H_

#include <vector>
#include <string>

struct vertexInfo
{
	int vIndice;
	int tIndice;
	int nIndice;

	vertexInfo(int _vIndice, int _tIndice = -1, int _nIndice = -1) :
		vIndice(_vIndice), tIndice(_tIndice), nIndice(_nIndice) {}
};

class OBJLoader
{
protected:
	std::string mFileName;
	float* mVertices;
	float* mTextureCoordinates;
	float* mNormals;
	unsigned int* mIndices;

	unsigned int nIndices;
	unsigned int nVertices;

public:
	OBJLoader ();
	OBJLoader (const char* file);
	~OBJLoader (void);

	void setFile(const char* file);
	bool init (void);
	void print (void);

	const float* getVerticesArray(void) { return mVertices; }
	const float* getTextureCoordinatesArray(void) { return mTextureCoordinates; }
	const float* getNormalsArray(void) { return mNormals; }
	unsigned int* getIndicesArray(void) { return mIndices; }

	inline unsigned int getNIndices(void) { return nIndices; }
	inline unsigned int getNVertices(void) { return nVertices; }

private:
	std::vector<std::string> tokenize(const char* line, const char token, bool skip=false);
};

#endif //_OBJ_LOADER_H_