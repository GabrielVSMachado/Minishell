#include <criterion/criterion.h>
#include "expand_str.h"
#include "tokenizer.h"
#include "hashtable.h"
#include <string.h>

Test(expand_command, expected_result_eq_expected_value_variable) {
	const char *expected_value[] = {"echo", "42sp"};
	struct s_tokens	*result = NULL;

	init_hashtbl();
	result = tokenizer("echo $USER");
	insert_hashtbl(strdup("USER"), strdup("42sp"));
	expand_command(&result->next->value);
	int i = 0;
	for (struct s_tokens *tmp = result; tmp; tmp = tmp->next) {
		cr_assert_str_eq(tmp->value, expected_value[i++]);
	}
	destroy_hashtbl();
	clear_tokens(&result);
}
