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
    
    
def main():
    arquivo = open("cut1.txt","r")
    arquivo_instancia = open("instance1.txt","w")
    
    processa_arquivo(arquivo, arquivo_instancia)
    
    arquivo.close()
    arquivo_instancia.close()

main()