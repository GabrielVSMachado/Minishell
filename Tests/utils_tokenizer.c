#include <criterion/criterion.h>
#include "tokenizer.h"


Test(new_tokens, expected_new_token_not_null) {
	struct s_tokens	*node;

	node = new_token("galinhas", T_WORD);
	cr_assert_str_eq(node->value, "galinhas", "WRONG value on node");
	cr_assert(node->token == T_WORD, "wrong token");
	cr_assert(node->next == NULL);
	free(node);
}
