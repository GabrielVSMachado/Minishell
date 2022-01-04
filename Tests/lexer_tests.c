#include <minishell.h>
#include <criterion/criterion.h>

static t_list	*head = NULL;

Test(token_word, expected_len_str_7_and_head_with_node_with_str) {
	char	*test = "gabriel vitor";

	int len = token_word(test, 0, &head);
	cr_assert_str_eq((char *)head->content, "gabriel", "Wrong str is %s\n", (char *)head->content);
	cr_assert(len == 7, "Wrong len is %d\n", len);
}

Test(token_word, expected_len_str_11_and_head_with_node_with_str) {
	char	*test = "minishell.h";

	int	len = token_word(test, 0, &head);
	cr_assert_str_eq((char *)head->content, "minishell.h", "Wrong str is %s\n", (char *)head->content);
	cr_assert(len == 11, "Wrong len_str: %d\n", len);
}

Test(token_word, expected_len_str_10_and_head_with_the_str_test) {
	char	*test = "..";
	int		len = token_word(test, 0, &head);

	cr_assert_str_eq((char *)head->content, "..", "Wrong str is %s\n", (char *)head->content);
	cr_assert(len == 2, "Wrong len_str: %d\n", len);
}
