//===----------------------------------------------------------------------===//
//                         DuckDB
//
// postgres_parser.hpp
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include <string>
#include <vector>
#include "nodes/pg_list.hpp"
#include "pg_simplified_token.hpp"
// #include "duckdb/common/vector.hpp"

namespace hiqe {
class PostgresParser {
public:
	PostgresParser();
	~PostgresParser();

	bool success;
	hiqe_libpgquery::PGList *parse_tree;
	std::string error_message;
	int error_location;
public:
	void Parse(const std::string &query);
	static std::vector<hiqe_libpgquery::PGSimplifiedToken> Tokenize(const std::string &query);

	static bool IsKeyword(const std::string &text);
	static std::vector<hiqe_libpgquery::PGKeyword> KeywordList();

	static void SetPreserveIdentifierCase(bool downcase);
};

}
