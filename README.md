# ResourceParser
c++ header library for parsing image/model files

# ModelParser
Parser .obj or .stl files in the following form.:
```cpp
struct Model{
	vector<float> vertices;
	vector<float> textures; //in case of .stl there are no texture coordinates
	vector<float> normals;
}
```

# BMPParser
Parses .bmp files the result is a pixel array.
```cpp
vector<unsigned char> pixels;
```

# Usage
The library uses cpp headers. You can just copy them into your project and include them no need to precompile them.

# Plans
Support for sound files, use indices for obj file where the same vertex is used multiple times.