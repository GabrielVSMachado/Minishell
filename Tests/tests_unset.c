#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <string.h>
#include "linked_list.h"
#include "minishell.h"
#include "hashtable.h"
#include "parsing.h"
#include "../src/expand/envs.h"
#include "tokenizer.h"

extern struct s_hashtbl g_envs;

Test(unset, expected_result_eq_null)
{
	struct s_keyval *result;
	struct s_list *params = NULL;

	ft_lstadd_back(&params, ft_lstnew(strdup("USER")));
	init_hashtbl();
	insert_hashtbl(strdup("USER"), strdup("42sp"));
	unset(params);
	result = hashtbl_lookup("USER");
	cr_assert_null(result);
	destroy_hashtbl();
	ft_lstclear(&params, free);
}

extern struct s_hashtbl g_envs;

Test(unset, check_for_infinity_loop_when_unexistent_variable) {
	struct s_tokens *token = tokenizer("unset asdfsf");
	struct s_program *prog = parsing(token);

	clear_tokens(&token);
	init_hashtbl();
	init_envs();
	unsigned int	size_before = g_envs.size;
	unset(prog->params);
	cr_assert_eq(size_before, g_envs.size);
	destroy_hashtbl();
	destroy_programs(&prog);
}
