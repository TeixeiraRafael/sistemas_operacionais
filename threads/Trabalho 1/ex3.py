import os
import sys
import threading
from collections import Counter
from os.path import isfile, join

CONSONANTS = "bcdfghjklmnpqrstvwxyz"
VOWELS = "aeiou"
BASE_DIR = sys.argv[1] + '/'

# Calcula as estatísticas de um dado arquivo
def stats(filepath):
    input_file = open(filepath, "r")

    output_path = filepath.split('/')[0] + '/uppercase/' + filepath.split('/')[1]
    output_file = open(output_path, 'w')
    
    file_words = []
    file_lines = input_file.read().splitlines()

    for line in file_lines:
        output_file.write(line.upper() + "\n")
        words = line.split(" ")
        for word in words:
            file_words.append(word)
    
    file_content = "".join(file_lines)
    vowels = Counter(v for v in file_content if v in VOWELS)
    consonants = Counter(c for c in file_content if c in CONSONANTS)
    words = Counter(w for w in file_words)

    input_file.close()
    output_file.close()

    print(
        "\n=======================================================\n"
        + filepath + " has " + str(len(file_words)) + " words, " 
        + str(len(consonants)) + " consonants and " 
        + str(len(vowels)) + " vowels.\n"
        + "\'" + str(words.most_common()[0][0]) + "\' is the most common word.\n"
        + "\'" + str(vowels.most_common()[0][0]) + "\' is the most common vowel.\n"
        + "\'" + str(consonants.most_common()[0][0]) + "\' is the most common consonant."
        + "\n=======================================================\n"
    )

# Cria uma lista de arquivos em um diretório ignorando subdiretórios
file_list = [f for f in os.listdir(BASE_DIR) if isfile(join(BASE_DIR, f))]

#Cria um diretório de saída, caso ele ainda não exista
if not os.path.exists(BASE_DIR + "uppercase/"):
    os.makedirs(BASE_DIR + "uppercase/")
    
for x in file_list:
    filepath = (BASE_DIR + x)
    t = threading.Thread(target=stats, args=(filepath,))
    t.start()
