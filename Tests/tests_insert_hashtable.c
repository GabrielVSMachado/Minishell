#include <criterion/criterion.h>
#include "hashtable.h"

extern struct s_hashtbl g_envs;

Test(insert_hashtbl, expected_pointer_value_not_null) {
	struct s_keyval *value;

	init_hashtbl();
	insert_hashtbl(strdup("pamonha"), strdup("de piracicaba"));
	value = hashtbl_lookup(strdup("pamonha"));
	cr_assert_str_eq(value->key, "pamonha");
	cr_assert_str_eq(value->val, "de piracicaba");
	cr_assert(g_envs.size == 1);
}

Test(insert_hashtbl, expected_pointer_value_null) {
	struct s_keyval *value;

	init_hashtbl();
	value = hashtbl_lookup("pamonha");
	cr_assert_null(value);
}

Test(insert_hashtbl, expected_pointer_value_not_null_with_one_element) {
	struct s_keyval *tmp;

	init_hashtbl();
	insert_hashtbl(strdup("pamonha"), strdup("de piracicaba"));
	insert_hashtbl(strdup("queijo"), strdup("minas"));
	tmp = hashtbl_lookup("queijo");
	cr_assert_str_eq(tmp->key, "queijo");
	cr_assert_str_eq(tmp->val, "minas");
	cr_assert_null(tmp->next);
}
