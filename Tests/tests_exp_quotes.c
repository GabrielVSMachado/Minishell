#include <criterion/criterion.h>
#include "expand_str.h"
#include <stdio.h>

Test(expand_quotess, expected_line_eq_expected_value) {
	char *line = strdup("mi'ni'sh'ell'");
	const char *expected_value = "minishell";

	expand_quotes(&line);
	cr_assert_str_eq(line, expected_value);
	free(line);
}

Test(expand_quotes, expected_line_eq_expected_value_2) {
	char *line = strdup("\"mi'ni'sh'ell'\"");
	const char *expected_value = "mi'ni'sh'ell'";

	expand_quotes(&line);
	cr_assert_str_eq(line, expected_value);
	free(line);
}

Test(expand_quotes, expected_line_eq_expected_value_3) {
	char *line = strdup("mi\"ni\"sh'ell'");
	const char *expected_value = "minishell";

	expand_quotes(&line);
	cr_assert_str_eq(line, expected_value);
	free(line);
}

Test(expand_quotes, expected_line_eq_expected_value_4) {
	char *line = strdup("mi\"ni'shell'\"");
	const char *expected_value = "mini'shell'";

	expand_quotes(&line);
	cr_assert_str_eq(line, expected_value);
	free(line);
}

Test(expand_quotes, expected_line_eq_expected_value_5) {
	char *line = strdup("mi\"ni'shell'\"");
	const char *expected_value = "mini'shell'";

	expand_quotes(&line);
	cr_assert_str_eq(line, expected_value);
	free(line);
}

Test(expand_quotes, expected_line_eq_expected_value_6) {
	char *line = strdup("mi'ni''sh''ell'");
	const char *expected_value = "minishell";

	expand_quotes(&line);
	cr_assert_str_eq(line, expected_value);
	free(line);
}

Test(expand_quotes, expected_line_eq_expected_value_7) {
	char *line = strdup("mi\"\"ni\"sh\"\"ell\"");
	const char *expected_value = "minishell";

	expand_quotes(&line);
	cr_assert_str_eq(line, expected_value);
	free(line);
}

Test(expand_quotes, expected_line_eq_expected_value_8) {
	char *line = strdup("'mi\"\"ni\"sh\"\"ell\"'");
	const char *expected_value = "mi\"\"ni\"sh\"\"ell\"";

	expand_quotes(&line);
	cr_assert_str_eq(line, expected_value);
	free(line);
}

Test(expand_quotes, expected_line_eq_expected_value_9) {
	char *line = strdup("'mi\"\"ni\"sh'\"\"ell\"\"");
	const char *expected_value = "mi\"\"ni\"shell";

	expand_quotes(&line);
	cr_assert_str_eq(line, expected_value);
	free(line);
}

Test(expand_quotes, expected_line_eq_expected_value_10) {
	char *line = strdup("\"mini shell\"");
	const char *expected_value = "mini shell";

	expand_quotes(&line);
	cr_assert_str_eq(line, expected_value);
	free(line);
}

Test(expand_quotes, expected_line_eq_expected_value_11) {
	char *line = strdup("\"mini shell\"");
	const char *expected_value = "mini shell";

	expand_quotes(&line);
	cr_assert_str_eq(line, expected_value);
	free(line);
}
