import tkinter as tk
from tkinter import messagebox
from tkinter.scrolledtext import ScrolledText
import subprocess

# Função para ler o arquivo e preencher os campos
def ler_def():
    with open("parameters.h", "r") as file:
        in_operacoes = False  # Flag para saber se estamos dentro do vetor de operações

        for line in file:
            line = line.strip()  # Remove espaços extras no início e fim da linha

            # Verifica se a linha é uma definição de constante
            if line.startswith("#define"):
                parts = line.split()
                if len(parts) >= 3:
                    key = parts[1]
                    value = parts[2]

                    if key == "POP_MAX":
                        ins_pop.delete(0, tk.END)
                        ins_pop.insert(0, value)
                    elif key == "GEN_MAX":
                        ins_gen.delete(0, tk.END)
                        ins_gen.insert(0, value)
                    elif key == "TERM_MAX":
                        ins_term.delete(0, tk.END)
                        ins_term.insert(0, value)
                    elif key == "NUM_VAR":
                        ins_var.delete(0, tk.END)
                        ins_var.insert(0, value)
                    elif key == "NUM_CLS":
                        ins_cla.delete(0, tk.END)
                        ins_cla.insert(0, value)

            # Detecta o início do vetor de operações
            elif line.startswith("char *operacoes_t[] = {"):
                in_operacoes = True
                operacoes = []

            # Lê as operações do vetor
            elif in_operacoes:
                if line == "};":
                    in_operacoes = False
                    ins_eq.delete(1.0, tk.END)
                    for operacao in operacoes:
                        ins_eq.insert(tk.END, operacao + "\n")
                elif line and not line.startswith("//"):
                    # Remove todas as aspas e vírgulas
                    operacao = line.replace('"', '').replace(',', '').strip()
                    # Ignora chaves e linhas vazias
                    if operacao and operacao not in ['{', '}']:
                        operacoes.append(operacao)

# Função para escrever no arquivo
def escrever_def():
    with open("parameters.h", "w") as file:
        file.write("#define POP_MAX " + ins_pop.get() + " // Indivíduos na população\n")
        file.write("#define GEN_MAX " + ins_gen.get() + " // Limite de gerações\n")
        file.write("#define TERM_MAX " + ins_term.get() + " // Máximo de termos em uma única cláusula\n")
        file.write("#define NUM_VAR " + ins_var.get() + " // Número de variáveis\n")
        file.write("#define NUM_CLS " + ins_cla.get() + " // Número de cláusulas na equação\n")
        
        # Pega o conteúdo da caixa de texto e separa as operações
        eq_content = ins_eq.get("1.0", tk.END).strip("\n").split("\n")
        
        file.write("\n// Vetor de chars denota todas as cláusulas.\n")
        file.write("char *operacoes_t[] = {\n")
        
        # Escreve as operações com aspas e vírgulas
        for i, operacao in enumerate(eq_content):
            if operacao.strip():  # Só escreve linhas não vazias
                if i == len(eq_content) - 1:  # Última operação
                    file.write('    "' + operacao.strip("\n") + '"\n')
                else:
                    file.write('    "' + operacao.strip("\n") + '",\n')
        
        file.write("};")

# Função para rodar o programa
def rodar_programa():
    subprocess.run(["gcc", "agbinary.c", "sat.c", "-o", "sat", "-lGL", "-lGLU", "-lglut"], check=True)
    res = subprocess.Popen(["./sat"], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    stdout, stderr = res.communicate()

    if stdout.strip():
        janela_saida = tk.Toplevel(janela)
        janela_saida.title("Equation Solution")

        text_widget = ScrolledText(janela_saida, wrap=tk.WORD, width=30, height=10)
        text_widget.pack(padx=10, pady=10, fill=tk.BOTH, expand=True)

        text_widget.insert(tk.END, stdout)
        text_widget.see(tk.END)
        process.stdout.close()

# Configuração inicial
janela = tk.Tk()
janela.title("Interface - nSat")
janela.geometry("600x300")

# Frames principais
frame_esquerdo = tk.Frame(janela)
frame_esquerdo.pack(side=tk.LEFT, padx=10, pady=10)

frame_direito = tk.Frame(janela)
frame_direito.pack(side=tk.LEFT, padx=10, pady=10)

# Frame esquerdo: Campos de entrada
tk.Label(frame_esquerdo, text="Max Pop").grid(row=0, column=0, padx=10, pady=5)
ins_pop = tk.Entry(frame_esquerdo, width=10)
ins_pop.grid(row=0, column=1, padx=10, pady=5)

tk.Label(frame_esquerdo, text="Max Gerações").grid(row=1, column=0, padx=10, pady=5)
ins_gen = tk.Entry(frame_esquerdo, width=10)
ins_gen.grid(row=1, column=1, padx=10, pady=5)

tk.Label(frame_esquerdo, text="Max Termos").grid(row=2, column=0, padx=10, pady=5)
ins_term = tk.Entry(frame_esquerdo, width=10)
ins_term.grid(row=2, column=1, padx=10, pady=5)

tk.Label(frame_esquerdo, text="N° Variáveis").grid(row=3, column=0, padx=10, pady=5)
ins_var = tk.Entry(frame_esquerdo, width=10)
ins_var.grid(row=3, column=1, padx=10, pady=5)

tk.Label(frame_esquerdo, text="N° Cláusulas").grid(row=4, column=0, padx=10, pady=5)
ins_cla = tk.Entry(frame_esquerdo, width=10)
ins_cla.grid(row=4, column=1, padx=10, pady=5)

b_salvardef = tk.Button(frame_esquerdo, text="Salvar parâmetros", command=escrever_def)
b_salvardef.grid(row=5, column=0, columnspan=2, pady=20)

# Frame direito: Campo de texto para equações
tk.Label(frame_direito, text="Equação").pack(padx=10, pady=5)
ins_eq = tk.Text(frame_direito, height=10, width=40)
ins_eq.pack(padx=10, pady=5)

b_rodar = tk.Button(frame_direito, text="Rodar o programa", command=rodar_programa)
b_rodar.pack(pady=10)

# Inicia o loop principal da interface
ler_def()
janela.mainloop()
