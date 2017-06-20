import numpy as np

def formatar_tempo(tempo):
    tempo /= 1000
    tempo = round(tempo, 2)
    if(tempo > 60):
        tempo /= 60
        tempo = round(tempo, 2)
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
final = np.array(["Instancia","Pior resultado (\%)", "Melhor Resultado (\%)", "Tempo Medio"])

contador = 0
for file in files:
    data = np.loadtxt(file)
    min = data.min(axis=0)
    max = data.max(axis=0)
    media = data.mean(axis=0)

    p_result = formatar_resultado(max[0])
    #p_tempo = formatar_tempo(max[1])
    
    m_result = formatar_resultado(min[0])
    #m_tempo = formatar_tempo(min[1])
    
    t_medio = formatar_tempo(media[1])
    
    linha = np.array([str(contador), p_result, m_result, t_medio])
    final = np.vstack((final,linha))
    contador+=1

print final

np.savetxt("resultados.csv", final,delimiter=";",fmt="%s")
 

