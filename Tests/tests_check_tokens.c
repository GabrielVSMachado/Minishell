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
