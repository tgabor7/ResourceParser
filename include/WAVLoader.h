#pragma once
#include <fstream>
enum Format {
	STEREO16,
	STEREO8,
	MONO16,
	MONO8
};
struct Sound {
	int format;
	char* data;
	int freq;
};
class WAVLoader {
public:
	inline static Sound loadWAV(const char* path)
	{
		Sound s;
		std::ifstream file(path, std::ios::in | std::ios::binary);
		
		int chunkid, chunksize, samplerate, subchunkid, subchunksize, audioformat, freq, byterate, subchunk2id, size;
		short numchannels;
		short bitspersample;
		Format format;
		char* sh = new char[2];

		file.read((char*)&chunkid, 4);
		file.read((char*)&chunksize, 4);
		file.read((char*)&samplerate, 4);
		file.read((char*)&subchunkid, 4);
		file.read((char*)&subchunksize, 4);
		file.read((char*)&audioformat, 2);
		file.read((char*)&numchannels, 2);
		file.read((char*)&freq, 4);
		file.read((char*)&byterate, 4);
		file.read(sh, 2);
		//memcpy(&numchannels, idk, 2);
		file.read((char*)&bitspersample, 2);
		file.read((char*)&subchunk2id, 4);
		file.read((char*)&size, 4);

		char* data = new char[size];
		file.read(data, size);

		bool stereo = (samplerate > 1);

		switch (bitspersample) {
		case 16:
			if (stereo)
				format = STEREO16;
			else
				format = MONO16;
		case 8:
			if (stereo)
				format = STEREO8;
			else
				format = MONO8;
		default:
			format = MONO16;
		}
		s.format = format;
		s.data = data;
		s.freq = freq;

		return s;
	}
};