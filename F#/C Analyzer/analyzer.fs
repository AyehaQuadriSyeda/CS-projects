//
// Analyzer for simple C programs.  This component performs
// semantic analysis, in particular collecting variable
// names and their types. The analysis also checks to ensure
// variable names are unique --- no duplicates.
//
// If all is well, a "symbol table" is built and returned,
// containing all variables and their types. A symbol table
// is a list of tuples of the form (name, type).  Example:
//
//   [("x", "int"); ("y", "int"); ("z", "real")]
//
// Modified by:
//   << Ayesha Quadri Syeda >>
//
// Original author:
//   Prof. Joe Hummel
//   U. of Illinois, Chicago
//   CS 341, Spring 2022
//

namespace compiler

module analyzer =
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

//  contains_var; checks if the 
//  variable declaration is in the symboltable

  let rec private contains_var x symboltable =
    match symboltable with
    |[] -> false
    |(n, t)::rest when n = x -> true
    |(n, t)::rest -> contains_var x rest

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
      List.tail tokens

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
    else   
      matchToken "false" tokens

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
  let rec private vardec1 tokens symboltable=
    let h1 = List.head tokens  // type 
    let t1 = List.tail tokens
    let h2 = List.head t1    // identifier
    let t2 = List.tail t1   // ; and rest
    let t3 = matchToken ";" t2
    let substring = h2.[11..]
    if contains_var substring symboltable = true then
      failwith("redefinition of variable '" + substring + "'")
    else
     ([(substring, h1)] @ symboltable, t3)
    
    
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
  let rec private stmt tokens symboltable = 
    let h1 = List.head tokens
    if h1 = ";" then
      (symboltable, matchToken ";" tokens)
    elif h1 = "int" then 
      vardec1 tokens symboltable
    elif h1 = "real" then
      vardec1 tokens symboltable
    elif h1 = "cin" then 
      (symboltable, input tokens)
    elif h1 = "cout" then 
      (symboltable, output tokens)
    elif beginswith "identifier" h1 = true then
      (symboltable, assignment tokens)
    else  
      let (symboltable, t1) = ifstmt tokens symboltable
      (symboltable, t1)

//  Runs through the then-part BNF rule
//  calls stmt and returns the rest of the List
//
  and private thenpart tokens = 
    stmt tokens

//  Runs through the else-part BNF rule 
//  matches tokens and calls stmt if necessary
//  returns the rest of the list 
  and private elsepart tokens symboltable= 
    let h1 = List.head tokens 
    if h1 = "else" then 
      let t1 = matchToken "else" tokens
      stmt t1 symboltable
    else  
      (symboltable, tokens)
    

//  Runs through the ifstmt BNF rule 
//  returns the rest of the List
//
  and private ifstmt tokens symboltable= 
    let t1 = matchToken "if" tokens
    let t2 = matchToken "(" t1
    let t3 = condition t2
    let t4 = matchToken ")" t3
    let (symboltable1, t5) = thenpart t4 symboltable
    let (symboltable2, t6) = elsepart t5 symboltable1
    (symboltable2, t6)

//  Checks if there are more statments then call the stmt 
//  function
//  returns the rest of the List
// 
  let rec private morestmts tokens symboltable = 
    let h1 = List.head tokens

    // If the code is done
    if h1 = "}" then 
      (symboltable, tokens)

    else  // If there are more stmts to be read
      let (symboltable1, t1) = stmt tokens symboltable
      morestmts t1 symboltable1

  let private stmts tokens = 
    let (symboltable, t1) = stmt tokens []
    morestmts t1 symboltable
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
    let (symboltable, T7) = stmts T6 
    let T8 = matchToken "}" T7
    let T9 = matchToken "$" T8 // $ => EOF, 
    //  there should be no more tokens
    (T9, symboltable)


  //
  // build_symboltable tokens
  //
  // Given a list of tokens, analyzes the program by looking
  // at variable declarations and collecting them into a
  // list. This list is known as a symbol table. Returns
  // a tuple (result, symboltable), where result is a string 
  // denoting "success" if valid, otherwise a string of the 
  // form "semantic_error:...".
  //
  // On success, the symboltable is a list of tuples of the
  // form (name, type), e.g. [("x","int"); ("y","real")]. On 
  // an error, the returned list is empty [].
  //
  let build_symboltable tokens = 
    try
      let (T2, symboltable) = simpleC tokens
      ("success", symboltable)
    with 
      | ex -> ("semantic_error: " + ex.Message, [])
