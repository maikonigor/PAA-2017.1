import numpy as np

def formatar_tempo(tempo):
    tempo /= 1000
    tempo = round(tempo, 4)
    if(tempo > 60):
        tempo /= 60
        tempo = round(tempo, 4)
        tempo = str(tempo) + "m"
    else:
         tempo = str(tempo) + "s"
    return tempo

def formatar_resultado(resultado):
    resultado = round(resultado,4) * 100
    return str(resultado)

files = [
    "FUN_instance1.txt",
    "FUN_instance2.txt",
    "FUN_instance5.txt",
    "FUN_instance7.txt",
    "FUN_instance9.txt",
    "FUN_instance12.txt",
    "FUN_instance13.txt",
    "FUN_instance14.txt",
    "FUN_instance17.txt"
    ]

instancias = [
    "src/instances/instance1.txt",
    "src/instances/instance2.txt",
    "src/instances/instance5.txt",
    "src/instances/instance7.txt",
    "src/instances/instance9.txt",
    "src/instances/instance12.txt",
    "src/instances/instance13.txt",
    "src/instances/instance14.txt",
    "src/instances/instance17.txt"
    ]
final = np.array(["Instancia","Dimensao","qtd_pecas","Pior(\%)","Medio (\%)", "Melhor (\%)", "Tempo Medio"])

contador = 0
ins_data = np.loadtxt(instancias[contador])

for file in files:
    data = np.loadtxt(file)
    
    ins_data = np.loadtxt(instancias[contador])
    quantidades =  ins_data[:,2]
    quantidade_pecas = int(quantidades[0])
    dimen_placa = str(int(ins_data[0][0])) + " x " + str(int(ins_data[0][1]))
    min = data.min(axis=0)
    max = data.max(axis=0)
    media = data.mean(axis=0)

    p_result = formatar_resultado(max[0])
    #p_tempo = formatar_tempo(max[1])
    
    m_result = formatar_resultado(min[0])
    #m_tempo = formatar_tempo(min[1])
    
    t_medio = formatar_tempo(media[1])
    r_medio = formatar_resultado(media[0])
    
    linha = np.array([str(contador), dimen_placa,quantidade_pecas, p_result, r_medio, m_result, t_medio])
    final = np.vstack((final,linha))
    contador+=1

print final

np.savetxt("resultados.csv", final,delimiter=";",fmt="%s")


