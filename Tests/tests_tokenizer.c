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

Test(tokenizer, expected_llist_with_three_words_and_one_routput) {
	char const	*line = "cat Makefile > makefile.txt";
	struct s_tokens	*head = NULL;

	head = tokenizer(line);

	cr_assert_str_eq(head->value, "cat",
			"head->value on third test: %s\n", head->value);
	cr_assert(head->token == T_WORD,
			"head->token on third test: %d\n", head->token);

	cr_assert_str_eq(head->next->value, "Makefile",
			"head->next->value on third test: %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on third test: %d\n", head->next->token);

	cr_assert_null(head->next->next->value,
			"head->next->next->value is not null");
	cr_assert(head->next->next->token == T_ROUTPUT,
			"head->next->next->token on third test: %d\n",
			head->next->next->token);

	cr_assert_str_eq(
			head->next->next->next->value, "makefile.txt",
			"head->next->next->next->next->next->value on third test: %s\n",
			head->next->next->next->value);
	cr_assert(head->next->next->next->token == T_WORD,
			"head->next->next->next->next->token on third test: %d\n",
			head->next->next->next->token);
	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_fours_words_and_one_rinput_complex) {
	char const	*line = "tr 'banana pera' 'manga abacaxi' < frutas.csv";
	struct s_tokens	*head = NULL;

	head = tokenizer(line);

	cr_assert_str_eq(head->value, "tr",
			"head->value on fourth test: %s\n", head->value);
	cr_assert(head->token == T_WORD,
			"head->token on fourth test: %d\n", head->token);

	cr_assert_str_eq(head->next->value, "'banana pera'",
			"head->next->value on fourth test: %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on fourth test: %d\n", head->next->token);

	cr_assert_str_eq(head->next->next->value, "'manga abacaxi'",
			"head->next->value on fourth test: %s\n", head->next->next->value);
	cr_assert(head->next->next->token == T_WORD,
			"head->next->token on fourth test: %d\n", head->next->next->token);

	cr_assert_null(head->next->next->next->value,
			"head->next->next->next->value on fourth test");
	cr_assert(head->next->next->next->token == T_RINPUT,
			"head->next->next->token on fourth test: %d\n",
			head->next->next->next->token);

	cr_assert_str_eq(
			head->next->next->next->next->value, "frutas.csv",
			"head->next->next->next->next->value on fourth test: %s\n",
			head->next->next->next->next->value);
	cr_assert(head->next->next->next->next->token == T_WORD,
			"head->next->next->next->next->token on fourth test: %d\n",
			head->next->next->next->next->token);
	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_four_words_and_one_pipe_with_one_token_invalid) {
	char const	*line = "valgrind ./test |& cat -e";
	struct s_tokens	*head = NULL;

	head = tokenizer(line);

	cr_assert_str_eq(head->value, "valgrind",
			"head->value on fifth %s\n", head->value);
	cr_assert(head->token == T_WORD,
			"head->token on fifth %d\n", head->token);

	cr_assert_str_eq(head->next->value, "./test",
			"head->next->value on fifth %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on fifth %d\n", head->next->token);

	cr_assert_null(head->next->next->value,
			"head->next->next->value is not NULL");
	cr_assert(head->next->next->token == T_PIPE,
			"head->next->next->token on fifth %d\n", T_PIPE);

	cr_assert_null(head->next->next->next->value,
			"head->next->next->next->value is not null"); //invalid token
	cr_assert(head->next->next->next->token == T_WORD,
			"head->next->next->next->token on fifth %d\n",
			head->next->next->next->token);

	cr_assert_str_eq(head->next->next->next->next->value, "cat",
			"head->next->next->next->next->value on fifth %s\n",
			head->next->next->next->next->value);
	cr_assert(head->next->next->next->next->token == T_WORD,
			"head->next->next->next->next->token on fifth %d\n",
			head->next->next->next->next->token);

	cr_assert_str_eq(head->next->next->next->next->next->value, "-e",
			"head->next->next->next->next->next->value on fifth %s\n",
			head->next->next->next->next->next->value);
	cr_assert(head->next->next->next->next->next->token == T_WORD,
			"head->next->next->next->next->next->token on fifth %d\n",
			head->next->next->next->next->next->token);
	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_heredoc_and_four_words) {
	char const	*line = "<< out tr 'a' 'b'";
	struct s_tokens	*head = NULL;

	head = tokenizer(line);

	cr_assert_null(head->value, "head->value on sixth is not NULL");
	cr_assert(head->token == T_HEREDOC, "head->token on sixth %d\n", head->token);

	cr_assert_str_eq(head->next->value, "out",
			"head->next->value on sixth %s\n", head->next->value);
	cr_assert(head->next->token == T_WORD,
			"head->next->token on sixth %d\n", head->next->token);

	cr_assert_str_eq(head->next->next->value, "tr",
			"head->next->next->value on sixth %s\n", head->next->next->value);
	cr_assert(head->next->next->token == T_WORD,
			"head->next->next->token on sixth %d\n", head->next->next->token);

	cr_assert_str_eq(head->next->next->next->value, "'a'",
			"head->next->next->next->value on sixth %s\n",
			head->next->next->next->value);
	cr_assert(head->next->next->next->token == T_WORD,
			"head->next->next->next->token on sixth %d\n",
			head->next->next->next->token);

	cr_assert_str_eq(head->next->next->next->next->value, "'b'",
			"head->next->next->next->next->value on sixth %s\n",
			head->next->next->next->next->value);
	cr_assert(head->next->next->next->next->token == T_WORD,
			"head->next->next->next->next->token on sixth %d\n",
			head->next->next->next->next->token);
	clear_tokens(&head);
}

Test(tokenizer, expected_llist_with_six_words_and_AND_and_OR) {
	char const *line = "true && echo $? && false || echo $?";
	struct s_tokens	*head = NULL;
	unsigned int	tokens[] = {
		T_WORD,
		T_AND,
		T_WORD,
		T_WORD,
		T_AND,
		T_WORD,
		T_OR,
		T_WORD,
		T_WORD
	};
	char *values[] = {
		"true",
		NULL,
		"echo",
		"$?",
		NULL,
		"false",
		NULL,
		"echo",
		"$?"
	};
	head = tokenizer(line);
	int i = 0;
	for (struct s_tokens *tmp = head; tmp != NULL; tmp = tmp->next) {
		if (values[i] == NULL) {
			cr_assert_null(tmp->value);
		} else {
			cr_assert_str_eq(tmp->value, values[i]);
		}
		cr_assert(tmp->token == tokens[i++]);
	}
}
