#include <criterion/criterion.h>
#include "hashtable.h"
#include <stdio.h>
#include <string.h>

Test(remove_key, expected_pointer_with_the_right_key_and_lookup_return_NULL) {
	const	char	*key = "USER";
	struct s_keyval	**pointer = NULL;
	struct s_keyval	*result_lookup;

	if (init_hashtbl())
		cr_assert_fail("Fail allocation\n");
	insert_hashtbl(strdup(key), strdup("42sp"));
	pointer = remove_key(key);
	cr_assert_str_eq((*pointer)->key, key);
	free((*pointer)->key);
	free((*pointer)->val);
	free(*pointer);
	*pointer = NULL;
	result_lookup = hashtbl_lookup(key);
	cr_assert_null(result_lookup);
	destroy_hashtbl();
}
