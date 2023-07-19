//
// Analyzer for simple C programs.  This component performs
// type checking.  The analyzer returns a string denoting
// success or failure. The string "success" if the input 
// program is legal, otherwise the string "type_error: ..." 
// is returned denoting an invalid simple C program.
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

module checker =
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

//  contains_op; checks the operator type
//
  let rec private contains_op x list = 
    match list with
    |[] -> false
    |h1::t1 when h1 = x ->true
    |h1::t1  -> contains_op x t1

//  contains_var; checks if the 
//  variable declaration is in the symboltable
//
  let rec private contains_var x symboltable =
    match symboltable with
    |[] -> false
    |(n, t)::rest when n = x -> true
    |(n, t)::rest -> contains_var x rest

// get_type; finds the type of the variable and returns it
//
  let rec private get_type x symboltable = 
    match symboltable with
    |(n, t)::rest when x = n -> t
    |(n, t)::rest -> get_type x rest
    |_ -> failwith("variable '" + x + "' undefined")

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
  let rec private exprvalue tokens symboltable= 
    let h1 = List.head tokens
    let t1 = List.tail tokens
    let h2 = string h1
    let substring = h2.[11..]
    if beginswith "identifier" h1 = true then 
      let t = get_type substring symboltable
      if contains_var substring symboltable = true then
        (t, t1)
      else 
        failwith("variable '" + substring + "' undefined")
    elif beginswith "int_literal" h1 = true then 
      ("int", t1)
    elif beginswith "str_literal" h1 = true then 
      ("str", t1)
    elif beginswith "real_literal" h1 = true then
      ("real", t1)
    elif h1 = "true" then
      ("bool", matchToken "true" tokens)
    else  
      ("bool", matchToken "false" tokens)

//  Runs through the expr BNF rule 
//  returns the rest of the List
//
  let rec expr tokens symboltable= 
    let (t, t1) = exprvalue tokens symboltable
    let h1 = List.head t1
    let t2 = List.tail t1
    let h2 = List.head t2
    let b_op = ["<"; "<="; ">="; ">"; "=="; "!="; "true"; "false"]
    let a_op = ["+"; "-"; "*"; "/"; "^"]

    //  check if there are more components to this 
    //  statment
    if isexprop t1 = true then
      let t3 = exprop t1
      let (ty, t4) = exprvalue t3 symboltable
      if contains_op h1 b_op = true then
        if ty = t then
          if h1 = "==" && ty = "real" && t = "real" then
            printfn "warning: comparing real numbers with == may never be true"
            ("bool", t4)
          else
            ("bool", t4)
        else
          failwith("type mismatch '" + t + "' " + h2 + " '" + ty + "'") 
      elif contains_op h1 a_op = true then
        if t = "int" && t = ty then
          (t, t4)
        elif t = "real" && t = ty then
          (t, t4)
        else
          failwith("operator " + h2 + " must involve 'int' or 'real'")
      else
        (ty, t4)
    else 
      (t, t1)

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
  let rec private input tokens symboltable = 
    let t1 = matchToken "cin" tokens
    let t2 = matchToken ">>" t1
    let h2 = List.head t2 
    let t3 = List.tail t2
    let sub = h2.[11..]
    if beginswith "identifier" h2 = true then 
      if contains_var sub symboltable = true then
        matchToken ";" t3
      else
        failwith("variable '" + sub + "' undefined")
    else 
      failwith ("expecting identifier, but found " + h2)

//  Runs through the output-value BNF rule
//  returns the rest of the List
//
  let rec private outputvalue tokens symboltable = 
    let h1 = List.head tokens

    // check if head is endl
    if h1 = "endl" then  
      let t1 = matchToken "endl" tokens
      t1
    else  
      let (t, t2) = exprvalue tokens symboltable
      t2


//  Runs through the output BNF rule 
//  returns the rest of the List
//
  let rec private output tokens symboltable = 
    let t1 = matchToken "cout" tokens
    let t2 = matchToken "<<" t1
    let t3 = outputvalue t2 symboltable
    let t4 = matchToken ";" t3
    t4

