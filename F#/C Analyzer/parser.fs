//
// Parser for simple C programs.  This component checks 
// the input program to see if it meets the syntax rules
// of simple C.  The parser returns a string denoting
// success or failure. 
//
// Returns: the string "success" if the input program is
// legal, otherwise the string "syntax_error: ..." is
// returned denoting an invalid simple C program.
//
// <<Ayesha Quadri Syeda>>
//
// Original author:
//   Prof. Joe Hummel
//   U. of Illinois, Chicago
//   CS 341, Spring 2022
//

namespace compiler

module parser =
  //
  // NOTE: all functions in the module must be indented.
  //

  //
  // matchToken
  //
  let private matchToken expected_token tokens =
    //
    // if the next token matches the expected token,  
    // keep parsing by returning the rest of the tokens.
    // Otherwise throw an exception because there's a 
    // syntax error, effectively stopping compilation
    // at the first error.
    //
    let next_token = List.head tokens

    if expected_token = next_token then  
      List.tail tokens
    else
      failwith ("expecting " + expected_token + ", but found " + next_token)

//  contains; checks if a symbol is in the List
//  returns true or false
//  or the rest of the list with the symbol 
//
  let rec private contains x list = 
    match list with
    | []  -> false
    | head::tail when head = x -> true
    | head::tail -> contains x tail

//  Checks if the string begins with the given string
//  Returns true or false
//
  let private beginswith (pattern: string) (token: string) =
    token.StartsWith (pattern)

//  Checks if the head token is a expr-op 
//  returns true or false
//
  let rec private isexprop tokens = 
    let h1 = List.head tokens
    let op = ["+"; "-"; "*"; "/"; "^"; "<"; "<="; ">"; ">="; "=="; "!="]

    // checks if the symbol is valid
    if contains h1 op = true then
      true
    else
      false

//  Runs through the expr-op BNF rule 
//  returns the rest of the List
//
  let rec private exprop tokens = 
    let h1 = List.head tokens
    let op = ["+"; "-"; "*"; "/"; "^"; "<"; "<="; ">"; ">="; "=="; "!="]

    // checks if the symbol is valid
    if contains h1 op = true then
      List.tail tokens
    else 
      failwith ("expecting expression operator, but found " + h1)

//  Runs through the expr-value BNF rule
//  returns the rest of the List
//  
  let rec private exprvalue tokens = 
    let h1 = List.head tokens
    let t1 = List.tail tokens

    if beginswith "identifier" h1 = true then 
      t1
    elif beginswith "int_literal" h1 = true then 
      t1
    elif beginswith "str_literal" h1 = true then 
      t1
    elif beginswith "real_literal" h1 = true then
      t1
    elif h1 = "true" then
      matchToken "true" tokens
    elif h1 = "false" then  
      matchToken "false" tokens
    else  
      failwith ("expecting identifier or literal, but found " + h1)

//  Runs through the expr BNF rule 
//  returns the rest of the List
//
  let rec expr tokens = 
    let t1 = exprvalue tokens
    let h1 = List.head t1
    let t2 = List.tail t1

    //  check if there are more components to this 
    //  statment
    if isexprop t1 = true then
      let t3 = exprop t1
      exprvalue t3
    else 
      t1

//  runs through the vardec1 BNF rule
//  returns the rest of the tokens list or throws an exception
//
  let rec private vardec1 tokens =
    let h1 = List.head tokens
    let l2 = matchToken (string h1) tokens
    let h2 = List.head l2
    let t2 = List.tail l2
    if beginswith "identifier" h2 = true then 
      matchToken ";" t2
    else 
      failwith ("expecting identifier, but found " + h2)
    
//  Runs through the input BNF rule
//  returns the rest of the List
//
  let rec private input tokens = 
    let t1 = matchToken "cin" tokens
    let t2 = matchToken ">>" t1
    let h2 = List.head t2 
    let t3 = List.tail t2
    if beginswith "identifier" h2 = true then 
      matchToken ";" t3
    else 
      failwith ("expecting identifier, but found " + h2)

