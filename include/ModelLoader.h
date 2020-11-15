#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>

struct vec3 {
	float x;
	float y;
	float z;
};
struct vec2 {
	float x;
	float y;
};
struct Model {
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> textures;
};
class ModelLoader {
public:
	template<typename Out>
	inline static void split(const std::string& s, char delim, Out result) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			*(result++) = item;
		}
	}
	inline static std::vector<std::string> split(const std::string& s, char delim) {
		std::vector<std::string> elements;
		split(s, delim, std::back_inserter(elements));
		return elements;
	}
	inline static Model loadOBJ(const char* path)
	{
		std::vector<vec3> vertices;
		std::vector<vec2> textures;
		std::vector<vec3> normals;
		Model m;

		try {
			std::ifstream file(path);
			std::string line;

			while (getline(file, line)) {
				if (line.substr(0, line.find(' ')) == "v") {
					line.erase(0, 1);
					float x, y, z;
					std::stringstream ls = std::stringstream(line);
					ls >> x >> y >> z;
					vertices.push_back({ x,y,z });
				}
				if (line.substr(0, line.find(' ')) == "vt") {
					line.erase(0, 2);
					float x, y;
					std::stringstream ls = std::stringstream(line);
					ls >> x >> y;
					textures.push_back({ x,y });
				}
				if (line.substr(0, line.find(' ')) == "vn") {
					line.erase(0, 2);
					float x, y, z;
					std::stringstream ls = std::stringstream(line);
					ls >> x >> y >> z;
					normals.push_back({ x,y,z });
				}
				if (line.substr(0, line.find(' ')) == "f") {
					line.erase(0, 1);
					
					std::vector<std::string> ls = split(line, '/');
					int vertex_index = atoi(ls[0].c_str());
					int texture_index = atoi(ls[1].c_str());
					int normal_index = atoi(ls[2].c_str());

					m.vertices.push_back(vertices[vertex_index - 1].x);
					m.vertices.push_back(vertices[vertex_index - 1].y);
					m.vertices.push_back(vertices[vertex_index - 1].z);

					m.textures.push_back(textures[texture_index - 1].x);
					m.textures.push_back(textures[texture_index - 1].y);
					
					m.normals.push_back(normals[normal_index - 1].x);
					m.normals.push_back(normals[normal_index - 1].y);
					m.normals.push_back(normals[normal_index - 1].z);
				}
			}

			file.close();
		}
		catch (std::ifstream::failure ex) {
			assert("File not found");
		}

		return m;
	}
	inline static Model loadSTL(const char* path)
	{
		Model m;

		try {
			std::ifstream file(path, std::ios::binary);
			std::string header = readHeader(file);
			int size = getInt(file);

			for (int i = 0; i < size; i++) {
				for (int j = 0; j < 9; j++) {
					float f = getFloat(file);
					m.vertices.push_back(f);
				}
			}
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < 3; j++) {
					m.normals.push_back(getFloat(file));
				}
				for (int j = 0; j < 3; j++) {
					m.normals.push_back(getFloat(file));
				}
				for (int j = 0; j < 3; j++) {
					m.normals.push_back(getFloat(file));
				}
			}
#ifdef MODELLOADER_VERBOSE
			std::cout << header;
			std::cout << "\nSize: " << size << "\n";
#endif
			file.close();
		}
		catch (std::ifstream::failure ex) {
			assert("File not found");
		}
		
		return m;
	}
private:
	inline static float getFloat(std::ifstream& stream)
	{
		float f;
		stream.read((char*)&f, 4);

		return f;
	}
	inline static int getInt(std::ifstream& stream)
	{
		int i;
		stream.read((char*)&i, 4);

		return i;
	}
	inline static std::string readHeader(std::ifstream &stream)
	{
		char* head = new char[80];
		stream.read(head, 80);

		return std::string(head);
	}
};