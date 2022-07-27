#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
using namespace std;

int main()
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile("test", aiProcess_Triangulate | aiProcess_FlipUVs);

	cout << "test" << endl;
	system("pause");
	return 0;
}