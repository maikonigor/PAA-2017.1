import numpy as np

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
final = np.array(["Instancia","Pior resultado","Pior Tempo", "Melhor Resultado", "Tempo melhor", "Tempo Medio"])

contador = 0
for file in files:
    data = np.loadtxt(file)
    min = data.min(axis=0)
    max = data.max(axis=0)
    media = data.mean(axis=0)
    
    linha = np.array([str(contador), str(max[0]), str(max[1]/1000), str(min[0]), str(min[1]/1000), str(media[1]/1000)])
    final = np.vstack((final,linha))
    contador+=1

print final

np.savetxt("resultados.csv", final,delimiter=";",fmt="%s")
 

