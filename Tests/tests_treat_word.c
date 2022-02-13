#include <criterion/criterion.h>
#include "libft.h"
#include "tokenizer.h"

static int	is_special(char	const c)
{
	return (ft_strchr("|&()><", c) != NULL);
}

static void	treat_words(struct s_tokens **head, char const *line,
		unsigned int *cursor)
{
	unsigned int	counter;
	unsigned char	c;

	counter = *cursor + 1;
	while (line[counter] != '\0' && !is_special(line[counter]))
	{
		c = ('\'' * (line[counter] == '\''))
			| ('\"' * (line[counter] == '\"'));
		if (c != 0)
		{	
			counter += (ft_strchr(line + counter, c) - (line + counter));
		}
		counter += 1;
	}
	add_back_token(head,
		new_token(ft_substr(line, *cursor, counter - *cursor), T_WORD));
	(*cursor) += counter;
}

Test(treat_words, expected_llist_with_token_with_the_word_minishell) {
	struct s_tokens	*head = NULL;
	char const		*line = "minishell";
	unsigned int	cursor = 0;

	treat_words(&head, line, &cursor);
	cr_assert_str_eq(head->value, "minishell", "Wrong value Result: %s\n", head->value);
	cr_assert(head->token == T_WORD, "Wrong token Result: %u\n", head->token);
	cr_assert(cursor == strlen("minishell"));
	free(head->value);
	free(head);
}


Test(treat_words, expected_llist_with_token_with_the_word_minishell_with_squotes) {
	struct s_tokens	*head = NULL;
	char const		*line = "mi'ni'sh'ell'";
	unsigned int	cursor = 0;

	treat_words(&head, line, &cursor);
	cr_assert_str_eq(head->value, "mi'ni'sh'ell'", "Wrong value Result_2: %s\n", head->value);
	cr_assert(head->token == T_WORD, "Wrong token Result_2: %u\n", head->token);
	cr_assert(cursor == strlen("mi'ni'sh'ell'"), "Wrong cursor %u\n", cursor);
	free(head->value);
	free(head);
}

Test(treat_words,
	expected_llist_with_token_with_the_word_minishell_with_squotes_and_dquotes) {
	struct s_tokens	*head = NULL;
	char const		*line = "mi\"ni\"sh'ell'";
	unsigned int	cursor = 0;

	treat_words(&head, line, &cursor);
	cr_assert_str_eq(head->value, "mi\"ni\"sh'ell'", "Wrong value Result_3: %s\n", head->value);
	cr_assert(head->token == T_WORD, "Wrong token Result_3: %u\n", head->token);
	cr_assert(cursor == strlen("mi\"ni\"sh'ell'"), "Wrong cursor: %u\n", cursor);
	free(head->value);
	free(head);
}


Test(treat_words,
	expected_llist_with_token_with_the_word_minishell_squotes_inside_dquotes) {
	struct s_tokens	*head = NULL;
	char const		*line = "mi\"ni'shell'\"";
	unsigned int	cursor = 0;

	treat_words(&head, line, &cursor);
	cr_assert_str_eq(head->value, "mi\"ni'shell'\"", "Wrong value Result_4: %s\n", head->value);
	cr_assert(head->token == T_WORD, "Wrong token Result_4: %u\n", head->token);
	cr_assert(cursor == strlen("mi\"ni'shell'\""), "Wrong cursor: %u\n", cursor);
	free(head->value);
	free(head);
}


Test(treat_words,
	expected_llist_with_token_with_the_word_minishell_squotes_empty) {
	struct s_tokens	*head = NULL;
	char const		*line = "mi'ni''sh''ell'";
	unsigned int	cursor = 0;

	treat_words(&head, line, &cursor);
	cr_assert_str_eq(head->value, "mi'ni''sh''ell'", "Wrong value Result_5: %s\n", head->value);
	cr_assert(head->token == T_WORD, "Wrong token Result_5: %u\n", head->token);
	cr_assert(cursor == strlen("mi'ni''sh''ell'"), "Wrong cursor: %u\n", cursor);
	free(head->value);
	free(head);
}

Test(treat_words,
	expected_llist_with_token_with_the_word_minishell_dquotes_empty) {
	struct s_tokens	*head = NULL;
	char const		*line = "mi\"\"ni\"sh\"\"ell\"";
	unsigned int	cursor = 0;

	treat_words(&head, line, &cursor);
	cr_assert_str_eq(head->value, "mi\"\"ni\"sh\"\"ell\"", "Wrong value Result_6: %s\n", head->value);
	cr_assert(head->token == T_WORD, "Wrong token Result_6: %u\n", head->token);
	cr_assert(cursor == strlen("mi\"\"ni\"sh\"\"ell\""), "Wrong cursor: %u\n", cursor);
	free(head->value);
	free(head);
}

Test(treat_words,
	expected_llist_with_token_with_the_word_minishell_dquotes_within_squotes) {
	struct s_tokens	*head = NULL;
	char const		*line = "'mi\"\"ni\"sh\"\"ell\"'";
	unsigned int	cursor = 0;

	treat_words(&head, line, &cursor);
	cr_assert_str_eq(head->value, "'mi\"\"ni\"sh\"\"ell\"'", "Wrong value Result_7: %s\n", head->value);
	cr_assert(head->token == T_WORD, "Wrong token Result_7: %u\n", head->token);
	cr_assert(cursor == strlen("'mi\"\"ni\"sh\"\"ell\"'"), "Wrong cursor: %u\n", cursor);
	free(head->value);
	free(head);
}

Test(treat_words,
	expected_llist_with_token_with_the_word_minishell_mix_squotes_and_dquotes) {
	struct s_tokens	*head = NULL;
	char const		*line = "'mi\"\"ni\"sh'\"\"ell\"\"";
	unsigned int	cursor = 0;

	treat_words(&head, line, &cursor);
	cr_assert_str_eq(head->value, "'mi\"\"ni\"sh'\"\"ell\"\"", "Wrong value Result_8: %s\n", head->value);
	cr_assert(head->token == T_WORD, "Wrong token Result_8: %u\n", head->token);
	cr_assert(cursor == strlen("'mi\"\"ni\"sh'\"\"ell\"\""), "Wrong cursor: %u\n", cursor);
	free(head->value);
	free(head);
}

Test(treat_words,
	expected_llist_with_token_with_the_word_minishell_str_with_space_inside_dquotes) {
	struct s_tokens	*head = NULL;
	char const		*line = "\"mini shell\"";
	unsigned int	cursor = 0;

	treat_words(&head, line, &cursor);
	cr_assert_str_eq(head->value, "\"mini shell\"", "Wrong value Result_9: %s\n", head->value);
	cr_assert(head->token == T_WORD, "Wrong token Result_9: %u\n", head->token);
	cr_assert(cursor == strlen("\"mini shell\""), "Wrong cursor: %u\n", cursor);
	free(head->value);
	free(head);
}
