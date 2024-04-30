#pragma once

#include "core/nums.h"

typedef enum ParseResult {
	PARSE_SUCCESS = 0,
	
	PARSE_FAILURE_NULL_INPUT = 1,
	PARSE_FAILURE_BAD_INPUT = 2,
	
	PARSE_FAILURE_UNEXPECTED_SIGN = 3,	
	PARSE_FAILURE_UNEXPECTED_CHAR = 4,	
	PARSE_FAILURE_OVERFLOW = 5,

} ParseResult;

/// Returns 'PARSE_SUCCESS' for any Value Between 0 and u64_MAX
ParseResult try_parse_uint(const char* str, u64* out);

const char* parse_result_to_str(ParseResult res); 
