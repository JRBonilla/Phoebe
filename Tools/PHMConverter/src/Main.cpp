#include "PHMWriter.h"
#include "Utils.h"

using namespace ph::tools;

static std::unordered_map<Vertex, uint> s_IndexMapping;
static std::vector<Vertex>              s_Vertices;
static std::vector<uint>                s_Indices;
static uint                             s_VertexAttributes;

void InsertVertex(const Vec3& position, const Vec3& normal, const Vec2& uv, const Vec3& tangent, const Vec3& bitangent) {
	Vertex vertex = { position, normal, uv, tangent, bitangent };
	auto lookup = s_IndexMapping.find(vertex);
	if (lookup != s_IndexMapping.end()) {
		s_Indices.push_back(lookup->second);
	}
	else {
		uint index = s_Vertices.size();
		s_IndexMapping[vertex] = index;
		s_Indices.push_back(index);
		s_Vertices.push_back(vertex);
	}
}

void ProcessMesh(aiMesh* mesh, const aiScene* scene) {
	uint vertexCount = mesh->mNumVertices;
	for (uint i = 0; i < vertexCount; i++) {
		Vec3 position  = Vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		Vec3 normal    = Vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		Vec2 uv        = mesh->HasTextureCoords(0) ? Vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y) : Vec2();
		Vec3 tangent   = Vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
		Vec3 bitangent = Vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);

		s_VertexAttributes |= VertexAttribute::POSITION;
		s_VertexAttributes |= VertexAttribute::NORMAL;
		s_VertexAttributes |= VertexAttribute::UV;
		s_VertexAttributes |= VertexAttribute::TANGENT;
		s_VertexAttributes |= VertexAttribute::BITANGENT;

		InsertVertex(position, normal, uv, tangent, bitangent);
	}
}

void ProcessNode(aiNode* node, const aiScene* scene) {
	for (uint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene);
	}

	for (uint i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: PHMConverter filename [output_filename]\n");
		return -1;
	}
	std::string path = argv[1];
	std::vector<std::string> pathTokens = SplitString(path, "/\\");
	std::string filename = pathTokens.back();
	std::string directory = path.substr(0, path.find(pathTokens.back()));

	std::string outputPath;
	if (argc > 2) {
		outputPath = argv[2];
	}
	else {
		outputPath = directory + filename.substr(0, filename.find(".")) + ".phm";
	}

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		printf("Could not load model file: %s!\n", path.c_str());
		printf("ASSIMP ERROR: %s\n", importer.GetErrorString());
		return -1;
	}
	ProcessNode(scene->mRootNode, scene);

	PHMWriter writer(filename, s_VertexAttributes, s_Vertices, s_Indices);
	writer.Write(outputPath);

	return 0;
}