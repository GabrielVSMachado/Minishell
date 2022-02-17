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

Test(tokenizer, expected_llist_with_fours_words_and_one_rinput) {
	char const	line[] = "tr '\n' ' ' < command.txt";
	struct s_tokens	*head = NULL;

	head = tokenizer(line);
	cr_assert_str_eq(head->value, "tr",
			"head->value on second test: %s\n", head->value);
	cr_assert(head->token == T_WORD,
			"head->token on second test: %d\n", head->token);


	cr_assert_str_eq(head->next->value, "'\n'",
			"head->next->value on second test: %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on second test: %d\n", head->next->token);


	cr_assert_str_eq(head->next->next->value, "' '",
		"head->next->next->value on second test: %s\n", head->next->next->value);
	cr_assert(head->next->next->token == T_WORD,
		"head->next->next->token on second test: %d\n", head->next->next->token);


	cr_assert_null(head->next->next->next->value,
		"head->next->next->next->next->value is not null on second test");
	cr_assert(
		head->next->next->next->token == T_RINPUT,
		"head->next->next->next->next->token on second test: %d\n",
		head->next->next->next->token
		);


	cr_assert_str_eq(
			head->next->next->next->next->value,
			"command.txt",
		"head->next->next->next->next->next->next->next->next->value on second test: %s\n",
		head->next->next->next->next->value);
	cr_assert(
		head->next->next->next->next->token == T_WORD,
		"head->next->next->next->next->next->next->next->next->token on second test: %d\n",
		head->next->next->next->next->token);

	clear_tokens(&head);
}
