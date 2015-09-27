A C program to simulate the output of the circuits for both combinational and sequential circuits. Takes two file names as command line arguments: the name of the circuit description file and the name of the file with values for the input variables.

The circuit description file provides the description of the circuit. A sample file is included in the repository. Input variables used in the circuit are provided using the INPUTVAR directive in the circuit description file, followed by the number of variables and and the names of the input variables.

eg. INPUTVAR 3 A B C

The outputs produced by the circuit are specified using the OUTPUTVAR directive.

eg. OUTPUTVAR 1 P

The following arguments may be used:

NOT gate, directive followed by the name of an input and output:
	NOT A B

AND gate, directive followed by name of two inputs and output:
	AND A B C

OR gate, directive followed by name of two inputs and output:
	OR A B C
	
DECODER, directive followed by number of inputs, names of inputs, and names of outputs. Outputs ordered in gray code sequence. Example for decoder with 2 inputs A and B:
	DECODER 2 A B P Q R S

MULTIPLEXER, directive followed by the number of inputs, names of inputs, names of selectors, and name of output. Inputs ordered in gray code sequence. Example for multiplexer implementing an AND gate using a 4:1 multiplexer:
	MULTIPLEXER 4 0 0 1 0 A B P

Example execution: ./comb samplecircuit.txt sampleinput.txt