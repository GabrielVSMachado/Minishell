#include <criterion/criterion.h>
#include "hashtable.h"

extern struct s_hashtbl g_envs;

Test(destroy_hashtable, expected_g_envs_null){
	init_hashtbl();
	insert_hashtbl(strdup("pamonha"), strdup("de piracicaba"));
	insert_hashtbl(strdup("queijo"), strdup("minas"));
	insert_hashtbl(strdup("42"), strdup("sp"));
	insert_hashtbl(strdup("paulo"), strdup("pescoço em francês é anus, orgão vital"));
	insert_hashtbl(strdup("henrique"), strdup("to puto"));
	insert_hashtbl(strdup("rogerio"), strdup("matematica estravagante"));
	insert_hashtbl(strdup("joao"), strdup("da chupetinha"));
	insert_hashtbl(strdup("welton"), strdup("me daaaa um real"));
	insert_hashtbl(strdup("dani"), strdup("do elixir"));
	destroy_hashtbl();
	for (int bucket = 0; bucket < TBLSIZE; bucket++) {
		cr_assert_null(g_envs.hashtbl[bucket]);
	}
}
