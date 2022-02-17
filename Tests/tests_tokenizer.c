#include <criterion/criterion.h>
#include "tokenizer.h"


Test(tokenizer, expected_llist_with_two_words) {
	char const	*line;
	struct s_tokens	*head = NULL;

	line = strdup("cat Makefile");
	head = tokenizer(line);
	cr_assert_str_eq(
			head->value, "cat",
			"head->value on first test: %s\n", head->value);
	cr_assert(
		head->token == T_WORD,
		"head->token on first test: %i\n", head->token
		);
	cr_assert_str_eq(head->next->value, "Makefile",
			"head->next->value on first test: %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on first test: %i\n", head->next->token);
	clear_tokens(&head);
	free((void *)line);
}
