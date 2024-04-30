#include "core/parse.h"

ParseResult try_parse_uint(const char* str, u64* out) {
	if (!str || !out) {
		return PARSE_FAILURE_NULL_INPUT;
	}

	if (str[0] == '\0') {
		return PARSE_FAILURE_BAD_INPUT;
	}

	if (str[0] == '-') {
		return PARSE_FAILURE_UNEXPECTED_SIGN;
	}
	
	u64 result = 0;
	for (int i = 0; str[i] != '\0'; i++) {
		if (i > 20) {
			return PARSE_FAILURE_OVERFLOW;
		}
		
		if (str[i] < '0' || str[i] > '9') {
			return PARSE_FAILURE_UNEXPECTED_CHAR;
		}
		
		u64 next = result * 10 + (str[i] - '0');
		if (result > next) {
			return PARSE_FAILURE_OVERFLOW;
		}
		result = next;
	}

	*out = result;
	return PARSE_SUCCESS;
}

const char* parse_result_to_str(ParseResult res) {
	switch (res) {
		case PARSE_FAILURE_NULL_INPUT:
			return "Null Parameter";
		case PARSE_FAILURE_BAD_INPUT:
			return "Unparseable String";
		case PARSE_FAILURE_UNEXPECTED_SIGN:
			return "Value is Negative";
		case PARSE_FAILURE_UNEXPECTED_CHAR:
			return "String Contains Unexpected Character";
		case PARSE_FAILURE_OVERFLOW:
			return "Value is too Big";
		case PARSE_SUCCESS:
			return "Success";
		default: 
				return "Unknown Failure";
	}
	
	return "Unknown Failure";
}
