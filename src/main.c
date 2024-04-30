#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "core/prng.h"
#include "core/parse.h"

#define USAGE_TEXT "Usage:\n hext [Options]\n\n  Options:\n  -w<1 | 2 | 4 | 8>: Byte Width of the Hex Values <Default: 1>\n  -h: Print This Text\n\n  REPL Commands:\n   q | quit: Quit\n   w<1 | 2 | 4 | 8> Change Hex Value Byte Width\n   h: Print This Text\n"

int main(int argc, char** argv) {
  u64 value_width = 1; // [0x00-0xff]
  for(int i = 1; i < argc; i++) {
    char* arg = argv[i];
    if (arg[0] != '-') {
			fprintf(stderr, "Argument Not Recognized: %s\n", arg);
			return 1;
		}

		switch (arg[1]) {
			case 'w': {
				u64 out = 0;
				ParseResult res = try_parse_uint(arg + 2, &out);
				if (res != PARSE_SUCCESS) {
					fprintf(stderr, "Failed to Parse Byte Width Argument: %s\n", arg);
					fprintf(stderr, "  %s\n", parse_result_to_str(res));
					return 1;
				}

				if (out != 1 && out != 2 && out != 4 && out != 8) {
					fprintf(stderr, "Byte Width Argument must be either 1, 2, 4 or 8. %llu is not valid\n", out);
					return 1;
				}

				value_width = out;
			} break;
			
			case 'h': {
				printf(USAGE_TEXT);
				return 0;
			} break;

			default: {
				fprintf(stderr, "Argument Not Recognized: %s\n", arg);
				return 1;
			} break;
		}
  }

  splitmix64_seed = time(0);
  xoshiro_seed[0] = splitmix64();
  xoshiro_seed[1] = splitmix64();
  xoshiro_seed[2] = splitmix64();
  xoshiro_seed[3] = splitmix64();
	
	u64 num = 0;
	bool8 repeat_num = 0;
	for (;;) {
		if (!repeat_num) {
			num = xoshiro256ss();
		} else {
			repeat_num = 0;
		}

		u64 truncated = num;

		switch (value_width) {
			case 1: {
				truncated = (u8)num;
				printf("0x%02hhX\n", (u8)truncated);
			} break;

			case 2: {
				truncated = (u16)num;
				printf("0x%04hX\n", (u16)truncated);
			} break;
			
			case 4: {
				truncated = (u32)num;
				printf("0x%08X\n", (u32)truncated);
			} break;

			case 8:
			default: {
				printf("0x%016llX\n", num);
			} break;
		}
		
		char buffer[21] = {0};
		printf(">");
		for (int i = 0; i < 20; i++) {
			int ch = getchar();
			if (ch == EOF || ch == '\n') break;
			buffer[i] = (u8)ch;
		}

		if (buffer[0] == 'q' || !strcmp(buffer, "quit")) {
			return 0;
		}

		if (buffer[0] == 'w') {
			repeat_num = 1;
			u64 out = 0;
			ParseResult res = try_parse_uint(buffer + 1, &out);
			if (res != PARSE_SUCCESS) {
				fprintf(stderr, "  Failed to Parse Byte Width Change Command: %s\n", buffer);
				continue;
			}

			if (out != 1 && out != 2 && out != 4 && out != 8) {
				fprintf(stderr, "  New Byte Width Must be either 1, 2, 4 or 8. %llu is not valid\n", out);
				continue;
			}

			value_width = out;
			continue;
		}


		if (buffer[0] == 'h') {
			printf("%s\n", USAGE_TEXT);
			repeat_num = 1;
			continue;
		}

		u64 guess = 0;
		ParseResult res = try_parse_uint(buffer, &guess);
		if (res != PARSE_SUCCESS || guess != truncated) {
			printf("  Wrong, Correct: %llu\n", truncated);
		} else {
			printf("  Correct\n");
		}
	}
}
