#include <criterion/criterion.h>
#include "minishell.h"
#include "hashtable.h"

extern struct s_hashtbl g_envs;

Test(unset, expected_result_eq_null)
{
	struct s_keyval *result;

	init_hashtbl();
	insert_hashtbl(strdup("USER"), strdup("42sp"));
	unset("USER");
	result = hashtbl_lookup("USER");
	cr_assert_null(result);
	destroy_hashtbl();
}
