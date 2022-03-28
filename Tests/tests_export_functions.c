#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>
#include "hashtable.h"
#include "minishell.h"
#include "libft.h"
#include "../src/expand/envs.h"
#include "parsing.h"
#include "tokenizer.h"

static int	is_interpreted_symbol(int c)
{
	return (ft_isdigit(c) || c == '?' || c == '!' || c == '-');
}

static int	check_valid_key(const char *word)
{
	int	counter;

	if (is_interpreted_symbol(*word))
		return (*word);
	counter = 0;
	while (word[counter] && word[counter] != '='
		&& (ft_isalnum(word[counter]) || word[counter] == '_'))
		counter += 1;
	return ((word[counter] != 0 && word[counter] != '=') * (word[counter]));
}

Test(check_valid_key, expected_result_eq_0)
{
	char	result;

	result = check_valid_key("g");
	cr_assert_eq(result, 0);
}

Test(check_valid_key, expected_result_eq_interrogation)
{
	char	result;

	result = check_valid_key("ga?=");
	cr_assert_eq(result, '?');
}

Test(check_valid_key, expected_result_eq_1)
{
	char	result;

	result = check_valid_key("1ga?=");
	cr_assert_eq(result, '1');
}

Test(check_valid_key, expected_result_eq_0_when_valid_key_without_equal_char)
{
	char	result;

	result = check_valid_key("ga_1");
	cr_assert_eq(result, 0);
}

Test(check_valid_key, expected_result_eq_difference_char)
{
	char	result;

	result = check_valid_key("ga-1");
	cr_assert_eq(result, '-');
}

Test(export, expected_key_on_envs) {
	struct s_program *prog = NULL;
	struct s_tokens	*tokens = NULL;

	init_hashtbl();
	init_envs();
	tokens = tokenizer("export 123=42sp sp42=42sp");
	prog = parsing(tokens);
	clear_tokens(&tokens);
	export(prog->params);
	struct s_keyval *tmp = hashtbl_lookup("123");
	cr_assert_null(tmp);
	tmp = hashtbl_lookup("sp42");
	cr_assert_str_eq(tmp->val, "42sp");
	destroy_hashtbl();
	destroy_programs(&prog);
}

Test(export, expected_key_on_envs_1) {
	struct s_program	*prog;
	struct s_tokens		*t;

	init_hashtbl();
	init_envs();
	t = tokenizer("export 42sp asdf sp42=42sp");
	prog = parsing(t);
	clear_tokens(&t);
	export(prog->params);
	struct s_keyval *tmp = hashtbl_lookup("42sp");
	cr_assert_null(tmp);
	tmp = hashtbl_lookup("asdf");
	cr_assert_null(tmp);
	tmp = hashtbl_lookup("sp42");
	cr_assert_str_eq(tmp->val, "42sp");
	destroy_programs(&prog);
	destroy_hashtbl();
}
