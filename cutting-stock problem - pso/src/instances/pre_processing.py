import numpy as np
import os.path
def calcular_quantidade(largura_placa, altura_placa, largura_peca, altura_peca):
    maiorAlutura = 0
    maiorLargura = 0

    #converter valores para inteiro    
    largura_peca = int(largura_peca)
    altura_peca = int(altura_peca)
    
    cabe = True
    
    #quantidade de pecas que cabem na placa
    quantidade = 0;
    
    while (altura_placa - maiorAlutura)  > altura_peca:
        maiorLargura = 0
        pecaMaisAlta = 0
        while (maiorLargura + largura_peca) < largura_placa:
           maiorLargura = (maiorLargura + largura_peca)
           quantidade = quantidade + 1
           if(pecaMaisAlta < altura_peca):
               pecaMaisAlta = altura_peca
        
        maiorAlutura = maiorAlutura + pecaMaisAlta
        
    
    return quantidade
    
def processa_arquivo(arquivo_cut, arquivo_instancia):
    
    line = arquivo_cut.readline() # Le a primeira linha do arquivo
    arquivo_instancia.write(line); #escreve no novo arquivo a primeira linha
    
    [plWidth, plHeight, qPecas] = line.split(" ")
    plWidth = int(plWidth)
    plHeight = int(plHeight)
    
    for linha in arquivo_cut.readlines():
        [largura_peca, altura_peca, qtd] = linha.split(" ")
        quantidade = calcular_quantidade(plWidth, plHeight, largura_peca, altura_peca)
        new_line = str(largura_peca) + " " + str(altura_peca) + " " + str(quantidade) + "\n"
        arquivo_instancia.write(new_line)

def rotacionar_pecas(arquivo_cut, arquivo_aux):
     f_line = arquivo_cut.readline().split(" ")
     f_line = remover_espaco(f_line)
     quantidade_pecas = int(f_line[2]);
        
     linha_original = ""
     new_line = ""
     
     for linha in arquivo_cut.readlines():
         linha = linha.split(" ")
         linha = remover_espaco(linha)
         linha_original = linha_original + str(linha[0]) + " " + str(linha[1]) + " " + linha[2] + "\n"
         
         if not linha[0] == linha[1]:
             new_line += str(linha[1]) + " " + str(linha[0]) + " " + linha[2] + "\n"
             quantidade_pecas = quantidade_pecas + 1
    
     str_f_line = str(f_line[0]) + " " + str(f_line[1]).strip() + " " + str(quantidade_pecas).strip() + "\n"
     arquivo_aux.write(str_f_line)
     arquivo_aux.write(linha_original)
     arquivo_aux.write(new_line)

def remover_espaco(linha):
     new_line = []
     for index in range(0, len(linha)):
         if linha[index]:
            new_line.append(linha[index])
     return new_line
 
def main():
    
    for x in range(2,18):
        assets = "assets/"
        cut_name = assets + "cut" + str(x) + ".txt"
        instance_name = "instance" + str(x) + ".txt"
        if os.path.exists(cut_name):
            arquivo_aux = open("a.txt","w")
            arquivo_cut = open(cut_name,"r")
            arquivo_instancia = open(instance_name,"a")
            
            rotacionar_pecas(arquivo_cut, arquivo_aux)
            arquivo_cut.close()
            arquivo_aux = open("a.txt","r")
            processa_arquivo(arquivo_aux, arquivo_instancia)
            
            arquivo_aux.close()
            arquivo_cut.close()
            arquivo_instancia.close()
            print cut_name

main()
