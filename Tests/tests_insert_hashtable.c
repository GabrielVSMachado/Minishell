#include <criterion/criterion.h>
#include "hashtable.h"

struct s_hashtbl *g_envs;

Test(insert_hashtbl, expected_pointer_value_not_null) {
	struct s_keyval *value;

	g_envs = malloc(sizeof(struct s_hashtbl));
	insert_hashtbl("pamonha", "de piracicaba");
	value = hashtbl_lookup("pamonha");
	cr_assert_str_eq(value->key, "pamonha");
	cr_assert_str_eq(value->val, "de piracicaba");
}
