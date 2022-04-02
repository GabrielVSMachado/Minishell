#include <criterion/criterion.h>
#include "libft.h"
#include <stdio.h>
#include "hashtable.h"
#include "expand_str.h"

static int	add_string_without_quotes(char *tmp, struct s_list **to_join)
{
	char			*holder;
	char			*result_str;
	unsigned int	len_str;

	holder = tmp;
	while (*tmp && *tmp != '\'' && *tmp != '"')
		tmp += 1;
	len_str = tmp - holder;
	result_str = ft_substr(holder, 0, len_str);
	ft_lstadd_back(to_join, ft_lstnew(result_str));
	return (len_str + 1);
}

static int	add_string_delimited_by_c(char *str, struct s_list **to_join,
		char c)
{
	char			*string_to_add;
	unsigned int	len_string;

	len_string = ft_strchr(str + 1, c) - str;
	string_to_add = ft_substr(str, 0, len_string + 1);
	ft_lstadd_back(to_join, ft_lstnew(string_to_add));
	return (len_string + 2);
}

Test(add_string_delimited_by_c, expected_len_eq_expected_len)
{
	char	*tmp = "'$USER'";
	const int	expected_len = 8;
	t_list		*to_join = NULL;
	int			result;

	result = add_string_delimited_by_c(tmp, &to_join, '\'');
	cr_assert_eq(result, expected_len);
	cr_assert_str_eq(to_join->content, tmp);
	ft_lstclear(&to_join, free);
}

Test(add_s_quote_string, expected_string_in_llist_equal_expected_value)
{
	const char	*expected_value = "'$USERgabr'";
	char		*value_passed_to_function = "'$USERgabr'iel";
	const int	len_expected_value = 12;
	int			result;
	t_list		*llist = NULL;

	result = add_string_delimited_by_c(value_passed_to_function, &llist, '\'');
	cr_assert_str_eq(llist->content, expected_value);
	cr_assert_eq(result, len_expected_value);
	ft_lstclear(&llist, free);
}

Test(add_string_delimited_by_c, expected_string_in_llist_equal_expected_value_with_dquotes) {
	const char	*expected_value = "\"$USER\"";
	t_list		*llist = NULL;
	const	int	expected_len = 8;
	int		result;

	result = add_string_delimited_by_c((char *)expected_value, &llist, '"');
	cr_assert_eq(result, expected_len);
	cr_assert_str_eq(llist->content, expected_value);
	ft_lstclear(&llist, free);
}

Test(add_string_without_quotes, expected_string_in_llist_equal_expected_value_2) {
	const char *expected_value = "gabriel$USER";
	char	*string_pass_in_function = "gabriel$USER'vitor'";
	t_list	*llist = NULL;
	const	int	expected_len = 13;
	int	result;

	result = add_string_without_quotes(string_pass_in_function, &llist);
	cr_assert_eq(result, expected_len);
	cr_assert_str_eq(llist->content, expected_value);
	ft_lstclear(&llist, free);
}

Test(add_string_without_quotes, expected_string_in_llist_equal_expected_value_3) {
	const char *expected_value = "$USER";
	char	*string_pass_in_function = "$USER";
	t_list	*llist = NULL;
	const	int	expected_len = 6;
	int	result;

	result = add_string_without_quotes(string_pass_in_function, &llist);
	cr_assert_eq(result, expected_len);
	cr_assert_str_eq(llist->content, expected_value);
	ft_lstclear(&llist, free);
}

extern struct s_hashtbl	g_envs;

Test(expand_env_command, expected_result_eq_expected_value)
{
	const char	*expected_value = "42sp";
	char		*word = ft_strdup("$USER");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
}

Test(expand_env_command, expected_result_eq_expected_value_2) {
	const char *expected_value = "\"42sp'gabriel42sp'\"";
	char	*word = ft_strdup("\"$USER'gabriel$USER'\"");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_3) {
	const char *expected_value = "'$USER'";
	char	*word = ft_strdup("'$USER'");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_4) {
	const char *expected_value = "\"42sp\"";
	char	*word = ft_strdup("\"$USER\"");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_5) {
	const char *expected_value = "\"42sp\"";
	char	*word = ft_strdup("\"42sp\"");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_6) {
	const char *expected_value = "echo\"42sp\"";
	char	*word = ft_strdup("echo\"$USER\"");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}


Test(expand_env_command, expected_result_eq_expected_value_7) {
	const char *expected_value = "echo\"42sp\"";
	char	*word = ft_strdup("echo\"$USER\"");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_8) {
	const char *expected_value = "echo42sp";
	char	*word = ft_strdup("echo$USER");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_9) {
	const char *expected_value = "echo42sp42sp";
	char	*word = ft_strdup("echo$USER$USER");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_10) {
	const char *expected_value = "echo42sp";
	char	*word = ft_strdup("echo$US$ER$USER");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_11) {
	const char *expected_value = "\"42sp é legal\"";
	char	*word = ft_strdup("\"$USER é legal\"");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_12) {
	const char *expected_value = "'$USER é legal'";
	char	*word = ft_strdup("'$USER é legal'");

	init_hashtbl();
	insert_hashtbl(ft_strdup("USER"), ft_strdup("42sp"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_13) {
	const char *expected_value = "9098USER é legal";
	char	*word = ft_strdup("$$USER é legal");

	init_hashtbl();
	insert_hashtbl(ft_strdup("$"), ft_strdup("9098"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_14) {
	const char *expected_value = "$=USER é legal";
	char	*word = ft_strdup("$=USER é legal");

	init_hashtbl();
	insert_hashtbl(ft_strdup("$"), ft_strdup("9098"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_15) {
	const char *expected_value = "$@USER é legal";
	char	*word = ft_strdup("$@USER é legal");

	init_hashtbl();
	insert_hashtbl(ft_strdup("$"), ft_strdup("9098"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_16) {
	const char *expected_value = "$(USER é legal";
	char	*word = ft_strdup("$(USER é legal");

	init_hashtbl();
	insert_hashtbl(ft_strdup("$"), ft_strdup("9098"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_17) {
	const char *expected_value = "$)USER é legal";
	char	*word = ft_strdup("$)USER é legal");

	init_hashtbl();
	insert_hashtbl(ft_strdup("$"), ft_strdup("9098"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_18) {
	const char *expected_value = "$*USER é legal";
	char	*word = ft_strdup("$*USER é legal");

	init_hashtbl();
	insert_hashtbl(ft_strdup("$"), ft_strdup("9098"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_19) {
	const char *expected_value = "massa$";
	char	*word = ft_strdup("massa$");

	init_hashtbl();
	insert_hashtbl(ft_strdup("$"), ft_strdup("9098"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}

Test(expand_env_command, expected_result_eq_expected_value_21) {
	const char *expected_value = "\"daora$\"massa";
	char	*word = ft_strdup("\"daora$\"massa");

	init_hashtbl();
	insert_hashtbl(ft_strdup("$"), ft_strdup("9098"));
	expand_env_variables(&word);
	cr_assert_str_eq(word, expected_value);
	destroy_hashtbl();
	free(word);
}
