/** Grammars always start with a grammar header. This grammar is called
 *  SPCalculator and must match the filename: SPCalculator.g4
 */
grammar SPCalculator;

/**
* All generated files must reside in the package SP alongside our implementation
* of the tree and the main function.
*/
@header{
package SP;
}

@parser::members{
	//We define a new method in our praser. This method will return a string
	//Representing our tree in LISP-Style
	public String getLisp(){
		StatContext ctx = (StatContext)stat();
		if(ctx.exception!=null){
			return new String("Invalid Expression!");		
		}else{
			return ctx.tree.getLisp();
		}
	}
}

//Valid statement is either a termination command || an arithmetical expression
stat returns [SPTree tree] : e1=TERMINATION {$tree = new SPTree($e1.text);}
			   | e2=exp {$tree = $e2.tree;}
                           ; 

exp returns [SPTree tree] :
			     OPEN_PAREN e1=exp CLOSE_PAREN  //parenthesis
					{$tree = $e1.tree;}
					
			   | e1=exp e2=DOLLAR e3=exp  //dollar operation
			   		{ $tree = new SPTree($e2.text);
			   		$tree.insertChild($e1.tree);
			   		$tree.insertChild($e3.tree); }
			   		
			   | e1=exp e2=MUL e3=exp  //multiplication
			   		{ $tree = new SPTree($e2.text);
			   		$tree.insertChild($e1.tree);
			   		$tree.insertChild($e3.tree); }
			   | e1=exp e2=DIV e3=exp  //division
			   		{ $tree = new SPTree($e2.text);
			   		$tree.insertChild($e1.tree);
			   		$tree.insertChild($e3.tree); }
			   		
			   | e1=exp e2=PLUS e3=exp  //addition
			   		{ $tree = new SPTree($e2.text);
			   		$tree.insertChild($e1.tree);
			   		$tree.insertChild($e3.tree); }
			   | e1=exp e2=MINUS e3=exp  //subtraction
			   		{ $tree = new SPTree($e2.text);
			   		$tree.insertChild($e1.tree);
			   		$tree.insertChild($e3.tree); }
			   		
			   | e1=NUMBER  //terminate with number
			   		{ $tree = new SPTree($e1.text); }
			   		
			   | e1=PLUS e2=exp  //ignore extra plus signs
			   		{ $tree = $e2.tree; }
			   | e1=MINUS e2=exp  //flip sign with minus
			   		{ $tree = new SPTree($e1.text);
			   		newTree = new SPTree("0");
			   		$tree.insertChild(newTree);
			   		$tree.insertChild($e2.tree); }
			   		
			  ;

// parser rules start with lowercase letters, lexer rules with uppercase
TERMINATION: '<>';
NUMBER: [0-9]+;
WHITE_SPACE: [ \t\n\r]+ -> skip;
PLUS: '+';
MINUS: '-';
MUL: '*';
DIV: '/';
DOLLAR: '$';
OPEN_PAREN: '(';
CLOSE_PAREN: ')';
