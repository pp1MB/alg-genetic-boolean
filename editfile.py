with open("2sat.c", "r+") as file:
    if(input("Deseja alterar os parâmetros do AG? (y/n)") == "y"):
        file.seek(121)
        file.write("#define POP_MAX " + input("Insira a população máxima: ") + " // Indivíduos na população\n")
        file.write("#define GEN_MAX " + input("Insira o número máximo de gerações: ") + " // Limite de gerações\n")
        file.write("#define TERM_MAX " + input("Insira máximo de termos em uma única clausula: ") + " // Máximo de termos em uma única clausula.\n")
        file.write("#define NUM_VAR " + input("Insira o número de variáveis: ") + " // Número de variáveis.\n")
        file.write("#define NUM_CLS " + input("Insira o número de cláusulas: ") + " // Número de clausulas na equação.\n")
    if(input("Deseja inserir uma equação? (y/n)") == "y"):
        file.seek()