//  Runs through the assignment BNF rule 
//  returns the rest of the List
//
  let rec private assignment tokens symboltable = 
    let h1 = List.head tokens
    let t1 = List.tail tokens

    if beginswith "identifier" h1 = true then 
      let t2 = matchToken "=" t1
      let ty = get_type h1.[11..] symboltable 
      let (t, t3) = expr t2 symboltable
      if ty <> t then
        if ty = "real" && t = "int" then
          matchToken ";" t3
        else
          failwith("cannot assign '" + ty + "' to variable of type '" + t + "'")
      else
        matchToken ";" t3
    else 
      failwith ("expecting identifier, but found " + h1)

//  Runs through the condition BNF rule
//  calls expr and returns the rest of the List
  let rec private condition tokens symboltable = 
    let (t, t1) = expr tokens symboltable
    if t <> "bool" then
      failwith ("if condition must be 'bool', but found '" + t + "'")
    else
      t1

//  Goes through the different statments
//  Returns the rest of the List
// 
  let rec private stmt tokens symboltable = 
    let h1 = List.head tokens
    if h1 = ";" then
      matchToken ";" tokens
    elif h1 = "int" then 
      vardec1 tokens
    elif h1 = "real" then
      vardec1 tokens
    elif h1 = "cin" then 
      input tokens symboltable 
    elif h1 = "cout" then 
      output tokens symboltable
    elif beginswith "identifier" h1 = true then
      assignment tokens symboltable
    elif h1 = "if" then  
      ifstmt tokens symboltable
    else  
      failwith("expecting statement, but found " + h1)

//  Runs through the then-part BNF rule
//  calls stmt and returns the rest of the List
//
  and private thenpart tokens symboltable= 
    stmt tokens symboltable

//  Runs through the else-part BNF rule 
//  matches tokens and calls stmt if necessary
//  returns the rest of the list 
  and private elsepart tokens symboltable = 
    let h1 = List.head tokens 
    if h1 = "else" then 
      let t1 = matchToken "else" tokens
      stmt t1 symboltable
    else  
      tokens
    

//  Runs through the ifstmt BNF rule 
//  returns the rest of the List
//
  and private ifstmt tokens symboltable = 
    let t1 = matchToken "if" tokens
    let t2 = matchToken "(" t1
    let t3 = condition t2 symboltable
    let t4 = matchToken ")" t3
    let t5 = thenpart t4 symboltable
    let t6 = elsepart t5 symboltable
    t6

//  Checks if there are more statments then call the stmt 
//  function
//  returns the rest of the List
// 
  let rec private morestmts tokens symboltable = 
    let h1 = List.head tokens

    // If the code is done
    if h1 = "}" then 
      tokens

    else  // If there are more stmts to be read
      let t1 = stmt tokens symboltable
      morestmts t1 symboltable

  let private stmts tokens symboltable = 
    let t1 = stmt tokens symboltable
    morestmts t1 symboltable
  //  morestmts t1
  
  //
  // simpleC
  //
  let private simpleC tokens symboltable = 
    let T2 = matchToken "void" tokens
    let T3 = matchToken "main" T2
    let T4 = matchToken "(" T3
    let T5 = matchToken ")" T4
    let T6 = matchToken "{" T5
    let T7 = stmts T6 symboltable
    let T8 = matchToken "}" T7
    let T9 = matchToken "$" T8 // $ => EOF, 
    //  there should be no more tokens
    T9


  //
  // typecheck tokens symboltable
  //
  // Given a list of tokens and a symbol table, type-checks 
  // the program to ensure program's variables and expressions
  // are type-compatible. If the program is valid, returns 
  // the string "success". If the program contains a semantic
  // error or warning, returns a string of the form
  // "type_error: ...".
  //
  let typecheck tokens symboltable = 
    try
      let T2 = simpleC tokens symboltable
      "success"
    with 
      | ex -> "type_error: " + ex.Message