//  Runs through the output-value BNF rule
//  returns the rest of the List
//
  let rec private outputvalue tokens = 
    let h1 = List.head tokens

    // check if head is endl
    if h1 = "endl" then  
      let t1 = matchToken "endl" tokens
      t1
    else  
      exprvalue tokens


//  Runs through the output BNF rule 
//  returns the rest of the List
//
  let rec private output tokens = 
    let t1 = matchToken "cout" tokens
    let t2 = matchToken "<<" t1
    let t3 = outputvalue t2
    let t4 = matchToken ";" t3
    t4

//  Runs through the assignment BNF rule 
//  returns the rest of the List
//
  let rec private assignment tokens = 
    let h1 = List.head tokens
    let t1 = List.tail tokens

    if beginswith "identifier" h1 = true then 
      let t2 = matchToken "=" t1
      let t3 = expr t2
      matchToken ";" t3

    else 
      failwith ("expecting identifier, but found " + h1)

//  Runs through the condition BNF rule
//  calls expr and returns the rest of the List
  let rec private condition tokens = 
    expr tokens

//  Goes through the different statments
//  Returns the rest of the List
// 
  let rec private stmt tokens = 
    let h1 = List.head tokens
    if h1 = ";" then
      matchToken ";" tokens
    elif h1 = "int" then 
      vardec1 tokens
    elif h1 = "real" then
      vardec1 tokens
    elif h1 = "cin" then 
      input tokens
    elif h1 = "cout" then 
      output tokens
    elif beginswith "identifier" h1 = true then
      assignment tokens
    elif h1 = "if" then  
      ifstmt tokens
    else  
      failwith("expecting statement, but found " + h1)

//  Runs through the then-part BNF rule
//  calls stmt and returns the rest of the List
//
  and private thenpart tokens = 
    stmt tokens

//  Runs through the else-part BNF rule 
//  matches tokens and calls stmt if necessary
//  returns the rest of the list 
  and private elsepart tokens = 
    let h1 = List.head tokens 
    if h1 = "else" then 
      let t1 = matchToken "else" tokens
      stmt t1
    else  
      tokens
    

//  Runs through the ifstmt BNF rule 
//  returns the rest of the List
//
  and private ifstmt tokens = 
    let t1 = matchToken "if" tokens
    let t2 = matchToken "(" t1
    let t3 = condition t2
    let t4 = matchToken ")" t3
    let t5 = thenpart t4
    let t6 = elsepart t5
    t6

//  Checks if there are more statments then call the stmt 
//  function
//  returns the rest of the List
// 
  let rec private morestmts tokens = 
    let h1 = List.head tokens

    // If the code is done
    if h1 = "}" then 
      tokens

    else  // If there are more stmts to be read
      let t1 = stmt tokens
      morestmts t1

  let private stmts tokens = 
    let t1 = stmt tokens
    morestmts t1
  //  morestmts t1
  
  //
  // simpleC
  //
  let private simpleC tokens = 
    let T2 = matchToken "void" tokens
    let T3 = matchToken "main" T2
    let T4 = matchToken "(" T3
    let T5 = matchToken ")" T4
    let T6 = matchToken "{" T5
    let T7 = stmts T6
    let T8 = matchToken "}" T7
    let T9 = matchToken "$" T8 // $ => EOF, 
    //  there should be no more tokens
    T9

  
  // let private simpleC tokens = 
  //   matchToken "" tokens


  //
  // parse tokens
  //
  // Given a list of tokens, parses the list and determines
  // if the list represents a valid simple C program.  Returns
  // the string "success" if valid, otherwise returns a 
  // string of the form "syntax_error:...".
  //
  let parse tokens = 
    try
      let result = simpleC tokens
      "success"
    with 
      | ex -> "syntax_error: " + ex.Message
