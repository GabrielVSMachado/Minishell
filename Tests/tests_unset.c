#include <criterion/criterion.h>
#include <string.h>
#include "linked_list.h"
#include "minishell.h"
#include "hashtable.h"
#include "parsing.h"

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
