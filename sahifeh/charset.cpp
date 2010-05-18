#include <list>
#include <cstdio>
#include <stdint.h>

void hex_print(FILE* f, const uint8_t* data, uint32_t length)
{
	for (uint32_t i = 0; i < length; )
	{
		fprintf(f, "%.2x ", data[i]);
		if (++i % 4 == 0)
			fputc(' ', f);
	}
}

struct CharSet
{
	struct Block
	{
		uint8_t character;
		uint8_t unknown_0[48];

		void read(FILE* f)
		{
			fread(&character, 1, sizeof(character), f);
			fread(unknown_0, 1, sizeof(unknown_0), f);
		}

		void print(FILE* f) const
		{
			fprintf(f, "character: %u [%#.2x]\n", character, character);
			hex_print(f, unknown_0, sizeof(unknown_0));
			fputc('\n', f);
		}
	};

	typedef std::list<Block> Blocks;

	uint16_t version;		// [unsure]
	uint32_t header_size;		// [unsure]
	uint16_t unique_chars_no;	// [unsure] number of unique characters - 1
	uint16_t unknown_1;
	uint16_t block_size;		// [unsure] block size - 1
	uint32_t unknown_2;

	Blocks blocks;

	void read(FILE* f)
	{
		fread(&version, 1, sizeof(version), f);
		fread(&header_size, 1, sizeof(header_size), f);
		fread(&unique_chars_no, 1, sizeof(unique_chars_no), f);
		fread(&unknown_1, 1, sizeof(unknown_1), f);
		fread(&block_size, 1, sizeof(block_size), f);
		fread(&unknown_2, 1, sizeof(unknown_2), f);
		Block block;
		while (!feof(stdin))
		{
			block.read(f);
			blocks.push_back(block);
		}
	}

	void print(FILE* f) const
	{
		fprintf(f, "version: %u\n", version);
		fprintf(f, "header size: %u\n", header_size);
		fprintf(f, "unique charcters no.: %u\n", unique_chars_no + 1);
		fprintf(f, "unknown 1: %u\n", unknown_1);
		fprintf(f, "block size: %u\n", block_size + 1);
		fprintf(f, "unknown 2: %u\n", unknown_2);
		fprintf(f, "blocks no.: %u\n", (uint32_t) blocks.size());
		uint32_t i = 0;
		for (Blocks::const_iterator it = blocks.begin(); it != blocks.end(); ++it)
		{
			fprintf(f, "============ block #%u ============\n", ++i);
			it->print(f);
		}
	}
};

int main(int argc, const char* argv[])
{
	if (argc > 1 && freopen(argv[1], "r", stdin) == NULL)
	{
		fputs("Error: Failed to open input file\n", stderr);
		return 1;
	}
	CharSet charset;
	charset.read(stdin);
	charset.print(stdout);
	return 0;
}
