#include <criterion/criterion.h>
#include "hashtable.h"
#include "../src/expand/envs.h"

extern struct s_hashtbl g_envs;

Test(init_envs, expected_all_values_of_environ) {
	init_envs();
	cr_assert_not_null(hashtbl_lookup("PATH"));
	cr_assert_not_null(hashtbl_lookup("USER"));
	/* cr_assert_not_null(hashtbl_lookup("SHELL")); */
	cr_assert_not_null(hashtbl_lookup("OLDPWD"));
	destroy_hashtbl();
}
