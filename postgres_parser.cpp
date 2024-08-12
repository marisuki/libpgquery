#include "postgres_parser.hpp"

#include "pg_functions.hpp"
#include "parser/parser.hpp"
#include "parser/scansup.hpp"
#include "common/keywords.hpp"

namespace hiqe {

PostgresParser::PostgresParser() : success(false), parse_tree(nullptr), error_message(""), error_location(0) {}

void PostgresParser::Parse(const std::string &query) {
	hiqe_libpgquery::pg_parser_init();
	hiqe_libpgquery::parse_result res;
	pg_parser_parse(query.c_str(), &res);
	success = res.success;

	if (success) {
		parse_tree = res.parse_tree;
	} else {
		error_message = std::string(res.error_message);
		error_location = res.error_location;
	}
}

std::vector<hiqe_libpgquery::PGSimplifiedToken> PostgresParser::Tokenize(const std::string &query) {
	hiqe_libpgquery::pg_parser_init();
	auto tokens = hiqe_libpgquery::tokenize(query.c_str());
	hiqe_libpgquery::pg_parser_cleanup();
	return std::move(tokens);
}

PostgresParser::~PostgresParser()  {
    hiqe_libpgquery::pg_parser_cleanup();
}

bool PostgresParser::IsKeyword(const std::string &text) {
	return hiqe_libpgquery::is_keyword(text.c_str());
}

std::vector<hiqe_libpgquery::PGKeyword> PostgresParser::KeywordList() {
	// FIXME: because of this, we might need to change the libpg_query library to use duckdb::vector
	return std::forward<std::vector<hiqe_libpgquery::PGKeyword> >(hiqe_libpgquery::keyword_list());
}

void PostgresParser::SetPreserveIdentifierCase(bool preserve) {
	hiqe_libpgquery::set_preserve_identifier_case(preserve);
}

}
