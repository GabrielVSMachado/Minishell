#include <criterion/criterion.h>
#include "tokenizer.h"

Test(check_tokens, expected_head_to_be_null) {
	const char		*line = "( cat Makefile";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_null(head);
}

Test(check_tokens, expected_head_to_be_null_because_of_amper_after_pipe) {
	const char	*line = "valgrind ./test |& cat -e ";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_null(head);
}

Test(check_tokens, expected_head_to_be_null_because_after_heredoc_needed_word) {
	const char	*line = "<< (cat Makefile)";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_null(head);
}

Test(check_tokens, expected_head_to_be_null_because_after_rinput_need_word) {
	const char	*line = "tr 'a' 'b' < (cat Makefile)";
	struct s_tokens	*head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_null(head);
}

Test(check_tokens, expected_head_to_be_null_because_after_raoutput_need_word) {
	const char	*line = "cat Makefile >> | tr 'a' 'b'";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_null(head);
}

Test(check_tokens, expected_head_to_be_not_null_with_valid_command) {
	const char	*line = "<< out tr 'a' 'b'";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_not_null(head);
	clear_tokens(&head);
}

Test(check_tokens, expected_head_to_be_not_null_with_valid_command_2) {
	const char *line = "tr 'banana pera' 'manga abacaxi' < frutas.csv";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_not_null(head);
	clear_tokens(&head);
}

Test(check_tokens, expected_head_to_be_not_null_with_valid_command_3) {
	const char *line = "(echo oi | < infile cat)";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_not_null(head);
	clear_tokens(&head);
}

Test(check_tokens, expected_head_to_be_not_null_with_valid_command_4) {
	const char *line = "echo oi | (cat -e)";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_not_null(head);
	clear_tokens(&head);
}

Test(check_tokens, expected_head_to_be_null_open_and_close_parenthesis_without_content) {
	const char *line = "()";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_null(head);
}

Test(check_tokens, expected_head_to_be_null_because_alone_close_parenthesis) {
	const char *line = ") cat";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_null(head);
}


Test(check_tokens, expected_head_to_be_null_because_unclosed_parenthesis) {
	const char *line = "echo oi | ((cat -e)";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_null(head);
}

Test(check_tokens, expected_head_to_be_null_because_parenthesis_after_pipe) {
	const char *line = "(echo oi | )";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_null(head);
}

Test(check_tokens, expected_head_to_be_not_null_with_valid_command_5) {
	const char *line = "(echo oi | > outfile cat)";
	struct s_tokens *head = NULL;

	head = tokenizer(line);
	head = check_tokens(&head);
	cr_assert_not_null(head);
	clear_tokens(&head);
}
