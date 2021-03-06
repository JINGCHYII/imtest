#ifndef MESH_H
#define MESH_H

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <vector>
using namespace std;

#define MAX_BONE_INFLUENCE 4

struct LVertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
    // tangent
    glm::vec3 Tangent;
    // bitangent
    glm::vec3 Bitangent;
	//bone indexes which will influence this vertex
	//int m_BoneIDs[MAX_BONE_INFLUENCE];
	//weights from each bone
	//float m_Weights[MAX_BONE_INFLUENCE];
};

struct LTexture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    // mesh Data
    vector<LVertex>       vertices;
    vector<unsigned int> indices;
    vector<LTexture>      textures;
    unsigned int VAO;

    // constructor
    Mesh(vector<LVertex> vertices, vector<unsigned int> indices, vector<LTexture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
    }
};
#endif
