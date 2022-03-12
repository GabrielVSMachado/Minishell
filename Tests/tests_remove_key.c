#include <criterion/criterion.h>
#include "hashtable.h"
#include <stdio.h>
#include <string.h>
#include "../src/builtins/hashtable/utils_keyval_lst.h"

static unsigned int	hash(const char *key)
{
	int				counter;
	unsigned int	val;
	unsigned int	tmp;

	counter = 0;
	val = 0;
	while (key[counter])
	{
		val += key[counter];
		tmp = val & 0xf0000000;
		if (tmp)
		{
			val = val ^ (tmp >> 24);
			val = val ^ tmp;
		}
		counter += 1;
	}
	return (val % TBLSIZE);
}

Test(remove_key, expected_pointer_with_the_right_key_and_lookup_return_NULL) {
	const	char	*key = "USER";
	struct s_keyval	*pointer = NULL;
	struct s_keyval	*result_lookup;

	if (init_hashtbl())
		cr_assert_fail("Fail allocation\n");
	insert_hashtbl(strdup(key), strdup("42sp"));
	pointer = remove_key(key);
	cr_assert_str_eq(pointer->key, key);
	free(pointer->key);
	free(pointer->val);
	free(pointer);
	pointer = NULL;
	result_lookup = hashtbl_lookup(key);
	cr_assert_null(result_lookup);
	destroy_hashtbl();
}

extern struct s_hashtbl g_envs;

Test(remove_key, expected_pointer_with_the_right_key_and_lookup_return_NULL_1) {
	const	char	*key = "USER";
	struct s_keyval	*pointer = NULL;
	struct s_keyval	*n_pointer = NULL;

	if (init_hashtbl())
		cr_assert_fail("Fail allocation\n");
	insert_hashtbl(strdup(key), strdup("42sp"));
	g_envs.hashtbl[hash("USER") % TBLSIZE]->next = new_node_of_bucket(
			strdup("oi"), strdup("42sp"));
	pointer = remove_key(key);
	cr_assert_str_eq(pointer->key, key);
	free(pointer->key);
	free(pointer->val);
	free(pointer);
	pointer = NULL;
	n_pointer = g_envs.hashtbl[hash("USER") % TBLSIZE];
	cr_assert_not_null(n_pointer);
	destroy_hashtbl();
}
