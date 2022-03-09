#include <criterion/criterion.h>
#include "hashtable.h"

extern struct s_hashtbl g_envs;

Test(destroy_hashtable, expected_g_envs_null){
	insert_hashtbl("pamonha", "de piracicaba");
	insert_hashtbl("queijo", "minas");
	insert_hashtbl("42", "sp");
	insert_hashtbl("paulo", "pescoço em francês é anus, orgão vital");
	insert_hashtbl("henrique", "to puto");
	insert_hashtbl("rogerio", "matematica estravagante");
	insert_hashtbl("joao", "da chupetinha");
	insert_hashtbl("welton", "me daaaa um real");
	insert_hashtbl("dani", "do elixir");
	destroy_hashtbl();
	for (int bucket = 0; bucket < TBLSIZE; bucket++) {
		cr_assert_null(g_envs.hashtbl[bucket]);
	}
}
