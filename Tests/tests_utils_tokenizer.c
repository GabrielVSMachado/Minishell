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

Test(last_token, expected_last_token_and_dont_lost_reference_pointer) {
	struct s_tokens *node;
	struct s_tokens	*last;

	node = new_token("fuga", T_WORD);
	node->next = new_token("das", T_WORD);
	node->next->next = new_token("galinhas", T_WORD);
	last = last_token(node);
	cr_assert_str_eq(last->value, "galinhas", "Wrong value on last pointer");
	cr_assert(last->token == T_WORD, "Wrong type o token on last pointer");
	cr_assert_str_eq(node->value, "fuga", "Wrong head on lst_last first test");
	cr_assert(node->token == T_WORD, "Wrong token for head on lst_last first test");
	free(node->next->next);
	free(node->next);
	free(node);
}

Test(add_back, expected_list_with_three_tokens)
{
	struct s_tokens *node = NULL;

	add_back_token(&node, new_token("fuga", T_WORD));
	add_back_token(&node, new_token("das", T_WORD));
	add_back_token(&node, new_token("galinhas", T_WORD));

	cr_assert_str_eq(node->value, "fuga", "Wrong first pointer content on add_back");
	cr_assert_str_eq(node->next->value, "das", "Wrong second pointer content on add_back");
	cr_assert_str_eq(node->next->next->value, "galinhas", "Wrong third pointer content on add_back");
	cr_assert(node->token == T_WORD, "Wrong token on first pointer on add_back");
	cr_assert(node->next->token == T_WORD, "Wrong token on second pointer on add_back");
	cr_assert(node->next->next->token == T_WORD, "Wrong token on third pointer on add_back");
	cr_assert(node->next->next->next == NULL);
	free(node->next->next);
	free(node->next);
	free(node);
}

Test(clear_tokens, expected_head_null) {
	struct s_tokens	*head = NULL;

	head = new_token(strdup("fuga"), T_WORD);
	head->next = new_token(strdup("das"), T_WORD);
	head->next = new_token(strdup("galinhas"), T_WORD);

	clear_tokens(&head);
	cr_assert(head == NULL, "head after clear_tokens is not NULL");
}
