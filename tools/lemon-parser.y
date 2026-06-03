%name j128_lemon
%token_prefix J128_TOKEN_

%token_type {j128_token}
%default_type {j128_token}
%extra_context {j128 *additional_data}

%syntax_error {
    additional_data->error_code = J128_SYNTAX_ERROR;
}

%parse_failure {
    additional_data->error_code = J128_SYNTAX_ERROR;
}

program ::= array.

array ::= LEFT_BRACKET RIGHT_BRACKET.  /* Empty array [] */
array ::= LEFT_BRACKET array_elements RIGHT_BRACKET.  /* Array with elements */

array_elements ::= array.  /* Single nested array */
array_elements ::= array_elements COMMA array.  /* Multiple arrays separated by commas */
