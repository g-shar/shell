# CS 100 Programming Project

# Project Information
Fall 2019
Richard Duong
Gregory Shar 862087118

# Introduction

# Diagram

# Classes

# Protoypes/Research

# Development and Testing Roadmap




# Current Developments 10/27/2019 6:06 PM


Base_Cmd:
  
	Cmd_Obj:
		execute(); 

		Executable* obj1;
        Arg_List* obj2;

	Connectors:

		Base_Cmd *left, *right
        
        AND_AND &&       
        PIPE_PIPE ||
      	SEMICOLON ;

EXECUTABLE

Arg_List

int main(){
	
    
}

class Interface{
  
  
};

//	Abstract base class for commands
class Base_Cmd{
	public:
		Base_Cmd();										//Constructor
  	virtual string display() = 0;
  	
  		
  
};


class Cmd_Obj: public Base_Cmd{
  public:
  	Cmd_Obj();										//Constructor
  	virtual string display();			//Display
    void execute();								//Executes the full command using private variables
  	
  
  private:
		Executable* obj1;			//Executable from bin
    Arg_list* obj2;				//List of args related to the executable
  	
};


class Connectors: public Base_Cmd{
  protected:
    string display();
  	Base_Cmd *left, *right	// Left & Right tree connections (connectors or full_cmds)
    
               
};

class And: public Connectors{
  
};

class Or: public Connectors{

};

class Semicolon: public Connectors{
  
  
};


// special case with semicolon as leaf node
; echo "hello"
;
echo "hello" ;

; echo "hello" && echo "there" ;


echo "hello"

		

Executable:		// independent header files for each exec. ?

Arg_List:
		vector<string>arguments;
		parse();






echo hello && goodbye
echo "hello && goodbye"


ls ;
ls -a; echo hello && mkdir test || echo world; git status;


	"ls -a" <- ; -> &&

git clone <assignment-repo-url>
cd <assignment-repo-url>
git checkout tags/hw2
git submodule init
git submodule update
cmake3 .
make
test -e rshell || echo “rshell executable missing, check submission instruction section of the specifications”
test -e test || echo “test executable missing, check submission instruction section of the specifications”
test -d unit_tests || echo “unit_tests/ directory missing, check submission instruction section of the specifications”
test -d integration_tests || echo “integration_tests/ directory missing, check submission instruction section of the specifications”


